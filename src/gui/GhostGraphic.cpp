/*
 * GhostGraphic.cpp
 *
 *  Created on: 19 sty 2021
 *      Author: mateu
 */

#include "GhostGraphic.h"

GhostGraphic::GhostGraphic(Ghost * ghost, std::string ppm) :
	ghost_ppm(std::string(ppm))
{
	this->ghost = ghost;
}

GhostGraphic::~GhostGraphic() {

}

void GhostGraphic::drawTo(PaintDevice &paintDevice) const {
	const auto pos = ghost->getPos();
	paintDevice.drawPixmap(ghost_ppm, pos.first, pos.second);
}

Rect GhostGraphic::boundingRect() const {
	return Rect(ghost->x + ghost->off_x,
			ghost->y + ghost->off_y,
			ghost_ppm.getWidth(),
			ghost_ppm.getHeight());
}
