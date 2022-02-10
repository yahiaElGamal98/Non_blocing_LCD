/*
 * registers.h
 *
 * Created: 1/2/2022 4:17:35 PM
 *  Author: No. 01
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "STD_types.h"

#define PORTA_DATA (*((volatile uint8_t *)(0x3B)))
#define PORTA_DIR (*((volatile uint8_t *)(0x3A)))
#define PORTA_STATUS (*((volatile uint8_t *)(0x39)))

#define PORTB_DATA (*((volatile uint8_t *)(0x38)))
#define PORTB_DIR (*((volatile uint8_t *)(0x37)))
#define PORTB_STATUS (*((volatile uint8_t *)(0x36)))

#define PORTC_DATA (*((volatile uint8_t *)(0x35)))
#define PORTC_DIR (*((volatile uint8_t *)(0x34)))
#define PORTC_STATUS (*((volatile uint8_t *)(0x33)))

#define PORTD_DATA (*((volatile uint8_t *)(0x32)))
#define PORTD_DIR (*((volatile uint8_t *)(0x31)))
#define PORTD_STATUS (*((volatile uint8_t *)(0x30)))





#endif /* REGISTERS_H_ */