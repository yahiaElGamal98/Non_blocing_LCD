/*
 * DIO.c
 *
 * Created: 1/2/2022 4:03:15 PM
 * Author : No. 01
 */ 

#include "DIO.h"


int main(void)
{
	uint8_t u8_data;
	volatile uint8_t u8_buttonPressed=0;		//flag  for pressing button
	volatile uint8_t u8_buttonPressedConfidenceLevel=0;	//counter to remove bouncing on pushing the button
	volatile uint8_t u8_buttonReleasedConfidenceLevel=0;	//counter to remove bouncing on releasing the button
	volatile uint8_t u8_confidenceThreshold = 200;		//number of ticks to block the toggling for
	
	ST_DIO_config_t ST_configLED={'B',P4,OUTPUT};		//configuration struct for LED
	ST_DIO_config_t ST_configPB={'B',P2,INPUT};	//configuration struct for Push Button.

	DIO_init(&ST_configLED);	//initialize LED
	DIO_init(&ST_configPB);	//initialize PushButton 
    /* Replace with your application code */
    while (1) 
    {
		DIO_read('B',P2,&u8_data);	//read the switch and place the bit in data
		if(HIGH==u8_data)
		{
			if(u8_buttonPressed==0)
			{
				if(u8_buttonPressedConfidenceLevel>u8_confidenceThreshold)
				{
					DIO_toggle('B',P4);		//Toggle the LED 
					u8_buttonPressed=1;	//set flag
				}
				else  //Burn through these counts till it reaches 200 counts (remove the bouncing and make sure the button is pressed)
				{
					u8_buttonPressedConfidenceLevel++;
					u8_buttonReleasedConfidenceLevel=0;
				}
			}
		}
		else
		{
			if(u8_buttonReleasedConfidenceLevel>u8_confidenceThreshold)
			{
				u8_buttonPressed=0;	//clear flag
			}
			else	///Burn through these counts till it reaches 200 counts (remove the bouncing and make sure the button is released)
			{
				u8_buttonReleasedConfidenceLevel++;
				u8_buttonPressedConfidenceLevel=0;
			}
		}
		
				
    }
}

