/*
*
*/

#include "dma.h"

#define CHANNEL 0

struct ControlBlock cb __attribute__((aligned(32)));

void InitializeDMA()
{
	// TODO
}

void SetupMemCopy(unsigned int src, unsigned int dst, unsigned int length)
{
	cb.TransferInfomation = DMA_TI_SRC_WIDTH | DMA_TI_DST_WIDTH | DMA_TI_SRC_INC | DMA_TI_DST_INC | DMA_TI_TDMODE;
 	cb.SourceAddress = src | 0x40000000;
	cb.DestinationAddress = dst | 0x40000000;
	cb.TransferLength = (2 << 16) | 25600; 
	cb.ModeStride = 0;
	cb.NextControlBlockAddress = 0;
	cb.Reserved[0] = 0;
	cb.Reserved[1] = 0;
}

void StartDMACopy()
{
	// Reset DMA CHANEEL  
	*DMA_CHANNEL_CS(CHANNEL) = DMA_CS_RESET;
	*DMA_CHANNEL_CONCLK(CHANNEL) = (unsigned int)&cb| 0x40000000;
	*DMA_CHANNEL_CS(CHANNEL) = DMA_CS_ACTIVE;
}

void WaitDMAComplete()
{
	// Wait Until DMA Transfer Complet
	while(*DMA_CHANNEL_CS(CHANNEL) & 0x01){
		;
	}
}
