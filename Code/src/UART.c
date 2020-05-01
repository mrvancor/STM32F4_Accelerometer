#include "UART.h"

void GPIO_UART_Config( void )
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_UART;
	GPIO_Init_UART.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_UART.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_UART.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init_UART.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_Init_UART);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
}
//---------------------------------------
//
//---------------------------------------
void UART_Config( void ) 
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_InitTypeDef UART_InitStruct;
	
	UART_InitStruct.USART_BaudRate = 9600;
	UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStruct.USART_Mode =  USART_Mode_Tx;
	UART_InitStruct.USART_Parity = USART_Parity_No;
	UART_InitStruct.USART_StopBits = USART_StopBits_1;
	UART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2, &UART_InitStruct);
 	USART_Cmd(USART2, ENABLE);
}
//---------------------------------------
//
//---------------------------------------
void UART_SendData(uint8_t data)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	USART_SendData(USART2, data);
}
