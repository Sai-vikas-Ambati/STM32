#include "stm32f4xx.h"
int data;
int threshold = 1229;
int count = 0;
int main(void)
{
	RCC -> AHB1ENR |= (1U << 0);
	RCC -> AHB1ENR |= (1U << 1);
	
	GPIOA -> MODER |= (0U << 13);
	GPIOA -> MODER |= (0U << 12);
	
	GPIOA -> PUPDR = 0;
	GPIOA -> PUPDR |= (0U << 13);
	GPIOA -> PUPDR |= (1U << 12);
	
	GPIOB -> MODER |= (0U << 21);
	GPIOB -> MODER |= (0U << 20);
	
	GPIOB -> PUPDR = 0;
	GPIOB -> PUPDR |= (0U << 21);
	GPIOB -> PUPDR |= (1U << 20);
	
	GPIOA -> MODER |= (1U << 1);
	GPIOA -> MODER |= (1U << 0);
	
	GPIOB -> MODER |= (0U << 19);
	GPIOB -> MODER |= (1U << 18);
	
	RCC -> APB2ENR |= (1U << 14);
	
	SYSCFG -> EXTICR[1] |= (0U << 11);
	SYSCFG -> EXTICR[1] |= (0U << 10);
	SYSCFG -> EXTICR[1] |= (0U << 9);
	SYSCFG -> EXTICR[1] |= (0U << 8);
	
	SYSCFG -> EXTICR[2] |= (0U << 11);
	SYSCFG -> EXTICR[2] |= (0U << 10);
	SYSCFG -> EXTICR[2] |= (0U << 9);
	SYSCFG -> EXTICR[2] |= (0U << 8);
	
	EXTI -> IMR |= (1U << 6);
	EXTI -> IMR |= (1U << 10);
	
	EXTI -> FTSR |= (1U << 6);
	EXTI -> FTSR |= (1U << 10);
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	RCC -> APB2ENR |= (1U << 8);
	
	ADC1 -> SMPR2 |= (0U << 3);
	ADC1 -> SMPR2 |= (0U << 2);
	ADC1 -> SMPR2 |= (0U << 1);
	
	ADC -> CCR |= (0U << 17);
	ADC -> CCR |= (1U << 16);
	
	ADC1 -> SQR3 |= (0U << 4);
	ADC1 -> SQR3 |= (0U << 3);
	ADC1 -> SQR3 |= (0U << 2);
	ADC1 -> SQR3 |= (0U << 1);
	ADC1 -> SQR3 |= (0U << 0);
	
	ADC1 -> SQR1 |= (0U << 23);
	ADC1 -> SQR1 |= (0U << 22);
	ADC1 -> SQR1 |= (0U << 21);
	ADC1 -> SQR1 |= (0U << 20);
	
	ADC1 -> CR2 = 0;
	
	ADC1 -> CR2 |= (1U << 0);
	
	while( !(ADC1 -> CR2 & (1U << 0)) ){}
	
	while(1)
	{
		
	}
}

void EXTI9_5_IRQHandler(void)
{
	count ++;
	
	if(count%2 != 0) 
	{
		if( EXTI -> PR & (1U << 6))
		{
			EXTI -> PR |= (1U << 6);
		
			SysTick -> LOAD = 16000000-1;
			SysTick -> VAL = 0;
			SysTick -> CTRL = 7;
		}
	}
	else
	{
		GPIOB -> ODR &= ~(1U << 9);
		SysTick -> CTRL = 0;
	}
}

void SysTick_Handler(void)
{
	ADC1 -> CR2 |= (1U << 30);
	while( !(ADC1 -> SR & (1U << 1)) ){}
	data = ADC1 -> DR;
	if(data > threshold)
		{
			GPIOB -> ODR |= (1U << 9);
		}
	else if(data < threshold)
	{
		GPIOB -> ODR &= ~(1U << 9);
	}
}