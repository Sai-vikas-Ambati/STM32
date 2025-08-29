#include "stm32f4xx.h"

int main()
{
	RCC -> AHB1ENR |= (1U << 0);//enabling GPIOA
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC
	RCC -> AHB1ENR |= (1U << 1);//enabling GPIOB
	
	GPIOA -> MODER |= (0U << 12);//configuring GPIOA i/o pin 6 as input"00" - Switch/interrupt
	GPIOA -> MODER |= (0U << 13);
	
	GPIOA -> PUPDR = 0;//clearing bits
	GPIOA -> PUPDR |= (1U << 12);//configuring A6 as pull-up register"01"
	GPIOA -> PUPDR |= (0U << 13);
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOC i/o pin 14 as ouput"01" - LED1
	GPIOC -> MODER |= (0U << 29);
	
	GPIOB -> MODER |= (1U << 18);//configuring GPIOB i/o pin 9 as output"01" - LED2
	GPIOB -> MODER |= (0U << 19);
	
	RCC -> APB2ENR |= (1U << 14);//enabling SYSCFG 
	
	SYSCFG -> EXTICR[1] |= (0U << 8);//configuring EXTICR - External Interrupt Configuration Register to Port A
	SYSCFG -> EXTICR[1] |= (0U << 9);
	SYSCFG -> EXTICR[1] |= (0U << 10);
	SYSCFG -> EXTICR[1] |= (0U << 11);
	
	EXTI -> IMR |= (1U << 6);//configuring IMR - Interrupt Mask Register - unmask specific interrupt channel
	
	EXTI -> FTSR |= (1U << 6);//configuring FTSR - Falling Trigger Selection Register - switch is pull-up
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);//calling interrupt function - NVIC - Nested Vector Interrupt Controller
	
	while(1)
	{
		GPIOB -> ODR |= (1U << 9);//turning on LED at B9
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI -> PR & (1U << 6))
	{
		GPIOB -> ODR &= ~(1U << 9);//turning Off LED at B9 when interrupt called
		GPIOC -> ODR |= (1U << 14);//turning on LED at C14
	}
}