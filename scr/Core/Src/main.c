/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#include <stdlib.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

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
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
GPIO_TypeDef *LED_PORT [12] = {
		LED0_GPIO_Port,
		LED1_GPIO_Port,
		LED2_GPIO_Port,
		LED3_GPIO_Port,
		LED4_GPIO_Port,
		LED5_GPIO_Port,
		LED6_GPIO_Port,
		LED7_GPIO_Port,
		LED8_GPIO_Port,
		LED9_GPIO_Port,
		LED10_GPIO_Port,
		LED11_GPIO_Port
};
uint16_t LED_Pin[12] ={
		LED0_Pin,
		LED1_Pin,
		LED2_Pin,
		LED3_Pin,
		LED4_Pin,
		LED5_Pin,
		LED6_Pin,
		LED7_Pin,
		LED8_Pin,
		LED9_Pin,
		LED10_Pin,
		LED11_Pin
};
GPIO_PinState LED_state[4][12] = {
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0}
};

void set_led (const GPIO_PinState *state){
	for (int i =0; i< 12; i++){
		HAL_GPIO_WritePin(LED_PORT[i], LED_Pin[i], state[i]);
	}
}

//code led 7 doan
GPIO_TypeDef *SEG_PORT [14] = {
		SEG0_GPIO_Port,
		SEG1_GPIO_Port,
		SEG2_GPIO_Port,
		SEG3_GPIO_Port,
		SEG4_GPIO_Port,
		SEG5_GPIO_Port,
		SEG6_GPIO_Port,
		SEG7_GPIO_Port,
		SEG8_GPIO_Port,
		SEG9_GPIO_Port,
		SEG10_GPIO_Port,
		SEG11_GPIO_Port,
		SEG12_GPIO_Port,
		SEG13_GPIO_Port
};

uint16_t SEG_Pin[14] ={
		SEG0_Pin,
		SEG1_Pin,
		SEG2_Pin,
		SEG3_Pin,
		SEG4_Pin,
		SEG5_Pin,
		SEG6_Pin,
		SEG7_Pin,
		SEG8_Pin,
		SEG9_Pin,
		SEG10_Pin,
		SEG11_Pin,
		SEG12_Pin,
		SEG13_Pin
};


GPIO_PinState SEG_state[10][7] = {
    // a, b, c, d, e, f, g
    {0, 0, 0, 0, 0, 0, 1}, // 0
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 1, 1, 1, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 1, 0, 0}  // 9
};
void set_led_7_x (const GPIO_PinState *state){
	for (int i =0; i< 7; i++){
		HAL_GPIO_WritePin(SEG_PORT[i], SEG_Pin[i], state[i]);
	}
}
void display7seg_x(int num) {
    if (num >= 0 && num <= 9) {
        set_led_7_x(SEG_state[num]);
    }
}


void set_led_7_y (const GPIO_PinState *state){
	for (int i =0; i< 7; i++){
		HAL_GPIO_WritePin(SEG_PORT[i+7], SEG_Pin[i+7], state[i]);
	}
}
void display7seg_y(int num) {
    if (num >= 0 && num <= 9) {
        set_led_7_y(SEG_state[num]);
    }
}



// ====================QUEUE===========================
enum color{red, yellow, green};

typedef struct NODE {
    int type;
    int max_time;
    int remaining_time;
} NODE;


typedef struct queue_node {
    NODE data;
    struct queue_node *next;
} queue_node;

typedef struct queue {
    queue_node *front, *rear;
    int size;
} queue;



void initQueue(queue *q) {
    q->front = q->rear = NULL;
    q->size = 0;
}


int isEmpty(queue *q) {
    return (q->size == 0);
}


void enqueue(queue *q, NODE value) {
    queue_node *temp = (queue_node*)malloc(sizeof(queue_node));
    if (!temp) {
        return;
    }
    temp->data = value;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->size++;
}


int dequeue(queue *q, NODE *out) {
    if (isEmpty(q)) {
        return 0;
    }

    queue_node *temp = q->front;
    *out = temp->data;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    q->size--;
    return 1;
}


NODE peek(queue *q) {
    NODE err = {-1, -1, -1};
    if (isEmpty(q)) return err;
    return q->front->data;
}


//================================
#define RED_X 5
#define YELLOW_X 3
#define GREEN_X 4

#define RED_Y 7
#define YELLOW_Y 2
#define GREEN_Y 3
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */



int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	queue q1, q2;
	initQueue(&q1);
	initQueue(&q2);

	NODE a1 = { red, RED_X, RED_X };
	NODE b1 = { yellow, YELLOW_X, YELLOW_X };
	NODE c1 = { green, GREEN_X, GREEN_X };
	enqueue(&q1, a1);
	enqueue(&q1, c1);
	enqueue(&q1, b1);


	NODE a2 = { red, RED_Y, RED_Y };
	NODE b2 = { yellow, YELLOW_Y, YELLOW_Y };
	NODE c2 = { green, GREEN_Y, GREEN_Y };
	enqueue(&q2, c2);
	enqueue(&q2, b2);
	enqueue(&q2, a2);


  while (1)
  {
	  queue_node *h1 = q1.front;
	  queue_node *h2 = q2.front;



	  if (h1->data.remaining_time <= 0) {
		NODE done;
		dequeue(&q1, &done);
		done.remaining_time = done.max_time;
		enqueue(&q1, done);
		h1 = q1.front;
	  }

	  if (h2->data.remaining_time <= 0) {
		NODE done;
		dequeue(&q2, &done);
		done.remaining_time = done.max_time;
		enqueue(&q2, done);
		h2 = q2.front;
	  }


	  if      (h1->data.type == green  	&& h2->data.type == red) 	 set_led(LED_state[0]);
	  else if (h1->data.type == yellow  && h2->data.type == red)     set_led(LED_state[1]);
	  else if (h1->data.type == red     && h2->data.type == green)   set_led(LED_state[2]);
	  else if (h1->data.type == red     && h2->data.type == yellow)  set_led(LED_state[3]);



	  if (h1->data.remaining_time > 0) {
		  display7seg_y(h1->data.remaining_time);
		  h1->data.remaining_time--;
	  }
	  if (h2->data.remaining_time > 0) {
		  display7seg_x(h2->data.remaining_time);
		  h2->data.remaining_time--;
	  }

	  HAL_Delay(1000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin
                          |LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin
                          |LED8_Pin|LED9_Pin|LED10_Pin|LED11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG10_Pin
                          |SEG11_Pin|SEG12_Pin|SEG13_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|SEG7_Pin
                          |SEG8_Pin|SEG9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED0_Pin LED1_Pin LED2_Pin LED3_Pin
                           LED4_Pin LED5_Pin LED6_Pin LED7_Pin
                           LED8_Pin LED9_Pin LED10_Pin LED11_Pin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin
                          |LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin
                          |LED8_Pin|LED9_Pin|LED10_Pin|LED11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG10_Pin
                           SEG11_Pin SEG12_Pin SEG13_Pin SEG3_Pin
                           SEG4_Pin SEG5_Pin SEG6_Pin SEG7_Pin
                           SEG8_Pin SEG9_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG10_Pin
                          |SEG11_Pin|SEG12_Pin|SEG13_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|SEG7_Pin
                          |SEG8_Pin|SEG9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//NODE *h1 = queue_peek_ptr(&q1);
	  //NODE *h2 = queue_peek_ptr(&q2)
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
