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

	framebuffer = mmap(NULL, fix_info.line_length * 480, PROT_READ | PROT_WRITE,MAP_SHARED, frameBufferFD, 0);
	buffer = (unsigned int*)malloc(fix_info.smem_len);
}

PaintDevice::~PaintDevice()
{
	close(frameBufferFD);
}

void PaintDevice::drawBitmap()
{
	FILE *bitmapFile = fopen("bitmapaRPi.ppm", "rb");
	u_int8_t bitmap[640*480*3];

	fread(&bitmap, sizeof(u_int8_t), 640*480*3, bitmapFile);
	u_int8_t *screen = (u_int8_t*)buffer;

	int a = 0;
	for(int i = 0; i < 640*480*4; i += 4)
	{
		screen[i] = bitmap[a + 2];
		screen[i + 1] = bitmap[a + 1];
		screen[i + 2] = bitmap[a];
		screen[i + 3] = 0x00;
		a += 3;
	}

	fclose(bitmapFile);
}

void PaintDevice::clear()
{
	memset(buffer, 0, fix_info.smem_len);
}

void PaintDevice::swapBuffers()
{
	memcpy(framebuffer, buffer, fix_info.smem_len);
}
