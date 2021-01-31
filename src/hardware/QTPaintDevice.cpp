#include "QTPaintDevice.h"

#include <stdio.h>
#include <stdlib.h>

QTPaintDevice::QTPaintDevice(QPaintDevice *paintDev, const std::string &fontFile) :
    paintDev(paintDev),
    fontPixmap(fontFile)
{
    width = 640;
    height = 480;

    buffer = new uint32_t[width*height];

    screenBuffer = new QImage((uint8_t*)buffer,
                              width, height,
                              width*sizeof(*buffer),
                              QImage::Format_RGB32);
}

QTPaintDevice::~QTPaintDevice()
{
    delete screenBuffer;
    delete[] buffer;
}

void QTPaintDevice::drawPixmap(const PPMPixmap &pixmap, unsigned x, unsigned y)
{
    for(unsigned row = 0; row < pixmap.getHeight(); ++row)
    {
        if(!isInBounds(x, y + row))
            break;

        memcpy(pixelAt(x, y + row), pixmap.pixelAt(0, row), pixmap.getWidth()*4);
    }
}

void QTPaintDevice::drawRect(unsigned x, unsigned y,
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

void QTPaintDevice::drawText(const std::string &text, unsigned x, unsigned y)
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

void QTPaintDevice::drawChar(char chr, unsigned x, unsigned y)
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

uint8_t* QTPaintDevice::pixelAt(unsigned x, unsigned y) const
{
    uint8_t *bufferBytes = (uint8_t*)buffer;
    return &bufferBytes[(x + (y*width))*4];
}

bool QTPaintDevice::isInBounds(unsigned x, unsigned y) const
{
    if(x >= width || y >= height)
        return false;
    return true;
}

void QTPaintDevice::setPixel(unsigned x, unsigned y, unsigned color)
{
    uint32_t *pixel = (uint32_t*)pixelAt(x, y);
    *pixel = color;
}

void QTPaintDevice::clear()
{
    memset(buffer, 0, width*height / sizeof(*buffer));
}

void QTPaintDevice::swapBuffers()
{
    QPainter painter(paintDev);
    painter.drawImage(0, 0, *screenBuffer);
}




