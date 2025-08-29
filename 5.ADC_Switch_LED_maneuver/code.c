#include "stm32f4xx.h"
uint16_t data;

int main()
{
	RCC -> AHB1ENR |= (1U << 0);//enabling GPIOA
	RCC -> AHB1ENR |= (1U << 1);//enabling GPIOB
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC

	GPIOA -> MODER |= (0U << 12);//configuring GPIOA i/o pin 6 as input "00" - Swtich
	GPIOA -> MODER |= (0U << 13);
	
	GPIOA -> PUPDR = 0;//clearing the register
	GPIOA -> PUPDR |= (1U << 12);//configuring A6 as pull-up register for switch
	GPIOA -> PUPDR |= (0U << 13);
	
	GPIOA -> MODER |= (1U << 0);//configuring A0 as analog - Potentiometer
	GPIOA -> MODER |= (1U << 1);
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOA i/o pin 14 as output"01" - LED connected
	GPIOC -> MODER |= (0U << 29);
	
	GPIOB -> MODER |= (1U << 18);//configuring GPIOB i/o pin 9 as output"01" - LED connected
	GPIOB -> MODER |= (0U << 19);
	
	RCC -> APB2ENR |= (1U << 8);//enabling the ADC - "ADC1 EN"
	
	ADC1 -> SMPR2 |= (0U << 0);//configuring SMPR2 - Sampling Time Register - Number of Clock Cycles - 000 for 3CLK
	ADC1 -> SMPR2 |= (0U << 1);//selecting Channel 0 as PA0
	ADC1 -> SMPR2 |= (0U << 2);//Each channel has 3 bits
	
	ADC -> CCR |= (1U << 16);//configuring prescaling factor - CCR - Common Control Register - ADCPRE "01" - frequency divided by 4
	ADC -> CCR |= (0U << 17);
	
	ADC1 -> SQR3 |= (0U << 0);//configuring the SQR - Sequence Register with the binary number of the channel
	ADC1 -> SQR3 |= (0U << 1);
	ADC1 -> SQR3 |= (0U << 2);
	ADC1 -> SQR3 |= (0U << 3);
	ADC1 -> SQR3 |= (0U << 4);
	
	ADC1 -> SQR1 |= (0U << 20);//configuring Length of Conversion - 1 conversion "0000"
	ADC1 -> SQR1 |= (0U << 21);
	ADC1 -> SQR1 |= (0U << 22);
	ADC1 -> SQR1 |= (0U << 23);
	
	ADC1 -> CR2 = 0;//clearing the register
	
	ADC1 -> CR2 |= (1U << 0);//ADCON bit
	while(!(ADC1 -> CR2 & (1U << 0))){}//waiting for complete intialization of ADC
		
	ADC1 -> CR2 |= (1U << 1);//CONT bit- continuous conversion enabled
	ADC1 -> CR2 |= (1U << 30);//SWSTART bit - software start
		
	while(1)
	{
		while(!(ADC1 -> SR & (1U << 1))){}//SR - Status Register consists EOC - End of COnversion flag
		
		data = ADC1 -> DR;
			
		//if data converted is greated than 800 and A6 switch pressed - both LED blinks simultaneously
		if((data > 800) && !(GPIOA -> IDR & (1U << 6)))
		{
			GPIOC -> ODR |= (1U << 14);
			GPIOB -> ODR |= (1U << 9);
			
			for(int i=0 ; i<180000 ; i++){}
				
			GPIOC -> ODR &= ~(1U << 14);
			GPIOB -> ODR &= ~(1U << 9);
				
			for(int i=0 ; i<1800000 ; i++){}
		}
		//if data converted is less than 800 and A6 switch not pressed - both LED blinks simultaneously
		else if((data > 800) && (GPIOA -> IDR & (1U << 6)))
		{
			GPIOC -> ODR |= (1U << 14);
			GPIOB -> ODR &= ~(1U << 9);
			
			for(int i=0 ; i<1800000 ; i++){}
				
			GPIOB -> ODR |= (1U << 9);
			GPIOC -> ODR &= ~(1U << 14);
				
			for(int i=0 ; i<1800000 ; i++){}
		}
		//if switched not pressed and converted value less that 800
		else
		{
			GPIOB -> ODR &= ~(1U << 9);
			GPIOC -> ODR &= ~(1U << 14);
		}
	}
	
}