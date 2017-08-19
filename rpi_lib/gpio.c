/*
*
*/

#include "rpi_address.h"
#include "gpio.h"

void InitializeGpio(void){
	int i;
	// pullup all
	*GPPUD 	= 0x02;
	// wait 150 cycle
	for(i=0;i<150;i++){
		// nop
		asm("mov r0,r0");
	}
	*GPPUDCKL0 = 0xffffffff;
	*GPPUDCKL1 = 0xffffffff;
	// wait 150 cycle
	for(i=0;i<150;i++){
		// nop
		asm("mov r0,r0");
	}
	*GPPUDCKL0 = 0;
	*GPPUDCKL1 = 0;

	*GPIFSEL0 = 0;
	*GPIFSEL1 = 0;
	*GPIFSEL2 = 0;
	*GPIFSEL3 = 0;
	*GPIFSEL4 = 0;
	*GPIFSEL5 = 0;
}

void setPullUpDown(unsigned int pin, unsigned int mode)
{
	volatile unsigned int* addr;
	volatile unsigned int i;
	
	 if(pin < 0 || pin > 53){
	 	return;
	 }else if(pin < 32){
	 	addr = GPPUDCKL0;
	 }else{
	 	addr = GPPUDCKL1;
	 }
	 
	 if(mode == PULLDOWN){
	 	*GPPUD = 0x01;
	 }else if(mode == PULLUP){
	 	*GPPUD = 0x02;
	 }else{
	 	return;
	 }
	 
	for(i=0;i<150;i++){
		asm("mov r0,r0");
	}
	*addr = (1 << (pin % 32));
	for(i=0;i<150;i++){
		asm("mov r0,r0");
	}
	*addr = 0;
}

void pinMode(unsigned int pin, unsigned int type)
{
	volatile unsigned int* addr;

	if(pin < 0 || pin > 53){
		return;
	}else if(pin < 10){
		addr = GPIFSEL0;
	}else if(pin < 20){
		addr = GPIFSEL1;
	}else if(pin < 30){
		addr = GPIFSEL2;
	}else if(pin < 40){
		addr = GPIFSEL3;
	}else if(pin < 50){
		addr = GPIFSEL4;
	}else{
		addr = GPIFSEL5;		
	}

	switch(type){
	case INPUT:
		*addr |=  (~(0xFFFFFFFF) & (INPUT << (pin % 10) * 3));
		break;
	case PULLDOWN:
		setPullUpDown(pin, PULLDOWN);
		*addr |=  (~(0xFFFFFFFF) & (INPUT << (pin % 10) * 3));
		break;
	case PULLUP:
		setPullUpDown(pin, PULLUP);
		*addr |=  (~(0xFFFFFFFF) & (INPUT << (pin % 10) * 3));
		break;
	case OUTPUT:
		*addr |= (OUTPUT << (pin % 10) * 3);
		break;
	case ALT0:
		*addr |= (ALT0 << (pin % 10) * 3);
		break;
	case ALT1:
		*addr |= (ALT1 << (pin % 10) * 3);
		break;
	case ALT2:
		*addr |= (ALT2 << (pin % 10) * 3);
		break;
	case ALT3:
		*addr |= (ALT3 << (pin % 10) * 3);
		break;
	case ALT4:
		*addr |= (ALT4 << (pin % 10) * 3);
		break;
	case ALT5:
		*addr |= (ALT5 << (pin % 10) * 3);
		break;
	default:
		break;
	}
	
}

void digitalWrite(unsigned int pin, unsigned int value)
{
	volatile unsigned int* addr;
	
	if(value == HIGH){
		if(pin < 0 || pin > 53){
			return ;
		}else if(pin <= 31){
			addr = GPSET0;
		}else{
			addr = GPSET1;
		}
	}else if(value == LOW){
		if(pin < 0 || pin > 53){
			return ;
		}else if(pin <= 31){
			addr = GPCLR0;
		}else{
			addr = GPCLR1;
		}
	}	
	
	*addr |= (1 << (pin % 32)); 
}

int digitalRead(unsigned int pin)
{
	volatile unsigned int* addr;
	volatile unsigned int mask;

	if(pin < 0 || pin > 53){
		return -1;
	}else if(pin <= 31){
		addr = GPLEV0;
	}else{
		addr = GPLEV1;
	}

	mask = 1 << (pin % 32);
	if((*addr & mask) != 0){
		return HIGH;
	}
	return LOW;
}


