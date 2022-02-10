/*
 * DIO.h
 *
 * Created: 1/2/2022 4:39:05 PM
 *  Author: No. 01
 */ 


#ifndef DIO_H_
#define DIO_H_

#define HIGH 1     //HIGH MACRO set bit (1)
#define LOW 0      //LOW MACRO set bit (0)

typedef enum DIR //enum for direction  either input (0) or output (1)
{
	INPUT=0,	//INPUT LOW	
	OUTPUT=1	//OUTPUT HIGH
}EN_Dir;


typedef enum PINS //enum for pins bit 0 to 7
{
	P0=0,	
	P1,
	P2,
	P3,
	P4,
	P5,
	P6,
	P7
}EN_pins;


typedef struct ST_DIO_config_t	//struct for DIO configuration of needed pin 
{
	uint8_t PORT;	//takes (PORT as 'A', 'B','C','D')
	EN_pins Px;		//takes (PINS as Enum P0, P1....,P7)
	EN_Dir DDRx;	//takes (DIR as Enum INPUT or OUTPUT)
	
}ST_DIO_config_t;

void DIO_init(ST_DIO_config_t* configurations);		//takes configuration and initializes the pin
void DIO_write(uint8_t port, EN_pins pin, uint8_t data);	//writes 'data' on needed 'pin' located in 'port'
void DIO_port(uint8_t port, uint8_t data);
void DIO_read(uint8_t port, EN_pins pin, uint8_t *data);	//reads data and loads it in the last argument '*data' (pointer)
void DIO_toggle(uint8_t port, EN_pins pin);		//toggles the needed 'pin' located in 'port'




#endif /* DIO_H_ */