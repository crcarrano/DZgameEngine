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
 * 03-10-2015	file created                                              *
 **************************************************************************/


#include "DZlevel.h"
#include "DZlogger.h"
#include "DZxmlParser.h"
#include "DZstate.h"


DZlevel::DZlevel(DZstate* state_ptr)
{
	DZ_LOG(DZ_LOG_TRACE, "Creating level");

	layerList = new DZarray<DZlayer*>;
	tilesetList = new DZarray<TILESET*>;
	statePtr = state_ptr;
}


DZlevel::~DZlevel()
{
	DZ_LOG(DZ_LOG_TRACE, "Destroying level");
}


void DZlevel::onEnter(const char* filename)
{
	unsigned int i,j;
	TILESET* ts_ptr;

	DZxmlParser doc(filename);

	if (doc.getMap() == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No map description");
		return;
	}

	// read list of tilesets and store it

	if (doc.getFirstTileset() == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No tileset description");
		return;
	}

	i = 0;
	do
	{
		ts_ptr = new TILESET;
		ts_ptr->firstGridID =	doc.getTilesetFirstGID();
		ts_ptr->tileWidth =		doc.getTilesetTileWidth();
		ts_ptr->tileHeight =	doc.getTilesetTileHeight();
		ts_ptr->spacing =		doc.getTilesetSpacing();
		ts_ptr->margin =		doc.getTilesetMargin();
		doc.getImage();
		ts_ptr->width =			doc.getImageWidth();
		ts_ptr->height =		doc.getImageHeight();
		ts_ptr->numColumns =	ts_ptr->width / (ts_ptr->tileWidth + ts_ptr->spacing);
		ts_ptr->numRows = 		ts_ptr->height / (ts_ptr->tileHeight + ts_ptr->spacing);
		ts_ptr->id =			doc.getTilesetID();
		(*tilesetList)[i++] =	ts_ptr;
		statePtr->add_texture(doc.getImageSourceFile(), ts_ptr->id);
		doc.getNextTileset();
	}
	while (doc.getTilesetFirstGID() != 0);

	// read list of layers and store it

	if (doc.getFirstLayer() == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No layer description");
		return;
	}

	i = 0;
	do
	{
		DZlayer* l_ptr = new DZlayer();
		l_ptr->setHeight(doc.getLayerHeight());
		l_ptr->setWidth(doc.getLayerWidth());
		l_ptr->setID(doc.getLayerID());
		doc.getFirstTile();
		j = 0;
		do
		{
			l_ptr->setGid(j++, doc.getTileGID());
		}
		while (doc.getNextTile() != 0);

		(*layerList)[i++] = l_ptr;
	}
	while (doc.getNextLayer() != 0);
}


void DZlevel::onExit()
{
	unsigned int list_num;
	unsigned int i;

	list_num = layerList->getSize();
	for (i=0 ; i < list_num ; i++)
	{
		if ((*layerList)[i] != 0)
		{
			delete (*layerList)[i];
		}
	}
	delete layerList;

	list_num = tilesetList->getSize();
	for (i=0 ; i < list_num ; i++)
	{
		if ((*tilesetList)[i] != 0)
		{
			delete (*tilesetList)[i];
		}
	}
	delete tilesetList;
}


void DZlevel::update()
{
}


void DZlevel::render(LAYER_ID layer)
{
	unsigned int	num_tiles;		// number of tiles
	unsigned int	num_tilesets;	// number of tilesets;
	unsigned int	col;			// number of columns in the layer
	unsigned int	row;			// number of rows in the layer
	unsigned int	gt;				// tile GID
	unsigned int	tex;			// texture id;
	DZlayer*		l_ptr;			// pointer to layer
	TILESET*		ts_ptr;			// pointer to tileset
	SDL_Rect 		src;			// source tile
	SDL_Rect 		dst;			// destination tile

	if (layer >= layerList->getSize())
	{
		DZ_LOG1(DZ_LOG_WARN, "layer id out of range: ", layer);
		return;
	}

	l_ptr = (*layerList)[layer];

	col = l_ptr->getWidth();
	row = l_ptr->getHeight();
	num_tiles = col * row;
	num_tilesets = tilesetList->getSize();

	for (unsigned int i = 0 ; i < num_tiles ; i++)
	{
		gt = l_ptr->getGid(i);

		if (gt == 0)
		{
			// this tile does not need to be rendered
			continue;
		}

		tex = 0;
		for (unsigned int j=0 ; j < num_tilesets ; j++)
		{
			ts_ptr = (*tilesetList)[j];
			if ((gt >= ts_ptr->firstGridID) && (gt <= (ts_ptr->firstGridID + ts_ptr->numColumns * ts_ptr->numRows -1)))
			{
				tex = ts_ptr->id;
				break;
			}
		}

		if (tex == 0)
		{
			DZ_LOG(DZ_LOG_WARN, "Could not find tileset");
			return;
		}

		// normalize gt for the specific tileset
		gt -= (ts_ptr->firstGridID -1);

		src.x = ts_ptr->margin +
				(ts_ptr->tileWidth + ts_ptr->spacing) * (gt-1) -
				(ts_ptr->width - ts_ptr->margin) * ((gt-1) / ts_ptr->numColumns);
		src.y = ts_ptr->margin +
				((ts_ptr->spacing + ts_ptr->tileWidth)*((gt-1)/ts_ptr->numColumns));
		src.w = ts_ptr->tileWidth;
		src.h = ts_ptr->tileHeight;

		dst.x = ts_ptr->tileWidth * i -
				(ts_ptr->tileWidth * l_ptr->getWidth()) * (i / l_ptr->getWidth());
		dst.y = ts_ptr->tileHeight * (i / l_ptr->getWidth());
		dst.w = ts_ptr->tileWidth;
		dst.h = ts_ptr->tileHeight;

		statePtr->getTextureManager()->drawTile(tex, &src, &dst);
	}
}



