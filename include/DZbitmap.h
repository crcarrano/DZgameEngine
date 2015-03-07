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

/***************************************************************************
 * Change Log                                                              *
 *-------------------------------------------------------------------------*
 * 03-04-2015	file created                                               *
 ***************************************************************************/

/*****************************************************************
 *
 * Class:			DZbitmap
 *
 * Description:		Monodimentional bitmap template class
 *
 *					The class defines a bitmap of adjustable
 *					size. If adding an entry at an index beyond
 *					the max, the bitmap expands itself to cover
 *					that index. It is also possible to manually
 *					resize the bitmap to a smaller or bigger size.
 *					The bitmap is made up of a number of cells of
 *					type int. The number of bits per cell depends
 *					on the platform. The class adjusts automatically
 *					to different int type sizes.
 *
 * Interface:		DZbitmap()			class constructor
 *					DZbitmap(size)		class constructor
 *					~DZbitmap()			class destructor
 *					resize(new_size)	resize the bitmap
 *											if new_size >= current size
 *												all entries are preserved
 *											if new_size < current size
 *												elements above last available
 *												new index are lost
 *					[]					index operator
 *					set(index, value)	set to the value the bit at the
 *											given index
 *					clearAll()			set all the bits to 0 (false)
 *					setAll()			set all the bits to 1 (true)
 *					getSize()			returns current bitmap size in
 *											number of cells
 *					getCell(index)		retrieves the value of the whole
 *											cell at given index
 *					*					operator pointer to the bitmap
 *					store(filename)		store bitmap to disk
 *					retrieve(filename)	retrieve bitmap from disk
 *
 ****************************************************************/

#ifndef DZBITMAP_H
#define DZBITMAP_H


#include "DZlogger.h"
#include <iostream>
#include <fstream>

using namespace std;

#define CELL_SIZE (sizeof(int) * 8)


