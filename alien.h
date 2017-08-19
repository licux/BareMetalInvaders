/*
*
*/
#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "global.h"
#include "rpi_lib/image.h"
#include "rpi_lib/drawing.h"

#define ALIEN_SPEED 3

#define STAY	0
#define FORWARD	1

#define COLOR_MAX 10

#define ALIEN_IMAGE_HEIGHT 8

enum ALIEN_STATE{
	DEAD,
	ALIVE,
	EXPLOSION,
};

struct Alien{
	volatile int x;
	volatile int y;
	volatile enum ALIEN_STATE state;
	volatile int line;
	volatile struct Image image[3];
	volatile int score;
	volatile int step;
};

enum ALIEN_IMAGE_DATA{
	SMALL_ALIEN_0 = 0,
	SMALL_ALIEN_1 = 1,
	MEDIUM_ALIEN_0 = 2,
	MEDIUM_ALIEN_1 = 3,
	LARGE_ALIEN_0 = 4,
	LARGE_ALIEN_1 = 5,
	ALIEN_EXPLOSION = 6,
	ALIEN_IMAGE_MAX = 7,
};


extern const unsigned int alien_image_data[ALIEN_IMAGE_MAX][ALIEN_IMAGE_HEIGHT];
extern const unsigned int alien_image_width[ALIEN_IMAGE_MAX];

extern const enum ALIEN_IMAGE_DATA alien_data_line[ALIEN_NUM_VERTICAL];
extern const unsigned char alien_color[COLOR_MAX];
extern const int alien_score[];

extern int alienSpeed;
extern int stepForward;
extern int nextAlienActive;
extern int touch_down;

extern void InitializeAlien(struct Alien *alien, int _x, int _y, int _line);
extern void ResetAliens();
extern void MoveAlien(struct Alien *alien);
extern void StepAlien(struct Alien *alien);
extern void ExplosionAlien(struct Alien *alien);
extern void DrawAlien(struct Alien *alien);

#endif
