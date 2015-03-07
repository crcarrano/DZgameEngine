#ifndef DZARRAY_H_INCLUDED
#define DZARRAY_H_INCLUDED

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
 * 03-03-2015	file created                                              *
 **************************************************************************/



/*****************************************************************
 *
 * Class:		DZarray
 *
 * Description:		Monodimentional array template class
 *
 *					The class defines an array of adjustable
 *					size. If adding an entry at an index beyond
 *					the max, the array expands itself to cover
 *					that index. It is also possible to manually
 *					resize the array to a smaller or bigger size.
 *					It is also possible to insert a new entry
 *					between two consecutive indexes, thus
 *					reassigning the higher number indexes; or
 *					removing an entry compacting the indexes for
 *					the reminder of entries.
 *
 * Interface:		DZarray()			class constructor
 *					DZarray(size)		class constructor
 *					~DZarray()			class destructor
 *					resize(new_size)	resize the array
 *										if new_size >= current size
 *										all entries are preserved
 *										if new_size < current size
 *										elements above last available
 *										new index are lost
 *					[]					index operator
 *					insert(item, index)	insert item at the specified
 *										index making space for it
 *										by shifting forward all higher
 *										index elements
 *					remove(index)		remove item at given index
 *										compacting the array by
 *										shifting backward all higher
 *										index elements. Highest index
 *										item is set to 0.
 *					getSize()			returns current array size
 *					*					operator pointer to the array
 *					store(filename)		store array to disk
 *					retrieve(filename)	retrieve array from disk
 *
 ****************************************************************/


#include "DZlogger.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


// fast monodimensional array template class

template <class T> class DZarray
{
	private:
		unsigned int	ArraySize;
		T*				ArrayPtr;

	protected:

	public:
		//--------------------------------------------------------
		// Name:		DZarray::DZarray
		// Description:	constructor
		// Arguments:	none - creates an array of size 0 that
		//		      	can be later resized
		//--------------------------------------------------------
		DZarray()
		{
			ArrayPtr = new T[0];

			if (ArrayPtr != 0)
			{
				ArraySize = 0;
			}
			else
			{
				DZ_LOG(DZ_LOG_WARN, "Unable to allocate DZarray of size 0");
			}
		}



		//--------------------------------------------------------
		// Name:		DZarray::DZarray
		// Description:	constructor
		// Arguments:	size - initial size of the array
		//--------------------------------------------------------
		DZarray(unsigned int size)
		{
			ArrayPtr = new T[size];

			if (ArrayPtr != 0)
			{
				ArraySize = size;
				memset((void *)ArrayPtr, 0, size * sizeof(T));
			}
			else
			{
				ArraySize = 0;
				DZ_LOG1(DZ_LOG_WARN, "Unable to allocate DZarray of size ", size);
			}
		}



		//--------------------------------------------------------
		// Name:		DZarray::~DZarray
		// Description:	destructor
		// Arguments:	n/a
		//--------------------------------------------------------
		~DZarray()
		{
			if (ArrayPtr != 0)
			{
				delete[] ArrayPtr;
			}
		}



		//--------------------------------------------------------
		// Name:		DZarray::resize
		// Description:	resize the array to a new size
		// Arguments:	new_size - the new array size
		//--------------------------------------------------------
		void resize(unsigned int new_size)
		{
			T *tmp_ArrayPtr;
			unsigned int	min_size;

			tmp_ArrayPtr = new T[new_size];
			if (tmp_ArrayPtr == 0)
			{
				// failed to change the size, so leave it as is
				DZ_LOG2(DZ_LOG_WARN, "Unable to change DZarray size (from, to)", ArraySize, new_size);
				return;
			}

			memset((void *)tmp_ArrayPtr, 0, new_size * sizeof(T));

			if (new_size < ArraySize)
			{
				min_size = new_size;
			}
			else
			{
				min_size = ArraySize;
			}

			for (unsigned int i=0 ; i < min_size ; i++)
			{
				tmp_ArrayPtr[i] = ArrayPtr[i];
			}

			ArraySize = new_size;
			if (ArrayPtr != 0) delete[] ArrayPtr;
			ArrayPtr = tmp_ArrayPtr;
		}



		//--------------------------------------------------------
		// Name:		DZarray::operator[]
		// Description:	gets reference to the indexed item
		// Arguments:	index - index of the item
		// Return value:reference to the item of given index
		//--------------------------------------------------------
		T& operator[] (unsigned int index)
		{
			if (index >= ArraySize)
			{
				resize(index+1);
			}
			return ArrayPtr[index];
		}



		//--------------------------------------------------------
		// Name:		DZarray::insert
		// Description:	insert an entry in between two others
		// Arguments:	item  - the item to insert
		//				index - the position where to insert the item
		//--------------------------------------------------------
		void	insert(T item, unsigned int index)
		{
			if (index >= ArraySize)
			{
				resize(index+1);
				ArrayPtr[index] = item;
				return;
			}

			for (unsigned int i=ArraySize-1 ; i > index ; i--)
			{
				ArrayPtr[i] = ArrayPtr[i-1];
			}

			ArrayPtr[index] = item;
		}



		//--------------------------------------------------------
		// Name:		DZarray::remove
		// Description:	remove an item while compacting the array
		// Arguments:	index - the index of the item being removed
		//--------------------------------------------------------
		void	remove(unsigned int index)
		{
			for (unsigned int i=index+1 ; i < ArraySize ; i++)
			{
				ArrayPtr[i-1] = ArrayPtr[i];
			}
			ArrayPtr[ArraySize - 1] = (T) 0;
		}



		//--------------------------------------------------------
		// Name:		DZarray::getSize
		// Description:	retrieves the size of the array
		// Arguments:	n/a
		// Return value:the size of the array
		//--------------------------------------------------------
		unsigned int getSize()
		{
			return ArraySize;
		}



		//--------------------------------------------------------
		// Name:		DZarray::operator T*
		// Description:	conversion operator
		// Arguments:	n/a
		// Return value:pointer to the array
		//--------------------------------------------------------
		operator T* ()
		{
			return ArrayPtr;
		}



		//--------------------------------------------------------
		// Name:		DZarray::store
		// Description:	store array to disk
		// Arguments:	filename where to store the array
		//--------------------------------------------------------
		bool store(const char* fileName)
		{
			ofstream outFile(fileName, ios::out);
			if (outFile == 0)
			{
				DZ_LOG(DZ_LOG_WARN, "Cannot open file for writing");
				return false;
			}

			outFile << ArraySize << '\n';
			for (unsigned int i=0 ; i < ArraySize ; i++)
			{
				outFile << ArrayPtr[i] << '\n';
			}

			outFile.close();

			return true;
		}



		//--------------------------------------------------------
		// Name:		DZarray::retrieve
		// Description:	retrieve array from disk
		// Arguments:	filename from which to retrieve the array
		//--------------------------------------------------------
		bool retrieve(const char* fileName)
		{
			std::ifstream inFile(fileName, ios::in);
			if (inFile == 0)
			{
				DZ_LOG(DZ_LOG_WARN, "Cannot open file for reading");
				return false;
			}

			inFile >> ArraySize;

			resize(ArraySize);

			for (unsigned int i=0 ; i < ArraySize ; i++)
			{
				inFile >> ArrayPtr[i];
			}

			inFile.close();

			return true;
		}
};


#endif // DZARRAY_H_INCLUDED
