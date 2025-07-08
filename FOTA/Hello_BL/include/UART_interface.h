/*****************************************************************************************
 * Author:				Abdullah M. Abdullah
 * Creation Data:		03 Jun, 2023
 * Version:				v1.0
 * Compiler:			GNU ARM-GCC
 * Controller:			STM32F401CCU6 (32-bit Architecture)
 * Processor:			Cortex M4 (32-bit Architecture)
 * Layer:				MCAL Layer
 *****************************************************************************************/
/*****************************************************************************************
 * Version	  Date				  Author				  Description
 * v1.0		  03 Jun, 2023	Abdullah M. Abdullah		  Initial Creation
*****************************************************************************************/
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void MUSART1_voidInit(void);
void MUSART1_voidSendDataSynchronous(u8 Copy_u8Data);
void MUSART1_voidReceiveDataSynchronous(u8 * Copy_pu8ReceivedData);

void MUSART1_voidSendStringSynchronous(u8 * Copy_pu8StringArray);
void MUSART1_voidSendNumberSynchronous(u32 Copy_u32Number);
u8 MUSART1_u8ReceiveDataIfReceived(u8 * Copy_pu8ReceivedData);


u8   MUSART1_u8ReceiveTimeOut(void);
void MUSART1_voidReceiveBuffer(u8 *Copy_ptrBuffer , u32 Copy_SizeBuffer);





#endif