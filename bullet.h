/*
*
*/

#ifndef __BULLET_H__
#define __BULLET_H__

struct Bullet
{
	volatile int x;
	volatile int y;
	volatile int width;
	volatile int height;
};

extern void InitializeBullet();
extern void ShotBullet();
extern void MoveBullet();
extern void DrawBullet();

#endif
