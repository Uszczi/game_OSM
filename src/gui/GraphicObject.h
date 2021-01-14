/*
 * GraphicObject.h
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#ifndef GUI_GRAPHICOBJECT_H_
#define GUI_GRAPHICOBJECT_H_

#include "../hardware/PaintDevice.h"
#include "../misc/Rect.h"

class GraphicObject
{
public:
	virtual ~GraphicObject() = default;
	virtual void drawTo(PaintDevice &paintDevice) const = 0;
	virtual Rect boundingRect() const = 0;

	bool collidesWith(const GraphicObject& other) const {
		return this->boundingRect().intersects(other.boundingRect());
	}
};

#endif /* GUI_GRAPHICOBJECT_H_ */
