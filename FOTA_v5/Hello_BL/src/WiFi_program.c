#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
#include "../include/STK_interface.h"
#include "../include/UART_interface.h"
#include "../include/WiFi_interface.h"
#include "../include/WiFi_private.h"


u8 Local_u8ValidResponse[50]={0};

void WiFi_voidInit(void)
{
    MUSART1_voidSendStringSynchronous(WIFI_RestartModule);
    delay_us(10*1000);

    u8 Local_u8CMDValid = 0;
    while (Local_u8CMDValid == 0)
    {
        MUSART1_voidSendStringSynchronous(WIFI_ECHO_STATE);   
        Local_u8CMDValid = u8ValidateCmd(Local_u8ValidResponse,50);
    }

    Local_u8CMDValid = 0;
    while (Local_u8CMDValid == 0)
    {
        MUSART1_voidSendStringSynchronous(WIFI_NODE_MODE);
        Local_u8CMDValid = u8ValidateCmd(Local_u8ValidResponse,50);
    }    
}


void WiFi_voidConnectToWiFi(const u8* ssid, const u8* password)
{
    u8 Local_u8CMDValid = 0;
    while(Local_u8CMDValid == 0)
    {
        MUSART1_voidSendStringSynchronous("AT+CWJAP=\"");
        MUSART1_voidSendStringSynchronous(ssid); // Insert your network name here
        MUSART1_voidSendStringSynchronous("\",\"");
        MUSART1_voidSendStringSynchronous(password); // Insert your network password here
        MUSART1_voidSendStringSynchronous("\"\r\n");
        Local_u8CMDValid = u8ValidateCmd(Local_u8ValidResponse,50);

    }
}

void WiFi_voidDisConnectToWiFi(const u8* ssid, const u8* password)
{
    u8 Local_u8CMDValid = 0;
    while (Local_u8CMDValid == 0)
    {
        MUSART1_voidSendStringSynchronous(WIFI_DisConnect);
        Local_u8CMDValid = u8ValidateCmd(Local_u8ValidResponse,50);
        delay_us(500*1000);
    }    
}

void WiFi_voidServerConnect(const u8* ip, const u8* port)
{
    u8 Local_u8CMDValid = 0;
    while(Local_u8CMDValid == 0)
    {
        MUSART1_voidSendStringSynchronous("AT+CIPSTART=\"TCP\",\"");
        MUSART1_voidSendStringSynchronous(ip);
        MUSART1_voidSendStringSynchronous("\",");
        MUSART1_voidSendStringSynchronous(port);
        MUSART1_voidSendStringSynchronous("\r\n");
        Local_u8CMDValid = u8ValidateCmd(Local_u8ValidResponse,50);
    }
}

void WiFi_voidSendHttpRequest(const u8* request)
{
    u8 Local_u8CMDValid = 0;
    while(Local_u8CMDValid == 0)
    {
        u16 sendCmd[30];
        sprintf(sendCmd, "AT+CIPSEND=%d\r\n", strlen(request));
        MUSART1_voidSendStringSynchronous(sendCmd);

        Local_u8CMDValid = u8ValidateCmd(Local_u8ValidResponse,50);
    }
    MUSART1_voidSendStringSynchronous(request);
    delay_us(5*1000);
}

u8 u8ValidateCmd(u8* buffer, u16 bufferSize)
{
    u8 Local_u8CMDValid = 0;

    // Fill the buffer with received data
    MUSART1_voidReceiveBuffer(buffer,bufferSize);
    // Check for "OK" response within the buffer

    for(u16 i = 0; i < bufferSize - 1; i++) // Ensure there's room for buffer[i+1]
    {
        if(buffer[i] == 'O' && buffer[i+1] == 'K')
        {
            Local_u8CMDValid = 1;
            
            // Clear the buffer after validation
            for(u16 j = 0; j < bufferSize; j++)
            {
                buffer[j] = 0;
            }
       		delay_us(10*1000);
            break; // No need to continue checking after "OK" is found
        }
    }
    delay_us(10*1000);

    return Local_u8CMDValid;
}





void delay_us(u32 us) {
    // Assuming the system clock is 84 MHz (typical for STM32F4 running at max speed)
    // One clock cycle at 84 MHz is approximately 11.9 ns (1 / 84,000,000)
    // Therefore, we need about 84 cycles per microsecond

    u32 count = us * 16;
    while (count--) {
        asm("NOP");
    }
}
