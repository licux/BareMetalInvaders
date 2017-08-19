/*
*
*/

#ifndef __BUNKER_H__
#define __BUNKER_H__

#include "rpi_lib/image.h"

#define BUNKER_WIDTH 15
#define BUNKER_HEIGHT 10

enum BUNKER_STATE{
	NORMAL,
	DAMAGED,
	BROKEN,
};

struct Bunker{
	volatile int x;
	volatile int y;
	volatile enum BUNKER_STATE status;
};

extern const unsigned int damaged_data[BUNKER_HEIGHT];
extern struct Image damaged_image;

extern void SetBunker(struct Bunker* bunker, int sx, int sy);
extern void InitializeBunker(struct Bunker* bunker, int _x, int _y);
extern void DamagedBunker(struct Bunker* bunker);
extern void DrawBunker(struct Bunker* bunker);

#endif
