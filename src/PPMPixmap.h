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
	PPMPixmap(const char *filename);
	PPMPixmap(const PPMPixmap &other);
	PPMPixmap(PPMPixmap &&other);

	virtual ~PPMPixmap();

	const uint8_t *getData() const {
		return data;
	}

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
};

#endif /* PPMPIXMAP_H_ */
