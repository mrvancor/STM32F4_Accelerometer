/*
*		Name: 	STM32F4 Accelerometer LIS3DSH
*		Author: Vladislav Murashko
*		Date: 	25/04/2020
*/

#include "main.h"

#define RAD_TO_DEG 57.295
//#define PATTERN "%s%.2f  %s%.2f%s"
#define PATTERN "%s%d  %s%d%s"

uint8_t str_size;

char data[20];

//typedef struct {
//	float 	X_H;
//	float 	Y_H;
//} xData;

typedef struct {
	int8_t 	X_H;
	int8_t 	Y_H;
} xData;

xQueueHandle xQueue;
//---------------------------------------
//
//---------------------------------------
void Interfaces_Init( void )
{
	GPIO_SPI_Config();
	SPI_Config();
	
	GPIO_UART_Config();
	UART_Config();
}
//---------------------------------------
//
//---------------------------------------
void Accel_Init( void ) 
{
	SPI_Send(LIS3DSH_CTRL_REG4, ENABLE_XY);
	SPI_Send(LIS3DSH_CTRL_REG5, 0x48);
}
//---------------------------------------
//
//---------------------------------------
void printCoords(xData *Axis)
{
	str_size = sprintf(
					data, PATTERN, 
					"x:", Axis->X_H, 
					"y:", Axis->Y_H, 		 
					"\n\r"
	);
  
	for(register int i = 0; i < str_size; ++i)
	{
		UART_SendData(data[i]);
	}
}
//---------------------------------------
//
//---------------------------------------
float getAngle(int8_t *a, int8_t *b)
{
	return atan(*a / (*b)) * RAD_TO_DEG;
}
//---------------------------------------
//
//---------------------------------------
void vTaskGetXY ( void *params )
{
	xData Axis;
	
	Accel_Init();
	
	//int8_t x;
	//int8_t y;
	
	for(;;) 
	{	
		//x = SPI_Receive(LIS3DSH_OUT_X_H);
		//y = SPI_Receive(LIS3DSH_OUT_Y_H);
		Axis.X_H = SPI_Receive(LIS3DSH_OUT_X_H); //getAngle(&x, &y);
		Axis.Y_H = SPI_Receive(LIS3DSH_OUT_Y_H); //getAngle(&y, &x);
		
		xQueueSend(xQueue, &Axis, portMAX_DELAY);
	}
	
	vTaskDelete(NULL);
}
//---------------------------------------
//
//---------------------------------------
void vTaskDisplayXY ( void *params )
{
	xData Axis;
	
	for(;;) 
	{
		xQueueReceive(xQueue, &Axis, 0);
		
		printCoords(&Axis);
		
		vTaskDelay(20);
		taskYIELD();
	}
	
	vTaskDelete(NULL);
}
//---------------------------------------
//
//---------------------------------------
int main( void ) 
{
	Interfaces_Init();
	
	xQueue = xQueueCreate(1, sizeof(xData));
	
	xTaskCreate(vTaskGetXY, "GET_XY", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(vTaskDisplayXY, "DISPLAY_XY", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
	
	for(;;);
}
