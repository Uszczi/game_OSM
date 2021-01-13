/*
 * PaintDevice.cpp
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#include "PaintDevice.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

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
		if(!isInBounds(x, y + row))
			break;

		memcpy(pixelAt(x, y + row), pixmap.pixelAt(0, row), pixmap.getWidth()*4);
	}
}

void PaintDevice::drawRect(unsigned x, unsigned y,
							unsigned width, unsigned height, unsigned color)
{
	for(unsigned dx = 0; dx < width; ++dx)
	{
		for(unsigned dy = 0; dy < height; ++dy)
		{
			if(!isInBounds(x + dx, y + dy))
				break;

			setPixel(x + dx, y + dy, color);
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

			unsigned color = fontPixmap.colorAt(dx + fx0, dy + fy0);

			if(color != 0x00)
				setPixel(x + dx, y + dy, color);
		}
	}
}

uint8_t* PaintDevice::pixelAt(unsigned x, unsigned y) const
{
	uint8_t *bufferBytes = (uint8_t*)buffer;
	return &bufferBytes[(x + (y*width))*4];
}

bool PaintDevice::isInBounds(unsigned x, unsigned y) const
{
	if(x >= width || y >= height)
		return false;
	return true;
}

void PaintDevice::setPixel(unsigned x, unsigned y, unsigned color)
{
	uint8_t *pixel = pixelAt(x, y);
	pixel[0] = ((uint8_t*)&color)[0];
	pixel[1] = ((uint8_t*)&color)[1];
	pixel[2] = ((uint8_t*)&color)[2];
	pixel[3] = 0x00;
}

void PaintDevice::clear()
{
	memset(buffer, 0, fix_info.smem_len);
}

void PaintDevice::swapBuffers()
{
	memcpy(framebuffer, buffer, fix_info.smem_len);
}




