/*
 * Rect.cpp
 *
 *  Created on: 14 sty 2021
 *      Author: Adam
 */

#include "Rect.h"

Rect::Rect(int x, int y, int width, int height) :
	x(x), y(y), width(width), height(height)
{

}

bool Rect::intersects(const Rect &other) const
{
	return contains(other.x, other.y) ||
			contains(other.x + other.width, other.y) ||
			contains(other.x, other.y + other.height) ||
			contains(other.x + other.width, other.y + other.height);
}

bool Rect::contains(int Px, int Py) const
{
	return (Px > x && Px < x + width) && (Py > y && Py < y + height);
}
