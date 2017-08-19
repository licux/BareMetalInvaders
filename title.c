/*
*
*/

#include "rpi_lib/gpio.h"
#include "global.h"
#include "title.h"
#include "global.h"

char str[15];

void InitializeTitle()
{
	highscore = HIGHSCORE;
	score = 0;
	
	InitializeAlien(&title_aliens[0], 70, 150, SMALL_ALIEN_0);
	InitializeAlien(&title_aliens[1], 70, 170, MEDIUM_ALIEN_0);
	InitializeAlien(&title_aliens[2], 70, 190, LARGE_ALIEN_0);
}

void LoopTitle()
{
	if(digitalRead(Y) == LOW || digitalRead(A) == LOW || digitalRead(X) == LOW || digitalRead(B) == LOW){
		flag_state_change = 1;
	}
}

void DrawTitle()
{
	DrawString("PLAY", 100, 40, GREEN);
	DrawString("SPACE INVADERS", 70, 60, LIGHTBLUE);
	DrawString("SCORE ADVANCE TABLE", 45, 80, RED);
	
	DrawAlien(&title_aliens[0]);
	DrawString("= 30 POINTS", 85, 150, GREEN);
	DrawAlien(&title_aliens[1]);
	DrawString("= 20 POINTS", 85, 170, LIGHTBLUE);
	DrawAlien(&title_aliens[2]);
	DrawString("= 10 POINTS", 85, 190, RED);
	
	DrawVLine(0, 0, 240, WHITE);
	DrawVLine(240, 0, 240, WHITE);
	DrawVLine(319, 0, 240, WHITE);
	
	DrawString("HIGHSCORE", 250, 20, WHITE);
	sprintf(str, "%05d", highscore);
	DrawString(str, 270, 30, WHITE);
	
	DrawString("SCORE", 250, 80, WHITE);
	sprintf(str, "%05d", score);
	DrawString(str, 270, 90, WHITE);
	
	DrawString("STAGE", 250, 120, WHITE);
	DrawString("1", 270, 130, WHITE);
}
