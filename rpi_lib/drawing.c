/*
*
*/

#include "framebuffer.h"
#include "drawing.h"
#include "dma.h"

unsigned int __attribute__((aligned(32)))  zero_array[76800] = { 0 };

int64_t character[43] = {
	0x708898A8C8887000,	// 0
	0x2060202020207000,	// 1
	0x708808304080F800,	// 2
	0xF808103008887000,	// 3
	0x10305090F8101000,	// 4
	0xF880807008887000,	// 5
	0x314080F088887000,	// 6
	0xF808102040404000, // 7
	0x7088887088887000,	// 8
	0x708888780810E000,	// 9
	0x0000000000000000,	// :(TODO)
	0x0000000000000000,	// ;(TODO)
	0x0000000000000000,	// <(TODO)
	0x0000000000000000,	// =(TODO)
	0x0000000000000000,	// >(TODO)
	0x0000000000000000,	// ?(TODO)
	0x0000000000000000,	// @(TODO)
	0x20608888F8888800,	// A
	0xF08888F08888F000,	// B
	0x7088808080887000,	// C
	0xF08888888888F000,	// D
	0xF88080F08080F800,	// E
	0xF88080F080808000,	// F
	0x708880B888887000, // G
	0x888888F888888800,	// H
	0x7020202020207000,	// I
	0x0808080808887000,	// J
	0x8890A0C0A0908800,	// K
	0x808080808080F800,	// L
	0x88D8A8A888888800,	// M
	0x8888C8A898888800,	// N
	0x7088888888887000,	// O
	0xF08888F080808000,	// P
	0x70888888A8987800,	// Q
	0xF08888F0A0908800,	// R
	0x7088807008887000,	// S
	0xF820202020202000, // T
	0x8888888888887000,	// U
	0x8888888888502000,	// V
	0x888888A8A8D88800,	// W
	0x8888502050888800,	// X
	0x8888502020202000,	// Y
	0xF80810204080F800,	// Z
};

int area_x;
int area_y;
int area_width;
int area_height;

void SetFrameBuffer(volatile struct FrameBufferInfo* fb)
{
	framebuffer = fb;
	offset = 0;
	buffer_index = 0;
	buffer = (unsigned char*)framebuffer->buffer;
	offset = framebuffer->width * framebuffer->height;
	
	area_x = 0;
	area_y = 0;
	area_width = framebuffer->width;
	area_height = framebuffer->height;
}

void SetDrawingArea(int _x, int _y, int _width, int _height)
{
	area_x = _x;
	area_y = _y;
	area_width = _width;
	area_height = _height;
}


void Clear()
{
	SetupMemCopy(zero_array, &((unsigned char*)(framebuffer->buffer))[offset], offset);
	StartDMACopy();
}

void DrawPixel(unsigned int x, unsigned int y, unsigned char color)
{	
	buffer[x + (y * framebuffer->width) + offset] = color;
}

void DrawHLine(unsigned int x, unsigned int y, unsigned int width, unsigned char color)
{
	for(int i = 0; i < width; i++){
		buffer[x + i + (y * framebuffer->width) + offset] = color;	
	}
}

void DrawVLine(unsigned int x, unsigned int y, unsigned int height, unsigned char color)
{
	for(int i = 0; i < height; i++){
		buffer[x + ((y + i) * framebuffer->width) + offset] = color;
	}	
}

void DrawRect(unsigned int x, unsigned int y,	unsigned int width, unsigned int height, unsigned char color)
{
	volatile unsigned int row = 0;
	volatile unsigned int col = 0;
	
	unsigned char* pointer = (unsigned char*)framebuffer->buffer;
	
	for(col = 0; col < height; col++){
		for(row = 0; row < width; row++){
			buffer[(row + x) + ((col + y) * framebuffer->width) + offset] = color;
		}
	}

}

void DrawCircle(unsigned int x, unsigned int y, unsigned int r, unsigned char color)
{
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x1 = 0;
	int y1 = r;
	int cornername = 3;
	int delta = 0;

	DrawVLine(x, y - r, 2 * r + 1, color);
	while(x1 < y1){
		if(f >= 0){
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		
		x1++;
		ddF_x += 2;
		f += ddF_x;
		
		if(cornername & 0x1){
			DrawVLine(x + x1, y - y1, 2 * y1 + 1 + delta, color);
			DrawVLine(x + y1, y - x1, 2 * x1 + 1 + delta, color);
		}
		
		if(cornername & 0x2){
			DrawVLine(x - x1, y - y1, 2 * y1 + 1 + delta, color);
			DrawVLine(x - y1, y - x1, 2 * x1 + 1 + delta, color);
		}
	}

}

void DrawString(char* str, unsigned int x, unsigned int y, unsigned char color)
{
	unsigned int index = 0;
	while(str[index] != '\0'){
		if(str[index] == ' '){
			index++;
			continue;
		}
		for(int i = 0; i < CHARACTER_HEIGHT; i++){
			for(int j = 0; j < CHARACTER_WIDTH; j++){
				if((character[str[index] - '0'] >> (63 - (i * 8 + j))) & 0x01){
					buffer[(x + j + (index * 7)) + ((y + i) * framebuffer->width) + offset] = color;
				}
			}
		}
		index++;
	}
}

void DrawImage(int x, int y, const struct Image* image, unsigned char color)
{
	int offset_x = 0, offset_y = 0;
	int draw_width = image->imageWidth, draw_height = image->imageHeight;
	if(x < 0){
		offset_x = -x;
		draw_width -= offset_x;
	}
	if(y < 0){
		offset_y = -y;
		draw_height -= offset_y;
	}
	
	if(x + image->imageWidth > area_x + area_width){
		draw_width -= x + image->imageWidth - (area_x + area_width);
	}
	if(y + draw_height > area_y + area_height){
		draw_height -= y + image->imageHeight - (area_y + area_height);
	}
	
	for(int d_y = offset_y; d_y < draw_height; d_y++){
		for(int d_x = offset_x; d_x < draw_width; d_x++){
			if((image->imageData[d_y] >> (15 - d_x)) & 0x1){
				buffer[(x + d_x + offset_x) + ((y + d_y + offset_y) * framebuffer->width) + offset] = color;		
			}
		} 
	}
}


void Display()
{
	flip(0, 768 * buffer_index);
}

