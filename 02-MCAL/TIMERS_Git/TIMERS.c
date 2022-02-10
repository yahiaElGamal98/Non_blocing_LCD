/*
 * TIMERS.c
 *
 * Created: 1/4/2022 8:23:01 PM
 *  Author: No. 01
 */

#include "TIMERS.h"
#include "Registers.h"

#define NUM_TICKS_PER_MS 1000 //F_CPU(8MHZ)/PRESCALE(8)*1000
uint32_t gu32_T0_neededFlags=0;
uint8_t gu8_T0_initialTicks=0;
uint32_t gu32_T0_interruptCounter=0;
uint8_t gu8_T0_delayFlag=LOW;

uint32_t gu32_T2_neededFlags=0;
uint8_t gu8_T2_initialTicks=0;
uint32_t gu32_T2_interruptCounter=0;
uint8_t gu8_T2_delayFlag=LOW;

void TIMER0_callBack(void(*ISR) (void))
{
	TIMER_0_CALLBACK=ISR;
}
void TIMER2_callBack(void(*ISR) (void))
{
	TIMER_2_CALLBACK=ISR;
}
void __vector_10(void)
{
	if(TIMER_0_CALLBACK!=NULL)
	{
		TIMER_0_CALLBACK();
	}
}
void __vector_5(void)
{
	if(TIMER_2_CALLBACK!=NULL)
	{
		TIMER_2_CALLBACK();
	}
}
void __vector_4(void)
{
	if(TIMER_2_CALLBACK!=NULL)
	{
		TIMER_2_CALLBACK();
	}
}
void __vector_11(void)
{
	if(TIMER_0_CALLBACK!=NULL)
	{
		TIMER_0_CALLBACK();
	}
}

