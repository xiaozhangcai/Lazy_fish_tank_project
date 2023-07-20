#include "zd.h"

/*
AOUT     pb14    cn10-28




*/



double getadc(ADC_HandleTypeDef *a)
{
	uint adc,temp;
	HAL_ADC_Start(a);
	adc=HAL_ADC_GetValue(a);
	temp=(float)adc*(3.3/4096);
	temp=temp*100/30;
	return temp;
	
}
