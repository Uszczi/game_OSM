/*
 * Rect.h
 *
 *  Created on: 14 sty 2021
 *      Author: Adam
 */

#ifndef MISC_RECT_H_
#define MISC_RECT_H_

class Rect {
	int x, y;
	int width, height;

public:
	Rect(int x, int y, int width, int height);

	bool intersects(const Rect& other) const;
	bool contains(int Px, int Py) const;
};

#endif /* MISC_RECT_H_ */
