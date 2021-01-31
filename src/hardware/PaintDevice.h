/*
 * PaintDevice.h
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#ifndef PAINTDEVICE_H_
#define PAINTDEVICE_H_

#include "../gui/PPMPixmap.h"
#include <string>

constexpr unsigned CHAR_SIZE_X = 10;
constexpr unsigned CHAR_SIZE_Y = 22;

class PaintDevice {
public:
    virtual ~PaintDevice() = default;

    virtual unsigned getWidth() const = 0;
    virtual unsigned getHeight() const = 0;

    virtual void drawPixmap(const PPMPixmap &pixmap, unsigned x, unsigned y) = 0;
    virtual void drawText(const std::string &text, unsigned x, unsigned y) = 0;
    virtual void drawRect(unsigned x, unsigned y, unsigned width, unsigned height, unsigned color) = 0;

    virtual void setPixel(unsigned x, unsigned y, unsigned color) = 0;

    virtual void clear() = 0;
    virtual void swapBuffers() = 0;
};

#endif /* PAINTDEVICE_H_ */
