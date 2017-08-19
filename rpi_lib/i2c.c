/*
*
*/

#include <stdio.h>
#include "i2c.h"
#include "rpi_address.h"
#include "gpio.h"
#include "systemtimer.h"

#define ADDR 0x48

volatile unsigned int axis_addr[2] = {0x40, 0x50};

void i2c_init()
{
	pinMode(2, ALT0);
	pinMode(3, ALT0); 
	*BSC1_DIV = 0x177;
}

void i2c_write()
{
	*BSC1_S = S_CLKT | S_ERR | S_DONE;
	*BSC1_A = 0x48;
	*BSC1_C &= ~C_READ;
	*BSC1_C |= C_CLEAR_ALL;
	*BSC1_DLEN = 3;
	
	*BSC1_FIFO = 0x01;
	*BSC1_FIFO = 0xC3;
	*BSC1_FIFO = 0x83;
	
	*BSC1_C |= C_I2CEN | C_ST;
	
	while(!(*BSC1_S & S_DONE)){
		;
	}
		
}

void i2c_read(volatile int* value, char dir)
{	
	*BSC1_S = S_CLKT | S_ERR | S_DONE;
	*BSC1_A = 0x48;
	*BSC1_C &= ~C_READ;
	*BSC1_C |= C_CLEAR_ALL;
	*BSC1_DLEN = 3;
	
	*BSC1_FIFO = 0x01;
	*BSC1_FIFO = 0x83 | axis_addr[dir];
	*BSC1_FIFO = 0x83;
	
	*BSC1_C |= C_I2CEN | C_ST;
	
	while(!(*BSC1_S & S_DONE)){
		;
	}

	*BSC1_C &= ~C_I2CEN;

	*BSC1_S = S_CLKT | S_ERR | S_DONE;
	*BSC1_A = 0x48;
	*BSC1_C &= ~C_READ;
	*BSC1_C |= C_CLEAR_ALL;
	
	*BSC1_DLEN = 1; 
	
	*BSC1_FIFO = 0x00;
	*BSC1_C |= C_I2CEN | C_ST;
	while(!(*BSC1_S & S_DONE)){
		;
	}

	*BSC1_DLEN = 2;
	*BSC1_C |= C_READ;
	*BSC1_C |= C_ST;
	while(!(*BSC1_S & S_DONE)){
	}
	delay_ms(1);	
	
	int temp = 0;
	if(*BSC1_S & S_RXD){
		temp = *BSC1_FIFO;
		*value = (*BSC1_FIFO >> 4);
		*value |= (temp << 8);
	}

	*BSC1_C &= ~C_I2CEN;
}

void i2c_read_temp(volatile int* value)
{	
	*BSC1_S = S_CLKT | S_ERR | S_DONE;
	*BSC1_A = 0x18;
	*BSC1_C &= ~C_READ;
	*BSC1_C |= C_CLEAR_ALL;
	
	*BSC1_DLEN = 1; 
	
	*BSC1_FIFO = 0x05;
	*BSC1_C |= C_I2CEN | C_ST;
	while(!(*BSC1_S & S_DONE)){
		;
	}

	*BSC1_DLEN = 2;
	*BSC1_C |= C_READ;
	*BSC1_C |= C_ST;
	while(!(*BSC1_S & S_DONE)){
		;
	}
	delay_ms(300);	
	
	if(*BSC1_S & S_RXD){
		volatile int hi, low;

		hi = *BSC1_FIFO;
		low = (*BSC1_FIFO >> 4);
		*value = (hi << 8) | low ;
	}
	*BSC1_C &= ~C_I2CEN;
}
