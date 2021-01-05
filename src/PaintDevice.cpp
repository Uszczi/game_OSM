/*
 * PaintDevice.cpp
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#include "PaintDevice.h"

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

PaintDevice::PaintDevice()
{
	frameBufferFD = open("/dev/fb0", O_RDWR);
	ioctl(frameBufferFD, FBIOGET_FSCREENINFO, &fix_info);

	framebuffer = mmap(NULL, fix_info.smem_len, PROT_READ | PROT_WRITE,MAP_SHARED, frameBufferFD, 0);
	buffer = (unsigned int*)malloc(fix_info.smem_len);

	width = fix_info.line_length/4;
	height = fix_info.smem_len / fix_info.line_length;
}

PaintDevice::~PaintDevice()
{
	close(frameBufferFD);
	free(buffer);
}

void PaintDevice::drawPixmap(const PPMPixmap &pixmap, unsigned x, unsigned y)
{
	uint8_t *bufferBytes = (uint8_t*)buffer;
	uint8_t *pixmapData = (uint8_t*)pixmap.getData();

	const unsigned lineLength = fix_info.line_length/4;

	for(unsigned row = 0; row < pixmap.getHeight(); ++row)
	{
		for(unsigned column = 0; column < pixmap.getWidth(); ++column)
		{
			if(!isInBounds(x + column, y + row))
				break;

			const unsigned currentBufferByte = ((row + y)*lineLength + x + column)*4;

			copyPixmapPixel(&bufferBytes[currentBufferByte], &pixmapData[(row*pixmap.getWidth() + column)*3]);
		}
	}
}

bool PaintDevice::isInBounds(unsigned x, unsigned y) const
{
	if(x > width || y > height)
		return false;
	return true;
}


void PaintDevice::copyPixmapPixel(uint8_t *destination, const uint8_t *pixel) const
{
	destination[0] = pixel[2];
	destination[1] = pixel[1];
	destination[2] = pixel[0];
	destination[3] = 0x00;
}

void PaintDevice::clear()
{
	memset(buffer, 0, fix_info.smem_len);
}

void PaintDevice::swapBuffers()
{
	memcpy(framebuffer, buffer, fix_info.smem_len);
}

