/*
 * GhostGraphic.cpp
 *
 *  Created on: 19 sty 2021
 *      Author: mateu
 */

#include "GhostGraphic.h"

GhostGraphic::GhostGraphic(Ghost * ghost) :
	ghost_ppm(std::string("static/clyde.ppm"))
{
	this->ghost = ghost;
}

GhostGraphic::~GhostGraphic() {

}

void GhostGraphic::drawTo(PaintDevice &paintDevice) const {
//	const auto pos = pacman->getPos();
//	const auto v = pacman->getSpeed();

	paintDevice.drawPixmap(ghost_ppm, ghost->x, ghost->y);
}

Rect GhostGraphic::boundingRect() const {
//	auto pos = ghost->getPos();
	return Rect(10, 10, 10, 10);

}
