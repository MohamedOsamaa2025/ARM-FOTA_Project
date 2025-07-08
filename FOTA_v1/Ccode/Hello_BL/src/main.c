/*
 * main.c
 *
 *  Created on: Aug 28, 2024
 *      Author: Lenovo
 */


#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
#include "../include/RCC_interface.h"
#include "../include/GPIO_interface.h"
#include "../include/UART_interface.h"
#include "../include/STK_interface.h"
#include "../include/WiFi_interface.h"
#include "../include/BL_interface.h"
#include "../include/FPEC_interface.h"


void Func(void);
static u8 u8ReceiveBuffer[100] = {0};
static u8 u8Record[100] = {0};

static u8 u8ReceiveCounter = 8;
static u8 u8RecordCounter = 0;


static u8 u8BLWriteRequestFlag = 1;
u8 Local_u8ReceiveState = 0;
u8 u8RecDataFlag = 0;

u8* ProcessHexRequest = WIFI_ProcessHexRequest;
u8* RecordRequest = WIFI_RecordRequest;

typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

/*DO NOT FORGET TO CHANGE THE APPLICATION FLASH MEMORY OFFSET TO START FROM SECTOR 1,
AS THE BOOTLOADER WILL BE RESIDE AT SECTOR 0 (I.E, STARTS FROM @ 0X08000000) IN THE FLASH MEMORY*/




void main(void)
{
	RCC_voidInit();
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);
	RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_USART1EN);

    MSTK_voidInit();

    MUSART1_voidInit();
    MUSART1_voidSendStringSynchronous("\n");

    WiFi_voidInit();
    WiFi_voidConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);
    WiFi_voidServerConnect(WIFI_IP, WIFI_PORT);
	WiFi_voidSendHttpRequest(ProcessHexRequest);
    WiFi_voidDisConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);



	// MSTK_voidSetSingleInterval(80000000, &Func);

	while(1)
	{
				// MSTK_voidSTKDisable();
		u8RecDataFlag = 0;
		WiFi_voidConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);
    	WiFi_voidServerConnect(WIFI_IP, WIFI_PORT);
        WiFi_voidSendHttpRequest(RecordRequest);
		MUSART1_voidReceiveBuffer(u8ReceiveBuffer,100);
		WiFi_voidDisConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);

		for(u8 i =0;i<100;++i)
		{
			if(u8ReceiveBuffer[i] == ':')
			{
				u8RecDataFlag=1;
				int j=0;
				while(u8ReceiveBuffer[i+j+1] != '\n')
				{
					u8Record[j] = u8ReceiveBuffer[i+j+1];
					j++;
				}
				u8Record[j] = '\n';
				break;	
			}
		}		
		if(u8RecDataFlag == 0)
		{
			Func();
		}






		// WiFi_voidConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);
		// WiFi_voidServerConnect(WIFI_IP, WIFI_PORT);

		// while(u8ReceiveBuffer[u8ReceiveCounter] != '\n')
		// {
		// 	u8Record[u8ReceiveCounter] = u8ReceiveBuffer[u8ReceiveCounter+8];
		// 	u8ReceiveCounter++;
		// }
		// u8Record[u8ReceiveCounter+8] = '\n';






				/*Erasing the Flash memory before writing on it*/
				if (u8BLWriteRequestFlag == 1)
				{
					MFPEC_voidEraseAppArea();
					u8BLWriteRequestFlag = 0;
				}
				/*Parsing the Received Record*/
				MBL_voidParseRecord(&u8Record);
				/*Reset the ReceiveCounter variable*/
				// u8ReceiveCounter = 0;

				WiFi_voidConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);
				WiFi_voidServerConnect(WIFI_IP, WIFI_PORT);
				WiFi_voidSendHttpRequest(ProcessHexRequest);
				WiFi_voidDisConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);


				// MSTK_voidSetSingleInterval(80000000, &Func);
		
	}
}











void Func(void)
{

    WiFi_voidDisConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);


	#define SCB_VTOR *((volatile u32 *)0xE000ED08)
	/*Set the offset of the Vector Table Offset Address Of The Application In The Flash Memory*/
	SCB_VTOR = 0x08004000;
	/*Declare a Pointer To Function to the Start function of the application*/
	addr_to_call = *(Function_t*)(0x08004004);
	/*Execute the Start Function of the application using Software Function Call*/
	addr_to_call();
}
