/*
 * PaintDevice.h
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#ifndef PAINTDEVICE_H_
#define PAINTDEVICE_H_

#include <linux/fb.h>

class PaintDevice {
private:
	void *framebuffer;
	unsigned int* buffer;

	int frameBufferFD;
	struct fb_fix_screeninfo fix_info;

public:
	PaintDevice();
	virtual ~PaintDevice();

	void drawBitmap();

	void clear();
	void swapBuffers();
};

#endif /* PAINTDEVICE_H_ */
