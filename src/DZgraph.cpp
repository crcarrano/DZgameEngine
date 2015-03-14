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
 * 03-14-2015	file created                                              *
 **************************************************************************/


#include "DZgraph.h"

DZgraph::DZgraph()
{
	x_min = 0;
	x_max = 10;

	outside = 1;

	X__max = DZengine::getWindowWidth();
	Y__max = DZengine::getWindowHeight();
	density = X__max / (x_max - x_min);

	y_min = 0;
	y_max = y_min + Y__max / density;

	x_center = 0.5 * (x_min + x_max);
	y_center = 0.5 * (y_min + y_max);
	r_max = (x_center < y_center ? x_center : y_center);

	current_x = x_center;
	current_y = y_center;
}


void DZgraph::move(float x, float y)
{
	current_x = IX(x);
	current_y = IY(y);
}

void DZgraph::move(DZvector2D& v)
{
	current_x = v.getX();
	current_y = v.getY();
}


void DZgraph::draw(float x, float y)
{
	SDL_RenderDrawLine(DZengine::getRenderer(), current_x, current_y, IX(x), IY(y));
	current_x = IX(x);
	current_y = IY(y);
}

void DZgraph::draw(DZvector2D& v)
{
	SDL_RenderDrawLine(DZengine::getRenderer(), current_x, current_y, IX(v.getX()), IY(v.getY()));
	current_x = IX(v.getX());
	current_y = IY(v.getY());
}


void DZgraph::put_pixel(int X, int Y)
{
	SDL_RenderDrawPoint(DZengine::getRenderer(), X, Y__max - Y);
	current_x = X;
	current_y = Y__max - Y;
}

void DZgraph::put_pixel(DZvector2D& v)
{
	SDL_RenderDrawPoint(DZengine::getRenderer(), IX(v.getX()), Y__max - IY(v.getY()));
	current_x = IX(v.getX());
	current_y = IY(v.getY());
}


void DZgraph::horizontal_line(int x_left, int x_right, int y)
{
	SDL_RenderDrawLine(DZengine::getRenderer(), x_left, Y__max - y, x_right, Y__max - y);
}

void DZgraph::vertical_line(int x, int y_top, int y_bottom)
{
	SDL_RenderDrawLine(DZengine::getRenderer(), x, Y__max - y_top, x, Y__max - y_bottom);
}


void DZgraph::line(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(DZengine::getRenderer(), x1, Y__max - y1, x2, Y__max - y2);
}

void DZgraph::point(int x, int y)
{
	SDL_RenderDrawPoint(DZengine::getRenderer(), x, Y__max - y);
}


void DZgraph::rect(int x1, int y1, int x2, int y2)
{
	SDL_Rect r;
	r.x = x1;
	r.y = Y__max - y1;
	r.w = x2-x1;
	r.h = y1-y2;

	SDL_RenderDrawRect(DZengine::getRenderer(), &r);
}


void DZgraph::filled_rect(int x1, int y1, int x2, int y2)
{
	SDL_Rect r;
	r.x = x1;
	r.y = Y__max - y1;
	r.w = x2-x1;
	r.h = y1-y2;

	SDL_RenderFillRect(DZengine::getRenderer(), &r);
}


void DZgraph::set_color(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawColor(DZengine::getRenderer(), red, green, blue, 255);
}


int DZgraph::plot_coordinate(float x)
{
	return int(1000 * (x) + 0.5);
}


int DZgraph::IX(float x)
{
	int X = int(density * (x - x_min));
	if (X < 0)
	{
		X = 0;
		outside = 1;
	}
	if (X > X__max)
	{
		X = X__max ;
		outside = 1;
	}

	return X;
}

int DZgraph::IY(float y)
{
	int Y = Y__max -int(density * (y - y_min));
	if (Y < 0)
	{
		Y = 0;
		outside = 1;
	}
	if (Y > Y__max)
	{
		Y = Y__max;
		outside = 1;
	}

	return (Y);
}


float DZgraph::getXcenter()
{
	return x_center;
}


float DZgraph::getYcenter()
{
	return y_center;
}


float DZgraph::getRmax()
{
	return r_max;
}


