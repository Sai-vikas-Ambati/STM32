#include "stm32f4xx.h"

int main()
{
	RCC -> AHB1ENR |= (1U << 2); //enabling GPIOC
	
	GPIOC -> MODER |= (1U << 28); //configuring GPIOC -> i/o pin 14 as output"01"
	GPIOC -> MODER |= (0U << 29); //configuring
	
	while(1)
	{
		GPIOC -> ODR |= (1U << 14);//configuring the ODR - Output Data Register as 1 to turn on the led
	}
}