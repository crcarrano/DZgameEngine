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
 * 03-07-2015	file created                                              *
 **************************************************************************/



#ifndef DZINPUTHANDLER_H
#define DZINPUTHANDLER_H

#include "SDL.h"
#include "DZarray.h"
#include "DZkeyboard.h"
#include "DZmouse.h"
#include "DZjoystick.h"

typedef enum mouse_axis 			// CRC remove begin
{
	 MOUSE_X = 0
	,MOUSE_Y
} MOUSE_AXIS;									// CRC remove end


class DZengine;

class DZinputHandler
{
	public:
		DZinputHandler();
		~DZinputHandler();

		void			joystick_init();
		unsigned int	getJoyNum();
		unsigned int	getJoy_x(unsigned int joy, unsigned int stick);
		unsigned int	getJoy_y(unsigned int joy, unsigned int stick);
		bool			joyButton(unsigned int joy, unsigned int button);

		bool			mouseButton(unsigned int button);
		unsigned int	mousePosition(MOUSE_AXIS axis);

		SDL_Keycode		getKey();

		void			eventHandler(DZengine* engine);

	protected:
	private:
		DZmouse					mouse;
		DZkeyboard				keyboard;
		DZarray<DZjoystick*>*	joystickPtr;
		unsigned int			NumJoysticks;
};

#endif // DZINPUTHANDLER_H
