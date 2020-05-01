#include "SPI.h"


void GPIO_SPI_Config( void )
{
	GPIO_InitTypeDef GPIO_Init_SPI;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Init_SPI.GPIO_Pin = SPI_SCK_PIN | SPI_MISO_PIN | SPI_MOSI_PIN;
	GPIO_Init_SPI.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_SPI.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_SPI.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_Init_SPI);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_Init_SPI.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init_SPI.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_SPI.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(GPIOE, &GPIO_Init_SPI);
	
	SPI_CS_OFF();
}
//---------------------------------------
//
//---------------------------------------
void SPI_Config( void ) 
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStruct);
	
	SPI_Cmd(SPI1, ENABLE);
}
//---------------------------------------
//
//---------------------------------------
void SPI_Send(uint8_t adress, uint8_t data)
{
  SPI_CS_ON();

  while(isTransmitBufferNotEmpty());
	SPI_I2S_SendData(SPI1, adress);
  while(isReceiveBufferNotEmpty());
	SPI_I2S_ReceiveData(SPI1);
	
  while(isTransmitBufferNotEmpty());
	SPI_I2S_SendData(SPI1, data);
  while(isReceiveBufferNotEmpty());
	SPI_I2S_ReceiveData(SPI1);
	
  SPI_CS_OFF();
}
//---------------------------------------
//
//---------------------------------------
uint8_t SPI_Receive(uint8_t adress)
{
  SPI_CS_ON();
	
  adress = SPI_READ_BIT | adress;
	
  while(isTransmitBufferNotEmpty());
	SPI_I2S_SendData(SPI1, adress);
  while(isReceiveBufferNotEmpty());
	SPI_I2S_ReceiveData(SPI1);
	
  while(isTransmitBufferNotEmpty());
  SPI_I2S_SendData(SPI1, 0x00);
  while(isReceiveBufferNotEmpty());
  
  SPI_CS_OFF();
	
  return SPI_I2S_ReceiveData(SPI1);
}
