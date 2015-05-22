/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU Lesser General Public License as       *
 *   published by the Free Software Foundation; version 3 of the License. *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   Lesser General Public License for more details.                      *
 *   You should have received a copy of the Lesser GNU General Public     *
 *   License along with this program; if not, write to the Free Software  *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 05-21-2015	modified distribution license                             *
 * 03-07-2015	file created                                              *
 **************************************************************************/


#include "DZmouse.h"
#include "DZlogger.h"

DZmouse::DZmouse()
{
	for (int i=0 ; i < MAX_MOUSE_BUTTONS ; i++)
	{
		buttonStatus[i] = false;
	}
}

void DZmouse::eventHandler(SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			DZ_LOG1(DZ_LOG_DEBUG, "MOUSEBUTTONDOWN at ", event.button.timestamp);
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:
					buttonStatus[MOUSE_LEFT] = true;
					break;

				case SDL_BUTTON_MIDDLE:
					buttonStatus[MOUSE_MIDDLE] = true;
					break;

				case SDL_BUTTON_RIGHT:
					buttonStatus[MOUSE_RIGHT] = true;
					break;

				default:
					DZ_LOG1(DZ_LOG_WARN, "Wrong button mouse button number: ", event.button.button);
					break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			DZ_LOG1(DZ_LOG_DEBUG, "MOUSEBUTTONUP at ", event.button.timestamp);
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:
					buttonStatus[MOUSE_LEFT] = false;
					break;

				case SDL_BUTTON_MIDDLE:
					buttonStatus[MOUSE_MIDDLE] = false;
					break;

				case SDL_BUTTON_RIGHT:
					buttonStatus[MOUSE_RIGHT] = false;
					break;

				default:
					DZ_LOG1(DZ_LOG_WARN, "Wrong button mouse button number:", event.button.button);
					break;
			}
			break;

		case SDL_MOUSEMOTION:
			position[MOUSE_X] = event.motion.x;
			position[MOUSE_Y] = event.motion.y;
			return;

		default:
			DZ_LOG1(DZ_LOG_WARN, "Mouse event type not recognized:", event.type);
			break;
	}
}

bool DZmouse::getButtonStatus(MOUSE_BUTTONS button)
{
	if (button < MAX_MOUSE_BUTTONS)
	{
		if (buttonStatus[button] == true)
		{
			buttonStatus[button] = false;
			return true;
		}
		else
		{
			return false;
		}
	}

	DZ_LOG1(DZ_LOG_WARN, "Wrong mouse button:", button);
	return false;
}

unsigned int DZmouse::getValue(MOUSE_AXIS axis)
{
	if (axis < MAX_MOUSE_AXIS)
	{
		return position[axis];
	}

	DZ_LOG1(DZ_LOG_WARN, "Wrong mouse axis:", axis);
	return 0;
}

