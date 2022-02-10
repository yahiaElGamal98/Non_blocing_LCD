/*
 * LCD_interface.h
 *
 * Created: 2/10/2022 9:35:04 AM
 *  Author: No. 01
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*MACROS FOR LINE 1 & 2 in the LCD**/
#define LINE_1 0
#define LINE_2 1

typedef enum EN_LCD_state_t
{
	LCD_initDelayWait=0,
	LCD_initDelayOK=1,
	LCD_sendWait=2,
	LCD_sendOK=3,
	LCD_Done=4
}EN_LCD_state_t;

/***LCD COMMANDS***/
#define BIT_MODE ((uint8_t)(0b00101000))	//FUNCTION SET, 4 bit, 2-line display
#define ON_CONTROL ((uint8_t)(0b00001110)) //DISPLAY ON, CURSOR ON, BLINKING OFF
#define DISPLAY_CLEAR ((uint8_t)(0b00000001)) //CLEAR DISPLAY
#define ENTRY_MODE ((uint8_t)(0b00000110))  //INCREMENT CURSOR
#define HOME_POSITION_LINE_1 ((uint8_t)(0b10000000))
#define HOME_POSITION_LINE_2 ((uint8_t)(0b11000000))

//initialize LCD
EN_LCD_state_t LCD_init(void);
//send commands to LCD using 4 bit mode
void LCD_sendCmd(uint8_t u8_cmd);
//special function to send only the highest nibble of command for use in startup ONLY to avoid buggy startup
void LCD_sendStartCmd(uint8_t u8_cmd);
//function to send string to LCD (calls sendChar)
void LCD_sendStr(sint8_t* u8_str);
//function that sends a single character to LCD
void LCD_sendChar(uint8_t u8_char);
//function that sends starting position and line
void LCD_goToXY(uint8_t line, uint8_t pos);
//delay function for usage in the LCD



#endif /* LCD_INTERFACE_H_ */