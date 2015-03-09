/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; version 2 of the License.              *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   General Public License for more details.                             *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 03-08-2015	file created                                              *
 **************************************************************************/

#include "DZjoystick.h"

DZjoystick::DZjoystick(unsigned int id)
{
	axisValue = 0;
	buttonStatus = 0;
	joyPtr = 0;
	init(id);
}

DZjoystick::~DZjoystick()
{
	if (axisValue != 0)
	{
		delete axisValue;
	}
	if (buttonStatus != 0)
	{
		delete buttonStatus;
	}
	if (joyPtr != 0)
	{
		DZ_LOG(DZ_LOG_TRACE, "Closing joystick");
		SDL_JoystickClose(joyPtr);
	}
}

unsigned int DZjoystick::getId()
{
	return Id;
}

char* DZjoystick::getName()
{
	return Name;
}

unsigned int DZjoystick::getAxis()
{
	return NumAxis;
}

unsigned int DZjoystick::getTrackballs()
{
	return NumTrackballs;
}

unsigned int DZjoystick::getButtons()
{
	return NumButtons;
}

unsigned int DZjoystick::getHats()
{
	return NumHats;
}

unsigned int DZjoystick::getValue(unsigned int axis)
{
	return (*axisValue)[axis];
}


void DZjoystick::init(unsigned int id)
{
	char log_buffer[256];

	Id = id;
	joyPtr = SDL_JoystickOpen(id);
	if(joyPtr != 0)
	{
		strncpy(Name, SDL_JoystickName(joyPtr), MAX_JOY_NAME_SIZE-1);
		NumAxis = SDL_JoystickNumAxes(joyPtr);
		NumTrackballs = SDL_JoystickNumBalls(joyPtr);
		NumButtons = SDL_JoystickNumButtons(joyPtr);
		NumHats = SDL_JoystickNumHats(joyPtr);

		snprintf(log_buffer, 256,
				    "Opened Joystick:\n"
				    "\tId:                   %d\n"
				    "\tName:                 %s\n"
				    "\tNumber of axis:       %d\n"
				    "\tNumber of trackballs: %d\n"
				    "\tNumber of buttons:    %d\n"
				    "\tNumber of hats:       %d",
				    Id, Name, NumAxis, NumTrackballs, NumButtons, NumHats);
		DZ_LOG(DZ_LOG_INFO, log_buffer);

		axisValue = new DZarray<unsigned int>(NumAxis);
		buttonStatus = new DZarray<bool>(NumButtons);
		if (buttonStatus != 0)
		{
			for (unsigned int i = 0 ; i < NumButtons ; i++)
			{
				(*buttonStatus)[i] = false;
			}
		}
	}
	else
	{
		DZ_LOG(DZ_LOG_WARN, SDL_GetError());
	}
}

void DZjoystick::eventHandler(SDL_Event& event)
{
	if ((joyPtr == 0) || (axisValue == 0) || (buttonStatus == 0))
	{
		DZ_LOG(DZ_LOG_WARN, "Joystick object not initialized");
		return;
	}

	switch(event.type)
	{
		case SDL_JOYAXISMOTION:
			if (event.jaxis.value > JOY_DEAD_ZONE)
			{
				(*axisValue)[event.jaxis.axis] = 1;
			}
			else if (event.jaxis.value < - JOY_DEAD_ZONE)
			{
				(*axisValue)[event.jaxis.axis] = -1;
			}
			else
			{
				(*axisValue)[event.jaxis.axis] = 0;
			}
			break;

		case SDL_JOYBUTTONDOWN:
			(*buttonStatus)[event.jbutton.button] = true;
			break;

		case SDL_JOYBUTTONUP:
			(*buttonStatus)[event.jbutton.button] = false;
			break;

		default:
			DZ_LOG1(DZ_LOG_WARN, "Joystick event type not recognized:", event.type);
			break;
	}
}



bool DZjoystick::getButtonStatus(unsigned int button_number)
{
	if (buttonStatus == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Joystick object not correctly initialized");
	}
	else if (button_number < NumButtons)
	{
		return (*buttonStatus)[button_number];
	}

	return false;
}
