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

#ifndef DZLEVEL_H
#define DZLEVEL_H

#include "DZarray.h"
#include "DZlayer.h"

typedef struct tileSet
{
	unsigned int	firstGridID;	// gid
	unsigned int	tileWidth;		// tile width in pixels
	unsigned int	tileHeight;		// tile height in pixels
	unsigned int	spacing;		// space between tiles in texture image
	unsigned int	margin;			// margin at the edge of the whole picture
	unsigned int	width;			// tileset image width in pixels
	unsigned int	height;			// tileset image height in pixels
	unsigned int	numColumns;		// width / (tileWidth + spacing)
	unsigned int	numRows;		// height / (tileHeight + spacing)
	unsigned int	id;				// ID of the tileset; identifies the texture
} TILESET;


// add further layer ID before LAYER_MAX_ID
typedef enum
{
	 LAYER_BACKGROUND = 0
	,LAYER_FOREGROUND
	,LAYER_TOP
	,LAYER_MAX_ID
} LAYER_ID;


class DZstate;


class DZlevel
{
	public:
		DZlevel(DZstate* state_ptr);
		~DZlevel();

		void onEnter(const char* filename);
		void onExit();

		void update();
		void render(LAYER_ID layer);

	protected:
	private:
		DZarray<DZlayer*>*	 layerList;
		DZarray<TILESET*>*	 tilesetList;
		DZstate*	  		 statePtr;
};

#endif // DZLEVEL_H
