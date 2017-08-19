/*
*
*/

#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

struct FrameBufferInfo
{
	volatile unsigned int width;
	volatile unsigned int height;
	volatile unsigned int vWidth;
	volatile unsigned int vHeight;
	volatile unsigned int picth;
	volatile unsigned int bitDepth;
	volatile unsigned int x;
	volatile unsigned int y;
	volatile unsigned int buffer;
	volatile unsigned int size;
} ;
/*
struct FrameBufferInfo
{
	volatile unsigned int __attribute__((aligned(16))) width;
	volatile unsigned int __attribute__((aligned(16))) height;
	volatile unsigned int __attribute__((aligned(16))) vWidth;
	volatile unsigned int __attribute__((aligned(16))) vHeight;
	volatile unsigned int __attribute__((aligned(16))) picth;
	volatile unsigned int __attribute__((aligned(16))) bitDepth;
	volatile unsigned int __attribute__((aligned(16))) x;
	volatile unsigned int __attribute__((aligned(16))) y;
	volatile unsigned int __attribute__((aligned(16))) buffer;
	volatile unsigned int __attribute__((aligned(16))) size;
} ;*/

extern struct FrameBufferInfo* InitializeFrameBuffer(
								unsigned int width,
								unsigned int height,
								unsigned int bitDepth);											
extern void flip(unsigned int x, unsigned int y);

#endif
