#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm8s.h"

// 温度传感器GPIO 管脚
#define DHT11_DQ_PORT	GPIOA
#define DHT11_DQ_PIN	GPIO_PIN_1

#define DHT11_DQ_INPUT	GPIO_Init( DHT11_DQ_PORT, DHT11_DQ_PIN, GPIO_MODE_IN_PU_NO_IT )
#define DHT11_DQ_OUTPUT GPIO_Init( DHT11_DQ_PORT, DHT11_DQ_PIN, GPIO_MODE_OUT_PP_HIGH_FAST )
#define DHT11_DQ_HIGH	GPIO_WriteHigh( DHT11_DQ_PORT, DHT11_DQ_PIN )
#define DHT11_DQ_LOW	GPIO_WriteLow( DHT11_DQ_PORT, DHT11_DQ_PIN )

#define DHT11_DQ_READ GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN )
#define DHT11_DQ_WRITE( PortValue ) GPIO_Write( DHT11_DQ_PORT, PortValue )

extern unsigned char TempData;
extern unsigned char HumiData;

bool Start_DHT11( void );           //初始化

void ReadTempAndHumi( float *pTempValue, float *pHumiValue ); //读取温度和湿度值

#endif
/* EOF */
