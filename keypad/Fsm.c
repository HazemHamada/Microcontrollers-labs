#include "Fsm.h"
#include "tm4c123gh6pm.h"

unsigned long concateSwitchInput(){
	unsigned long reg = GPIO_PORTF_DATA_R; //to get rid of warning from using voltaile pointer directly
	return ((reg & 0x10) >> 3) | (reg & 0x01); 
}