void TIMER_start(ST_TIMER_config_t* configurations,uint8_t ticks)
{
	if(TIMER_0==configurations->timer)
	{
		//initialize prescaling and start timer
		switch(configurations->prescaling)
		{
			case(T0_NO_PRESCALING): TCCR0=T0_NO_PRESCALING;break;
			case(T0_PRESCALING_8): TCCR0=T0_PRESCALING_8;break;
			case(T0_PRESCALING_64): TCCR0=T0_PRESCALING_64;break;
			case(T0_PRESCALING_256): TCCR0=T0_PRESCALING_256;break;
			case(T0_PRESCALING_1024): TCCR0=T0_PRESCALING_1024;break;
			default: break;
		}
		//initialize mode and starting (NORMAL MODE) OR comparing ticks (CTC MODE)
		switch(configurations->mode)
		{
			case(CTC): OCR0=ticks;TCCR0|= HIGH<<3;break;
			case(NORMAL):TCNT0=ticks;break;
			default:break;
		}
	}
	else if(TIMER_2==configurations->timer) //same procedure as above if timer 2 is chosen
	{
		switch(configurations->prescaling)
		{
		case(T2_NO_PRESCALING): TCCR2=T2_NO_PRESCALING;break;
		case(T2_PRESCALING_8): TCCR2=T2_PRESCALING_8;break;
		case(T2_PRESCALING_32): TCCR2=T2_PRESCALING_32;break;
		case(T2_PRESCALING_64): TCCR2=T2_PRESCALING_64;break;
		case(T2_PRESCALING_128): TCCR2=T2_PRESCALING_128;break;
		case(T2_PRESCALING_256): TCCR2=T2_PRESCALING_256;break;
		case(T2_PRESCALING_1024): TCCR2=T2_PRESCALING_1024;break;
		default: break;
	}
	switch(configurations->mode)
	{
		case(CTC): OCR2=ticks;TCCR2|= HIGH<<3;break;
		case(NORMAL):TCNT2=ticks;break;
		default:break;
	}
	}
	
}
EN_TIMER_state_t TIMER0_msDelay(uint32_t u32_msNeeded)
{
	ST_TIMER_config_t ST_TIMER0_Delay_config_t = {TIMER_0,NORMAL,T0_PRESCALING_8};
		
	static EN_TIMER_state_t EN_current_state=EN_TIMER_INITIAL;
	
	uint32_t u32_totalTicks;
	if((EN_TIMER_INITIAL==EN_current_state)||(EN_TIMER_OK==EN_current_state))
	{
		u32_totalTicks= NUM_TICKS_PER_MS*u32_msNeeded;
		gu32_T0_neededFlags=u32_totalTicks/256;
		gu8_T0_initialTicks=u32_totalTicks%256;
		TIMER_start(&ST_TIMER0_Delay_config_t,gu8_T0_initialTicks);
		TIMER_interruptEnable(ST_TIMER0_Delay_config_t.timer,ST_TIMER0_Delay_config_t.mode);
		TIMER0_callBack(TIMER0_interruptFunction);
		EN_current_state=EN_TIMER_WAIT;	
	}
	else if(EN_TIMER_WAIT==EN_current_state)
	{
		if(HIGH==gu8_T0_delayFlag)
		{
			EN_current_state=EN_TIMER_OK;
			TIMER_stop(&ST_TIMER0_Delay_config_t);
			gu8_T0_delayFlag=LOW;
		}
		else
		{
			EN_current_state=EN_TIMER_WAIT;
		}
	}
	return EN_current_state;
}
void TIMER0_interruptFunction(void)
{
		gu32_T0_interruptCounter++;
		if(gu32_T0_interruptCounter==gu32_T0_neededFlags)
		{
			gu8_T0_delayFlag=HIGH;
			gu32_T0_interruptCounter=0;
		}
	
}
EN_TIMER_state_t TIMER2_msDelay(uint32_t u32_msNeeded)
{
	ST_TIMER_config_t ST_TIMER2_Delay_config_t = {TIMER_2,NORMAL,T2_PRESCALING_8};
	
	static EN_TIMER_state_t EN_current_state=EN_TIMER_INITIAL;
	
	uint32_t u32_totalTicks;
	if((EN_TIMER_INITIAL==EN_current_state)||(EN_TIMER_OK==EN_current_state))
	{
		u32_totalTicks= NUM_TICKS_PER_MS*u32_msNeeded;
		gu32_T2_neededFlags=u32_totalTicks/256;
		gu8_T2_initialTicks=u32_totalTicks%256;
		TIMER_start(&ST_TIMER2_Delay_config_t,gu8_T2_initialTicks);
		TIMER_interruptEnable(ST_TIMER2_Delay_config_t.timer,ST_TIMER2_Delay_config_t.mode);
		TIMER2_callBack(TIMER2_interruptFunction);
		EN_current_state=EN_TIMER_WAIT;
	}
	else if(EN_TIMER_WAIT==EN_current_state)
	{
		if(HIGH==gu8_T2_delayFlag)
		{
			EN_current_state=EN_TIMER_OK;
			TIMER_stop(&ST_TIMER2_Delay_config_t);
			gu8_T2_delayFlag=LOW;
		}
		else
		{
			EN_current_state=EN_TIMER_WAIT;
		}
	}
	return EN_current_state;
}
void TIMER2_interruptFunction(void)
{
	gu32_T2_interruptCounter++;
	if(gu32_T2_interruptCounter==gu32_T2_neededFlags)
	{
		gu8_T2_delayFlag=HIGH;
		gu32_T2_interruptCounter=0;
	}
	
}
void TIMER_stop(ST_TIMER_config_t* configurations)
{
	//stop the clock
		if(TIMER_0==configurations->timer)
		{
			TCCR0=LOW;
		}
		else if(TIMER_2==configurations->timer)
		{
			TCCR2=LOW;
		}
}
void TIMER_read(uint8_t timer, uint8_t *value)
{
	//reading values inside the timer data register
	if(TIMER_0==timer)
	{
		*value=TCNT0;
	}
	else if(TIMER_2==timer)
	{
		*value=TCNT2;
	}
	else
	{
		*value=NULL;
	}
}
void TIMER_interruptEnable(uint8_t timer,uint8_t mode)
{
	//enable global interrupts
	SREG|=HIGH<<GLOBAL_INTERRUPT_ENABLE;
	//enable whichever interrupt needed
	if(TIMER_0==timer)
	{
		switch(mode)
		{
			case(NORMAL):TIMSK=HIGH<<NORMAL_TIMER0;
			case(CTC):TIMSK=HIGH<<CTC_TIMER0;
		}
	}
	else if(TIMER_2==timer)
	{
		switch(mode)
		{
			case(NORMAL):TIMSK=HIGH<<NORMAL_TIMER2;
			case(CTC):TIMSK=HIGH<<CTC_TIMER2;
		}
	}
}
void TIMER_readInterruptFlag(ST_TIMER_config_t configurations, uint8_t *val)
{
	if(TIMER_0==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):*val=(TIFR&(HIGH<<NORMAL_TIMER0))>>NORMAL_TIMER0;
			case(CTC):*val=(TIFR&(HIGH<<CTC_TIMER0))>>CTC_TIMER0;
		}
	}
	else if(TIMER_2==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):*val=(TIFR&(HIGH<<NORMAL_TIMER2))>>NORMAL_TIMER2;
			case(CTC):*val=(TIFR&(HIGH<<CTC_TIMER2))>>CTC_TIMER2;
		}
	}
}
void TIMER_clearInterruptFlag(ST_TIMER_config_t configurations)
{
	if(TIMER_0==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):TIFR=HIGH<<NORMAL_TIMER0;
			case(CTC):TIFR=HIGH<<CTC_TIMER0;
		}
	}
	else if(TIMER_2==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):TIFR=HIGH<<NORMAL_TIMER2;
			case(CTC):TIFR=HIGH<<CTC_TIMER2;
		}
	}
}

 
