/*
*
*/

#ifndef __ALIENBULLET_H__
#define __ALIENBULLET_H__

#include <stdbool.h>

extern struct Alien;

struct AlienBullet
{
	volatile int x;
	volatile int y;
	volatile int width;
	volatile int height;
	volatile bool exist;
};

extern void InitializeAlienBullet(struct AlienBullet* bullet);
extern void ShotAlienBullet(struct AlienBullet* bullet, const struct Alien* alien);
extern void MoveAlienBullet(struct AlienBullet* bullet);
extern void DrawAlienBullett(const struct AlienBullet* bullet);

#endif
