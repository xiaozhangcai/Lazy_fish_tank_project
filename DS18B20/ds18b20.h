#ifndef __DS18B20_H__
#define __DS18B20_H__	 

#include "main.h"
#include "tim.h"
#include "usart.h"
#include <stdio.h>

void DS18B20_GPIO_In(void);
void DS18B20_GPIO_Out(void);
int Init_DS18B20(void);
void WriteOneChar(uint8_t dat);
int ReadOneChar(void);
uint8_t Read_Temperature(void);
void Disp_Temperature(void);



#endif
