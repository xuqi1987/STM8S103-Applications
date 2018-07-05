#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "stm8s.h"

#define MODE "AT+CWMODE=?\r\n"

void ESP8266_UART1_Init();
void Init_ESP8266();


#endif