/*
 * PaintDevice.h
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#ifndef PAINTDEVICE_H_
#define PAINTDEVICE_H_

#include "PPMPixmap.h"

#include <linux/fb.h>
#include <string>

class PaintDevice {
private:
	void *framebuffer;
	unsigned int* buffer;
	PPMPixmap fontPixmap;

	int frameBufferFD;
	struct fb_fix_screeninfo fix_info;
	unsigned width, height;

public:
	PaintDevice(const std::string &fontFile);
	virtual ~PaintDevice();

	void drawPixmap(const PPMPixmap &pixmap, unsigned x, unsigned y);
	void drawText(const std::string &text, unsigned x, unsigned y);

	void clear();
	void swapBuffers();

private:
	void drawChar(char chr, unsigned x, unsigned y);
	uint8_t *pixelAt(unsigned x, unsigned y) const;

	void copyPixmapPixel(uint8_t *destination, const uint8_t *pixel) const;
	bool isInBounds(unsigned x, unsigned y) const;
};

#endif /* PAINTDEVICE_H_ */
