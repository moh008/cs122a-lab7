/*
 * moh008_lab7_part2.c
 * Exercise Lab7 part2 (Microcontroller 1 sends light value to Raspberry Pi)
 * Created: 2019-11-07 오후 11:33:19
 * Author : Lincoln
 */ 

#include <avr/io.h>
#include "spi.h"

void ADC_init()
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;

	unsigned short newLightValue = 0x00;

	ADC_init();
	SPI_ServantInit();
	
	while (1) 
    {
		newLightValue = ADC;
		
		if(SPDR == 0x10)
		{
			SPI_Transmit(newLightValue);
		}
	}
}