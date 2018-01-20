#include "stm8s_it.h"
#include "dht11.h"


/***********************************************************
* Function:       // ��������
* Description:    // �������ܡ����ܵȵ�����
* Input:          // 1.�������1��˵��������ÿ�����������á�ȡֵ˵�����������ϵ
* Input:          // 2.�������2��˵��������ÿ�����������á�ȡֵ˵�����������ϵ
* Output:         // 1.�������1��˵��
* Return:         // ��������ֵ��˵��
* Others:         // ����˵��
***********************************************************/
void dht11_delay_1us( void )
{
	nop( );
	nop( );
	nop( );
	nop( );
}

/***********************************************************
* Function:       // ��������
* Description:    // �������ܡ����ܵȵ�����
* Input:          // 1.�������1��˵��������ÿ�����������á�ȡֵ˵�����������ϵ
* Input:          // 2.�������2��˵��������ÿ�����������á�ȡֵ˵�����������ϵ
* Output:         // 1.�������1��˵��
* Return:         // ��������ֵ��˵��
* Others:         // ����˵��
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
* Function:       // ��������
* Description:    // �������ܡ����ܵȵ�����
* Input:          // 1.�������1��˵��������ÿ�����������á�ȡֵ˵�����������ϵ
* Input:          // 2.�������2��˵��������ÿ�����������á�ȡֵ˵�����������ϵ
* Output:         // 1.�������1��˵��
* Return:         // ��������ֵ��˵��
* Others:         // ����˵��
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
   ��������:
   ��������:
   ��ڲ���:
   ��ڲ��������ͺͺ���:
   ���ڲ���: �� ע:
*************************************************************/
unsigned char s_ComDHT11( void )
{
	unsigned char i, ucComData = 0;
#if 0
	for( i = 8; i > 0; i-- )
	{
		comdata = comdata << 1;
		//���յ���Ӧ������50us�ĵ͵�ƽ��ʾ�������ݵĿ�ʼ��
		//��������ֻҪ��ʱ������50us����
		dht11_delay_us( 10 );

		while( !GPIO_ReadInputPin( GPIOD, DHT11_DQ_PIN ) )
		{
			;
		}

		//λ���ݡ�0���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ�� 26-28 ΢��ĸߵ�ƽ��
		//λ���ݡ�1���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ��70΢��ĸߵ�ƽ��
		dht11_delay_us( 50 );

		if( GPIO_ReadInputPin( GPIOD, DHT11_DQ_PIN ) ) // �ߵ�ƽΪ1���͵�ƽΪ0
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
		//���յ���Ӧ������50us�ĵ͵�ƽ��ʾ�������ݵĿ�ʼ��
		//��������ֻҪ��ʱ������50us����
		while( !GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) )
		{
			;
		}

		//λ���ݡ�0���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ�� 26-28 ΢��ĸߵ�ƽ��
		//λ���ݡ�1���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ��70΢��ĸߵ�ƽ��
		dht11_delay_us( 30 );

		if( GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) ) // �ߵ�ƽΪ1���͵�ƽΪ0

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
   ��������:
   ��������:
   ��ڲ���:
   ��ڲ��������ͺͺ���:
   ���ڲ���:
   �� ע:
*************************************************************/
void ReadTempAndHumi( float *pTempValue, float *pHumiValue )
{
	unsigned char ucDHT11Value[5] = { 0x00 };

	DHT11_DQ_OUTPUT;
	DHT11_DQ_LOW;

	// ����18MS����ʱ7
	dht11_delay_ms( 180 );

	DHT11_DQ_HIGH;
	DHT11_DQ_INPUT;

	dht11_delay_us( 25 );

	while( !GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) )
	{
		;                               //80us��Ӧ���ź� DHT11 TO MCU
	}

	while( GPIO_ReadInputPin( DHT11_DQ_PORT, DHT11_DQ_PIN ) )
	{
		;                               //80us��֪ͨ�ź� DHT11 TO MCU
	}

	ucDHT11Value[0]	   = s_ComDHT11( ); // ʪ��H
	ucDHT11Value[1]	   = s_ComDHT11( ); // ʪ��L
	ucDHT11Value[2]	   = s_ComDHT11( ); // �¶�H
	ucDHT11Value[3]	   = s_ComDHT11( ); // �¶�L
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
