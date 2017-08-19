/*
*
*/
#include "mailbox.h"

void MailboxWrite(unsigned int value, unsigned int channel)
{
	unsigned int write_value;
	
	if(value & 0xF != 0){
		return ;
	}
	
	while((*MAILBOX_STATUS & 0x800000000) != 0){
		;
	}
	
	write_value = value & ~(0xF);
	write_value = value | channel;
	*MAILBOX_WRITE = write_value;	
}

unsigned int MailboxRead(unsigned int channel)
{
	unsigned int value;
	unsigned int read_channel;
	if(channel > 15){
		return 0;
	}
	
	while(1){
		while((*MAILBOX_STATUS & 0x40000000) != 0){
			;
		}
	*GPSET0 = 1 << 16;
		value = *MAILBOX_READ;
		read_channel = value & 0xF;
	
		if(channel == read_channel){
			break;
		}
	}
	
	return (value & 0xFFFFFFF0);
}

