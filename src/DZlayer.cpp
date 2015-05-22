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



#include "DZlayer.h"
#include "DZlogger.h"


DZlayer::DZlayer()
{
	DZ_LOG(DZ_LOG_TRACE, "Creating layer");
	Width = 0;
	Height = 0;
	Id = 0;
}


DZlayer::~DZlayer()
{
	DZ_LOG(DZ_LOG_TRACE, "Destroying layer");
}



void DZlayer::setWidth(unsigned int width)
{
	Width = width;
}


void DZlayer::setHeight(unsigned int height)
{
	Height = height;
}


void DZlayer::setGid(unsigned int index, unsigned int gid)
{
	Gid[index] = gid;
}


void DZlayer::setID(unsigned int id)
{
	Id = id;
}


unsigned int DZlayer::getWidth()
{
	return Width;
}


unsigned int DZlayer::getHeight()
{
	return Height;
}


unsigned int DZlayer::getGid(unsigned int index)
{
	return Gid[index];
}

unsigned int DZlayer::getGidNum()
{
	return Gid.getSize();
}

unsigned int DZlayer::getID()
{
	return Id;
}

