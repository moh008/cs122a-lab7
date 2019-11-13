/*
 * moh008_lab7_part1_Microcontroller2.c
 *
 * Created: 2019-11-07 오후 2:37:00
 * Author : Lincoln
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "timer.h"
#include "spi.h"

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	
	SPI_ServantInit();
	LCD_init();
	
	unsigned char hundred = 0;
	unsigned char ten = 0;
	unsigned char one = 0;
	
	TimerOn();
	TimerSet(300);
	
    while (1)
    {
		hundred = SPDR/100;
		ten = SPDR / 10;
		ten = ten % 10;
		one = SPDR % 10;
		
		LCD_DisplayString(1, "Avg: ");
		LCD_Cursor(5);
		LCD_WriteData(hundred+'0');
		LCD_Cursor(6);
		LCD_WriteData(ten+'0');
		LCD_Cursor(7);
		LCD_WriteData(one+'0');
		while(!TimerFlag){}
			TimerFlag = 0;
    }
	return 0;
}

