/*
*
*/

#include "game.h"
#include "bullet.h"

void InitializeBullet()
{
	bullet.width = 3;
	bullet.height = 7;
}

void ShotBullet()
{
	if(cannon.isShot == LAUNCH)
		return;
		
	bullet.x = cannon.x + 5;
	bullet.y = cannon.y;
	cannon.isShot = LAUNCH;
}

void MoveBullet()
{
	if(cannon.isShot == NOT_LAUNCH)
		return;
	
	bullet.y -= 5;
	
	if(bullet.y < 0){
		cannon.isShot = NOT_LAUNCH;
	}
}

void DrawBullet()
{
	if(cannon.isShot == NOT_LAUNCH)
		return;
		
	DrawRect(bullet.x, bullet.y, bullet.width, bullet.height, YELLOW);
}

