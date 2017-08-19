/*
*
*/

#include "global.h"

#include "rpi_lib/image.h"

#define UFO_WIDTH	16
#define UFO_HEIGHT	7

#define UFO_SPEED 1

enum UFO_STATE{
	UFO_STATE_DEAD,
	UFO_STATE_ALIVE,
	UFO_STATE_EXPLOSION,
};

enum UFO_DIR{
	UFO_DIR_LEFT,
	UFO_DIR_RIGHT,
};

struct UFO{
	volatile int x;
	volatile int y;
	volatile enum UFO_STATE state;
	volatile enum UFO_DIR dir;
	volatile struct Image image[2];
	volatile int score;
};

extern unsigned int ufo_image_data[2][UFO_HEIGHT];
extern unsigned int ufo_explosion_count;

extern void InitialzeUFO(struct UFO* ufo);
extern void SetUFO(struct UFO* ufo);
extern void MoveUFO(struct UFO* ufo);
extern void ExplosionUFO(struct UFO* ufo);
extern void DrawUFO(struct UFO* ufo);


