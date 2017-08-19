/*
*
*/

#include <string.h>
#include "framebuffer.h"
#include "mailbox.h"
#include "dma.h"

static struct FrameBufferInfo framebuffer __attribute__((aligned(16)))
	= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
volatile unsigned int mb[32] __attribute__ ((aligned(16)));
volatile unsigned int buffer_size;

struct FrameBufferInfo* InitializeFrameBuffer(
								unsigned int width,
								unsigned int height,
								unsigned int bitDepth)
{
	unsigned int mail;
	framebuffer.width = framebuffer.vWidth = width;
	framebuffer.height =  height;
	framebuffer.vHeight = height * 2;
	framebuffer.bitDepth = bitDepth;
	
	// width * height * bit/pixel
	buffer_size = framebuffer.width * framebuffer.height;

	MailboxWrite(((unsigned int)(&framebuffer) | 0x40000000), 1);

	do{
		mail = MailboxRead(1);
	}while(mail != 0);

	mb[0] = 16 * 4;		// Buffer size
    mb[1] = 0;			// Request
    mb[2] = 0x0004800B;	// Tag id - Get physical width/height
    mb[3] = 10*4;		// Buffer size
    mb[4] = 0;			// Request/Response indicator (MSB 0 for request)
    mb[5] = 1;			// offset
    mb[6] = 8;			// length
    mb[7] = 0x0000FF;	// RED
    mb[8] = 0x00FF00;	// GREEN
    mb[9] = 0xFF0000;	// BLUE
    mb[10] = 0x00FFFF;	// YELLOW
    mb[11] = 0xFF6BEF;	// PINK
    mb[12] = 0x65FF95;	// LIGHTGREEN
    mb[13] = 0xFFFF00;	// LIGHTBLUE
    mb[14] = 0xFFFFFF;	// WHITE

    mb[15] = 0;			// End tag

	MailboxWrite(((unsigned int)(mb) | 0x40000000), 8);

	return &framebuffer;
}

void flip(unsigned int x, unsigned int y)
{

//	mb[0] = 8 * 4;		// Buffer size
//    mb[1] = 0;			// Request
//    mb[2] = 0x00048009;	// Tag id - Get physical width/height
//   mb[3] = 2*4;		// Buffer size
//    mb[4] = 0;			// Request/Response indicator (MSB 0 for request)
//    mb[5] = x;			// Width
//    mb[6] = y;			// Height
//    mb[7] = 0;			// End tag

//	MailboxWrite(((unsigned int)(mb) | 0x40000000), 8);


	//memcpy(&((unsigned char*)(framebuffer.buffer))[0], &((unsigned char*)(framebuffer.buffer))[buffer_size], buffer_size); 
	
	SetupMemCopy(&((unsigned char*)(framebuffer.buffer))[buffer_size], &((unsigned char*)(framebuffer.buffer))[0], buffer_size);
	StartDMACopy();
	
}
