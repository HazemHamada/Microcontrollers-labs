#include "tm4c123gh6pm.h"
#include "Port_INIT.h"

void PORTB_init (){
	
	unsigned int delay;
	SYSCTL_RCGC2_R |= (1U << 1);
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_LOCK_R = 0x4c4f434b;
	GPIO_PORTB_CR_R = 0xff;
	GPIO_PORTB_DIR_R |= 0xff;
	GPIO_PORTB_DEN_R |= 0xff;
	
}

void PORTF_init (){
	
	unsigned int delay;
	SYSCTL_RCGC2_R |= (1U << 5);
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTF_LOCK_R = 0x4c4f434b;
	GPIO_PORTF_CR_R = 0x1f;
	GPIO_PORTF_PUR_R |= (sw1 | sw2);
	GPIO_PORTF_DIR_R |= 0x0e;
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_DEN_R |= 0x1f;
	
}

void PORTA_init(void){//colomns_input

        unsigned int delay;
	SYSCTL_RCGC2_R |= (1U << 0);
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTA_LOCK_R = 0x4c4f434b;
	GPIO_PORTA_CR_R = 0x1f;  
  

        SYSCTL_RCGCGPIO_R|=(c1|c2|c3|c4) ;
        GPIO_PORTA_PUR_R |=(c1|c2|c3|c4) ;
	GPIO_PORTA_DIR_R &=~(c1|c2|c3|c4) ;
	GPIO_PORTA_DEN_R |=(c1|c2|c3|c4) ;

}

void PORTD_init(void){//rows_output
    
        unsigned int delay;
	SYSCTL_RCGC2_R |= (1U << 3);
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTD_LOCK_R = 0x4c4f434b;
	GPIO_PORTD_CR_R = 0x1f;  
  
  
        SYSCTL_RCGCGPIO_R|=(r1|r2|r3|r4) ;
        GPIO_PORTD_ODR_R |=(r1|r2|r3|r4) ;
	GPIO_PORTD_DIR_R |=(r1|r2|r3|r4) ;
	GPIO_PORTD_DEN_R |=(r1|r2|r3|r4) ;
  
}

