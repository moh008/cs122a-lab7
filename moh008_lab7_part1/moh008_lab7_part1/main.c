/*
 * moh008_lab7_part1.c
 * Exercise Lab7 part1 (Microcontroller 1 sends light value to Raspberry Pi)
 * Created: 2019-11-07 오후 1:42:00
 * Author : Lincoln
 */ 

#include <avr/io.h>
#include "spi.h"
#include <time.h>

void ADC_init()
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void)
{
	ADC_init();
	SPI_ServantInit();
	
	unsigned char newLightValue = 0x00;
	
	while (1) 
    {
		ADC = (newLightValue >> 2);
		newLightValue = ADC;
		SPI_Transmit(newLightValue);
    }
}