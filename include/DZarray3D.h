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
 * 03-04-2015	file created                                              *
 **************************************************************************/

/*****************************************************************
 *
 * Class:			DZarray3D
 *
 * Description:		Tridimensional array template class
 *
 *					The class defines an array of adjustable
 *				size. If adding an entry at an index beyond
 *				the max, the array expands itself to cover
 *				that index. It is also possible to manually
 *				resize the array to a smaller or bigger size.
 *
 * Interface:		DZarray3D()									class constructor
 *					DZarray3D(width, height, depth)				class constructor
 *					~DZarray()		class destructor
 *					resize(new_width, new_height, new_depth)	resize the array
 *																if new_size >= current size
 *																	all entries are preserved
 *																if new_size < current size
 *																	elements above last available
 *																	new index are lost
 *					value(x, y, z)								reference item at the given indexes
 *					getSize()									returns total number of elements
 *					getWidth()									returns the width of the array
 *																	(number of columns)
 *					getHeight()									returns the height of the array
 *																	(number of rows)
 *					getDepth()									returns the depth of the array
 *																	(number of planes)
 *					store(filename)								store array to disk
 *					retrieve(filename)							retrieve array from disk
 *
 ****************************************************************/


#ifndef DZARRAY3D_H
#define DZARRAY3D_H


template <class T> class DZarray3D
{
	public:
		//--------------------------------------------------------
		// Name:	DZarray3D::DZarray3D
		// Description:	constructor
		// Arguments:	none - creates an array of size 0,0,0 that
		//		       can be later resized
		//--------------------------------------------------------
		DZarray3D()
		{
			DZ_LOG(DZ_LOG_TRACE, "Constructing DZarray3D of size 0");
			ArrayPtr = new T[0];
			if (ArrayPtr != 0)
			{
				Width = 0;
				Height = 0;
				Depth = 0;
			}
			else
			{
				DZ_LOG(DZ_LOG_WARN, "Unable to allocate DZarray3D of size 0");
			}
		}

		//--------------------------------------------------------
		// Name:	DZarray3D::DZarray3D
		// Description:	constructor
		// Arguments:	width  - initial width of the array
		//		height - initial heigth of the array
		//		depth  - initial depth of the array
		//--------------------------------------------------------
		DZarray3D(unsigned int width, unsigned int height, unsigned int depth)
		{
			DZ_LOG(DZ_LOG_TRACE, "Constructing DZarray3D of given size");
			ArrayPtr = new T[width * height * depth];

			if (ArrayPtr != 0)
			{
				Width = width;
				Height = height;
				Depth = depth;
				memset((void *)ArrayPtr, 0, width * height * depth * sizeof(T));
			}
			else
			{
				Width = 0;
				Height = 0;
				Depth = 0;
				DZ_LOG(DZ_LOG_WARN, "Unable to allocate DZarray of given size");
			}
		}


		//--------------------------------------------------------
		// Name:	DZarray3D::~DZarray3D
		// Description:	destructor
		// Arguments:	n/a
		//--------------------------------------------------------
		~DZarray3D()
		{
			DZ_LOG(DZ_LOG_TRACE, "Destroying DZarray3D");
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
		//		new_depth  - the new depth size
		//--------------------------------------------------------
		void resize(unsigned int new_width, unsigned int new_height, unsigned int new_depth)
		{
			T *tmp_ArrayPtr;
			unsigned int	min_width;
			unsigned int	min_height;
			unsigned int	min_depth;

			DZ_LOG(DZ_LOG_TRACE, "Changing DZarray3D size");

			tmp_ArrayPtr = new T[new_width * new_height * new_depth];
			if (tmp_ArrayPtr == 0)
			{
				// failed to change the size, so leave it as is
				DZ_LOG(DZ_LOG_WARN, "Unable to change DZarray3D size");
				return;
			}

			memset((void *)tmp_ArrayPtr, 0, new_width * new_height * new_depth * sizeof(T));

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

			if (new_depth < Depth)
			{
				min_depth = new_depth;
			}
			else
			{
				min_depth = Depth;
			}

			for (unsigned int z=0 ; z < min_depth ; z++)
			{
				unsigned int z_new = z * new_width * new_height;
				unsigned int z_old = z * Width * Height;

				for (unsigned int y=0 ; y < min_height ; y++)
				{
					unsigned int y_new = y * new_width;
					unsigned int y_old = y * Width;

					for (unsigned int x=0 ; x < min_width ; x++)
					{
						tmp_ArrayPtr[z_new + y_new + x] = ArrayPtr[z_old + y_old + x];
					}
				}
			}

			Width = new_width;
			Height = new_height;
			Depth = new_depth;
			if (ArrayPtr != 0) delete[] ArrayPtr;
			ArrayPtr = tmp_ArrayPtr;
		}

		//--------------------------------------------------------
		// Name:	DZarray3D::value
		// Description:	references item at the given indexes
		// Arguments:	x, y, z - indexes at which to reference item
		//--------------------------------------------------------
		T& value(unsigned int x, unsigned int y, unsigned int z)
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");
			return ArrayPtr[z * Width * Height + y * Width + x];
		}

		//--------------------------------------------------------
		// Name:	DZarray3D::getSize
		// Description:	returns total number of elements
		// Arguments:	n/a
		//--------------------------------------------------------
		unsigned int getSize()
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");
			return Width * Height * Depth;
		}

		//--------------------------------------------------------
		// Name:	DZarray3D::getWidth
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
		// Name:	DZarray3D::getHeight
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
		// Name:	DZarray3D::getDepth
		// Description:	returns the depth of the array (number of
		//		planes)
		// Arguments:	n/a
		//--------------------------------------------------------
		unsigned int getDepth()
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");
			return Depth;
		}

		//--------------------------------------------------------
		// Name:	DZarray3D::store
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
			outFile << Depth << '\n';

			for (unsigned int i=0 ; i < (Width * Height * Depth) ; i++)
			{
				outFile << ArrayPtr[i] << '\n';
			}

			outFile.close();

			return true;
		}

		//--------------------------------------------------------
		// Name:	DZarray3D::retrieve
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
			inFile >> Depth;

			resize(Width, Height, Depth);

			for (unsigned int i=0 ; i < (Width * Height * Depth) ; i++)
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
		unsigned int	Depth;
};

#endif // DZARRAY3D_H
