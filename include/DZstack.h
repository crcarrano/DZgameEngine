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
 * 03-06-2015	file created                                              *
 **************************************************************************/



#ifndef DZSTACK_H
#define DZSTACK_H

#include "DZlogger.h"
#include "DZlist.h"

/*****************************************************************
 *
 * Class:		DZstack
 *
 * Description:	Implementation of a stack with single
 *				linked list
 *
 * Interface:	The class inherits from DZlist
 *				and can use all the exposed methods of it.
 *				In addition, the following methods are
 *				provided to implement the actual stack:
 *				Push(data)	- adds an entry on top
 *							  of the stack
 *				Pop()		- deletes the entry at
 *							  the top of the stack
 *				Top()		- returns a reference
 *							  to the entry at the top
 *							  of the stack
 *				isEmpty()	- returns 'true' if the
 *							  stack is empty
 *
 ****************************************************************/

template <class T> class DZstack : public DZlist<T>
{
	public:
		//--------------------------------------------------------
		// Name:		DZstack::Push
		// Description:	Push the given data to the top of the stack
		// Arguments:	data - the data to be stored on the stack
		//--------------------------------------------------------
		void Push(T data)
		{
			DZlist<T>::Prepend(data);
		}

		//--------------------------------------------------------
		// Name:		DZstack::Pop
		// Description:	Removes the top entry from the stack.
		// Arguments:	n/a
		//--------------------------------------------------------
		void Pop(void)
		{
			DZlist<T>::headRemove();
		}

		//--------------------------------------------------------
		// Name:		DZstack::Top
		// Description:	Returns a reference to the data at the top
		//				of the stack
		// Arguments:	n/a
		//--------------------------------------------------------
		T& Top()
		{
			return DZlist<T>::get_headPtr()->Data;
		}

		//--------------------------------------------------------
		// Name:		DZstack::isEmpty
		// Description:	Returns 'true' if the stack is empty;
		//				returns 'false' otherwise
		// Arguments:	n/a
		//--------------------------------------------------------
		bool isEmpty()
		{
			return (DZlist<T>::getCount() == 0);
		}

	protected:
	private:
};

#endif // DZSTACK_H
