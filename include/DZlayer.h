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
 * 03-10-2015	file created                                              *
 **************************************************************************/


#ifndef DZLAYER_H
#define DZLAYER_H

#include "DZarray.h"





class DZlayer
{
	public:
		DZlayer();
		~DZlayer();

		void setWidth(unsigned int width);
		void setHeight(unsigned int height);
		void setGid(unsigned int index, unsigned int gid);
		void setID(unsigned int id);

		unsigned int getWidth();
		unsigned int getHeight();
		unsigned int getGid(unsigned int index);
		unsigned int getGidNum();
		unsigned int getID();

	protected:
	private:
		DZarray<unsigned int> Gid;	// grid ID
		unsigned int Width;			// width in tiles
		unsigned int Height;		// height in tiles
		unsigned int Id;			// layer ID
};

#endif // DZLAYER_H
