/*
*
*/

#ifndef __DMA_H__
#define __DMA_H__

#include "rpi_address.h"
#include "stdint.h"

#define DMA_BASE			0x20007000
#define DMA_CHANNEL_CS(chan)		(volatile unsigned int *)(DMA_BASE + (chan) * 0x100)
#define DMA_CHANNEL_CONCLK(chan)	(volatile unsigned int *)(DMA_BASE + (chan) * 0x100 + 0x04)

#define DMA_CS_RESET	(0x01 << 31)
#define DMA_CS_ABORT	(0x01 << 30)
#define DMA_CS_ERROR	(0x01 <<  8)
#define DMA_CS_PAUSED	(0x01 <<  4)
#define DMA_CS_END		(0x01 <<  1)
#define DMA_CS_ACTIVE	(0x01 <<  0)

#define DMA_TI_SRC_WIDTH	(0x01 <<  9)
#define DMA_TI_SRC_INC		(0x01 <<  8)
#define DMA_TI_DST_WIDTH	(0x01 <<  5)
#define DMA_TI_DST_INC		(0x01 <<  4)
#define DMA_TI_WAIT_RESP	(0x01 <<  3)
#define DMA_TI_TDMODE		(0x01 <<  1)
#define DMA_TI_INTEN		(0x01)

struct ControlBlock{
	volatile uint32_t TransferInfomation;
	volatile uint32_t SourceAddress;
	volatile uint32_t DestinationAddress;
	volatile uint32_t TransferLength;
	volatile uint32_t ModeStride;
	volatile uint32_t NextControlBlockAddress;
	volatile uint32_t Reserved[2];
};

extern struct ControlBlock cb __attribute__((aligned(32)));

extern void InitializeDMA();

extern void SetupMemCopy(unsigned int src, unsigned int dst, unsigned int length);
extern void StartDMACopy();
extern void WaitDMAComplete();

#endif // __DMA_H__
