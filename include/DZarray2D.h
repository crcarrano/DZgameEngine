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
 * Class:			DZarray2D
 *
 * Description:		Bidimensional array template class
 *
 *					The class defines an array of adjustable
 *					size. If adding an entry at an index beyond
 *					the max, the array expands itself to cover
 *					that index. It is also possible to manually
 *					resize the array to a smaller or bigger size.
 *
 * Interface:		DZarray2D()						class constructor
 *					DZarray2D(width, height) 		class constructor
 *					~DZarray()						class destructor
 *					resize(new_width, new_height)	resize the array
 *													if new_size >= current size
 *														all entries are preserved
 *													if new_size < current size
 *														elements above last available
 *														new index are lost
 *					value(x, y)						reference item at the given indexes
 *					getSize()						returns total number of elements
 *					getWidth()						returns the width of the array
 *														(number of columns)
 *					getHeight()						returns the height of the array
 *														(number of rows)
 *					store(filename)					store array to disk
 *					retrieve(filename)				retrieve array from disk
 *
 ****************************************************************/



#ifndef DZARRAY2D_H
#define DZARRAY2D_H

#include "DZlogger.h"
#include <iostream>
#include <fstream>


template <class T> class DZarray2D
{
	public:
		//--------------------------------------------------------
		// Name:	DZarray2D::DZarray2D
		// Description:	constructor
		// Arguments:	none - creates an array of size 0,0 that
		//		       can be later resized
		//--------------------------------------------------------
		DZarray2D()
		{
			DZ_LOG(DZ_LOG_TRACE, "Constructing DZarray2D of size 0");
			ArrayPtr = new T[0];
			if (ArrayPtr != 0)
			{
				Width = 0;
				Height = 0;
			}
			else
			{
				DZ_LOG(DZ_LOG_WARN, "Unable to allocate DZarray2D of size 0");
			}
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::DZarray2D
		// Description:	constructor
		// Arguments:	width  - initial width of the array
		//		height - initial heigth of the array
		//--------------------------------------------------------
		DZarray2D(unsigned int width, unsigned int height)
		{
			DZ_LOG2(DZ_LOG_TRACE, "Constructing DZarray2D of size ", width, height);
			ArrayPtr = new T[width * height];

			if (ArrayPtr != 0)
			{
				Width = width;
				Height = height;
				memset((void *)ArrayPtr, 0, width * height * sizeof(T));
			}
			else
			{
				Width = 0;
				Height = 0;
				DZ_LOG2(DZ_LOG_WARN, "Unable to allocate DZarray of size ", width, height);
			}
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::~DZarray2D
		// Description:	destructor
		// Arguments:	n/a
		//--------------------------------------------------------
		~DZarray2D()
		{
			DZ_LOG(DZ_LOG_TRACE, "Destroying DZarray2D");
			if (ArrayPtr != 0)
			{
				delete[] ArrayPtr;
			}
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::resize
		// Description:	resize the array to a new size
		// Arguments:	new_width  - the new width size
		//		new_height - the new hieght size
		//--------------------------------------------------------
		void resize(unsigned int new_width, unsigned int new_height)
		{
			T *tmp_ArrayPtr;
			unsigned int	min_width;
			unsigned int	min_height;

			DZ_LOG2(DZ_LOG_TRACE, "Changing DZarray2D size to ", new_width, new_height);

			tmp_ArrayPtr = new T[new_width * new_height];
			if (tmp_ArrayPtr == 0)
			{
				// failed to change the size, so leave it as is
				DZ_LOG(DZ_LOG_WARN, "Unable to change DZarray2D size");
				return;
			}

			memset((void *)tmp_ArrayPtr, 0, new_width * new_height * sizeof(T));

			if (new_width < Width)
			{
				min_width = new_width;
			}
			else
			{
				min_width = Width;
			}

			if (new_height < Height)
			{
				min_height = new_height;
			}
			else
			{
				min_height = Height;
			}

			for (unsigned int y=0 ; y < min_height ; y++)
			{
				unsigned int t_new = y * new_width;
				unsigned int t_old = y * Width;

				for (unsigned int x=0 ; x < min_width ; x++)
				{
					tmp_ArrayPtr[t_new + x] = ArrayPtr[t_old + x];
				}
			}

			Width = new_width;
			Height = new_height;
			if (ArrayPtr != 0) delete[] ArrayPtr;
			ArrayPtr = tmp_ArrayPtr;
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::value
		// Description:	references item at the given indexes
		// Arguments:	x, y - indexes at which to reference item
		//--------------------------------------------------------
		T& value(unsigned int x, unsigned int y)
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");
			return ArrayPtr[y * Width + x];
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::getSize
		// Description:	returns total number of elements
		// Arguments:	n/a
		//--------------------------------------------------------
		unsigned int getSize()
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");
			return Width * Height;
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::getWidth
		// Description:	returns the width of the array (number of
		//		columns)
		// Arguments:	n/a
		//--------------------------------------------------------
		unsigned int getWidth()
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");
			return Width;
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::getHeight
		// Description:	returns the height of the array (number of
		//		rows)
		// Arguments:	n/a
		//--------------------------------------------------------
		unsigned int getHeight()
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");
			return Height;
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::store
		// Description:	store array to disk
		// Arguments:	filename - where to store the object
		//--------------------------------------------------------
		bool store(const char* fileName)
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");

			ofstream outFile(fileName, ios::out);
			if (outFile == 0)
			{
				DZ_LOG(DZ_LOG_WARN, "Cannot open file for writing");
				return false;
			}

			outFile << Width << '\n';
			outFile << Height << '\n';

			for (unsigned int i=0 ; i < (Width * Height) ; i++)
			{
				outFile << ArrayPtr[i] << '\n';
			}

			outFile.close();

			return true;
		}

		//--------------------------------------------------------
		// Name:	DZarray2D::retrieve
		// Description:	retrieve array from disk
		// Arguments:	filename - where to retrieve the object from
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

			inFile >> Width;
			inFile >> Height;

			resize(Width, Height);

			for (unsigned int i=0 ; i < (Width * Height) ; i++)
			{
				inFile >> ArrayPtr[i];
			}

			inFile.close();

			return true;
		}

	protected:
	private:
		T*				ArrayPtr;
		unsigned int	Width;
		unsigned int 	Height;
};

#endif // DZARRAY2D_H
