/*
*
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "rpi_lib/gpio.h"
#include "rpi_lib/drawing.h"
#include "rpi_lib/i2c.h"
#include "rpi_lib/systemtimer.h"

#include "global.h"
#include "bullet.h"
#include "cannon.h"
#include "bunker.h"
#include "alienbullet.h"
#include "alien.h"
#include "ufo.h"
#include "status.h"

#define INITIAL_STOCK 3

struct Cannon cannon;
struct Bullet bullet;
struct Bunker bunkers[BUNKER_NUM * BUNKER_PARTS];
struct Alien aliens[ALIEN_NUM_HORIZONTAL * ALIEN_NUM_VERTICAL];
struct AlienBullet alienbullets[ALIENBULLET_NUM];
struct UFO ufo;
extern int ufoAppearCount;
extern int alienMoveCount;
extern int alienShotCountRandom;
extern int alienShotCountMoving;
extern int alienShotCountNearCannon;
extern int moveAlienIndex;
extern int alienAlive;
extern int highscore;
extern int score;
extern int stock;
extern int stage;

extern void InitializeGame();
extern void InitializeStage();
extern void CheckCollision();
extern int FindShotAlien();
extern void StageStart();
extern void GameOver();
extern void LoopGame();
extern void DrawGame();

#endif
