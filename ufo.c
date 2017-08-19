/*
*
*/

#include <stdlib.h>
#include "rpi_lib/image.h"
#include "rpi_lib/drawing.h"
#include "ufo.h"

unsigned int ufo_image_data[2][UFO_HEIGHT] = {
	{0x03C0, 0x0FF0, 0x3FFC, 0x6DB6, 0xFFFF, 0x3BDC, 0x1008,},
	{0xA425, 0x524A, 0x0810, 0xC003, 0x0810, 0x524A, 0xA425,},
};	

unsigned int ufo_explosion_count;

void InitializeUFO(struct UFO* ufo)
{
	ufo->x = -50;
	ufo->y = -50;
	
	ufo->state = UFO_STATE_DEAD;
		
	LoadImage(&(ufo->image[0]), ufo_image_data[0], UFO_WIDTH, UFO_HEIGHT);
	LoadImage(&(ufo->image[1]), ufo_image_data[1], UFO_WIDTH, UFO_HEIGHT);
	
	score = 10;
}

void SetUFO(struct UFO* ufo)
{
	ufo->state = UFO_STATE_ALIVE;
	
	if((rand() % 2) == 0){
		ufo->dir = UFO_DIR_LEFT;
		ufo->x = MAINPANEL_WIDTH + 20;		
	}else{
		ufo->dir = UFO_DIR_RIGHT;
		ufo->x = -20;
	}
	ufo->y = 5;
	
	ufo_explosion_count = 0;
}

void MoveUFO(struct UFO* ufo)
{
	if(ufo->state == UFO_STATE_ALIVE){
		if(ufo->dir == UFO_DIR_LEFT){
			ufo->x -= UFO_SPEED;
			if(ufo->x < -20){
				ufo->state = UFO_STATE_DEAD;
			}
		}else{
			ufo->x += UFO_SPEED;
			if(ufo->x > MAINPANEL_WIDTH + 20){
				ufo->state = UFO_STATE_DEAD;
			}
		}
	}else if(ufo->state == UFO_STATE_EXPLOSION){
		if(ufo_explosion_count++ > 60){
			ufo->state = UFO_STATE_DEAD;
		}
	}
}

void ExplosionUFO(struct UFO* ufo)
{
	ufo->state = UFO_STATE_EXPLOSION;
}

void DrawUFO(struct UFO* ufo)
{
	if(ufo->state == UFO_STATE_ALIVE){
		DrawImage(ufo->x, ufo->y, &(ufo->image[0]), RED);
	}else if(ufo->state == UFO_STATE_EXPLOSION){
		DrawImage(ufo->x, ufo->y, &(ufo->image[1]), RED);
	}
}

