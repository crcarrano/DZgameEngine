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


#ifndef DZMOUSE_H
#define DZMOUSE_H

#include "SDL.h"

typedef enum mouse_buttons
{
	 MOUSE_LEFT = 0
	,MOUSE_MIDDLE
	,MOUSE_RIGHT
	,MAX_MOUSE_BUTTONS
} MOUSE_BUTTONS;

typedef enum mouse_axis
{
	 MOUSE_X = 0
	,MOUSE_Y
	,MAX_MOUSE_AXIS
} MOUSE_AXIS;


class DZmouse
{
	public:
		DZmouse();

		void 		 eventHandler(SDL_Event& event);
		bool 		 getButtonStatus(MOUSE_BUTTONS button);
		unsigned int getValue(MOUSE_AXIS axis);

	protected:
	private:
		bool 		 buttonStatus[MAX_MOUSE_BUTTONS];
		unsigned int position[MAX_MOUSE_AXIS];
};

#endif // DZMOUSE_H
