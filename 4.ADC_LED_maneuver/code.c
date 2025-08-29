#include "stm32f4xx.h"
uint16_t data;//adc value is 12bit long
int main()
{
	RCC -> AHB1ENR |= (1U << 0);//enabling GPIOA - Potentiometer
	RCC -> AHB1ENR |= (1U << 2);//enabling GPIOC - LED
	
	RCC -> APB2ENR |= (1U << 8);//enabling the ADC - "ADC1 EN"
	
	GPIOA -> MODER |= (1U << 0);//configuring GPIOA i/o pin 0 as analog"11" - Potentiometer to A0
	GPIOA -> MODER |= (1U << 1);
	
	GPIOC -> MODER |= (1U << 28);//configuring GPIOC i/o pin 14 as output"01" - LED connected
	GPIOC -> MODER |= (0U << 29);
	
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
	
	ADC1 -> CR2 = 0;//clearing the Control Register 2
	
	ADC1 -> CR2 |= (1U << 0);//ADCON bit
	while(!(ADC1 -> CR2 & (1U << 0))){}//waiting for proper intialization of ADC
		
	ADC1 -> CR2 |= (1U << 1);//CONT bit- continuous conversion enabled
	ADC1 -> CR2 |= (1U << 30);//SWSTART bit - software start
		
	while(1)
	{
		while(!(ADC1 -> SR & (1U << 1))){}//SR - Status Register consists EOC - End of COnversion flag
		
		data = ADC1 -> DR;//storing converted value in DR - Data Register to "data" variable
			
		if(data > 500)
		{
			GPIOC -> ODR |= (1U << 14);//turning on the LED - ODR - Output Data Register to 1
		}
		else
		{
			GPIOC -> ODR &= ~(1U << 14);//turning on the LED - ODR - Output Data Register to 1
		}
	}
	
	
	
	
}