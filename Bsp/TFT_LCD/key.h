#ifndef __KEY_H__
#define __KEY_H__	 
#include "main.h"
#include "stdbool.h"
 




#define KEY1  HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)//��ȡ����1
#define KEY2  HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)//��ȡ����2
#define KEY3  HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)//��ȡ����3
#define KEY4  HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)//��ȡ����4



#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2 
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES	4		//KEY4 


//void KEY_Init(void);//IO��ʼ��
unsigned char KEY_Scan(unsigned char mode);  	//����ɨ�躯��	

//unsigned char KEY_Scan(unsigned char mode);  	//����ɨ�躯��	

#endif
