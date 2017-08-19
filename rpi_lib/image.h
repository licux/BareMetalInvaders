/*
*
*/

#ifndef __IMAGE_H__
#define __IMAGE_H__

struct Image{
	unsigned int* imageData;
	unsigned int imageWidth;
	unsigned int imageHeight;
};

extern void LoadImage(struct Image* image, unsigned int* image_data, unsigned int width, unsigned int height);

#endif
