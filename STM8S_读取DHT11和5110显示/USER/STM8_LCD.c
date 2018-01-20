/* Includes ------------------------------------------------------------------*/
//#include "stm8s.h"
#include "STM8_LCD.h"
#include "stm8s.h"
//6x8.h文件：
/*-----------------------------------------------
6 x 8 font
1 pixel space at left and bottom
index = ASCII - 32
-----------------------------------------------*/
const unsigned char  font6x8[][6] =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },// sp
{ 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },// !
{ 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },// "
{ 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },// #
{ 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },// $
{ 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },// %
{ 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },// &
{ 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },// '
{ 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },// (
{ 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },// )
{ 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },// *
{ 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },// +
{ 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },// ,
{ 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },// -
{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },// .
{ 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },// /
{ 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },// 0
{ 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },// 1
{ 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },// 2
{ 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },// 3
{ 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },// 4
{ 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },// 5
{ 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },// 6
{ 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },// 7
{ 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },// 8
{ 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },// 9
{ 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },// :
{ 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },// ;
{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },// <
{ 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },// =
{ 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },// >
{ 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },// ?
{ 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },// @
{ 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },// A
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },// B
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },// C
{ 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },// D
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },// E
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },// F
{ 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },// G
{ 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },// H
{ 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },// I
{ 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },// J
{ 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },// K
{ 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },// L
{ 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },// M
{ 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },// N
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },// O
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },// P
{ 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },// Q
{ 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },// R
{ 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },// S
{ 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },// T
{ 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },// U
{ 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },// V
{ 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },// W
{ 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },// X
{ 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },// Y
{ 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },// Z
{ 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },// [
{ 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },// 55
{ 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },// ]
{ 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },// ^
{ 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },// _
{ 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },// '
{ 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },// a
{ 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },// b
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },// c
{ 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },// d
{ 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },// e
{ 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },// f
{ 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },// g
{ 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },// h
{ 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },// i
{ 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },// j
{ 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },// k
{ 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },// l
{ 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },// m
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },// n
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },// o
{ 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },// p
{ 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },// q
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },// r
{ 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },// s
{ 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },// t
{ 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },// u
{ 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },// v
{ 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },// w
{ 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },// x
{ 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },// y
{ 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },// z
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }// horiz lines
}; 



