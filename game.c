/*
*
*/

#include "rpi_lib/drawing.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

int ufoAppearCount;
int alienMoveCount;
int alienShotCountRandom;
int alienShotCountMoving;
int alienShotCountNearCannon;
int moveAlienIndex;
int alienAlive;
int highscore;
int score;
int stock;
int stage;

void InitializeGame()
{
	srand((unsigned int)(time(NULL)));
	stock = INITIAL_STOCK;
	
	highscore = HIGHSCORE;
	score = 0;

	stage = 0;
	
	touch_down = 0;
}

void InitializeStage()
{
	InitializeCannon();
	InitializeBullet();
	for(int i = 0; i < BUNKER_NUM; i++){
		SetBunker(&bunkers[i * BUNKER_PARTS], 80 * i + 20, 180);
	}

	InitializeUFO(&ufo);

	ResetAliens();
	alienAlive = 0;
	for(int i = 0; i < ALIEN_NUM_VERTICAL; i++){
		for(int j = 0; j < ALIEN_NUM_HORIZONTAL; j++){
			InitializeAlien(&aliens[j + i * ALIEN_NUM_HORIZONTAL],
							j * 18,
							(ALIEN_NUM_VERTICAL - 1 - i) * 16 + 20,
							 (ALIEN_NUM_VERTICAL - 1 - i));
			alienAlive++;
		}
	}

	for(int i = 0; i < ALIENBULLET_NUM; i++){
		InitializeAlienBullet(&alienbullets[i]);
	}
	
	ufoAppearCount = 20 * 30;
	
	alienMoveCount = ALIENMOVECOUNT_MAX;
	alienShotCountRandom = 80;
	alienShotCountMoving = 60 + random() % 30;
	alienShotCountNearCannon = 100;
	moveAlienIndex = 0;
	
	stage++;
	
	StageStart();
}

void CheckCollision()
{
	// check bullet and ufo
	if(cannon.isShot == LAUNCH && ufo.state == UFO_STATE_ALIVE
			&& bullet.y < (ufo.y + ufo.image[0].imageHeight)
			&& bullet.y + bullet.height > ufo.y
			&& bullet.x < (ufo.x + ufo.image[0].imageWidth)
			&& bullet.x + bullet.width > ufo.x){
		cannon.isShot = NOT_LAUNCH;
		score += ufo.score;
		ExplosionUFO(&ufo);
		if(score >= highscore){
			highscore = score;
		}
	}

	// check bullet and aliens
	for(int i = 0; i < ALIEN_NUM_HORIZONTAL * ALIEN_NUM_VERTICAL; i++){
		if(cannon.isShot == LAUNCH && aliens[i].state == ALIVE
			&& bullet.y < (aliens[i].y + aliens[i].image[aliens[i].step].imageHeight)
			&& bullet.y + bullet.height > aliens[i].y
			&& bullet.x < (aliens[i].x + aliens[i].image[aliens[i].step].imageWidth)
			&& bullet.x + bullet.width > aliens[i].x){
			ExplosionAlien(&aliens[i]);
			cannon.isShot = NOT_LAUNCH;
			alienAlive--;
			score += aliens[i].score;
			if(score >= highscore){
				highscore = score;
			}
		}
	}

	for(int i = 0; i < ALIENBULLET_NUM; i++){
		// alien_bullet and cannon
		if(alienbullets[i].exist == true
		 && cannon.y < (alienbullets[i].y + alienbullets[i].height)
			&& cannon.y + cannon.height > alienbullets[i].y
			&& cannon.x < (alienbullets[i].x + alienbullets[i].width)
			&& cannon.x + cannon.width > alienbullets[i].x){
			alienbullets[i].exist = false;
			ExplosionCannon();
			if(--stock < 0){
				GameOver();
				return;
			}
		}
		// alien_bullet and bunker
		for(int j = 0; j < BUNKER_NUM * BUNKER_PARTS; j++){
			if(alienbullets[i].exist == true && bunkers[j].status != BROKEN
			 && bunkers[j].y < (alienbullets[i].y + alienbullets[i].height)
				&& bunkers[j].y + BUNKER_HEIGHT > alienbullets[i].y
				&& bunkers[j].x < (alienbullets[i].x + alienbullets[i].width)
				&& bunkers[j].x + BUNKER_WIDTH > alienbullets[i].x){
				alienbullets[i].exist = false;
				DamagedBunker(&bunkers[j]);
				break;
			}
			// cannon_bullet and bunker
			if(cannon.isShot == LAUNCH && bunkers[j].status != BROKEN
			 && bunkers[j].y < (bullet.y + bullet.height)
				&& bunkers[j].y + BUNKER_HEIGHT > bullet.y
				&& bunkers[j].x < (bullet.x + bullet.width)
				&& bunkers[j].x + BUNKER_WIDTH > bullet.x){
				cannon.isShot = NOT_LAUNCH;
				DamagedBunker(&bunkers[j]);
				break;
			}
		}
	}

}

