#include "stm32f4xx.h"

int main()
{
	RCC -> AHB1ENR |= (1U << 0);//enabling GPIOA - Switch
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC - LED
	
	GPIOA -> MODER |= (0U << 12);//configuring GPIOA i/o pin 6 as input"00" - switch connected to A6
	GPIOA -> MODER |= (0U << 13);
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOC i/o pin 14 as output"01" - LED connected to C14
	GPIOC -> MODER |= (0U << 29);
	
	GPIOA -> PUPDR = 0;//reseting the PUPDR register for port A
	GPIOA -> PUPDR |= (1U << 12);//configuring GPIOA i/o pin 14 as pull-up register
	GPIOA -> PUPDR |= (0U << 13);
	
	while(1)
	{
		//comparing wether the IDR - Input Data Register for A6 with the mask
		if(GPIOA -> IDR & (1U << 6))
		{
			GPIOC -> ODR &= (0U << 14);//Turning off the led by setting the ODR - Output Data Register for C14
		}
		else
		{
			GPIOC -> ODR |= (1U << 14);//Turning led the led by setting the ODR - Output Data Register for C14
		}
	}
}