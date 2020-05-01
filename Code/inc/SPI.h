#ifndef SPI_H
#define SPI_H

#include "stm32f4xx_spi.h"

#define SPI_SCK_PIN   GPIO_Pin_5
#define SPI_MISO_PIN  GPIO_Pin_6
#define SPI_MOSI_PIN  GPIO_Pin_7
#define SPI_READ_BIT  0x80

#define SPI_CS_ON()   GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define SPI_CS_OFF()  GPIO_SetBits(GPIOE, GPIO_Pin_3)

#define isTransmitBufferNotEmpty()  !SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)
#define isReceiveBufferNotEmpty()   !SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)

void GPIO_SPI_Config( void );
void SPI_Config( void );
void SPI_Send(uint8_t adress, uint8_t data);
uint8_t SPI_Receive(uint8_t adress);

#endif
