/*
*
*/
#ifndef __CANNON_H_
#define __CANNON_H_

#include "rpi_lib/image.h"

#define LOW_THRESHOLD 2000
#define HIGH_THRESHOLD 20000

struct Cannon{
	volatile int x;
	volatile int y;
	volatile int width;
	volatile int height;
	volatile char isShot;
	volatile struct Image image;
};

#define CANNON_IMAGE_WIDTH 13
#define CANNON_IMAGE_HEIGHT 8

enum CANNON_IMAGE_DATA{
	CANNON = 0,
	CANNON_EXPLOSION = 1,
	CANNON_IMAGE_MAX = 2,
};
extern const unsigned int cannon_image_data[CANNON_IMAGE_MAX][CANNON_IMAGE_HEIGHT];
extern const unsigned int cannon_image_width[CANNON_IMAGE_MAX];

extern void InitializeCannon();
extern void ShotCannon();
extern void MoveCannon();
extern void ExplosionCannon();
extern void DrawCannon();

#endif
