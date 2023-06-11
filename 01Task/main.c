#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f407xx.h"

static void task1_handler(void* parameters);
static void task2_handler(void* parameters);
static void init_led(void);
GPIO_Handle_t GpioLed,GpioLed1;

int main(void)
{

  BaseType_t check1,check2;
  TaskHandle_t task1_handle;
  TaskHandle_t task2_handle;
  
  init_led();

  check1 = xTaskCreate(task1_handler, "Task-1", 200, "I am Task-1", 2, &task1_handle);
  configASSERT(check1 == pdPASS);

  check2 = xTaskCreate(task2_handler, "Task-2", 200, "I am Task-2", 2, &task2_handle);
  configASSERT(check2 == pdPASS);

  vTaskStartScheduler();

  while (1) 
  {
  } 
}
static void task1_handler(void* parameters)
{
	while(1)
	{
          GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
          vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}


static void task2_handler(void* parameters)
{
	while(1)
	{
          GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
          vTaskDelay(2000/portTICK_PERIOD_MS);
	}
}
static void init_led(void)
{
  // this is led gpio configuration
    GpioLed.pGPIOx = GPIOD;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&GpioLed);
    
    GpioLed1.pGPIOx = GPIOD;
    GpioLed1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GpioLed1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    GpioLed1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&GpioLed1);
}