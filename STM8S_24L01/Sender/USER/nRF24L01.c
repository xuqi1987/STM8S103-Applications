
#include "nRF24L01.h"
#include "stm8s.h"
#include "stdio.h"

uchar  TX_ADDRESS[TX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x01}; // Define a static TX address
uchar RX_ADDRESS[RX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x01}; // Define a static RX address

uchar  stat;		   //存放在可位寻址的区域

void inerDelay_us(unsigned char n)  //改为延时1US
{
    for(;n>0;n--)
    {
        asm("nop");  //在STM8里面，16M晶振，_nop_() 延时了 333ns
        asm("nop");
        asm("nop");
        asm("nop");
        //printf("\n\r delay \n\r");
    }
}

/**************************************************
Function: SPI_RW();

  Description:
  Writes one byte to nRF24L01, and return the byte read
  from nRF24L01 during write, according to SPI protocol
**************************************************/
uchar SPI_RW(uchar byte)
{
    /*!< Wait until the transmit buffer is empty */
    uchar retry;
    while (SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET)
    {}
    /*!< Send the byte */
    SPI_SendData(byte);
    
    /*!< Wait until a data is received */
    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET)
    {
        retry++;
        if(retry>200)return 0;

    }
    /*!< Get the received data */
    byte = SPI_ReceiveData();
    return(byte);
}
/**************************************************/

/**************************************************
Function: SPI_RW_Reg();

  Description:
  Writes value 'value' to register 'reg'
************************************************/
uchar SPI_RW_Reg(BYTE reg, BYTE value)
{
    uchar status;

    GPIO_WriteLow(NRF24L01_CS_PORT,NRF24L01_CS_PIN);                // CSN low, init SPI transaction
    status = SPI_RW(reg);      // select register
    SPI_RW(value);             // ..and write value to it..
    GPIO_WriteHigh(NRF24L01_CS_PORT,NRF24L01_CS_PIN);                   // CSN high again
    return(status);            // return nRF24L01 status byte
}
/**************************************************/

/**************************************************
Function: SPI_Read();

  Description:
  Read one byte from nRF24L01 register, 'reg'
**************************************************/
BYTE SPI_Read(BYTE reg)
{
    BYTE reg_val;

    GPIO_WriteLow(NRF24L01_CS_PORT,NRF24L01_CS_PIN);                 // CSN low, initialize SPI communication...
    //NRF24L01_CS_LOW() ;
    SPI_RW(reg);            // Select register to read from..
    reg_val = SPI_RW(0);    // ..then read registervalue
    GPIO_WriteHigh(NRF24L01_CS_PORT,NRF24L01_CS_PIN);           // CSN high, terminate SPI communication
    //NRF24L01_CS_HIGH() ;

    return(reg_val);        // return register value
}
/**************************************************/

/*************************************************
Function: SPI_Read_Buf();

  Description:
  
**************************************************/
uchar SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes)
{
    uchar status,byte_ctr;

    GPIO_WriteLow(NRF24L01_CS_PORT,NRF24L01_CS_PIN);// Set CSN low, init SPI tranaction
    status = SPI_RW(reg);       		// Select register to write to and read status byte
    //printf("\n\r %d \n\r",status);
    for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
        pBuf[byte_ctr] = SPI_RW(0);    //

    GPIO_WriteHigh(NRF24L01_CS_PORT,NRF24L01_CS_PIN);

    return(status);                    // return nRF24L01 status byte
}
/**************************************************/

/**************************************************
Function: SPI_Write_Buf();

  Description:
  Writes contents of buffer '*pBuf' to nRF24L01
  Typically used to write TX payload, Rx/Tx address
*************************************************/
uchar SPI_Write_Buf(uchar reg, uchar *pBuf, uchar bytes)
{
    uchar status,byte_ctr;

    GPIO_WriteLow(NRF24L01_CS_PORT,NRF24L01_CS_PIN);
    status = SPI_RW(reg);

    /*  if(status&0x10)//MAX_RT判断是否因为从发次数溢出而中断
    //PB_ODR ^= 0b00100000;
    SPI_RW_Reg(WRITE_REG+STATUS,0x70);//要用软件写1后才能清除IRQ_PIN为高电平*/

    for(byte_ctr=0; byte_ctr<bytes; byte_ctr++)
        SPI_RW(*pBuf++);
    GPIO_WriteHigh(NRF24L01_CS_PORT,NRF24L01_CS_PIN);
    return(status);
}
/**************************************************/

