/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "function.h"
#include "LCD.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LENGTH 21


extern uint8_t layer;
extern uint8_t target;
extern uint8_t pattern;
extern uint8_t change;
extern uint8_t func1_part;
extern uint8_t func4_part;


extern char k1,k2,k3;
extern int func3_num;
extern int func4_show;


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern uint8_t uart_dma_temp_rx[LENGTH];
extern uint8_t uart_dma_temp_tx[LENGTH];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

void check_received_data(const uint8_t *data){	
  if (strncmp((const char *)data, "A55AA5A5", 8) == 0){
    //printf("A55AA5A5\r\n");
    // layer = 1;
    // target = 0;
    pattern = 1;
    change = 1;
    k1 = 0;
    k2 = 1;
    k3 = 0;
    return ;
  }
  else
  {

      if (strncmp((const char *)data, "A55A", 4) == 0 && strncmp((const char *)(data + 15), "A5A5", 4) == 0 && strlen((const char *)data) == 19)  
      {
        char number[12];
        strncpy(number, (const char *)(data + 4), 11);
        number[11] = '\0';
        func4_show = 10;
        if (strcmp(number, "20221071019") == 0 ||
            strcmp(number, "20221071473") == 0 ||
            strcmp(number, "20221071345") == 0){
              if(strcmp(number, "20221071019") == 0){
                printf("20221071019\r\n");
                pattern = 3;
                change = 1;
                func3_num = 2;
                return;
              }
              if(strcmp(number, "20221071473") == 0){
                printf("20221071473\r\n");
                pattern = 3;
                change = 1;
                func3_num = 1;
                return;
              }
              if(strcmp(number, "20221071345") == 0){
            printf("20221071345\r\n");
            pattern = 3;
            change = 1;
            func3_num = 3;
            return;
          }
            }
        else{
              printf("Data Format Error!\r\n");
              return;			
            }
        
      }
      
      else
      {
        printf("Data Format Error!\r\n");
        return;
      }	
  }
      	
}

void func3_quit(const uint8_t *data){
  if (strncmp((const char *)data, "exit1", 5) == 0){
    //返回到功能界�?1
    pattern = 1;
    change = 1;
    return ;
  }
  if (strncmp((const char *)data, "exit2", 5) == 0){
    //返回到功能界�?1
    pattern = 2;
    change = 1;
    return ;
  }
}


void func4_ReceiveAndShow(uint8_t *data){
	check_received_data(data);
  func4_show = data[3] - '0';
  change = 1;
  return;
}

// }
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */
	/*
	if (__HAL_DMA_GET_FLAG(&hdma_usart1_rx, DMA_FLAG_TC1))
	{
		__HAL_DMA_CLEAR_FLAG(&hdma_usart1_rx, DMA_FLAG_TC1);
		for(uint8_t i=0;i<LENGTH;i++) uart_dma_temp_tx[i] = uart_dma_temp_rx[i];
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)uart_dma_temp_tx, LENGTH);
	}
	*/
  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel2 global interrupt.
  */
void DMA1_Channel2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_IRQn 0 */

  /* USER CODE END DMA1_Channel2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA1_Channel2_IRQn 1 */

  /* USER CODE END DMA1_Channel2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))  //进入了中�?
  {
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		HAL_UART_DMAStop(&huart1);
		
		uint8_t data_length = LENGTH - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
		
		//printf("CAPP_DMA_TEST is %d\r\n", data_length);
		uart_dma_temp_rx[data_length] = '\0';  // Null-terminate the received data
		
		// if(ifserial == 1){
		// 	check_received_data(uart_dma_temp_rx);
		// }
    printf("Received data: %s\r\n", uart_dma_temp_rx);
    if(pattern == 2){
		  check_received_data(uart_dma_temp_rx);
    }
    if(pattern == 3){
      func3_quit(uart_dma_temp_rx);
    }
    if(pattern == 4){
      func4_ReceiveAndShow(uart_dma_temp_rx);
    }
		
		
		//HAL_UART_Transmit_DMA(&huart1, uart_dma_temp_rx, data_length);
		memset(uart_dma_temp_rx, 0, LENGTH);  // ���DMA������
		/*
		printf("\r\n***TEST***\r\n");
		printf("%s\r\n",(uint8_t*)uart_dma_temp_rx);
		*/
		
		HAL_UART_Receive_DMA(&huart1, (uint8_t*)uart_dma_temp_rx, LENGTH);
		
		
	}
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
