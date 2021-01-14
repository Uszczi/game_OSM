/*
 * ScorePoint.h
 *
 *  Created on: 14 sty 2021
 *      Author: Adam
 */

#ifndef GUI_SCOREPOINT_H_
#define GUI_SCOREPOINT_H_

#include "GraphicObject.h"

class ScorePoint : public GraphicObject
{
	int x, y;
public:
	ScorePoint(int x, int y);

	virtual void drawTo(PaintDevice &paintDevice) const override;
	virtual Rect boundingRect() const override;
};

#endif /* GUI_SCOREPOINT_H_ */
