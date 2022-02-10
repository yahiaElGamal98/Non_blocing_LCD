/*
 * LCD_implementation.c
 *
 * Created: 2/10/2022 9:15:50 AM
 *  Author: No. 01
 */ 
#define F_CPU 8000000UL
#include "../../01-LIB/STD_types.h"
#include "../../02-MCAL/DIO_git/DIO.h"
#include "../../02-MCAL/TIMERS_Git/TIMERS.h"
#include <util/delay.h>
#include "Config.h"
#include "LCD_interface.h"


/**LCD PINS CONFIGURATIONS USING DIO**/
ST_DIO_config_t ST_LCD_RS_config = {LCD_PORT,LCD_RS_PIN,OUTPUT};
ST_DIO_config_t ST_LCD_RW_config = {LCD_PORT,LCD_RW_PIN,OUTPUT};
ST_DIO_config_t ST_LCD_E_config = {LCD_PORT,LCD_ENABLE_PIN,OUTPUT};
ST_DIO_config_t ST_LCD_D4_config = {LCD_PORT,LCD_D4_PIN,OUTPUT};
ST_DIO_config_t ST_LCD_D5_config = {LCD_PORT,LCD_D5_PIN,OUTPUT};
ST_DIO_config_t ST_LCD_D6_config = {LCD_PORT,LCD_D6_PIN,OUTPUT};
ST_DIO_config_t ST_LCD_D7_config = {LCD_PORT,LCD_D7_PIN,OUTPUT};
	
EN_LCD_state_t LCD_init(void)
{
	static EN_TIMER_state_t EN_TIMER_currentState;
	static EN_LCD_state_t EN_LCD_currentState=LCD_initDelayWait;
	if(LCD_initDelayWait==EN_LCD_currentState)
	{
		DIO_init(&ST_LCD_RW_config);
		DIO_init(&ST_LCD_RS_config);
		DIO_init(&ST_LCD_E_config);
		DIO_init(&ST_LCD_D4_config);
		DIO_init(&ST_LCD_D5_config);
		DIO_init(&ST_LCD_D6_config);
		DIO_init(&ST_LCD_D7_config);
		/*Awaiting LCD to settle*/
		EN_TIMER_currentState=TIMER2_msDelay(50);
		if(EN_TIMER_OK==EN_TIMER_currentState)
		{
			EN_LCD_currentState=LCD_initDelayOK;
		}
	}
	else if(LCD_initDelayOK==EN_LCD_currentState)
	{
		/*Configuring pins as output*/
		
		//LCD initializes and awaits an 8 bit instruction, this is to tell it that it will be operating 4 bits
		LCD_sendStartCmd(BIT_MODE);
		_delay_us(250);
		//Initialize starting modes
		LCD_sendCmd(BIT_MODE);
		_delay_us(250);
		LCD_sendCmd(ON_CONTROL);
		_delay_us(250);
		LCD_sendCmd(DISPLAY_CLEAR);
		_delay_us(250);
		LCD_sendCmd(ENTRY_MODE);
		_delay_us(250);
		EN_LCD_currentState=LCD_Done;
	}
	return EN_LCD_currentState;
	
}
void LCD_goToXY(uint8_t line, uint8_t pos)
{
	if(LINE_1==line)
	{
		LCD_sendCmd(HOME_POSITION_LINE_1+pos);
	}
	else if(LINE_2==line)
	{
		LCD_sendCmd(HOME_POSITION_LINE_2+pos);
	}
	
}
void LCD_sendStartCmd(uint8_t u8_cmd)
{
	//send only the high 4 bits and stop so as to tell the LCD we will be working in 4 bit mode
	DIO_port(LCD_PORT,(u8_cmd & 0xF0));
	DIO_write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
	DIO_write(LCD_PORT,LCD_RW_PIN,LOW);
	DIO_write(LCD_PORT,LCD_RS_PIN,LOW);
	_delay_us(1);
	DIO_write(LCD_PORT,LCD_ENABLE_PIN,LOW);
	_delay_us(250);
}
void LCD_sendCmd(uint8_t u8_cmd)
{
	//send high nibble
	DIO_port(LCD_PORT,(u8_cmd & 0xF0));
	DIO_write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
	DIO_write(LCD_PORT,LCD_RW_PIN,LOW);
	DIO_write(LCD_PORT,LCD_RS_PIN,LOW);
	_delay_us(1);
	DIO_write(LCD_PORT,LCD_ENABLE_PIN,LOW);
	_delay_us(250);
	//send low nibble
	DIO_port(LCD_PORT,(u8_cmd <<4));
	DIO_write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
	DIO_write(LCD_PORT,LCD_RW_PIN,LOW);
	DIO_write(LCD_PORT,LCD_RS_PIN,LOW);
	_delay_us(1);
	DIO_write(LCD_PORT,LCD_ENABLE_PIN,LOW);
	_delay_us(250);
}
void LCD_sendChar(uint8_t u8_char)
{
// 	static EN_LCD_state_t EN_LCD_sendState=LCD_sendWait;
// 	if(LCD_sendWait==EN_LCD_sendState||LCD_sendOK==EN_LCD_sendState)
// 	{
		DIO_port(LCD_PORT,(u8_char & 0xF0));
		DIO_write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_write(LCD_PORT,LCD_RW_PIN,LOW);
		DIO_write(LCD_PORT,LCD_RS_PIN,HIGH);
		_delay_us(1);
		DIO_write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		_delay_us(250);
		
		DIO_port(LCD_PORT,(u8_char <<4));
		DIO_write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_write(LCD_PORT,LCD_RW_PIN,LOW);
		DIO_write(LCD_PORT,LCD_RS_PIN,HIGH);
		_delay_us(1);
		DIO_write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		_delay_us(250);
// 		EN_LCD_sendState=LCD_sendOK;
// 	}
}
void LCD_sendStr(sint8_t au8_str[])
{
// 	static EN_LCD_state_t EN_LCD_sendState=LCD_sendWait;
// 	if(LCD_sendWait==EN_LCD_sendState)
// 	{
		uint8_t u8_index=0;
		while(au8_str[u8_index]!='\0')
		{
			LCD_sendChar(au8_str[u8_index]);
			u8_index++;
		}
// 		EN_LCD_sendState=LCD_sendOK;		
// 	}
}