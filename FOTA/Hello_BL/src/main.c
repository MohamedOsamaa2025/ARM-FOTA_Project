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


u8 u8ReceiveBuffer[22000] = {0};
u8 u8Record[120] = {0};

u8 u8RecDataFlag = 0;
u16 u16RecDataCounter = 0;
u8 u8BLWriteRequestFlag = 1;
u8 u8RecordCounter = 0;

u8* ProcessHexRequest = WIFI_ProcessHexRequest;
u8* RecordRequest = WIFI_RecordRequest;




void Func(void);
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
		WiFi_voidConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);
    	WiFi_voidServerConnect(WIFI_IP, WIFI_PORT);
        WiFi_voidSendHttpRequest(RecordRequest);
		MUSART1_voidReceiveBuffer(u8ReceiveBuffer,22000);
		WiFi_voidDisConnectToWiFi(WIFI_SSID, WIFI_PASSWORD);

	
		for(;u16RecDataCounter < 50;u16RecDataCounter++)
		{
			if(u8ReceiveBuffer[u16RecDataCounter] == ':')
			{
				u8RecDataFlag = 1;
				u16RecDataCounter++;
				break;
			}	
		}
		
		if(u8RecDataFlag == 0)
		{
			Func();
		}
		else
		{
			/*Erasing the Flash memory before writing on it*/
			if (u8BLWriteRequestFlag == 1)
			{
				MFPEC_voidEraseAppArea();
				u8BLWriteRequestFlag = 0;
			}
			
			while (u8ReceiveBuffer[u16RecDataCounter] != 255)
			{
				if(u8ReceiveBuffer[u16RecDataCounter] == '\r')
				{
					while(u8ReceiveBuffer[u16RecDataCounter] != ':')
					{
						u16RecDataCounter++;						
					}
				}
				else if(u8ReceiveBuffer[u16RecDataCounter] == 'C' && u8ReceiveBuffer[u16RecDataCounter+1] == 'L' && u8ReceiveBuffer[u16RecDataCounter+2] == 'O')
				{
					break;
				}
				else
				{
					u8Record[u8RecordCounter] = u8ReceiveBuffer[u16RecDataCounter];
					if(u8Record[u8RecordCounter] == '\n')
					{
						// u8Record[u8RecordCounter+1] = 0;

						/*Parsing the Received Record*/	
						MBL_voidParseRecord(&u8Record);
						for(u8 v=0;v<120;++v)
						{
							u8Record[v] = 0;
						}
						u8RecordCounter = 0;
					}
					else
					{
						u8RecordCounter++;
					}
				}
				u16RecDataCounter++;
			}

		}
			Func();




}





void Func(void)
{
	#define SCB_VTOR *((volatile u32 *)0xE000ED08)
	/*Set the offset of the Vector Table Offset Address Of The Application In The Flash Memory*/
	SCB_VTOR = 0x08004000;
	/*Declare a Pointer To Function to the Start function of the application*/
	addr_to_call = *(Function_t*)(0x08004004);
	/*Execute the Start Function of the application using Software Function Call*/
	addr_to_call();
}
