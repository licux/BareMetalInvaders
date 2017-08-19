/*
*
*/

#ifndef __DRAWING_H__
#define __DRAWING_H__

#include <stdint.h>
#include "framebuffer.h"
#include "image.h"

/*
#define BLACK	0x000000
#define BLUE	0x0000FF
#define GREEN	0x00FF00
#define YELLOW	0x00FFFF
#define RED		0xFF0000
*/

#define BLACK 		0
#define RED			1
#define GREEN		2
#define BLUE		3
#define YELLOW		4
#define PINK		5
#define LIGHTGREEN	6
#define LIGHTBLUE	7
#define WHITE		8

#define CHARACTER_WIDTH 5
#define CHARACTER_HEIGHT 7

extern int64_t character[43];

extern int area_x;
extern int area_y;
extern int area_width;
extern int area_height;

extern void SetFrameBuffer(volatile struct FrameBufferInfo* fb);
extern void SetDrawingArea(int _x, int _y, int _width, int _height);
extern void Clear();
extern void DrawPixel(unsigned int x, unsigned int y, unsigned char color);
extern void DrawHLine(unsigned int x, unsigned int y, unsigned int width, unsigned char color);
extern void DrawVLine(unsigned int x, unsigned int y, unsigned int height, unsigned char color);
extern void DrawRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char color);
extern void DrawCircle(unsigned int x, unsigned int y, unsigned int r, unsigned char color);
extern void DrawString(char* str, unsigned int x, unsigned int y, unsigned char color);
extern void DrawImage(int x, int y, const struct Image* image, unsigned char color);
extern void Display();

volatile struct FrameBufferInfo* framebuffer;
volatile int offset;
volatile int buffer_index;
volatile unsigned char* buffer;


#endif
