#ifndef SPI_H
#define SPI_H

unsigned char tmpSPDR;

#include <avr/interrupt.h>
#include <avr/io.h>

unsigned char tmpSPDR = 0x00;

void SPI_ServantInit(void)
{
	// set DDRB to have MISO Line as output and MOSI, SCK, and SS as input
	DDRB = (1<<PINB6);
	// set SPCR register to enable SPI and enable SPI interrupt
	SPCR = (1<<SPE) | (1<<SPIE);
	// make sure global interrupts are enabled on SREG register
	SREG = 0x80;
}

void SPI_Transmit(unsigned char cData)
{
	SPDR = cData; //which line to transmit? servant photoresistor
	while(!(SPSR &(1<<SPIF)));	//wait for tansmission to complete
}

unsigned char avg_cur = 0;
ISR(SPI_STC_vect)
{
	tmpSPDR = SPDR;
	
	if(tmpSPDR == 0x40)
	{
		avg_cur = 1;
	}
	else if(tmpSPDR == 0x20)
	{
		avg_cur = 0;
	}
}

#endif // SPI_H