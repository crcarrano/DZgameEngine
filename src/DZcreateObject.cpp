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

// WARNING	WARNING	WARNING
//
// This file provides the so called Objects Factory.
// It needs to be modified by adding an entry
// for each object derived from DZsdlObject as
// described inside the DZcreateObject function
// itself.


#include "DZlogger.h"
#include "DZobject.h"


/*****************************************************************
 *
 * Name:		DZcreateObject
 *
 * Description:	Used to create a new object among the
 *				full list of available objects for the
 *				application.
 *				When creating a new application, for each
 *				object derived from DZsdlObject an entry
 *				in the switch statement of this function
 *				needs to be created. The entry will simply
 *				create the object and return its pointer
 *				to the caller.
 *
 * Parameters:	object_id - the ID of tehe object to be
 *						    created
 *
 * Return value:The pointer to the object, in its
 *				polymorphed form of DZobject*
 *
 *****************************************************************/
DZobject* DZcreateObject(unsigned int object_id,
						 DZparams* parms_ptr,
						 DZarray<DZobject*>* obj_list)
{
	switch (object_id)
	{
		/*************************************************
		example case - build actual cases like the following:

		case 1:
			return new Object1(parms_ptr, obj_list);
		**************************************************/

		default:
			// the given object_id was not found, which
			// means the developer forgot to add the
			// creation code to this function.
			// If this warning is logged, please
			// provide the missing code.
			DZ_LOG1(DZ_LOG_WARN,
					"Missing object ID creator in DZcreateObject(). ID = ",
					object_id);
			return 0;
	}
}
