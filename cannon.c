/*
*
*/

#include "rpi_lib/drawing.h"
#include "rpi_lib/i2c.h"
#include "rpi_lib/gpio.h"
#include "global.h"
#include "cannon.h"
#include "game.h"

const unsigned int cannon_image_data[CANNON_IMAGE_MAX][CANNON_IMAGE_HEIGHT] = {
	{0x0200, 0x0700, 0x0700, 0x7FF0, 0xFFF8, 0xFFF8, 0xFFF8, 0xFFF8},
	{0x8208, 0x1000, 0x4408, 0x0C80, 0x9FC0, 0x3FC8, 0x3FE0, 0xFFF8},
};

volatile int x_axis;
volatile int y_axis;

void InitializeCannon()
{
	// Initialize variables
	cannon.x = 20;
	cannon.y = CANNON_POSITION;
	cannon.width = 13;
	cannon.height = 8;
	cannon.isShot = NOT_LAUNCH;
	LoadImage(&cannon.image, cannon_image_data[CANNON], CANNON_IMAGE_WIDTH, CANNON_IMAGE_HEIGHT);
}

void ShotCannon()
{
	if(digitalRead(Y) == LOW || digitalRead(A) == LOW
		|| digitalRead(X) == LOW || digitalRead(B) == LOW){
		if(cannon.isShot == NOT_LAUNCH){
			ShotBullet();
		}
	}else{
		
	}
}

void MoveCannon()
{

	i2c_read(&x_axis, X_AXIS);
	i2c_read(&y_axis, Y_AXIS);

	if(x_axis > HIGH_THRESHOLD){
		cannon.x += 5;
		if(cannon.x + cannon.width > MAINPANEL_WIDTH){
			cannon.x = MAINPANEL_WIDTH - cannon.width;
		}
	}else if(x_axis < LOW_THRESHOLD){
		cannon.x -= 5;
		if(cannon.x < 0){
			cannon.x = 0;
		}
	}
/*
	if(y_axis > HIGH_THRESHOLD){
		cannon.y += 5;
	}else if(y_axis < LOW_THRESHOLD){
		cannon.y -= 5;
	}
*/
	ShotCannon();

}

void ExplosionCannon()
{
	DrawRect(cannon.x, cannon.y, cannon.width, cannon.height, BLACK);
	LoadImage(&cannon.image, cannon_image_data[CANNON_EXPLOSION], CANNON_IMAGE_WIDTH, CANNON_IMAGE_HEIGHT);
	DrawImage(cannon.x, cannon.y, &(cannon.image), RED);
	Display();
	delay_ms(1000);
	cannon.x = 20;
	cannon.y = 220;
	LoadImage(&cannon.image, cannon_image_data[CANNON], CANNON_IMAGE_WIDTH, CANNON_IMAGE_HEIGHT);
}

void DrawCannon()
{
	DrawImage(cannon.x, cannon.y, &(cannon.image), LIGHTBLUE);
}

