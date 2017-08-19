/*
*
*/

#include "image.h"
#include "drawing.h"




void LoadImage(struct Image* image, unsigned int* image_data, unsigned int width, unsigned int height)
{
	image->imageData = image_data;
	image->imageWidth = width;
	image->imageHeight = height;
}


