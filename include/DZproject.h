#ifndef DZPROJECT_H_INCLUDED
#define DZPROJECT_H_INCLUDED

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
 * 03-13-2015	removed references to default state						  *
 * 03-09-2015	file created                                              *
 **************************************************************************/

#include "DZarray.h"

// Forward declarations
class DZobject;
class DZparams;


/*****************************************************************
 *
 * Component:		DZproject.h
 *
 * Description:		This file lists all the specific definitions
 *					for the application being developed.
 *					Update all the definitions in this file
 *					with the appropriate information for the
 *					application you are developing.
 *
 ****************************************************************/

// The name of the XML configuration file used for this application
#define DZCONFIGFILE	"./config/DZconfig.xml"

// Physics constants
#define FPS			60					// frames per second
#define DELAY_TIME	(1000.0f / FPS)		// main loop total delay time

// global function declarations
extern DZobject* DZcreateObject(unsigned int object_id,
								DZparams* parms_ptr,
								DZarray<DZobject*>* obj_list);

#endif // DZPROJECT_H_INCLUDED
