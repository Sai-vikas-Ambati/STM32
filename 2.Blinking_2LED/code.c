#include "stm32f4xx.h"

int main()
{
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC
	RCC -> AHB1ENR |= (1U << 1);//enabling GPIOB
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOC i/o pin 14 as output"01" - LED connected to C14
	GPIOC -> MODER |= (0U << 29);

	GPIOB -> MODER |= (1U << 18);//configuring GPIOB i/o pin 9 as output"01" - LED connected to B9
	GPIOB -> MODER |= (0U << 19);
	
	while(1)
	{
		GPIOC -> ODR |= (1U << 14);//Turning on the led by setting the ODR - Output Data Register for C14
		GPIOB -> ODR &= ~(1U << 9);//Turning off the led by setting the ODR - Output Data Register for B9
		
		for(int i=0 ; i<100000 ; i++){}
			
		GPIOC -> ODR &= ~(1U << 14);
		GPIOB -> ODR |= (1U << 9);
			
		for(int i=0 ; i<100000 ; i++){}
	}
}