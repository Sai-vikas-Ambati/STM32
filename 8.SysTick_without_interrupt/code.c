#include "stm32f4xx.h"

int main()
{
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOC i/o pin 14 as output"01" - LED
	GPIOC -> MODER |= (0U << 29);
	
	SysTick -> LOAD = 16000000 - 1;//LOAD = (Clock Frequence * Time) - 1
	SysTick -> VAL = 0;
	SysTick -> CTRL |= (1U << 0);//ENABLE
	SysTick -> CTRL |= (0U << 1);//TickInt - without interrupt
	SysTick -> CTRL |= (1U << 2);//Clock Source - no external clock reference
	
	while(1)
	{
		//Checks untill Count Flag is 1 - The times reads 0
		if(SysTick -> CTRL & (1U << 16))
		{
			GPIOC -> ODR ^= (1U << 14);//turning On and Off LED
		}
	}
	
}