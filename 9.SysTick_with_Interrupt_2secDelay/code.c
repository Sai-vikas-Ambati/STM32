#include "stm32f4xx.h"
int count = 0;//counter variable

int main()
{
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOC i/o pin 14 as output"01" - LED
	GPIOC -> MODER |= (0U << 29);
	
	SysTick -> LOAD = 16000000 - 1;
	SysTick -> VAL = 0;
	SysTick -> CTRL |= (1U << 0);//Enable
	SysTick -> CTRL |= (1U << 1);//TickInt - with Interrupt
	SysTick -> CTRL |= (1U << 2);//Clock Source
	
	while(1){}
}

//Turning on LED after every Two seconds
void SysTick_Handler(void)
{
	count++;
	if(count == 2)
	{
		GPIOC -> ODR ^= (1U << 14);//turning ON the LED
		count = 0;
	}
}