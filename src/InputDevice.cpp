/*
 * InputDevice.cpp
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#include "InputDevice.h"

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

InputDevice::InputDevice()
{
	inputEventsFD = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
}

InputDevice::~InputDevice()
{
	close(inputEventsFD);
}

int InputDevice::getKey()
{
	struct input_event ev;
	int key = 0;

	while (read(inputEventsFD, &ev, sizeof ev) > 0)
	{
		if (ev.type == EV_KEY) {
			key = ev.value ? ev.code : 0;
		}
	}

	return key;
}

