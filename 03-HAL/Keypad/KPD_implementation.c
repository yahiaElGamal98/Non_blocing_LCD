/*
 * KPD_implementation.c
 *
 * Created: 1/19/2022 12:48:43 AM
 *  Author: No. 01
 */ 


#include "../../01-LIB/STD_types.h"
#include "../../01-LIB/Registers.h"
#include "../../02-MCAL/DIO_Git/DIO.h"
#include "../../02-MCAL/TIMERS_Git/TIMERS.h"
#include "KPD_config.h"
#include "KPD_Interface.h"

#define KPD_size 6

uint8_t gau8_KPD_keys[3][3]={{'1','2','3'},
{'4','5','6'},
{'7','8','9'}};

// void KPD_msdelay(uint8_t time) //rough delay function using for loops
// {
// 	volatile uint8_t u8_index;
// 	volatile uint16_t u16_index;
// 	for(u8_index=0;u8_index<time;u8_index++)
// 	{
// 		for(u16_index=0; u16_index<450; u16_index++)
// 		{
// 			
// 		}
// 	}
// }
void KPD_init(void)
{
	uint8_t u8_index;	
	//Keypad config struct
	//define the rows as OUTPUT and the columns as INPUT
	ST_DIO_config_t ast_KPD_config[KPD_size]={{KPD_PORT,ROW1,OUTPUT},
	{KPD_PORT,ROW2,OUTPUT},
	{KPD_PORT,ROW3,OUTPUT},
	{KPD_PORT,COL1,INPUT},
	{KPD_PORT,COL2,INPUT},
	{KPD_PORT,COL3,INPUT}};
	//Loop to configure the struct
	for(u8_index=0;u8_index<KPD_size;u8_index++)
	{
		DIO_init(ast_KPD_config+u8_index);
		DIO_write(ast_KPD_config[u8_index].PORT,ast_KPD_config[u8_index].Px,HIGH); //write high on all pins
	}
}
//get value from keypad
EN_KPD_states_t KPD_getVal(uint8_t *val)
{
	static EN_KPD_states_t EN_KPD_currentSate=EN_KPD_NPRESSED;
	static EN_TIMER_state_t EN_TIMER_currentState;
	static EN_pins u8_colIndex=0, u8_rowIndex=0;	//Enum for pins of keypad
	static uint8_t u8_retVal=0;	//variable to store the pin value either high or low
	if(EN_KPD_NPRESSED==EN_KPD_currentSate || EN_KPD_DONE==EN_KPD_currentSate)
	{
		for(u8_rowIndex=ROW1;u8_rowIndex<=ROW3;u8_rowIndex++)
		{
			DIO_write(KPD_PORT,ROW1,HIGH); //write high on all rows
			DIO_write(KPD_PORT,ROW2,HIGH);
			DIO_write(KPD_PORT,ROW3,HIGH);
			DIO_write(KPD_PORT,u8_rowIndex,LOW);	//write low on current row
			for(u8_colIndex=COL1;u8_colIndex<=COL3;u8_colIndex++)
			{
				//check on columns
				//read the column value
				DIO_read(KPD_PORT,u8_colIndex,&u8_retVal);
				//if it is low then the corresponding key is pressed
				if(LOW==u8_retVal)
				{
					EN_KPD_currentSate=EN_KPD_PRESSED;
					return EN_KPD_currentSate;
				}
			}
		}
	}
	
	else if(EN_KPD_PRESSED==EN_KPD_currentSate)
	{
		EN_TIMER_currentState=TIMER0_msDelay(20);
	}
	if(EN_TIMER_currentState==EN_TIMER_OK)
	{
		EN_KPD_currentSate=EN_KPD_DONE;
		*val=gau8_KPD_keys[u8_rowIndex-ROW_OFFSET][u8_colIndex-COL_OFFSET];
	}			
	
	return EN_KPD_currentSate;
}