const unsigned char hanzi[]=
{
	/*--  文字:  室  --*/
	/*--  Trebuchet MS9;  此字体下对应的点阵为：宽x高=12x12   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
	0x1C,0x04,0x94,0xD4,0xB5,0x96,0x94,0xD4,0x94,0x04,0x1C,0x00,0x08,0x0A,0x0A,0x0A,
	0x0A,0x0F,0x0A,0x0A,0x0A,0x0A,0x08,0x00,
	
	/*--  文字:  内  --*/
	/*--  Trebuchet MS9;  此字体下对应的点阵为：宽x高=12x12   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
	0x00,0xFC,0x04,0x84,0x64,0x1F,0x24,0xC4,0x04,0xFC,0x00,0x00,0x00,0x0F,0x00,0x00,
	0x00,0x00,0x00,0x08,0x08,0x0F,0x00,0x00,
	
	/*--  文字:  温  --*/
	/*--  Trebuchet MS9;  此字体下对应的点阵为：宽x高=12x12   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
	0x22,0x44,0x00,0xC0,0x5F,0xD5,0x55,0xD5,0x5F,0xC0,0x00,0x00,0x04,0x02,0x09,0x0F,
	0x08,0x0F,0x08,0x0F,0x08,0x0F,0x08,0x00,
	
	/*--  文字:  度  --*/
	/*--  Trebuchet MS9;  此字体下对应的点阵为：宽x高=12x12   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
	0x00,0xFE,0x0A,0x8A,0xBE,0xAA,0xAB,0xAA,0xBE,0x8A,0x0A,0x00,0x08,0x07,0x00,0x08,
	0x09,0x0A,0x04,0x04,0x0A,0x09,0x08,0x00,
	
	/*--  文字:  :	--*/
	/*--  Trebuchet MS9;  此字体下对应的点阵为：宽x高=12x12   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
	0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	

	/*--  文字:  湿  --*/
	/*--  Trebuchet MS9;  此字体下对应的点阵为：宽x高=12x12   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
	0x11,0x22,0x80,0x3E,0x2A,0xEA,0x2A,0xEA,0x2A,0x3E,0x80,0x00,0x04,0x02,0x08,0x09,
	0x08,0x0F,0x08,0x0F,0x08,0x09,0x08,0x00,

	/*--  文字:  ℃  --*/
	/*--  Trebuchet MS9;  此字体下对应的点阵为：宽x高=12x12   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
	0x02,0x05,0x02,0xF8,0x04,0x02,0x02,0x02,0x04,0x0E,0x80,0x00,0x00,0x00,0x00,0x00,
	0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,

};


void Delayus(void) 
{  
    asm("nop"); //一个asm("nop")函数经过示波器测试代表100ns 
    asm("nop"); 
    asm("nop"); 
    asm("nop");  
} 

//---- 毫秒级延时程序----------------------- 
void delayms(unsigned int time) 
{ 
    unsigned int i; 
    while(time--)   
    for(i=900;i>0;i--) 
    Delayus();  
} 
/*--------------------------------------------
LCD_write_byte: 使用SPI接口写数据到LCD
输入参数：dt：写入的数据；
command ：写数据/命令选择；
编写日期：20080918 
----------------------------------------------*/
void LCD_write_byte(unsigned char dt, unsigned char command)
{
	unsigned char i; 
	SCE0;	
        if(command)
	    DC1;
	else
	    DC0;	
	for(i=0;i<8;i++)
	{ 
		if(dt&0x80)
			DN1;
		else
			DN0;
		dt=dt<<1;		
		SCLK0; 		
		SCLK1; 
	}	
	DC1;	
	SCE1;	
	DN1;
}
/*---------------------------------------
LCD_init: 3310LCD初始化
编写日期：20080918 
-----------------------------------------  */
void LCD_init(void)
{
	RST0;  	
  	delayms(10);
  	RST1;  
	LCD_write_byte(0x21,0);//初始化Lcd,功能设定使用扩充指令
	LCD_write_byte(0xC6,0);//设定液晶偏置电压
	LCD_write_byte(0x06,0);//温度校正
  	LCD_write_byte(0x13,0);;//1:48
	LCD_write_byte(0x20,0);//使用基本指令
	LCD_write_byte(0x0C,0);//设定显示模式，正常显示
}
/*-------------------------------------------
LCD_set_XY: 设置LCD坐标函数
输入参数：X：0－83  Y：0－5
编写日期：20080918 
---------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
{
	LCD_write_byte(0x40 | Y, 0);// column
	LCD_write_byte(0x80 | X, 0);// row
} 
/*------------------------------------------
LCD_clear: LCD清屏函数
编写日期：20080918 
--------------------------------------------*/
void LCD_clear(void)
{
	unsigned char t;
	unsigned char k;
	LCD_set_XY(0,0);
	for(t=0;t<6;t++)
	{ 
		for(k=0;k<84;k++)
		{ 
			LCD_write_byte(0x00,1);
				
		} 
	}
}
/*---------------------------------------
名称: 显示英文字符
参数：c：显示的字符在font6x8表格中的位置
----------------------------------------- */
void LCD_write_char(unsigned char c)
{
	unsigned char line;
	c-= 32;
	for (line=0; line<6; line++)
	  LCD_write_byte(font6x8[c][line], 1);
}


/*---------------------------------------------
名称: 英文字符串显示函数
参数：*s：英文字符串指针
-----------------------------------------------*/
void LCD_write_String(unsigned char X,unsigned char Y,char *s)
{
	LCD_set_XY(X,Y);
	while (*s) 
	{
		LCD_write_char(*s);
		s++;
	}
} 


/*---------------------------------------------
LCD_write_hanzi: 显示12（宽）*16（高）点阵列汉字等半角类
输入参数：c：显示的字符；
编写日期：20080918 
-----------------------------------------------*/
void LCD_write_hanzi(unsigned char row, unsigned char page,unsigned char c) //row:列 page:页 dd:字符
{
	unsigned char i;  	
	
	LCD_set_XY(row*6, page);// 列，页 
	for(i=0; i<12;i++) 
	{
		LCD_write_byte(hanzi[c*24+i],1); 
	}
	
    LCD_set_XY(row*6, page+1);// 列，页 
	for(i=12; i<24;i++) 
	{
		LCD_write_byte(hanzi[c*24+i],1);
	}	
}

void LCD_GPIO_Configuration(void)
{
    GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)(GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3), GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)(GPIO_PIN_3 | GPIO_PIN_4 )  , GPIO_MODE_OUT_PP_HIGH_FAST);
}


void LCD_Display_Name(void)
{
    LCD_write_hanzi(0,0,5);  //韭菜门禁系统	
    LCD_write_hanzi(2,0,6);  //	
    LCD_write_hanzi(4,0,7);  //	
    LCD_write_hanzi(6,0,8);  //	
    LCD_write_hanzi(8,0,9);  //	
    LCD_write_hanzi(10,0,10);  //	
}





