#ifndef UART_H
#define UART_H

#include "stm32f4xx_usart.h"

void GPIO_UART_Config( void );
void UART_Config( void );
void UART_SendData(uint8_t data);

#endif
