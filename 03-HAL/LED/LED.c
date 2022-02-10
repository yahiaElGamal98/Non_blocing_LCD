/*
 * LED.c
 *
 * Created: 1/28/2022 4:15:27 PM
 *  Author: No. 01
 */ 
#include "../../01-LIB/STD_types.h"
#include "../../01-LIB/Registers.h"
#include "../../02-MCAL/DIO_Git/DIO.h"
#include "LED.h"

ST_DIO_config_t gst_LED0 = {'B',P4,OUTPUT};
ST_DIO_config_t gst_LED1 = {'B',P5,OUTPUT};
ST_DIO_config_t gst_LED2 = {'B',P6,OUTPUT};
ST_DIO_config_t gst_LED3 = {'B',P7,OUTPUT};

void LED_init(EN_LED led_num)
{
	switch(led_num)
	{
		case LED0: DIO_init(&gst_LED0);break;
		case LED1: DIO_init(&gst_LED1);break;
		case LED2: DIO_init(&gst_LED2);break;
		case LED3: DIO_init(&gst_LED3);break;
		default: break;
	}
}
void LED_ON(EN_LED led_num)
{
	switch(led_num)
	{
		case LED0: DIO_write(gst_LED0.PORT,gst_LED0.Px,HIGH);break;
		case LED1: DIO_write(gst_LED1.PORT,gst_LED1.Px,HIGH);break;
		case LED2: DIO_write(gst_LED2.PORT,gst_LED2.Px,HIGH);break;
		case LED3: DIO_write(gst_LED3.PORT,gst_LED3.Px,HIGH);break;
		default: break;
	}
}
void LED_OFF(EN_LED led_num)
{
	switch(led_num)
	{
		case LED0: DIO_write(gst_LED0.PORT,gst_LED0.Px,LOW);break;
		case LED1: DIO_write(gst_LED1.PORT,gst_LED1.Px,LOW);break;
		case LED2: DIO_write(gst_LED2.PORT,gst_LED2.Px,LOW);break;
		case LED3: DIO_write(gst_LED3.PORT,gst_LED3.Px,LOW);break;
		default: break;
	}
}