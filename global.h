/*
*
*/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240

#define MAINPANEL_WIDTH 240

#define A		12
#define B		6
#define X		16
#define Y		13
#define START	26
#define SELECT	20
#define PLAYER1	22
#define PLAYER2	23

#define CANNON_POSITION 220

#define NOT_LAUNCH 0
#define LAUNCH 1

#define BUNKER_NUM 3
#define BUNKER_PARTS 8 

#define ALIENMOVECOUNT_MAX 10
#define ALIEN_NUM_HORIZONTAL 11
#define ALIEN_NUM_VERTICAL	5

#define ALIENBULLET_NUM 3

#define HIGHSCORE 5000

enum GAME_STATE
{
	TITLE,
	GAME,
};

enum GAME_STATE game_state;
int flag_state_change;

int highscore;
int score;

#endif
