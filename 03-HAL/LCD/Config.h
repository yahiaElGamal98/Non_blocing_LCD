/*
 * Config.h
 *
 * Created: 1/16/2022 5:03:51 PM
 *  Author: No. 01
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

/*
LCD_D4PORTA.4
- LCD_D5PORTA.5
- LCD_D6PORTA.6
- LCD_D7PORTA.7
CONTROL LINES
- LCD_RSPORTA.1
- LCD_RWPORTA.2
- LCD_EPORTB.3
*/

/*
PORT OPTIONS:
PORT A : 'A'
PORT B : 'B'
PORT C : 'C'
PORT D : 'D'
*/

#define LCD_PORT 'A'

/*    //USE THIS IF THE PINS ARE ON DIFFERENT PORTS
#define LCD_ENABLE_PORT A
#define LCD_RS_PORT A
#define LCD_RW_PORT A
#define LCD_DATA_PORT A
*/
/*

*/

/*
Pin options
P0
P1
P2
P3
P4
P5
P6
P7
*/
#define LCD_RS_PIN P1
#define LCD_RW_PIN P2
#define LCD_ENABLE_PIN P3
#define LCD_D4_PIN P4
#define LCD_D5_PIN P5
#define LCD_D6_PIN P6
#define LCD_D7_PIN P7
/*
Port options:
PORTA_DATA
PORTB_DATA
PORTC_DATA
PORTD_DATA
*/
#define LCD_DATA PORTA_DATA


#endif /* CONFIG_H_ */