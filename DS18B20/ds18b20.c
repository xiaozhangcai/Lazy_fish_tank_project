#include "ds18b20.h"
//温度引脚PC3
#define DQ0 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET) //DS18B20数据串口
#define DQ1 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET)
uint8_t presence;
uint8_t temp_data[2] = {0x00,0x00}; //存温度高低位
//uint8_t display[5] = {0x00,0x00,0x00,0x00,0x00};//存温度转换值
uint8_t ditab[16] = {0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x04, //温度值较准
0x05,0x06,0x06,0x07,0x08,0x08,0x09,0x09};
uint8_t temp[4]; //温度值缓存
/*
*********************************************************************************************************
* 函 数 名: Delayus
* 功能说明: us延时
* 形 参: 无
* 返 回 值: 无
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

/*************** 初始化DS18B20 ******************************************/
int Init_DS18B20(void)
{
uint8_t temp;
DS18B20_GPIO_Out(); // DQ为输出
DQ1; //DQ复位
Delayus(50); //稍做延时70us
DQ0; //将DQ拉低
HAL_Delay(480); //精确延时780us 大于 480us
DQ1; //拉高总线
DS18B20_GPIO_In(); //置DQ为输入
temp=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3); //读DQ值
Delayus(50); //稍做延时
if(temp==0) //如果=0则初始化成功 =1则初始化失败
presence = 1;
else
presence = 0;
Delayus(430); // 延时470us
DS18B20_GPIO_Out(); //置DQ为输出
DQ1; //释放总线
return(presence); //返回信号，0=presence,1= no presence
}
/****************写一个字节 ******************************************/
void WriteOneChar(uint8_t dat)
{
uint8_t i = 0;
DS18B20_GPIO_Out(); //置PD0为输出
for (i = 8; i > 0; i--) //写一字节
{
DQ0;
if(dat&0x01)
{
DQ1; //写"1"
}
else
{
DQ0; //写"0"
}
Delayus(60);
DQ1;
dat>>=1;
}
}
/*****************读一个字节 ****************************************/
int ReadOneChar(void)
{
uint8_t i = 0;
uint8_t dat = 0;
for (i = 8; i > 0; i--)
{
DQ0; //总线为低电平
dat >>= 1;
DQ1; //总线为高电平(释放总线)
DS18B20_GPIO_In(); //置DQ为输入
if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)) //读DQ
dat |= 0x80;
Delayus(70);
DS18B20_GPIO_Out(); //置DQ为输入
DQ1;
}
return (dat);
}
/*************读取温度 ********************************************/
uint8_t Read_Temperature(void)
{
#if 1
Init_DS18B20();
if(presence==0)
{
WriteOneChar(0xCC); // 跳过读序号列号的操作
WriteOneChar(0x44); // 启动温度转换
Init_DS18B20();
WriteOneChar(0xCC); //跳过读序号列号的操作
WriteOneChar(0xBE); //读取温度寄存器
temp_data[0] = ReadOneChar(); //温度低8位
temp_data[1] = ReadOneChar(); //温度高8位
}
temp_data[1]<<=4;
temp_data[1]+=(temp_data[0]&0xf0)>>4;
return temp_data[1]-5;
#else
//调试1US延时时使用
DS18B20_GPIO_Out();
DQ0;
Delayus(1);
DQ1;
#endif
}
