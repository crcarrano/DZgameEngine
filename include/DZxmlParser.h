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


#ifndef DZXMLPARSER_H
#define DZXMLPARSER_H


#include "tinyxml2.h"
#include "SDL.h"


using namespace tinyxml2;


typedef enum
{
	 DZ_COLLISION_NONE = 0
	,DZ_COLLISION_BOX
	,DZ_COLLISION_CIRCULAR
} DZ_COLLISION_TYPE;


/*****************************************************************
 *
 * Class:		DZxmlParser
 *
 * Description:	Read and parse the XML configuration file.
 *
 * Interface:	DZxmlParser()
 *
 *				getFirstState()
 *				getNextState()
 *				getStateID()
 *
 *				getFirstTexture()
 *				getNextTexture()
 *				getTesxtureID()
 *				getTextureFilename()
 *
 *				getFirstObject()
 *				getNextObject()
 *				getObjectID()
 *				getObjectXposition()
 *				getObjectYposition()
 *				getObjectXvelocity()
 *				getObjectYvelocity()
 *				getObjectXacceleration()
 *				getObjectYacceleration()
 *				getObjectWidth()
 *				getObjectHeight()
 *				getObjectNumFrames()
 *				getObjectCurrentRow()
 *				getObjectCurrentFrame()
 *				getObjectNumRows()
 *				getObjectTextureID()
 *				getObjectFlipValue()
 *
 *				getMap()
 * 				getMapWidth()
 *				getMapHeight()
 *				getMapTileWidth()
 *				getMapTileWidth()
 *
 *				getFirstTileset()
 *				getNextTileset()
 *
 *				getImage()
 *				getImageSourceFile()
 *				getImageWidth()
 *				getImageHeight()
 *
 *				getFirstLayer()
 *				getNextLayer()
 *				getLayerName()
 *				getLayerWidth()
 *				getLayerHeight()
 *
 *				getFirstTile()
 *				getNextTile()
 *				getTileGID()
 *				getTilesetID()
 *				getTilesetTileWidth()
 *				getTilesetTileHeight()
 *				getTilesetSpacing()
 *				getTilesetMargin()
 *				getTilesetFirstGID()
 *
 ****************************************************************/

class DZxmlParser
{
	public:
		DZxmlParser(const char* filename);

		XMLElement*			getFirstState();
		XMLElement*			getNextState();
		XMLElement*			getFirstTexture();
		XMLElement*			getNextTexture();
		XMLElement*			getFirstObject();
		XMLElement*			getNextObject();

		XMLElement*			getMap();
		XMLElement*			getFirstTileset();
		XMLElement*			getNextTileset();
		XMLElement*			getImage();
		XMLElement*			getFirstLayer();
		XMLElement*			getNextLayer();
		XMLElement*			getFirstTile();
		XMLElement*			getNextTile();

		unsigned int		getStateID();
		const char*			getStateLevel();

		unsigned int		getTextureID();
		const char*			getTextureFilename();

		unsigned int		getObjectID();
		DZ_COLLISION_TYPE	getCollisionType();
		float				getObjectXposition();
		float				getObjectYposition();
		float				getObjectXvelocity();
		float				getObjectYvelocity();
		float				getObjectXacceleration();
		float				getObjectYacceleration();
		float				getObjectXrotationCenter();
		float				getObjectYrotationCenter();
		float				getObjectAngularPosition();
		float				getObjectAngularVelocity();
		float				getObjectAngularAcceleration();
		unsigned int		getObjectWidth();
		unsigned int		getObjectHeight();
		unsigned int		getObjectNumFrames();
		unsigned int		getObjectCurrentRow();
		unsigned int		getObjectCurrentFrame();
		unsigned int		getObjectNumRows();
		unsigned int		getObjectTextureID();
		SDL_RendererFlip	getObjectFlipValue();

		unsigned int		getMapWidth();
		unsigned int		getMapHeight();
		unsigned int		getMapTileWidth();
		unsigned int		getMapTileHeight();

		unsigned int		getTilesetID();
		unsigned int		getTilesetTileWidth();
		unsigned int		getTilesetTileHeight();
		unsigned int		getTilesetSpacing();
		unsigned int		getTilesetMargin();
		unsigned int		getTilesetFirstGID();

		const char*			getImageSourceFile();
		unsigned int		getImageWidth();
		unsigned int		getImageHeight();

		unsigned int		getLayerID();
		unsigned int		getLayerWidth();
		unsigned int		getLayerHeight();

		unsigned int		getTileGID();

	protected:
	private:
		XMLDocument	doc;
		XMLElement*	currentState;
		XMLElement*	currentTexture;
		XMLElement*	currentObject;
		XMLElement*	currentMap;
		XMLElement*	currentTileset;
		XMLElement*	currentImage;
		XMLElement*	currentLayer;
		XMLElement*	currentTile;
};

#endif // DZXMLPARSER_H