class DZbitmap
{
	public:
		//--------------------------------------------------------
		// Name:	DZbitmap::DZbitmap
		// Description:	constructor
		// Arguments:	none - creates an array of size 0 that
		//		       can be later resized
		//--------------------------------------------------------
		DZbitmap()
		{
			DZ_LOG(DZ_LOG_TRACE, "Constructing DZbitmap of size 0");
			ArraySize = 0;
			ArrayPtr = 0;
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::DZbitmap
		// Description:	constructor
		// Arguments:	none - creates an array of given size in bits
		//--------------------------------------------------------
		DZbitmap(unsigned int size)
		{
			DZ_LOG1(DZ_LOG_TRACE, "Constructing DZbitmap of size ", size);
			ArraySize = 0;
			ArrayPtr = 0;
			resize(size);
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::~DZbitmap
		// Description:	destructor
		// Arguments:	none
		//--------------------------------------------------------
		~DZbitmap()
		{
			DZ_LOG(DZ_LOG_TRACE, "Destroying DZbitmap");
			if (ArrayPtr != 0)
			{
				delete[] ArrayPtr;
			}
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::resize
		// Description:	resize the array to a new size
		// Arguments:	new_size - the new array size in bits
		//--------------------------------------------------------
		void resize(unsigned int new_size)
		{
			DZ_LOG2(DZ_LOG_TRACE, "Changing DZbitmap size (from, to) ", ArraySize, new_size/CELL_SIZE + 1);

			unsigned int i;

			unsigned int newArraySize = new_size / CELL_SIZE + 1;

			int* newArrayPtr = 0;

			newArrayPtr = new int[newArraySize];
			if (newArrayPtr == 0)
			{
				DZ_LOG(DZ_LOG_WARN, "Unable to allocate new DZbitmap size");
				return;
			}

			for (i=0 ; i < newArraySize ; i++)
			{
				newArrayPtr[i] = 0x00;
			}

			// find the minimum size between the old and new bitmap
			unsigned int min = ArraySize;
			if (ArraySize > newArraySize)
			{
				min = newArraySize;
			}

			// copy cells from old to new array
			if (ArrayPtr != 0)
			{
				for (unsigned int i=0 ; i < min ; i++)
				{
					newArrayPtr[i] = ArrayPtr[i];
				}
				// delete old bitmap
				delete[] ArrayPtr;
			}

			// update internal attributes for new bitmap
			ArraySize = newArraySize;
			ArrayPtr = newArrayPtr;
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::operator[]
		// Description:	gets reference to the indexed item
		// Arguments:	index - index of the item
		// Return value:reference to the item of given index
		//--------------------------------------------------------
		bool operator[] (unsigned int index)
		{
			DZ_LOG(DZ_LOG_TRACE, "using operator []");

			unsigned int cell = index / CELL_SIZE;
			unsigned int bit  = index % CELL_SIZE;

			if ((ArrayPtr[cell] & (1 << bit)) != 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::set
		// Description:	sets a given bit within the array
		// Arguments:	index - the position in the array
		//		value - the value to which the bt is set
		//--------------------------------------------------------
		void set(unsigned int index, bool value)
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering ...");

			unsigned int cell = index / CELL_SIZE;
			unsigned int bit  = index % CELL_SIZE;

			int mask = 0x01 << bit;

			if (value == true)
			{
				ArrayPtr[cell] |= mask;
			}
			else
			{
				ArrayPtr[cell] &= ~mask;
			}
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::clearAll
		// Description:	set to 0 the content of the entire array
		// Arguments:	none
		//--------------------------------------------------------
		void clearAll()
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering ...");

			for (unsigned int i=0 ; i < ArraySize ; i++)
			{
				ArrayPtr[i] = 0x00;
			}
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::setAll
		// Description:	set to 1 the content of the entire array
		// Arguments:	none
		//--------------------------------------------------------
		void setAll()
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering ...");

			for (unsigned int i=0 ; i < ArraySize ; i++)
			{
				ArrayPtr[i] = (int)-1;
			}
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::getSize
		// Description:	retrieves the size of the array in number
		//		of bits
		// Arguments:	n/a
		// Return value:the size of the array
		//--------------------------------------------------------
		unsigned int getSize()
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering ...");
			return ArraySize * CELL_SIZE;
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::getCell
		// Description:	retrieves the value of a whole cell
		// Arguments:	index - the index of the cell being retrieved
		// Return value:the content of the cell, or 0 if the index is
		//		wrong
		//--------------------------------------------------------
		int getCell(unsigned int index)
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering ...");

			if (index < ArraySize)
			{
				return ArrayPtr[index];
			}
			else
			{
				return 0;
			}
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::operator T*
		// Description:	conversion operator
		// Arguments:	n/a
		// Return value:pointer to the array
		//--------------------------------------------------------
		operator int* ()
		{
			DZ_LOG(DZ_LOG_TRACE, "Using operator *");
			return ArrayPtr;
		}

		//--------------------------------------------------------
		// Name:	DZbitmap::store
		// Description:	store array to disk
		// Arguments:	filename where to store the array
		// Return value:n/a
		//--------------------------------------------------------
		bool store(const char* fileName)
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering...");

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
		// Name:	DZbitmap::retrieve
		// Description:	retrieve array from disk
		// Arguments:	filename from which to retrieve the array
		// Return value:n/a
		//--------------------------------------------------------
		bool retrieve(const char* fileName)
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");

			std::ifstream inFile(fileName, ios::in);
			if (inFile == 0)
			{
				DZ_LOG(DZ_LOG_WARN, "Cannot open file for reading");
				return false;
			}

			inFile >> ArraySize;

			resize(ArraySize * CELL_SIZE);

			for (unsigned int i=0 ; i < ArraySize ; i++)
			{
				inFile >> ArrayPtr[i];
			}

			inFile.close();

			return true;
		}

	protected:
	private:
		int*		ArrayPtr;	// pointer to the array of cells making the bitmap
		unsigned int	ArraySize;	// the number of cells making the bitmap
};

#endif // DZBITMAP_H
