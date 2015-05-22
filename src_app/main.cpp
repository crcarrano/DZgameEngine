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

/* Test program for DZgameEngine */


/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 05-21-2015	modified distribution license                             *
 * 03-07-2015	file created                                              *
 **************************************************************************/

#include "DZlogger.h"
#include "DZengine.h"


int main(int argc, char* argv[])
{
	DZengine myApp;

	if (myApp.init("Example application", 200, 100, 640, 480, DZ_WIN_NO_ATTR) == true)
	{
		myApp.exec();
	}
	else
	{
		DZ_LOG(DZ_LOG_WARN, "Failed to initialize engine");
		return 1;
	}

	DZ_LOG(DZ_LOG_TRACE, "Successfully executed DZgameEngine test program");
	return 0;
}
