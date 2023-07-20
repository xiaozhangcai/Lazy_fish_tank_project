#include "ds18b20.h"
//�¶�����PC3
#define DQ0 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET) //DS18B20���ݴ���
#define DQ1 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET)
uint8_t presence;
uint8_t temp_data[2] = {0x00,0x00}; //���¶ȸߵ�λ
//uint8_t display[5] = {0x00,0x00,0x00,0x00,0x00};//���¶�ת��ֵ
uint8_t ditab[16] = {0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x04, //�¶�ֵ��׼
0x05,0x06,0x06,0x07,0x08,0x08,0x09,0x09};
uint8_t temp[4]; //�¶�ֵ����
/*
*********************************************************************************************************
* �� �� ��: Delayus
* ����˵��: us��ʱ
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void Delayus( uint32_t uTime)
{
uint16_t i;
while(uTime--)
{
i = 23;
while(i--);
}
}
void DS18B20_GPIO_In(void)
{
GPIO_InitTypeDef GPIO_InitStruct;
__HAL_RCC_GPIOC_CLK_ENABLE();
GPIO_InitStruct.Pin = GPIO_PIN_3;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void DS18B20_GPIO_Out(void)
{
GPIO_InitTypeDef GPIO_InitStruct;
__HAL_RCC_GPIOC_CLK_ENABLE();
GPIO_InitStruct.Pin = GPIO_PIN_3;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/*************** ��ʼ��DS18B20 ******************************************/
int Init_DS18B20(void)
{
uint8_t temp;
DS18B20_GPIO_Out(); // DQΪ���
DQ1; //DQ��λ
Delayus(50); //������ʱ70us
DQ0; //��DQ����
HAL_Delay(480); //��ȷ��ʱ780us ���� 480us
DQ1; //��������
DS18B20_GPIO_In(); //��DQΪ����
temp=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3); //��DQֵ
Delayus(50); //������ʱ
if(temp==0) //���=0���ʼ���ɹ� =1���ʼ��ʧ��
presence = 1;
else
presence = 0;
Delayus(430); // ��ʱ470us
DS18B20_GPIO_Out(); //��DQΪ���
DQ1; //�ͷ�����
return(presence); //�����źţ�0=presence,1= no presence
}
/****************дһ���ֽ� ******************************************/
void WriteOneChar(uint8_t dat)
{
uint8_t i = 0;
DS18B20_GPIO_Out(); //��PD0Ϊ���
for (i = 8; i > 0; i--) //дһ�ֽ�
{
DQ0;
if(dat&0x01)
{
DQ1; //д"1"
}
else
{
DQ0; //д"0"
}
Delayus(60);
DQ1;
dat>>=1;
}
}
/*****************��һ���ֽ� ****************************************/
int ReadOneChar(void)
{
uint8_t i = 0;
uint8_t dat = 0;
for (i = 8; i > 0; i--)
{
DQ0; //����Ϊ�͵�ƽ
dat >>= 1;
DQ1; //����Ϊ�ߵ�ƽ(�ͷ�����)
DS18B20_GPIO_In(); //��DQΪ����
if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)) //��DQ
dat |= 0x80;
Delayus(70);
DS18B20_GPIO_Out(); //��DQΪ����
DQ1;
}
return (dat);
}
/*************��ȡ�¶� ********************************************/
uint8_t Read_Temperature(void)
{
#if 1
Init_DS18B20();
if(presence==0)
{
WriteOneChar(0xCC); // ����������кŵĲ���
WriteOneChar(0x44); // �����¶�ת��
Init_DS18B20();
WriteOneChar(0xCC); //����������кŵĲ���
WriteOneChar(0xBE); //��ȡ�¶ȼĴ���
temp_data[0] = ReadOneChar(); //�¶ȵ�8λ
temp_data[1] = ReadOneChar(); //�¶ȸ�8λ
}
temp_data[1]<<=4;
temp_data[1]+=(temp_data[0]&0xf0)>>4;
return temp_data[1]-5;
#else
//����1US��ʱʱʹ��
DS18B20_GPIO_Out();
DQ0;
Delayus(1);
DQ1;
#endif
}
