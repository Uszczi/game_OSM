/*
 * PaintDevice.h
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#ifndef PAINTDEVICE_H_
#define PAINTDEVICE_H_

#include <linux/fb.h>
#include "PPMPixmap.h"

class PaintDevice {
private:
	void *framebuffer;
	unsigned int* buffer;

	int frameBufferFD;
	struct fb_fix_screeninfo fix_info;
	unsigned width, height;

public:
	PaintDevice();
	virtual ~PaintDevice();

	void drawPixmap(const PPMPixmap &pixmap, unsigned x, unsigned y);

	void clear();
	void swapBuffers();

private:
	void copyPixmapPixel(uint8_t *destination, const uint8_t *pixel) const;
	bool isInBounds(unsigned x, unsigned y) const;
};

#endif /* PAINTDEVICE_H_ */
