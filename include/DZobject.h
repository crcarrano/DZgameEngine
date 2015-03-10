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
 * 03-09-2015	file created                                              *
 **************************************************************************/


#ifndef DZOBJECT_H
#define DZOBJECT_H


#include "DZparams.h"


/*****************************************************************
 *
 * Class:		DZobject
 *
 * Description:	Pure virstual class. It is at the base
 *				for the creation of the general objects
 *				that are used in the application.
 *
 * Interface:	draw()		- draws the object
 *				update()	- updates the object params
 *							  based on events and flowing
 *							  of time
 *
 ****************************************************************/
class DZobject
{
	public:
		virtual	     ~DZobject();
		virtual void draw() = 0;
		virtual void update() = 0;

	protected:
		DZobject(const DZparams* params_ptr);

	private:
};

#endif // DZOBJECT_H
