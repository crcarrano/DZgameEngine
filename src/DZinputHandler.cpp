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
 * 03-14-2015	added handling of SDL_USEREVENT							  *
 * 03-07-2015	file created                                              *
 **************************************************************************/


#include "DZinputHandler.h"
#include "DZengine.h"
#include "DZtimer.h"

DZinputHandler::DZinputHandler()
{
	NumJoysticks = 0;
	joystickPtr = new DZarray<DZjoystick*>(0);
}

DZinputHandler::~DZinputHandler()
{
	if (joystickPtr != 0)
	{
		if(NumJoysticks != 0)
		{
			for(unsigned int i = 0; i < NumJoysticks; i++)
			{
				delete (*joystickPtr)[i];
			}
		}
		delete joystickPtr;
	}
}


void DZinputHandler::joystick_init()
{
	if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if(SDL_NumJoysticks() > 0)
	{
		for(int i = 0; i < SDL_NumJoysticks(); i++)
		{
			(*joystickPtr)[i] = new DZjoystick(i);
			NumJoysticks++;
		}
		SDL_JoystickEventState(SDL_ENABLE);
		DZ_LOG(DZ_LOG_TRACE, "Joystick(s) initialized");
	}
	else
	{
		DZ_LOG(DZ_LOG_TRACE, "No connected joystick");
	}
	DZ_LOG1(DZ_LOG_INFO, "Number of detected joysticks:", joystickPtr->getSize());
}

unsigned int DZinputHandler::getJoyNum()
{
	return NumJoysticks;
}

unsigned int DZinputHandler::getJoy_x(unsigned int joy, unsigned int stick)
{
	if (joy < NumJoysticks)
	{
		if (stick == 0)
		{
			return (*joystickPtr)[joy]->getValue(0);
		}
		else
		{
			return (*joystickPtr)[joy]->getValue(3);
		}
	}

	return 0;
}

unsigned int DZinputHandler::getJoy_y(unsigned int joy, unsigned int stick)
{
	if (joy < NumJoysticks)
	{
		if (stick == 0)
		{
			return (*joystickPtr)[joy]->getValue(1);
		}
		else
		{
			return (*joystickPtr)[joy]->getValue(2);
		}
	}

	return 0;
}

bool DZinputHandler::joyButton(unsigned int joy, unsigned int button)
{
	if (joy < NumJoysticks && joystickPtr != 0)
	{
		return (*joystickPtr)[joy]->getButtonStatus(button);
	}
	return false;
}

bool DZinputHandler::mouseButton(MOUSE_BUTTONS button)
{
	return mouse.getButtonStatus(button);
}

unsigned int DZinputHandler::mousePosition(MOUSE_AXIS axis)
{
	return mouse.getValue(axis);
}

SDL_Keycode DZinputHandler::getKey()
{
	return keyboard.getKeycode();
	return 0;
}

void DZinputHandler::eventHandler(DZengine* engine)
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				DZ_LOG(DZ_LOG_TRACE, "Closing application");
				engine->quit();
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keyboard.eventHandler(event);
				break;

			case SDL_JOYAXISMOTION:
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				if (event.jaxis.which < (int) joystickPtr->getSize())
				{
					(*joystickPtr)[event.jaxis.which]->eventHandler(event);
				}
				else
				{
					DZ_LOG1(DZ_LOG_WARN, "wrong joystick id", (int)event.jaxis.which);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION:
				mouse.eventHandler(event);
				break;

			case SDL_USEREVENT:
			{
				SDL_UserEvent user_event = event.user;
				switch (user_event.code)
				{
					case DZ_USER_EVENT_TIMER:
					{
						DZtimer* timer = (DZtimer*) user_event.data1;
						timer->processTimer(timer);
						break;
					}

					default:
						DZ_LOG1(DZ_LOG_WARN, "Undefined user event; code = ", user_event.code);
						break;
				}
				break;
			}

			default:
				break;
		}
	}
}

