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

constexpr unsigned CHAR_SIZE_X = 10;
constexpr unsigned CHAR_SIZE_Y = 22;

PaintDevice::PaintDevice(const std::string &fontFile) :
	fontPixmap(fontFile)
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
	for(unsigned row = 0; row < pixmap.getHeight(); ++row)
	{
		for(unsigned column = 0; column < pixmap.getWidth(); ++column)
		{
			if(!isInBounds(x + column, y + row))
				break;

			copyPixmapPixel(pixelAt(x + column, y + row), pixmap.pixelAt(column, row));
		}
	}
}

void PaintDevice::drawText(const std::string &text, unsigned x, unsigned y)
{
	if(!isInBounds(x, y))
		return;

	unsigned dx = 0, dy = 0;

	for(unsigned i = 0; i < text.size(); ++i)
	{
		char chr = text[i];
		if(chr == '\n')
		{
			dx = 0;
			dy += CHAR_SIZE_Y;
		}
		else
		{
			drawChar(chr, x + dx, y + dy);
			dx += CHAR_SIZE_X;
		}
	}
}

void PaintDevice::drawChar(char chr, unsigned x, unsigned y)
{
	if(chr < '!' || chr > '}')
		return;

	chr -= '!';

	int fx0 = (chr*CHAR_SIZE_X) % fontPixmap.getWidth();
	int fy0 = (chr*CHAR_SIZE_X) / fontPixmap.getWidth() * CHAR_SIZE_Y;

	for (unsigned dy = 0; dy < CHAR_SIZE_Y; dy++)
	{
		for (unsigned dx = 0; dx < CHAR_SIZE_X; dx++)
		{
			if(!isInBounds(x + dx, y + dy))
				break;

			copyPixmapPixel(pixelAt(x+dx, y+dy), fontPixmap.pixelAt(dx + fx0, dy + fy0));
		}
	}
}

uint8_t* PaintDevice::pixelAt(unsigned x, unsigned y) const
{
	uint8_t *bufferBytes = (uint8_t*)buffer;
	return &bufferBytes[(x+(y*width))*4];
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

