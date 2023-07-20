#include "phcs.h"
#include "spi_tftlcd.h"
#include "GUI.h"
#include "stdio.h"

/*
cn10-24    pb1

*/



unsigned char AD_CHANNEL=0;
unsigned long PH_num=0,PU_V=0;
double PH_Value=0,ph=0;
uint8_t ph_temp=0;
uint16_t ph_result=0,tu_result=0;

char  PH_Buff[6];   //PH数据存储数组
char dissbuff[6];

// 用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[4]; 

double PHadc(ADC_HandleTypeDef *a)
{
	int i=0;
	double temp;
	HAL_ADC_Start(a);
	i=HAL_ADC_GetValue(a);
	temp=(float)i/4096*3.3;	
	PH_Value=-5.7541*temp+16.654;
	   
		if(PH_Value<=0.0){PH_Value=0.0;}
		if(PH_Value>=14.0){PH_Value=14.0;}
		
//	PH_Buff[0]=(int)(PH_Value*100)/1000+'0';	
//	PH_Buff[1]=(int)(PH_Value*100)%1000/100+'0';
//	PH_Buff[2]='.';
//	PH_Buff[3]=(int)(PH_Value*100)%100/10+'0';
//	PH_Buff[4]=(int)(PH_Value*100)%10+'0';	
//		dissbuff[1] = PH_Buff[0];
//		dissbuff[2] = PH_Buff[1];
//		dissbuff[3] = PH_Buff[2];
//		dissbuff[4] = PH_Buff[3];
//		dissbuff[5] = PH_Buff[4];
		//Gui_DrawFont_GBK16(16,300,RED,GRAY0,(uint8_t *)i);

		return PH_Value-5;
}


