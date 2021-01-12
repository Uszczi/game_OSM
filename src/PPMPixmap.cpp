/*
 * Pixmap.cpp
 *
 *  Created on: 5 sty 2021
 *      Author: Adam
 */

#include "PPMPixmap.h"

#include <cstring>

#include <string>
#include <sstream>

PPMPixmap::PPMPixmap(const std::string &filename) :
	data(nullptr),
	width(640),
	height(480)
{
	std::ifstream ppmFile(filename, std::ios::in | std::ios::binary);

	if(hasHeader(ppmFile))
	{
		std::string header;
		do {
			std::getline(ppmFile, header);			// Skip comments
		} while(header[0] == '#');

		std::stringstream pixmapSize(header);		// Read size
		pixmapSize >> width;
		pixmapSize >> height;

		std::getline(ppmFile, header);				// Skip max color value
	}
	else
	{
		ppmFile.clear();
		ppmFile.seekg(0);
	}

	data = new uint8_t[width*height*4];
	uint8_t *raw = new uint8_t[width*height*3];

	ppmFile.read((char*)raw, width*height*3);
	ppmFile.close();

	convertAndStore(raw);
	delete[] raw;
}

bool PPMPixmap::hasHeader(std::ifstream &file) const
{
	std::string header;
	std::getline(file, header);

	if(header == "P6")
		return true;
	return false;
}

void PPMPixmap::convertAndStore(uint8_t *raw)
{
	unsigned a, b;
	a = b = 0;

	while(a < width*height*4)
	{
		data[a] = raw[b + 2];
		data[a + 1] = raw[b + 1];
		data[a + 2] = raw[b];
		data[a + 3] = 0x00;

		a += 4;
		b += 3;
	}

}

PPMPixmap::PPMPixmap(const PPMPixmap &other) :
	width(other.width),
	height(other.height)
{
	const size_t dataSize = width*height*3;
	data = new uint8_t[dataSize];
	memcpy(data, other.data, dataSize);
}

PPMPixmap::PPMPixmap(PPMPixmap &&other) :
	width(other.width),
	height(other.height)
{
	data = other.data;
	other.data = nullptr;
}

PPMPixmap::~PPMPixmap()
{
	delete[] data;
}

unsigned PPMPixmap::colorAt(unsigned x, unsigned y) const {
	const uint8_t *pixel = pixelAt(x, y);

	return (unsigned)(pixel[0]) |
			((unsigned)(pixel[1]) << 8) |
			((unsigned)(pixel[2]) << 16);
}

PPMPixmap& PPMPixmap::operator=(const PPMPixmap &other)
{
	delete[] data;
	width = other.width;
	height = other.height;

	const size_t dataSize = width*height*3;
	data = new uint8_t[dataSize];
	memcpy(data, other.data, dataSize);

	return *this;
}

PPMPixmap& PPMPixmap::operator=(PPMPixmap &&other)
{
	delete[] data;
	width = other.width;
	height = other.height;

	data = other.data;
	other.data = nullptr;

	return *this;
}

