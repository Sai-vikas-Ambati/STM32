#include "stm32f4xx.h"

int main()
{
	RCC -> AHB1ENR |= (1U << 0);//enabling GPIOA 
	RCC -> AHB1ENR |= (1U << 1);//enabling GPIOB 
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC
	
	GPIOA -> MODER |= (0U << 12);//configuring GPIOA i/o pin 6 as input"00" - switch connected to A6
	GPIOA -> MODER |= (0U << 13);
	
	GPIOB -> MODER |= (0U << 20);//configuring GPIOB i/o pin 10 as input"00" - switch connected to B10
	GPIOB -> MODER |= (0U << 21);
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOC i/o pin 14 as output"01" - LED connected to C14
	GPIOC -> MODER |= (0U << 29);
	
	GPIOB -> MODER |= (1U << 18);//configuring GPIOB i/o pin 14 as output"01" - LED connected to B9
	GPIOB -> MODER |= (0U << 19);
	
	GPIOA -> PUPDR = 0;//clearing the bits
	GPIOA -> PUPDR |= (1U << 12);//configuring GPIOA i/o pin 14 as pull-up register
	GPIOA -> PUPDR |= (0U << 13);
	
	GPIOB -> PUPDR = 0;//clearing the bits
	GPIOB -> PUPDR |= (1U << 20);//configuring GPIOB i/o pin 9 as pull-up register
	GPIOB -> PUPDR |= (0U << 21);
	
	while(1)
	{
		//both leds will blink simultaneously
		if (!(GPIOA -> IDR & (1U << 6)) && (GPIOB -> IDR & (1U << 10)))
		{
			GPIOC -> ODR |= (1U << 14);
			GPIOB -> ODR |= (1U << 9);
			
			for(int i=0 ; i<180000 ; i++){}
				
			GPIOC -> ODR &= ~(1U << 14);
			GPIOB -> ODR &= ~(1U << 9);
				
			for(int i=0 ; i<180000 ; i++){}
		}
		
		//leds blink alternatively
		else if((GPIOA -> IDR & (1U << 6)) && !(GPIOB -> IDR & (1U << 10)))
		{
			GPIOC -> ODR |= (1U << 14);
			GPIOB -> ODR &= ~(1U << 9);
			
			for(int i=0 ; i<180000 ; i++){}
				
			GPIOB -> ODR |= (1U << 9);
			GPIOC -> ODR &= ~(1U << 14);
				
			for(int i=0 ; i<180000 ; i++){}
		}
	}

}