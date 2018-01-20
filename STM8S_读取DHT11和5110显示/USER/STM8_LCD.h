
#ifndef __STM8_LCD_H
#define __STM8_LCD_H

#define SCE0   GPIO_WriteLow(GPIOD, GPIO_PIN_2)    //片选    PG1
#define RST0   GPIO_WriteLow(GPIOD, GPIO_PIN_3)    //复位,0复位   PG0
#define DC0    GPIO_WriteLow(GPIOD, GPIO_PIN_1)   //1写数据，0写指令  PC7
#define DN0    GPIO_WriteLow(GPIOC, GPIO_PIN_4)   //数据      PC6 
#define SCLK0  GPIO_WriteLow(GPIOC, GPIO_PIN_3) //时钟        PC5

#define SCE1   GPIO_WriteHigh(GPIOD, GPIO_PIN_2)  //片选
#define RST1   GPIO_WriteHigh(GPIOD, GPIO_PIN_3)  //复位,0复位
#define DC1    GPIO_WriteHigh(GPIOD, GPIO_PIN_1)   //1写数据，0写指令
#define DN1    GPIO_WriteHigh(GPIOC, GPIO_PIN_4)   //数据
#define SCLK1  GPIO_WriteHigh(GPIOC, GPIO_PIN_3)   //时钟



void Delayus(void);
void delayms(unsigned int time);
void LCD_write_byte(unsigned char dt, unsigned char command);
void LCD_init(void);
void LCD_set_XY(unsigned char X, unsigned char Y);
void LCD_clear(void);
void LCD_write_char(unsigned char c);
void LCD_write_String(unsigned char X,unsigned char Y,char *s);
void LCD_write_shu(unsigned char row, unsigned char page,unsigned char c); //row:列 page:页 dd:字符
void LCD_write_hanzi(unsigned char row, unsigned char page,unsigned char c); //row:列 page:页 dd:字符
void LCD_GPIO_Configuration(void);

/*-----------------------显示函数--------------------------------*/
void LCD_Display_Name(void);


#endif   //_STM8_LCD
