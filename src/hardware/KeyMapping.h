/*
 * KeyMapping.h
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#ifndef KEYMAPPING_H_
#define KEYMAPPING_H_

#include <QKeyEvent>

enum KeyMapping
{
    KEY_ESC = Qt::Key_Escape,
    KEY_ENTER = Qt::Key_Return,
    KEY_SPACE = Qt::Key_Space,
    ARROW_LEFT = Qt::Key_Left,
    ARROW_UP = Qt::Key_Up,
    ARROW_RIGHT = Qt::Key_Right,
    ARROW_DOWN = Qt::Key_Down
};

#endif /* KEYMAPPING_H_ */
