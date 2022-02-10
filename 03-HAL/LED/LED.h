/*
 * LED.h
 *
 * Created: 1/28/2022 4:15:14 PM
 *  Author: No. 01
 */ 


#ifndef LED_H_
#define LED_H_

typedef enum LED
{
	LED0,
	LED1,
	LED2,
	LED3
	}EN_LED;



void LED_init(EN_LED led_num);
void LED_ON(EN_LED);
void LED_OFF(EN_LED);


#endif /* LED_H_ */