/**************************************************
Function: RX_Mode();

  Description:
  
*************************************************/
void RX_Mode(void)
{
    GPIO_WriteLow(NRF24L01_CE_PORT,NRF24L01_CE_PIN);


    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // Writes TX_Address to nRF24L01
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // Use the same address on the RX device as the TX device

    SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //频道0自动	ACK应答允许
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //允许接收地址只有频道0，
    SPI_RW_Reg(WRITE_REG + RF_CH, 40);        //   设置信道工作为2.4GHZ，收发必须一致
    //SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a);
    SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07); // 设置发射速率为1MHZ，发射功率为最大值0dB


    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);    //power up  1: PRX
    //CE = 1;
    GPIO_WriteHigh(NRF24L01_CE_PORT,NRF24L01_CE_PIN);
    inerDelay_us(130);

}
/**************************************************/
/**************************************************
Function: Set_TX_Mode()

  Description:
  
*************************************************/
void TX_Mode(void)
{
    GPIO_WriteLow(NRF24L01_CE_PORT,NRF24L01_CE_PIN);
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x02);   //0x0E		 // IRQ收发完成中断响应，16位CRC，主发送

    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址

    SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);//0x01);      //  频道0自动	ACK应答允许
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21
    SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a); // 设置自动重发时间和次数：500us + 86us, 10 retrans...
    SPI_RW_Reg(WRITE_REG + RF_CH, 40);        //   设置信道工作为2.4GHZ，收发必须一致
    //	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB

    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);//0x0E);

    GPIO_WriteHigh(NRF24L01_CE_PORT,NRF24L01_CE_PIN);
}
/**************************************************/
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;

    stat=SPI_Read(STATUS);	// read register STATUS's value
    if(stat&0x40==1)	// if receive data ready (RX_DR) interrupt
    {
        GPIO_WriteLow(NRF24L01_CE_PORT,NRF24L01_CE_PIN);
        SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
        revale =1;//we have receive data
    }
    SPI_RW_Reg(WRITE_REG+STATUS,stat);// clear RX_DR or TX_DS or MAX_RT interrupt flag

    return revale;
}

/**************************************************
Function: nRF24L01_TxPacket();

  Description:
  This function initializes one nRF24L01 device to
  TX mode, set TX address, set RX address for auto.ack,
  fill TX payload, select RF channel, datarate & TX pwr.
  PWR_UP is set, CRC(2 bytes) is enabled, & PRIM:TX.
  
    ToDo: One high pulse(>10us) on CE will now send this
    packet and expext an acknowledgment from the RX device.
**************************************************/
unsigned char nRF24L01_TxPacket(unsigned char * tx_buf)
{

    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 1.写TX的地址
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // 2.写Rx的地址，使Auto_ack使能

    SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);//0x01);      //  3.频道0自动	使能ACK应答允许
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  4.允许接收地址只有频道0，如果需要多频道可以参考Page21
    SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a); // 5.设置自动重发时间和次数：500us + 86us, 10 retrans...
    SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // 6.设置信道工作为2.4GHZ，收发必须一致
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);  // 7.设置发射速率为1MHZ，发射功率为最大值0dB

    GPIO_WriteLow(NRF24L01_CE_PORT,NRF24L01_CE_PIN);

    SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); // 8.选择通道0有效数据宽度
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0E);//0x0E;    // 9. 配置基本参数及切换工作模式

    GPIO_WriteHigh(NRF24L01_CE_PORT,NRF24L01_CE_PIN); // CE使能10us，发送数据
    inerDelay_us(35);		//延时10us
    GPIO_WriteLow(NRF24L01_CE_PORT,NRF24L01_CE_PIN);

    while(GPIO_ReadInputPin(NRF24L01_IRQ_PORT, NRF24L01_IRQ_PIN)!=0);//等待发送中断
    stat = SPI_Read(STATUS);//读取状态寄存器的值
    SPI_RW_Reg(WRITE_REG+STATUS, stat); //清除TX_DS或MAX_RT中断标志
    if(stat&MAX_TX)//达到最大重发次数
    {
        SPI_RW_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器
        return MAX_TX;
    }
    if(stat&TX_OK)//发送完成
    {
        return TX_OK;
    }
    return 0xff;//其他原因发送失败
}


/**************************************************/

//上电检测NRF24L01是否在位
//写5个数据然后再读回来进行比较，相同时返回值:0，表示在位;否则返回1，表示不在位	
BYTE NRF24L01_Check(void)
{
    BYTE buf[5]={0xa9,0xa9,0xa9,0xa9,0xa9};
    BYTE buf1[5];
    BYTE i;
    SPI_Write_Buf(WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.
    SPI_Read_Buf(TX_ADDR,buf1,5);              //读出写入的地址
    for(i=0;i<5;i++)
        if(buf1[i]!=0xA9)
            break;
    if(i!=5)
        return 1;                               //NRF24L01不在位
    return 0;		                                //NRF24L01在位
}	 	
/*************************************************************/
