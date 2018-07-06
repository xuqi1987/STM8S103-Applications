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
#include "nRF24L01.h"
#include "stdio.h"



/* Private defines -----------------------------------------------------------*/
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
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

void main(void)
{

    char data;
    uchar TxBuf[TX_PLOAD_WIDTH]={0x01,0x01,0x01,0x01,0x01};

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); 

    // 1.串口初始串口  
     /* UART1 configuration -------------------------------------------------------*/
    /* UART1 configured as follow:
           - Word Length = 8 Bits
           - 1 Stop Bit
           - No parity
           - BaudRate = 9600 baud
           - UART1 Clock enabled
           - Polarity Low
           - Phase Middle
           - Last Bit enabled
           - Receive and transmit enabled
    */
    UART1_DeInit();

    UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
               (UART1_SyncMode_TypeDef)(UART1_SYNCMODE_CLOCK_ENABLE | UART1_SYNCMODE_CPOL_LOW |UART1_SYNCMODE_CPHA_MIDDLE |UART1_SYNCMODE_LASTBIT_ENABLE),
               UART1_MODE_TXRX_ENABLE);
    UART1_Cmd(ENABLE);

    Delay_MS(500);

    printf("\n\r串口初始化完成\n\r");

    // 2.STM8和NRF24L01连接的IO口初始化 
    GPIO_Init(NRF24L01_CE_PORT, (GPIO_Pin_TypeDef)(NRF24L01_CE_PIN ), GPIO_MODE_OUT_PP_HIGH_FAST);//ce
    GPIO_Init(NRF24L01_CS_PORT, (GPIO_Pin_TypeDef)(NRF24L01_CS_PIN ), GPIO_MODE_OUT_PP_HIGH_FAST);//cs
    GPIO_Init(NRF24L01_SCK_PORT, (GPIO_Pin_TypeDef)(NRF24L01_SCK_PIN ), GPIO_MODE_OUT_PP_HIGH_FAST);//sck
    GPIO_Init(NRF24L01_MOSI_PORT, (GPIO_Pin_TypeDef)(NRF24L01_MOSI_PIN ), GPIO_MODE_OUT_PP_HIGH_FAST);//MOSI
    GPIO_Init(NRF24L01_MISO_PORT, (GPIO_Pin_TypeDef)(NRF24L01_MISO_PIN), GPIO_MODE_IN_FL_NO_IT);//MISO
    GPIO_Init(NRF24L01_IRQ_PORT, (GPIO_Pin_TypeDef)(NRF24L01_IRQ_PIN ), GPIO_MODE_IN_FL_NO_IT); //IRQ

    // 3.STM8和NRF24L01连接，STM8为主模式
    SPI_DeInit();
    /* Initialize SPI in Slave mode  */
    SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW,
             SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT,(uint8_t)0x07);

    /* Enable the SPI*/
    SPI_Cmd(ENABLE);

    printf("\n\rSPI设置完成\n\r");

    // 4.24L01模块的CE=0,CS=1,SCK=0,IRQ=1初始化， CE待机，CS SPI禁止，SCK SPI时钟置低，IRQ中断复位

    GPIO_WriteLow(NRF24L01_CE_PORT, NRF24L01_CE_PIN);   // CE待机
    GPIO_WriteHigh(NRF24L01_CS_PORT, NRF24L01_CS_PIN);  // SPI禁止
    GPIO_WriteLow(NRF24L01_SCK_PORT, NRF24L01_SCK_PIN); // SPI时钟置低
    GPIO_WriteHigh(NRF24L01_IRQ_PORT, NRF24L01_IRQ_PIN);    // IRQ中断复位

    printf("\n\r24L01模块的CE,CS,SCK初始化完成\n\r");

    Delay_MS(500);

    printf("\n\r正在检测NRF24L01设备\n\r");

    if(NRF24L01_Check()==0)
    {
        Delay_MS(500);
        printf("\n\r设备安装正确\n\r");
    }
    else
    {
        printf("\n\r>>>请检查设备是否安装正确<<\n\r");
    }
    printf("\n\r请输入命令：\n\r");
    while(1)
    {
        data = getchar();
        TxBuf[0]=data-'0';
        if(nRF24L01_TxPacket(TxBuf)==TX_OK)
        {
            GPIO_WriteHigh(GPIOD, GPIO_PIN_0);
            GPIO_WriteHigh(GPIOD, GPIO_PIN_2);
            GPIO_WriteHigh(GPIOD, GPIO_PIN_3);
            Delay_MS(0xFFFF);  //延时
            GPIO_WriteLow(GPIOD, GPIO_PIN_0);
            GPIO_WriteLow(GPIOD, GPIO_PIN_2);
            GPIO_WriteLow(GPIOD, GPIO_PIN_3);
            printf("\n 发送成功\n\r");
            Delay_MS(200);
        }
        else
        {
            printf("\n\r发送失败\n\r");
        }
    }

}

/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
PUTCHAR_PROTOTYPE
{
    /* Write a character to the UART1 */
    UART1_SendData8(c);
    /* Loop until the end of transmission */
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);

    return (c);
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval char Character to Read
  */
GETCHAR_PROTOTYPE
{
#ifdef _COSMIC_
    char c = 0;
#else
    int c = 0;
#endif
    /* Loop until the Read data register flag is SET */
    while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
    c = UART1_ReceiveData8();
    return (c);
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
