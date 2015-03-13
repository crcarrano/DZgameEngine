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
 * 03-10-2015	file created                                              *
 **************************************************************************/



#ifndef DZSTATE_H
#define DZSTATE_H

#include "DZarray.h"
#include "DZobject.h"
#include "DZxmlParser.h"
#include "DZlevel.h"

class DZstateMachine;

/*****************************************************************
 *
 * Class:		DZstate
 *
 * Description:	Pure virtual class. Defines the class of
 *				state objects that make a finite state
 *				machine. All the states of the FSM inherit
 *				from this class
 *
 * Interface:	update()		Update status of all the
 *								general objects.
 *				render()		Renders all the general
 *								objects.
 *				onEnter()		Procedure to be executed
 *								when entering the state.
 *				onExit()		Procedure to be executed
 *								when leaving the state.
 *				getStateID()	returns the state ID.
 *
 ****************************************************************/
class DZstate
{
	public:
		DZstate();
		virtual ~DZstate() {}

		virtual void onEnter();
		virtual void onExit();

		virtual void update();
		virtual void render();

		virtual void add_texture(const char* filename, unsigned int id);
		DZtextureManager* getTextureManager();

		virtual unsigned int getStateID() const = 0;

	protected:
		DZarray<DZobject*>  objectList;
		DZtextureManager*   textureManagerPtr;
		DZlevel*	    	levelPtr;
		DZstateMachine*		fsmPtr;

	private:
};

#endif // DZSTATE_H
