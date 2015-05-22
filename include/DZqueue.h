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
 * 03-06-2015	file created                                              *
 **************************************************************************/


#ifndef DZQUEUE_H
#define DZQUEUE_H

#include "DZlist.h"


/*****************************************************************
 *
 * Class:		DZqueue
 *
 * Description:	Queue implementation with single linked list
 *
 * Interface:	The class inherits from DZlist
 *				and can use all the exposed methods of it.
 *				In addition, the following methods are
 *				provided to implement the actual stack:
 *				Push(data)	- adds an entry at the
 *							  input of the queue
 *				Pop()		- deletes the entry at
 *							  the output of the queue
 *				Front()		- returns a reference
 *							  to the entry at the output
 *							  of the queue
 *				isEmpty()	- returns 'true' if the
 *							  queue is empty
 *
 ****************************************************************/


template <class T> class DZqueue : public DZlist<T>
{
	public:
		//--------------------------------------------------------
		// Name:		DZqueue::Push
		// Description:	Push the given data to the input of the queue
		// Arguments:	data - the data to be stored in the queue
		//--------------------------------------------------------
		void Push(T data)
		{
			DZlist<T>::Append(data);
		}

		//--------------------------------------------------------
		// Name:		DZqueue::Pop
		// Description:	Removes the entry at the output of the queue.
		// Arguments:	n/a
		//--------------------------------------------------------
		void Pop(void)
		{
			DZlist<T>::headRemove();
		}

		//--------------------------------------------------------
		// Name:		DZqueue::Front
		// Description:	Returns a reference to the data at the output
		//				of the queue
		// Arguments:	n/a
		//--------------------------------------------------------
		T& Front()
		{
			return DZlist<T>::get_headPtr()->Data;
		}

		//--------------------------------------------------------
		// Name:		DZqueue::isEmpty
		// Description:	Returns 'true' if the queue is empty;
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

#endif // DZQUEUE_H
