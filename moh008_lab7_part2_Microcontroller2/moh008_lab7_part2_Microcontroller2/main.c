/*
 * moh008_lab7_part2_Microcontroller2.c
 *
 * Created: 2019-11-07 오후 11:36:30
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
	
	unsigned char avg = 0;
	unsigned char cur = 0;
	
	unsigned char avg_hundred = 0;
	unsigned char avg_ten = 0;
	unsigned char avg_one = 0;
	
	unsigned char cur_hundred = 0;
	unsigned char cur_ten = 0;
	unsigned char cur_one = 0;
	
	SPI_ServantInit();
	LCD_init();
	LCD_ClearScreen();
	TimerOn();
	TimerSet(500);
	
    while (1)
    {
		if(avg_cur)
		{
			avg = tmpSPDR;
		}
		else if(!avg_cur)
		{
			cur = tmpSPDR;
		}
		avg_hundred = avg/100;
		avg_ten = avg / 10;
		avg_ten = avg_ten % 10;
		avg_one = avg % 10;
		
		cur_hundred = cur/100;
		cur_ten = cur/10;
		cur_ten = cur_ten % 10;
		cur_one = cur % 10;
		
		LCD_DisplayString(1, "Avg:            Cur:");
		LCD_Cursor(5);
		LCD_WriteData(avg_hundred+'0');
		LCD_Cursor(6);
		LCD_WriteData(avg_ten+'0');
		LCD_Cursor(7);
		LCD_WriteData(avg_one+'0');
		
		LCD_Cursor(21);
		LCD_WriteData(cur_hundred+'0');
		LCD_Cursor(22);
		LCD_WriteData(cur_ten+'0');
		LCD_Cursor(23);
		LCD_WriteData(cur_one+'0');
		
		while(!TimerFlag){}
			TimerFlag = 0;
    }
	return 0;
}

