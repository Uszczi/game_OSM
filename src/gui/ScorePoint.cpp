/*
 * ScorePoint.cpp
 *
 *  Created on: 14 sty 2021
 *      Author: Adam
 */

#include "ScorePoint.h"

ScorePoint::ScorePoint(int x, int y) :
	x(x), y(y)
{

}

void ScorePoint::drawTo(PaintDevice &paintDevice) const
{
	paintDevice.drawRect(x, y, 8, 8, 0xffff00);
}

Rect ScorePoint::boundingRect() const
{
	return Rect(x, y, 8, 8);
}
