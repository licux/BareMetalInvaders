/*
*
*/
#ifndef __MAILBOX_H__
#define __MAILBOX_H__

#include "rpi_address.h"

void MailboxWrite(unsigned int value, unsigned int channel);
unsigned int MailboxRead(unsigned int channel);

#endif
