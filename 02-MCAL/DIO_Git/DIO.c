/*
 * DIO.c
 *
 * Created: 1/2/2022 4:56:25 PM
 *  Author: No. 01
 */ 
#include "../../01-LIB/STD_types.h"
#include "../../01-LIB/Registers.h"
#include "DIO.h"


void DIO_init(ST_DIO_config_t* configurations)   
{
	switch(configurations->PORT)
	{
		case 'A':
			if(OUTPUT==configurations->DDRx) //set bit high if OUTPUT
			{
				PORTA_DIR|=HIGH<<configurations->Px;
			}
			else //clear bit (low) if INPUT
			{
				PORTA_DIR&=~(HIGH<<configurations->Px);
			}
			break;
		case 'B':
			if(OUTPUT==configurations->DDRx)
			{
				PORTB_DIR|=HIGH<<configurations->Px;
			}
			else
			{
				PORTB_DIR&=~(HIGH<<configurations->Px);
			}
			break;
		case 'C':
			if(OUTPUT==configurations->DDRx)
			{
				PORTC_DIR|=HIGH<<configurations->Px;
			}
			else
			{
				PORTC_DIR&=~(HIGH<<configurations->Px);
			}
			break;
		case 'D':
			if(OUTPUT==configurations->DDRx)
			{
				PORTD_DIR|=HIGH<<configurations->Px;
			}
			else
			{
				PORTD_DIR&=~(HIGH<<configurations->Px);
			}
			break;
		default:
			break; //invalid config
	}
	
}
void DIO_port(uint8_t port, uint8_t data)
{
	EN_pins EN_counter;
	uint8_t u8_pinData;
	for(EN_counter=P0;EN_counter<=P7;EN_counter++)
	{
		u8_pinData=((data&(HIGH<<EN_counter))>>EN_counter);
		DIO_write(port,EN_counter,u8_pinData);
	}
}

void DIO_write(uint8_t port, EN_pins pin, uint8_t data)
{
	switch(port)
	{
		case 'A':
		if(HIGH==data)
		{
			PORTA_DATA|=HIGH<<pin;	//Set bit if data is high
		}
		else
		{
			PORTA_DATA&=~(HIGH<<pin);	//Clear bit if data is low
		}
		break;
		case 'B':
		if(HIGH==data)
		{
			PORTB_DATA|=HIGH<<pin;
		}
		else
		{
			PORTB_DATA&=~(HIGH<<pin);
		}
		break;
		case 'C':
		if(HIGH==data)
		{
			PORTC_DATA|=HIGH<<pin;
		}
		else
		{
			PORTC_DATA&=~(HIGH<<pin);
		}
		break;
		case 'D':
		if(HIGH==data)
		{
			PORTD_DATA|=HIGH<<pin;
		}
		else
		{
			PORTD_DATA&=~(HIGH<<pin);
		}
		break;
		default:
		break; //invalid config
	}
}
void DIO_read(uint8_t port, EN_pins pin, uint8_t *data)
{
	switch(port)
	{
		case 'A':
		*data=(PORTA_STATUS&(HIGH<<pin))>>pin;	//place bit in data
		break;
		case 'B':
		*data=((PORTB_STATUS&(HIGH<<pin))>>pin);
		break;
		case 'C':
		*data=(PORTC_STATUS&(HIGH<<pin))>>pin;
		break;
		case 'D':
		*data=(PORTD_STATUS&(HIGH<<pin))>>pin;
		break;
		default:
		break; //invalid config
	}
}
void DIO_toggle(uint8_t port, EN_pins pin)
{
	switch(port)
	{
		case 'A':
		PORTA_DATA=PORTA_DATA^(HIGH<<pin);
		break;
		case 'B':
		PORTB_DATA=PORTB_DATA^(HIGH<<pin);
		break;
		case 'C':
		PORTC_DATA=PORTC_DATA^(HIGH<<pin);		
		break;
		case 'D':
		PORTD_DATA=PORTD_DATA^(HIGH<<pin);
		break;
		default:
		break; //invalid config
	}
}