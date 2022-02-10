/*
 * ADC.c
 *
 * Created: 1/18/2022 4:12:38 PM
 * Author : No. 01
 */ 

#include "01-LIB/STD_types.h"
//#include "03-HAL/Keypad/KPD_Interface.h"
#include "03-HAL/LCD/LCD_interface.h"


int main()
{
// 	uint8_t u8_retVal;
// 	EN_KPD_states_t EN_KPD_currentState;
	EN_LCD_state_t EN_LCD_initCurrentState;
	//uint8_t u8_KPD_val;
	/*KPD_init();*/		/*initialization of keypad */
	/*LCD_init();*/			/* Initialization of LCD */
	//LCD_sendStr("KeyPad button");	/* Write string on 1st line of LCD */
	
	while(1)
	{
		EN_LCD_initCurrentState=LCD_init();
		if(LCD_Done==EN_LCD_initCurrentState)
		{
			LCD_goToXY(LINE_1, 2);
			LCD_sendStr("Yahia ElGamal");
		}
// 		LCD_goToXY(LINE_2,8);	/* LCD16x2 cursor position */
// 		KPD_getVal(&u8_KPD_val);	/*get Keypad value*/
// 		LCD_sendChar(u8_KPD_val); /*Send it to LCD*/
// 		LCD_sendStr("  ");
// 		msdelay(200);
	}
	return 0;

}