int FindShotAlienRandom(){
	int index = rand() % ALIEN_NUM_HORIZONTAL;
	while(index < ALIEN_NUM_VERTICAL * ALIEN_NUM_HORIZONTAL){
		if(aliens[index].state == ALIVE){
			return index;
		}
		index += ALIEN_NUM_HORIZONTAL;
	}

	return -1;
}

int FindShotAlienMoving(){
	if(aliens[moveAlienIndex].state == ALIVE){
		return moveAlienIndex;
	}
	return -1;
}


int FindShotAlienNearCannon(){
	
	int index = 0;

	for(int i = 0; i < ALIEN_NUM_VERTICAL; i++){
		for(int j = 0; j < ALIEN_NUM_HORIZONTAL; j++){
			if(aliens[index].state == ALIVE
				&& cannon.x < (aliens[index].x + aliens[index].image[aliens[index].step].imageWidth)
				&& cannon.x + cannon.width > aliens[index].x){
					return index;
			}
			index++;	
		}
	}
	
	return -1;
}

void StageStart()
{
	Clear();
	DrawGame();
	DrawString("STAGE STAGE", 100, 120, WHITE);
	Display();
	delay_ms(3000);
}

void GameOver()
{
	DrawString("GAME OVER..", 100, 120, WHITE);
	Display();
	delay_ms(5000);
	flag_state_change = 1;
}

void LoopGame()
{
	if(alienAlive == 0){
		delay_ms(1000);
		// Stage Clear
		InitializeStage();
	}

	// UFO
	if(ufoAppearCount-- < 0){
		SetUFO(&ufo);
		ufoAppearCount = 20 * 30;
	}
	MoveUFO(&ufo);

	// move aliens
	if(moveAlienIndex < ALIEN_NUM_HORIZONTAL * ALIEN_NUM_VERTICAL){
		if(stepForward == FORWARD){
			StepAlien(&aliens[moveAlienIndex]);
			if(touch_down == 1){
				GameOver();
			}
		}else{
			MoveAlien(&aliens[moveAlienIndex]);
		}
		do{
			moveAlienIndex++;
		}while(moveAlienIndex < ALIEN_NUM_HORIZONTAL * ALIEN_NUM_VERTICAL
				&& aliens[moveAlienIndex].state == DEAD);
	}else{
		if(stepForward == FORWARD){
			stepForward = STAY;
			alienSpeed *= -1;
		}
		if(nextAlienActive == FORWARD){
			stepForward = FORWARD;
			nextAlienActive = STAY;
		}
		moveAlienIndex = 0;
		while(aliens[moveAlienIndex].state == DEAD){
			moveAlienIndex++;
		}
	}
	
	// shot alien bullets

	if(alienShotCountRandom-- < 0){
		if(alienbullets[0].exist == false){
			int index = FindShotAlienRandom();
			if(index >= 0){
				ShotAlienBullet(&alienbullets[0], &aliens[index]);
			}
		}
		alienShotCountRandom = 100 + (random() % 30);
	}
	if(alienShotCountMoving-- < 0){
		if(alienbullets[1].exist == false){
			int index = FindShotAlienMoving();
			if(index >= 0){
				ShotAlienBullet(&alienbullets[1], &aliens[index]);
			}
		}
		alienShotCountMoving = 150 + (random() % 30);
	}
	if(alienShotCountNearCannon-- < 0){
		if(alienbullets[2].exist == false){
			int index = FindShotAlienNearCannon();
			ShotAlienBullet(&alienbullets[2], &aliens[index]);
		}
		alienShotCountNearCannon = 70 + (random() % 30);
	}

	// move alien bullets
	for(int i = 0; i < ALIENBULLET_NUM; i++){
		MoveAlienBullet(&alienbullets[i]);
	}
	
	// move alien 
	MoveBullet();
	MoveCannon();
	CheckCollision();
	
}

void DrawGame()
{
	for(int i = 0; i < ALIEN_NUM_HORIZONTAL * ALIEN_NUM_VERTICAL; i++){
		DrawAlien(&aliens[i]);
	}
	for(int i = 0; i < ALIENBULLET_NUM; i++){
		DrawAlienBullet(&alienbullets[i]);
	}
	DrawUFO(&ufo);
	for(int i = 0; i < BUNKER_NUM * BUNKER_PARTS; i++){
		DrawBunker(&bunkers[i]);
	}
	DrawBullet();
	DrawCannon();
	DrawVLine(0, 0, 240, WHITE);
	DrawVLine(240, 0, 240, WHITE);
	DrawVLine(319, 0, 240, WHITE);
	
	DrawStatus();
}


