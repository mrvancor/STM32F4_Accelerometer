#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <math.h>

#include "stm32f4xx.h"
#include "SPI.h"
#include "UART.h"
#include "LIS3DSH.h"
#include "FreeRTOS.h"
#include "FreeRToSConfig.h"
#include "task.h"
#include "queue.h"

void vApplicationMallocFailedHook( void ) 
{
	
}
//---------------------------------------
//
//---------------------------------------
void vApplicationIdleHook( void ) 
{
	
}
//---------------------------------------
//
//---------------------------------------
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	
}
//---------------------------------------
//
//---------------------------------------
void vApplicationTickHook( void ) 
{
	
}
//---------------------------------------
//
//---------------------------------------

#endif
