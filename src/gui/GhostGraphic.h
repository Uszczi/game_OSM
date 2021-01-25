/*
 * GhostGraphic.h
 *
 *  Created on: 19 sty 2021
 *      Author: mateu
 */

#ifndef GUI_GHOSTGRAPHIC_H_
#define GUI_GHOSTGRAPHIC_H_
#include "../game/Ghost.h"
#include "PPMPixmap.h"
#include "GraphicObject.h"

class GhostGraphic : public GraphicObject {
public:
	Ghost * ghost;
	PPMPixmap ghost_ppm;

	GhostGraphic(Ghost *);
	virtual ~GhostGraphic();

	virtual void drawTo(PaintDevice &paintDevice) const override;
	virtual Rect boundingRect() const override;
};

#endif /* GUI_GHOSTGRAPHIC_H_ */
