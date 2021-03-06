#ifndef DZPROJECT_H_INCLUDED
#define DZPROJECT_H_INCLUDED

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

// Intro music
#define DZ_INTRO_MUSIC_FILE	"assets/intro.wav"
#define	DZ_INTRO_AVAILABLE	true
//#define	DZ_INTRO_AVAILABLE	false

// Physics constants
#define FPS			60					// frames per second
#define DELAY_TIME	(1000.0f / FPS)		// main loop total delay time

// List of the user defined events that can be processed in
// DZinputHandler::eventHandler()
typedef enum
{
	 DZ_USER_EVENT_NONE = 0
	,DZ_USER_EVENT_TIMER
} DZ_USER_EVENT;


// global function declarations
extern DZobject* DZcreateObject(unsigned int object_id,
								DZparams* parms_ptr,
								DZarray<DZobject*>* obj_list);

#endif // DZPROJECT_H_INCLUDED
