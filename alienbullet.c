/*
*
*/

#include "alienbullet.h"
#include "alien.h"
#include "rpi_lib/drawing.h"
#include "global.h"

void InitializeAlienBullet(struct AlienBullet* bullet)
{
	bullet->x = 0;
	bullet->y = 0;
	bullet->width = 3;
	bullet->height = 7;
	bullet->exist = false;
}

void ShotAlienBullet(struct AlienBullet* bullet, const struct Alien* alien)
{
	bullet->x = alien->x + 5;
	bullet->y = alien->y + alien->image[alien->step].imageHeight;
	bullet->exist = true;
}

void MoveAlienBullet(struct AlienBullet* bullet)
{
	if(bullet->exist == false) return;
	
	bullet->y += 3;
	if(bullet->y >= WINDOW_HEIGHT){
		bullet->exist = false;
	}
}

void DrawAlienBullet(const struct AlienBullet* bullet)
{
	if(bullet->exist == false) return;
	DrawRect(bullet->x, bullet->y, bullet->width, bullet->height, WHITE);
}

