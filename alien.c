/*
*
*/

#include "alien.h"
#include "global.h"
#include "rpi_lib/drawing.h"
#include "rpi_lib/image.h"

int alienSpeed = ALIEN_SPEED;
int stepForward = STAY;
int nextAlienActive = STAY;
int touch_down = 0;

const unsigned int alien_image_data[ALIEN_IMAGE_MAX][ALIEN_IMAGE_HEIGHT] =
{
	{0x1800, 0x3C00, 0xDB00, 0xFF00, 0x5A00, 0x5A00, 0x8100, 0x4200},

	{0x1800, 0x3C00, 0xDB00, 0xFF00, 0x5A00, 0x2400, 0x5A00, 0xA500},

	{0x2080, 0x1100, 0x3F80, 0x6EC0, 0xFFE0, 0xBFA0, 0xA0A0, 0x1B00},
	 
	{0x2080, 0x9120, 0xBFA0, 0xEEE0, 0xFFE0, 0x7FC0, 0x2080, 0x4040},
	
	{0x0F00, 0x7FE0, 0xFFF0, 0xE679, 0xFFF0, 0x1980, 0x36C0, 0xC030},
	
	{0x0F00, 0x7FE0, 0xFFF0, 0xE679, 0xFFF0, 0x38C0, 0x6660, 0x30C0},
	
	{0x9120, 0x4A40, 0x2080, 0xC060, 0x2080, 0x4A40, 0x9120},
};

const unsigned int alien_image_width[ALIEN_IMAGE_MAX] = {8, 8, 11, 11, 12, 12, 11};

const enum ALIEN_IMAGE_DATA alien_data_line[ALIEN_NUM_VERTICAL] = {SMALL_ALIEN_0, MEDIUM_ALIEN_0, MEDIUM_ALIEN_0, 	LARGE_ALIEN_0, LARGE_ALIEN_0};

const unsigned char alien_color[COLOR_MAX] = {GREEN, GREEN, LIGHTBLUE, LIGHTBLUE, PINK, PINK, YELLOW, YELLOW, RED, RED};

const int alien_score[] = {10, 10, 20, 20, 30, 30, 0};

void InitializeAlien(struct Alien *alien, int _x, int _y, int _line)
{
	alien->x = _x;
	alien->y = _y;
	alien->state = ALIVE;
	alien->line = _line;
	LoadImage(&(alien->image[0]), alien_image_data[alien_data_line[_line]], alien_image_width[alien_data_line[_line]], ALIEN_IMAGE_HEIGHT);
	LoadImage(&(alien->image[1]), alien_image_data[alien_data_line[_line] + 1], alien_image_width[alien_data_line[_line] + 1], ALIEN_IMAGE_HEIGHT);
	LoadImage(&(alien->image[2]), alien_image_data[ALIEN_EXPLOSION], alien_image_width[ALIEN_EXPLOSION], ALIEN_IMAGE_HEIGHT);
	alien->score = alien_score[_line];
	alien->step = 0;
}

void ResetAliens()
{
	alienSpeed = ALIEN_SPEED;
	stepForward = STAY;
	nextAlienActive = STAY;
}

void MoveAlien(struct Alien *alien)
{
	if(alien->state == ALIVE){
		alien->x += alienSpeed;
		if(alien->x + alien->image[alien->step].imageWidth + alienSpeed >= MAINPANEL_WIDTH || alien->x + alienSpeed < 0){	
			nextAlienActive = FORWARD;
		}
		alien->step = (alien->step + 1) % 2;
	}else if(alien->state == EXPLOSION){
		alien->state = DEAD;
	}
}

void StepAlien(struct Alien *alien)
{
	if(alien->state == ALIVE){
		alien->y += 16;
		if(alien->line < COLOR_MAX - 1){
			alien->line++;
		}
		if(alien->y > CANNON_POSITION){
			touch_down = 1;
		}
	}else if(alien->state == EXPLOSION){
		alien->state = DEAD;
	}
}

void ExplosionAlien(struct Alien *alien)
{
	alien->state = EXPLOSION;

}

void DrawAlien(struct Alien *alien)
{
	if(alien->state == ALIVE){
		DrawImage(alien->x, alien->y, &(alien->image[alien->step]), alien_color[alien->line]);
	}else if(alien->state == EXPLOSION){
		DrawImage(alien->x, alien->y, &(alien->image[2]), RED);	
	}
}
