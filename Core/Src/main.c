/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi_tftlcd.h"
#include "GUI.h"
//#include "font.h"
#include "stdio.h"
//#include "csb.h"
#include "string.h"
#include "zd.h"
#include "phcs.h"
#include "key.h"
#include "ds18b20.h"
#include "rgb.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint csb;
uint8_t temperature;
uint8_t humidity;
void ESP8266_SendATCommand(char *cmd);
int i=0;
//int fputc(int ch, FILE *f){
//HAL_UART_Transmit (&huart1,(uint8_t *)&ch,1,0xffff);
//return ch;
//}

#define TRIG_ON HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
#define TRIG_OFF HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
double S1,S2,distance; //数据1，数据2，距离
int32_t distance1; //距离1
uint32_t chaoshenbo_flag=0;
double chaoshenbo_data = 0;

/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void chaoShenBo(){
htim16.Instance->CNT=0;
TRIG_OFF;
TRIG_ON;
HAL_Delay(1);
TRIG_OFF; //根据时序要求拉低TR引脚，等待EC引脚回应
while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin)==GPIO_PIN_RESET);
S1=htim16.Instance->CNT; //EC回应低，记录其时间S1
while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin)==1);
S2=htim16.Instance->CNT; //EC回应高，记录其时间S2
distance=(S2-S1)*0.034/2; //用时间S2-S1=声波返回时间 再乘0.034/2（声速/2）=距离 时间*速度=距离
distance1=distance*100; //将小数放大百倍
distance=distance1; //转化为整数型 去掉后面尾数 保证数据精确 反正我是这样子想的
distance/=100; //转回浮点数
//distance-=90;
}
//蜂鸣器
//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);	
//加热棒
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
//		HAL_Delay(5000);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
unsigned char key_value;
	int a=0,e=0,c=0,d=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM16_Init();
  MX_ADC4_Init();
  MX_ADC3_Init();
  MX_TIM17_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
	/* USER CODE BEGIN 2 */
	Lcd_Init();	
	//HAL_TIM_IC_CaptureCallback(&htim16);
	//HAL_TIM_IC_Start_IT(&htim16,TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim16);  
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	Init_DS18B20();
	int pwmval=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	Lcd_Clear(BLACK);
  Gui_DrawFont_GBK16(16,60,WHITE,BLACK,(uint8_t *)"团队名称：ZDZ");
	Gui_DrawFont_GBK16(16,80,WHITE,BLACK,(uint8_t *)"团队编号：11645");
	Gui_DrawFont_GBK16(16,100,WHITE,BLACK,(uint8_t *)"项目名称：懒人养鱼缸");
	Gui_DrawFont_GBK16(16,150,WHITE,BLACK,(uint8_t *)"团队成员:组长：张帅文");
	Gui_DrawFont_GBK16(90,170,WHITE,BLACK,(uint8_t *)"组员：董夕雨,周思辉");
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
  while (1)
  {
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
		//led_loop();
	while(pwmval < 500)
		{
			pwmval++;
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,pwmval);
			HAL_Delay(1);
		}
		while(pwmval>1)
		{
			pwmval--;
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,pwmval);
			HAL_Delay(1);
		}	
		HAL_Delay(200);
		
  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		key_value	= KEY_Scan(0);
	if(key_value == KEY1_PRES)
	{
		Lcd_Clear(BLACK);
		a=1;
	}
	if(key_value == KEY2_PRES)
	{
		c=1;
		
	}
	if(key_value == KEY3_PRES)
	{
		d=1;
	
	} 
	if(key_value == KEY4_PRES)
	{
		e=!e;
	
	}
	if(a==1)
	{
		char b[30];
		sprintf(b,"浊度:%.2f",getadc(&hadc4));	
		Gui_DrawFont_GBK16(16,60,WHITE,BLACK,(uint8_t*)b);
		__HAL_RCC_GPIOB_CLK_ENABLE();
		
		sprintf(b,"PH值:%.3f",PHadc(&hadc3));	
		Gui_DrawFont_GBK16(16,80,WHITE,BLACK,(uint8_t*)b);
		
		chaoShenBo();
		sprintf(b,"水位:%.2f",distance);	
		Gui_DrawFont_GBK16(16,100,WHITE,BLACK,(uint8_t*)b);
		
		sprintf(b,"温度:%d",Read_Temperature());	
		Gui_DrawFont_GBK16(16,120,WHITE,BLACK,(uint8_t *)b);	
		if(c==0)
	{
		//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		Gui_DrawFont_GBK16(16,210,WHITE,BLACK,(uint8_t *)"喂食器：关闭");
	}
	if(c==1)
	{
		for(int i=0;i<=5;i++)
		{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		Gui_DrawFont_GBK16(16,210,WHITE,BLACK,(uint8_t *)"喂食器：打开");
		}
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		Gui_DrawFont_GBK16(16,210,WHITE,BLACK,(uint8_t *)"喂食器：关闭");
		c=0;
	}
	if(d==0)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
		Gui_DrawFont_GBK16(16,190,WHITE,BLACK,(uint8_t *)"出水电机：关闭");
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
		Gui_DrawFont_GBK16(16,170,WHITE,BLACK,(uint8_t *)"进水电机：关闭");
	}
	if(d==1)
	{
		if(distance<70&&distance>20)
		{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
		Gui_DrawFont_GBK16(16,190,WHITE,BLACK,(uint8_t *)"出水电机：开启");
		}
		if(distance>70)
		{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
			Gui_DrawFont_GBK16(16,190,WHITE,BLACK,(uint8_t *)"出水电机：关闭");
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET);
			Gui_DrawFont_GBK16(16,170,WHITE,BLACK,(uint8_t *)"进水电机：开启");
		}
		if(distance<20)
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
			Gui_DrawFont_GBK16(16,170,WHITE,BLACK,(uint8_t *)"进水电机：关闭");
			d=0;
		}
		
	}
	if(e==0||Read_Temperature()>25)
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
		Gui_DrawFont_GBK16(16,150,WHITE,BLACK,(uint8_t *)"加热棒：关闭");	
	}
	if(e==1||Read_Temperature()<20)
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
		Gui_DrawFont_GBK16(16,150,WHITE,BLACK,(uint8_t *)"加热棒：开启");	
	}
	if(Read_Temperature()>=30)
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
	}
	if(Read_Temperature()<30)
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	}	
	}
	
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_ADC345;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Adc345ClockSelection = RCC_ADC345CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* 发送AT指令 */
//void ESP8266_SendATCommand(char *cmd)
//{
//  HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
//  HAL_UART_Transmit(&huart1, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
//}
///* 接收ESP8266响应 */
//uint8_t ESP8266_ReadResponse(char *response, uint32_t timeout)
//{
//    uint8_t index = 0;
//    uint32_t tickstart = HAL_GetTick();
//    do {
//        if(HAL_UART_Receive(&huart1, (uint8_t *)&response[index], sizeof(char), 0xFF) == HAL_OK) {
//            index++;
//            /* 如果接收到了完整的响应，返回成功 */
//            if(strstr(response, "OK")) {
//                return 1;
//            }
//        }
//    } while((HAL_GetTick() - tickstart) < timeout);  

//    /* 指定时间内未接收到响应，返回失败 */
//    return 0;    
//}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
