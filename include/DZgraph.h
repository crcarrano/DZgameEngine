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
 * 03-14-2015	file created                                              *
 **************************************************************************/


#ifndef DZGRAPH_H
#define DZGRAPH_H


#include "DZengine.h"
#include "DZvector2D.h"


class DZgraph
{
	public:
		DZgraph();
		~DZgraph() {}

		//--------------------------------------------------------
		// Name:		DZgraph::move
		// Description:	position current coordinates
		// Arguments:	x, y
		//--------------------------------------------------------
		void move(float x, float y);

		//--------------------------------------------------------
		// Name:		DZgraph::draw
		// Description:	draw a line from current coordinates to
		//				new given coordinates, then update
		//				current coordinates to the new ones
		// Arguments:	x, y
		//--------------------------------------------------------
		void draw(float x, float y);

		//--------------------------------------------------------
		// Name:		DZgraph::put_pixel
		// Description:	draw a pixel at the given coordinates
		//				then update current coordinates to the new
		//				ones
		// Arguments:	x, y
		//--------------------------------------------------------
		void put_pixel(int X, int Y);

		//--------------------------------------------------------
		// Name:		DZgraph::move
		// Description:	move surrent coordinates to the new ones
		//				given by the vector
		// Arguments:	v
		//--------------------------------------------------------
		void move(DZvector2D& v);

		//--------------------------------------------------------
		// Name:		DZgraph::draw
		// Description:	draw a line from current coordinates to the
		//				new ones given by the vector, then update
		//				current coordinates to the new ones
		// Arguments:	v
		//--------------------------------------------------------
		void draw(DZvector2D& v);

		//--------------------------------------------------------
		// Name:		DZgraph::put_pixel
		// Description:	draw a pixel at the coordinates given by
		//				the vector, then update the current
		//				coordinates to the new ones
		// Arguments:	v
		//--------------------------------------------------------
		void put_pixel(DZvector2D& v);

		//--------------------------------------------------------
		// Name:		DZgraph::horizontal_line
		// Description:	draw an horizontal line
		// Arguments:	x_left
		//				x_right
		//				y
		//--------------------------------------------------------
		void horizontal_line(int x_left, int x_right, int y);

		//--------------------------------------------------------
		// Name:		DZgraph::vertical_line
		// Description:	draw a vertical line
		// Arguments:	x
		//				y_top
		//				y_bottom
		//--------------------------------------------------------
		void vertical_line(int x, int y_top, int y_bottom);

		//--------------------------------------------------------
		// Name:		DZgraph::draw_line
		// Description:	draw a line
		// Arguments:	x1
		//				x2
		//				y1
		//				y2
		//--------------------------------------------------------
		void line(int x1, int y1, int x2, int y2);

		//--------------------------------------------------------
		// Name:		DZgraph::point(int x, int y);
		// Description:	draw a point
		// Arguments:	x, y
		//--------------------------------------------------------
		void point(int x, int y);

		//--------------------------------------------------------
		// Name:		DZgraph::rect
		// Description:	draw a rectangle given the lower left
		//				corner vertex and the upper right corner
		//				vertex
		// Arguments:	x1, y1, x2, y2
		//--------------------------------------------------------
		void rect(int x1, int y1, int x2, int y2);

		//--------------------------------------------------------
		// Name:	DZgraph::filled_rect
		// Description:	draw a filled rectangle given the lower left
		//				corner vertex and the upper right corner
		//				vertex
		// Arguments:	x1, y1, x2, y2
		//--------------------------------------------------------
		void filled_rect(int x1, int y1, int x2, int y2);

		//--------------------------------------------------------
		// Name:		DZgraph::IX
		// Description:	convert to int and normalize X coordinate
		// Arguments:	x
		//--------------------------------------------------------
		int IX(float x);

		//--------------------------------------------------------
		// Name:		DZgraph::IY
		// Description:	convert to int and normalize Y coordinate
		// Arguments:	y
		//--------------------------------------------------------
		int IY(float y);

		//--------------------------------------------------------
		// Name:		DZgraph::set_color
		// Description:	set the foreground color for drawing;
		//				color can be changed while drawing
		// Arguments:	red
		//				green
		//				blue
		//--------------------------------------------------------
		void set_color(Uint8 red, Uint8 green, Uint8 blue);

		float getXcenter();
		float getYcenter();
		float getRmax();

	protected:
	private:
		float	x_min;
		float	x_max;
		float	y_min;
		float	y_max;
		float	x_center;
		float	y_center;
		float	r_max;
		float	density;
		int	X__max;
		int	Y__max;
		int outside;
		int current_x;
		int current_y;

		int plot_coordinate(float x);
};

#endif // DZGRAPH_H
