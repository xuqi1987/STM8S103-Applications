/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

#include "STM8_LCD.h"
#include "dht11.h"
#include "stdio.h"
#include "string.h"

u8 TempData;
u8 HumiData;
u8 RxData[256];

//要连接的无线网络名、密码
#define NET_NAME    "TP-LINK_xuqi2"	
#define NET_PASSORD "xgm10503"	

//发送数据模式、服务器地址、端口号
#define SERVER_MODE 		"TCP"							//发送数据模式
#define SERVER_ADDRESS  "192.168.1.109"	//服务器地址
#define SERVER_PORT			"8080"						//服务器端口号，如果您有自己的服务器，也可以设置为您自己的服务器端口号

/* Private defines -----------------------------------------------------------*/
u8 UART1_ReceiveByte(void);
void UART1_SendByte(u8 data);
void UART1_SendString(u8* Data,u16 len);
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {   
    nCount--;
  }
}

void Delay_US(void)
{ 
	nop();
	nop();
	nop();
	nop();
}

void Delay_nUS(u16 time)
{ 
	u16 temp = time;
	if(time == 10)	temp = 8;
	if(time == 20)	temp = 20;
	if(time == 30)	temp = 32;
	if(time == 40)	temp = 42;
	if(time == 50)	temp = 54;
	while(temp--)
	{
		nop();
		nop();
		nop();
		nop();
	}
}

void Delay_MS(u16 time)
{
  u16 i;
  while(time--)  
  for(i=900;i>0;i--)
		Delay_US();
}

void ESP8266_Display_Info(char *str)
{
	LCD_write_String(0,0,str);
}


void Init_ESP8266(void)
{
        char dest[40];
	char *str1="AT+RST\n";
	char *str2="ATE0\r\n";
	char *str3="AT+CWMODE=1\r\n";
        char *str4="AT+CIPMUX=0\r\n";
        

	UART1_SendString((u8*)str1,strlen(str1));
	Delay_MS(5000);
	UART1_SendString((u8*)str2,strlen(str2));
	Delay_MS(1000);
	UART1_SendString((u8*)str3,strlen(str3));
	Delay_MS(1000);
        UART1_SendString((u8*)str4,strlen(str4));
	Delay_MS(1000);
        
        sprintf(dest,"AT+CWJAP=\"%s\",\"%s\"\r\n",NET_NAME,NET_PASSORD);
	UART1_SendString(dest,strlen(dest));
        Delay_MS(6000);
}

void Connect_StartSend_ESP8266(void)
{
  	char dest[60];
        char *str1="AT+CIPMODE=1\r\n";
        char *str2="AT+CIPSEND\r\n";
        
        sprintf(dest,"AT+CIPSTART=\"%s\",\"%s\",%s\r\n",SERVER_MODE,SERVER_ADDRESS,SERVER_PORT);
        UART1_SendString(dest,strlen(dest));
        Delay_MS(2000);
        UART1_SendString((u8*)str1,strlen(str1));
        
        Delay_MS(2000);
        UART1_SendString((u8*)str2,strlen(str2));
        
}


void main(void)
{

  float 	  fTempDataValue		 = 0;
  float 	  fHumiDataValue		 = 0;
  char            cTempHumi[40];
  //初始化
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); //16MHz高速内部RC振荡器(HSI)
  /* Initialize I/Os in Output Mode */
  GPIO_Init(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
  
  // LCD初始化
  LCD_GPIO_Configuration();
  LCD_init();
  LCD_clear();
  
  // 串口初始化
  UART1_DeInit();
  UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
  UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE  );
  UART1_Cmd(ENABLE );
  
  disableInterrupts();
  Delay_MS(1000);
  	
  // 初始化ESP8266
  Init_ESP8266();
  Connect_StartSend_ESP8266();
  enableInterrupts();
   
  while(1)
  {
        Delay_MS(1000);
        ESP8266_Display_Info("XXXX");
        ReadTempAndHumi( &fTempDataValue, &fHumiDataValue );
        sprintf(cTempHumi,"%d %d\r\n",TempData,HumiData);
        UART1_SendString(cTempHumi,sizeof(cTempHumi));
	//UART1_SendString((u8*)RxData,strlen(RxData));
	//UART1_SendString((u8*)str1,strlen(str1));
       
        //ReadTempAndHumi( &fTempDataValue, &fHumiDataValue );
        //LCD_Display_Room_Info(TempData,HumiData);
     // LCD_write_char(UART1_ReceiveByte());
	//Delay_MS(1000);
	//
  }
  
}




u8 UART1_ReceiveByte(void)
{
	u8 USART1_RX_BUF; 
	while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
	USART1_RX_BUF=UART1_ReceiveData8();
	return  USART1_RX_BUF;
}

void UART1_SendByte(u8 data)
{
	UART1_SendData8((unsigned char)data);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}

void UART1_SendString(u8* Data,u16 len)
{
  u16 i=0;
  for(;i<len;i++)
    UART1_SendByte(Data[i]);
}

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
      /* Read one byte from the receive data register */
  //if( UART1_GetITStatus(UART1_IT_RXNE) == SET)
 // {
     //LCD_write_char( UART1_ReceiveData8());
 // }

}



#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
