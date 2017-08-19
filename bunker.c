/*
*
*/

#include "rpi_lib/drawing.h"
#include "bunker.h"

const unsigned int damaged_data[BUNKER_HEIGHT] = {
	0x2950,
	0x4DA8,
	0xA870,
	0x14AE,
	0x1B98,
	0x993A,
	0xBAE2,
	0xBFF6,
	0xFFBE,
	0xFFFE,
};

struct Image damaged_image;

void SetBunker(struct Bunker* bunker, int sx, int sy)
{
	InitializeBunker(&bunker[0], sx,      sy);
	InitializeBunker(&bunker[1], sx + 15, sy);
	InitializeBunker(&bunker[2], sx + 30, sy);
	InitializeBunker(&bunker[3], sx,	  sy + 10);
	InitializeBunker(&bunker[4], sx + 15, sy + 10);
	InitializeBunker(&bunker[5], sx + 30, sy + 10);
	InitializeBunker(&bunker[6], sx,	  sy + 20);
	InitializeBunker(&bunker[7], sx + 30, sy + 20);
}

void InitializeBunker(struct Bunker* bunker, int _x, int _y)
{
	bunker->x = _x;
	bunker->y = _y;
	
	bunker->status = NORMAL;
	
	LoadImage((&damaged_image), damaged_data, BUNKER_WIDTH, BUNKER_HEIGHT);
}

void DamagedBunker(struct Bunker* bunker)
{
	switch(bunker->status){
		case NORMAL:
			bunker->status = DAMAGED;
			break;
		case DAMAGED:
			bunker->status = BROKEN;
			break;
		default:
			break;
	}
}	
void DrawBunker(struct Bunker* bunker)
{
	switch(bunker->status){
		case NORMAL:
			DrawRect(bunker->x, bunker->y, BUNKER_WIDTH, BUNKER_HEIGHT, RED);
			break;
		case DAMAGED:
			DrawImage(bunker->x, bunker->y, &damaged_image, RED);
			break;
		default:
			break;
	}
}
