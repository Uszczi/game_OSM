#ifndef QTPAINTDEVICE_H
#define QTPAINTDEVICE_H

#include "PaintDevice.h"

#include "../gui/PPMPixmap.h"
#include <string>

#include <QPaintDevice>
#include <QPainter>
#include <QImage>

class QTPaintDevice : public PaintDevice
{
private:
    QPaintDevice* paintDev;
    QImage *screenBuffer;
    uint32_t *buffer;

    PPMPixmap fontPixmap;
    unsigned width, height;

public:
    QTPaintDevice(QPaintDevice* paintDev, const std::string &fontFile);
    virtual ~QTPaintDevice();

    unsigned getWidth() const override {
        return width;
    }

    unsigned getHeight() const override {
        return height;
    }

    void drawPixmap(const PPMPixmap &pixmap, unsigned x, unsigned y) override;
    void drawText(const std::string &text, unsigned x, unsigned y) override;
    void drawRect(unsigned x, unsigned y, unsigned width, unsigned height, unsigned color) override;

    void setPixel(unsigned x, unsigned y, unsigned color) override;

    void clear() override;
    void swapBuffers() override;

private:
    void drawChar(char chr, unsigned x, unsigned y);
    uint8_t *pixelAt(unsigned x, unsigned y) const;

    bool isInBounds(unsigned x, unsigned y) const;
};

#endif // QTPAINTDEVICE_H
