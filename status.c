/*
*
*/

#include "rpi_lib/drawing.h"
#include "game.h"
#include "status.h"

char str[15];

void DrawStatus()
{
	DrawString("HIGHSCORE", 250, 20, WHITE);
	sprintf(str, "%05d", highscore);
	DrawString(str, 270, 30, WHITE);
	
	DrawString("SCORE", 250, 80, WHITE);
	sprintf(str, "%05d", score);
	DrawString(str, 270, 90, WHITE);
	
	DrawString("STAGE", 250, 120, WHITE);
	DrawString("1", 270, 130, WHITE);
	
}
