#include "rpi_lib/rpi.h"
#include "rpi_lib/rpi_address.h"
#include "rpi_lib/gpio.h"
#include "rpi_lib/framebuffer.h"
#include "rpi_lib/drawing.h"
#include "rpi_lib/i2c.h"
#include "rpi_lib/systemtimer.h"
#include "rpi_lib/uart.h"
#include "rpi_lib/dma.h"

#include "global.h"

#include <stdio.h>

#define TIME_PER_FRAME 33333
//#define TIME_PER_FRAME 100000

void ChangeState(enum GAME_STATE _state){
	switch (_state){
		case TITLE:
			game_state = TITLE;
			InitializeTitle();
			break;
		case GAME:
			game_state = GAME;
			InitializeGame();
			break;
		default:
			break;
	}
}

int main(void){

	volatile struct FrameBufferInfo* framebuffer;
	volatile unsigned long long start, end;

	rpi_init();
	InitializeGpio();
	i2c_init();
	UartInit();

	// Set GPIO pin
	pinMode(A,			PULLUP);
	pinMode(B, 			PULLUP);
	pinMode(X, 			PULLUP);
	pinMode(Y, 			PULLUP);
	pinMode(START,		PULLUP);
	pinMode(SELECT,		PULLUP);
	pinMode(PLAYER1, 	PULLUP);
	pinMode(PLAYER2, 	PULLUP);

	framebuffer = InitializeFrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 8);
	SetFrameBuffer(framebuffer);
	SetDrawingArea(0, 0, MAINPANEL_WIDTH, WINDOW_HEIGHT);
	
	flag_state_change = 0;
	ChangeState(TITLE);

	while(1){
		start = getSysTime();
	
		// main process
		switch(game_state){
			case TITLE:

				LoopTitle();
								Clear();
				WaitDMAComplete();
				DrawTitle();
				Display();
				break;
			case GAME:
				Clear();
				LoopGame();		
				WaitDMAComplete();
				DrawGame();
				Display();
				break;
			default:
				break;
		}
	
		if(flag_state_change == 1){
			switch(game_state){
				case TITLE:
					ChangeState(GAME);
					break;
				case GAME:
					ChangeState(TITLE);
					break;
				default:
					break;
			}
			flag_state_change = 0;
		}

		end = getSysTime() - start;
		if(TIME_PER_FRAME > end){
			delay_micros(TIME_PER_FRAME - end);
		}
//	For Debug
//		printf("Loop %llu\n", end);
	}

	return 0;
}
