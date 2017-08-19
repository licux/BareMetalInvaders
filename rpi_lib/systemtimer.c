/*
*
*/

#include "rpi_address.h"
#include "systemtimer.h"

/*
* System Timer increments Counter by 1every 1 micro second.
*/
volatile unsigned long long getSysTime()
{
	unsigned long long hi = *SYSTEMTIMER_CHI;
	unsigned int lo = *SYSTEMTIMER_CLO;

	return ((hi << 32) + lo);
}

/*
* This function is assumed for mill second.
*/
void delay_micros(unsigned long long time)
{
	unsigned long long start = getSysTime();
	
	while(time > getSysTime() - start) ;
	
	return ;	
}

/*
* This function is assumed for nano second.
*/
void delay_ms(unsigned int time)
{
	unsigned long long start = getSysTime();
	unsigned long long time_ms = time * 1000;
	
	while(time_ms > getSysTime() - start) ;
	
	return ;	
}
