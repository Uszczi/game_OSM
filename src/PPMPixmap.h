/*
 * Pixmap.h
 *
 *  Created on: 5 sty 2021
 *      Author: Adam
 */

#ifndef PPMPIXMAP_H_
#define PPMPIXMAP_H_

#include <stdint.h>
#include <fstream>

class PPMPixmap {
	uint8_t *data;
	unsigned width, height;

public:
	PPMPixmap(const std::string &filename);
	PPMPixmap(const PPMPixmap &other);
	PPMPixmap(PPMPixmap &&other);

	virtual ~PPMPixmap();

	const uint8_t *getData() const {
		return data;
	}

	const uint8_t *pixelAt(unsigned x, unsigned y) const {
		return &data[(x + (y*width))*4];
	}

	unsigned colorAt(unsigned x, unsigned y) const;

	unsigned getWidth() const {
		return width;
	}

	unsigned getHeight() const {
		return height;
	}

	PPMPixmap& operator=(const PPMPixmap &other);
	PPMPixmap& operator=(PPMPixmap &&other);

private:
	bool hasHeader(std::ifstream &file) const;
	void convertAndStore(uint8_t *raw);
};

#endif /* PPMPIXMAP_H_ */
