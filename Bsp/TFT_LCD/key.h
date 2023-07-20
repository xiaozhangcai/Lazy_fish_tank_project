#ifndef __KEY_H__
#define __KEY_H__	 
#include "main.h"
#include "stdbool.h"
 




#define KEY1  HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)//读取按键1
#define KEY2  HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)//读取按键2
#define KEY3  HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)//读取按键3
#define KEY4  HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)//读取按键4



#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2 
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES	4		//KEY4 


//void KEY_Init(void);//IO初始化
unsigned char KEY_Scan(unsigned char mode);  	//按键扫描函数	

//unsigned char KEY_Scan(unsigned char mode);  	//按键扫描函数	

#endif
