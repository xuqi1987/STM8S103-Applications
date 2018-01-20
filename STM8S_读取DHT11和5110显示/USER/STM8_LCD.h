
#ifndef __STM8_LCD_H
#define __STM8_LCD_H

#define SCE0   GPIO_WriteLow(GPIOD, GPIO_PIN_2)    //Ƭѡ    PG1
#define RST0   GPIO_WriteLow(GPIOD, GPIO_PIN_3)    //��λ,0��λ   PG0
#define DC0    GPIO_WriteLow(GPIOD, GPIO_PIN_1)   //1д���ݣ�0дָ��  PC7
#define DN0    GPIO_WriteLow(GPIOC, GPIO_PIN_4)   //����      PC6 
#define SCLK0  GPIO_WriteLow(GPIOC, GPIO_PIN_3) //ʱ��        PC5

#define SCE1   GPIO_WriteHigh(GPIOD, GPIO_PIN_2)  //Ƭѡ
#define RST1   GPIO_WriteHigh(GPIOD, GPIO_PIN_3)  //��λ,0��λ
#define DC1    GPIO_WriteHigh(GPIOD, GPIO_PIN_1)   //1д���ݣ�0дָ��
#define DN1    GPIO_WriteHigh(GPIOC, GPIO_PIN_4)   //����
#define SCLK1  GPIO_WriteHigh(GPIOC, GPIO_PIN_3)   //ʱ��



void Delayus(void);
void delayms(unsigned int time);
void LCD_write_byte(unsigned char dt, unsigned char command);
void LCD_init(void);
void LCD_set_XY(unsigned char X, unsigned char Y);
void LCD_clear(void);
void LCD_write_char(unsigned char c);
void LCD_write_String(unsigned char X,unsigned char Y,char *s);
void LCD_write_shu(unsigned char row, unsigned char page,unsigned char c); //row:�� page:ҳ dd:�ַ�
void LCD_write_hanzi(unsigned char row, unsigned char page,unsigned char c); //row:�� page:ҳ dd:�ַ�
void LCD_GPIO_Configuration(void);

/*-----------------------��ʾ����--------------------------------*/
void LCD_Display_Name(void);


#endif   //_STM8_LCD
