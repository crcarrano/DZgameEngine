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
 * 03-08-2015	file created                                              *
 **************************************************************************/

#ifndef DZJOYSTICK_H
#define DZJOYSTICK_H

#include "SDL.h"
#include "DZarray.h"

#define MAX_JOY_NAME_SIZE	64
#define JOY_DEAD_ZONE		10000



class DZjoystick
{
	public:
		DZjoystick(unsigned int id);
		~DZjoystick();

		unsigned int getId();
		char* 		 getName();
		unsigned int getAxis();
		unsigned int getTrackballs();
		unsigned int getButtons();
		unsigned int getHats();

		unsigned int getValue(unsigned int axis);
		bool 		 getButtonStatus(unsigned int button_number);

		void 		 eventHandler(SDL_Event& event);

	protected:
	private:
		void init(unsigned int id);

		SDL_Joystick*	joyPtr;
		unsigned int	Id;
		char			Name[MAX_JOY_NAME_SIZE];
		unsigned int	NumAxis;
		unsigned int	NumTrackballs;
		unsigned int	NumButtons;
		unsigned int	NumHats;

		DZarray<unsigned int>*	axisValue;
		DZarray<bool>*		buttonStatus;
};

#endif // DZJOYSTICK_H
