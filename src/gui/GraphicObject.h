/*
 * GraphicObject.h
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#ifndef GUI_GRAPHICOBJECT_H_
#define GUI_GRAPHICOBJECT_H_

#include "../hardware/PaintDevice.h"

class GraphicObject
{
public:
	virtual ~GraphicObject() = default;
	virtual void drawTo(PaintDevice &paintDevice) const = 0;
};

#endif /* GUI_GRAPHICOBJECT_H_ */
