#include "stm8s_it.h"
#include "dht11.h"


/***********************************************************
* Function:       // 函数名称
* Description:    // 函数功能、性能等的描述
* Input:          // 1.输入参数1，说明，包括每个参数的作用、取值说明及参数间关系
* Input:          // 2.输入参数2，说明，包括每个参数的作用、取值说明及参数间关系
* Output:         // 1.输出参数1，说明
* Return:         // 函数返回值的说明
* Others:         // 其它说明
***********************************************************/
void dht11_delay_1us( void )
{
	nop( );
	nop( );
	nop( );
	nop( );
}

/***********************************************************
* Function:       // 函数名称
* Description:    // 函数功能、性能等的描述
* Input:          // 1.输入参数1，说明，包括每个参数的作用、取值说明及参数间关系
* Input:          // 2.输入参数2，说明，包括每个参数的作用、取值说明及参数间关系
* Output:         // 1.输出参数1，说明
* Return:         // 函数返回值的说明
* Others:         // 其它说明
***********************************************************/
void dht11_delay_us( u16 time )
{
	u16 temp = time;
	if( time == 10 )
	{
		temp = 8;
	}
	if( time == 20 )
	{
		temp = 20;
	}
	if( time == 30 )
	{
		temp = 32;
	}
	if( time == 40 )
	{
		temp = 42;
	}
	if( time == 50 )
	{
		temp = 54;
	}

	while( temp-- )
	{
		nop( );
		nop( );
		nop( );
		nop( );
	}
}

/***********************************************************
* Function:       // 函数名称
* Description:    // 函数功能、性能等的描述
* Input:          // 1.输入参数1，说明，包括每个参数的作用、取值说明及参数间关系
* Input:          // 2.输入参数2，说明，包括每个参数的作用、取值说明及参数间关系
* Output:         // 1.输出参数1，说明
* Return:         // 函数返回值的说明
* Others:         // 其它说明
***********************************************************/
void dht11_delay_ms( u16 time )
{
	u16 i;
	while( time-- )
	{
		for( i = 900; i > 0; i-- )
		{
			dht11_delay_1us( );
		}
	}
}

/*************************************************************
   函数名称:
   函数功能:
   入口参数:
   入口参数的类型和含义:
   出口参数: 备 注:
*************************************************************/
unsigned char s_ComDHT11( void )
{
	unsigned char i, ucComData = 0;
#if 0
	for( i = 8; i > 0; i-- )
	{
		comdata = comdata << 1;
		//接收到响应后会出现50us的低电平表示发送数据的开始，
		//所以这里只要延时不超过50us即可
		dht11_delay_us( 10 );

		while( !GPIO_ReadInputPin( GPIOD, DHT11_DQ_PIN ) )
		{
			;
		}

		//位数据“0”的格式为： 50 微秒的低电平和 26-28 微秒的高电平，
		//位数据“1”的格式为： 50 微秒的低电平加70微秒的高电平。
		dht11_delay_us( 50 );

		if( GPIO_ReadInputPin( GPIOD, DHT11_DQ_PIN ) ) // 高电平为1，低电平为0
		{
			comdata |= 0x01;
			//while( !GPIO_ReadInputPin( GPIOD, GPIO_PIN_4 ) )
			//{
			//	;
			//}
			dht11_delay_us( 40 );
		}
		else
		{
			comdata &= 0xfe;
		}
	}
#endif
	for( i = 0; i < 8; i++ )
	{
		//接收到响应后会出现50us的低电平表示发送数据的开始，
		//所以这里只要延时不超过50us即可
		while( !GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) )
		{
			;
		}

		//位数据“0”的格式为： 50 微秒的低电平和 26-28 微秒的高电平，
		//位数据“1”的格式为： 50 微秒的低电平加70微秒的高电平。
		dht11_delay_us( 30 );

		if( GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) ) // 高电平为1，低电平为0

		{
			ucComData |= ( 1 << ( 7 - i ) );
		}

		while( GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) )
		{
			;
		}
	}

	return ucComData;
}

/*************************************************************
   函数名称:
   函数功能:
   入口参数:
   入口参数的类型和含义:
   出口参数:
   备 注:
*************************************************************/
void ReadTempAndHumi( float *pTempValue, float *pHumiValue )
{
	unsigned char ucDHT11Value[5] = { 0x00 };

	DHT11_DQ_OUTPUT;
	DHT11_DQ_LOW;

	// 至少18MS的延时7
	dht11_delay_ms( 180 );

	DHT11_DQ_HIGH;
	DHT11_DQ_INPUT;

	dht11_delay_us( 25 );

	while( !GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) )
	{
		;                               //80us的应答信号 DHT11 TO MCU
	}

	while( GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) )
	{
		;                               //80us的通知信号 DHT11 TO MCU
	}

	ucDHT11Value[0]	   = s_ComDHT11( ); // 湿度H
	ucDHT11Value[1]	   = s_ComDHT11( ); // 湿度L
	ucDHT11Value[2]	   = s_ComDHT11( ); // 温度H
	ucDHT11Value[3]	   = s_ComDHT11( ); // 温度L
	ucDHT11Value[4]	   = s_ComDHT11( ); // Check sum

	DHT11_DQ_OUTPUT;

	if( ( ucDHT11Value[0] +
	      ucDHT11Value[1] +
	      ucDHT11Value[2] +
	      ucDHT11Value[3] ) ==
	    ucDHT11Value[4] )
	{
		*pHumiValue	   = ucDHT11Value[0] + ucDHT11Value[1] / 10;
		*pTempValue	   = ucDHT11Value[2] + ucDHT11Value[4] / 10;
		TempData = ucDHT11Value[2];
		HumiData = ucDHT11Value[0];
	}
}

/* EOF */
