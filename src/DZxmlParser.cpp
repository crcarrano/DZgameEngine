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



#include "DZxmlParser.h"
#include "DZlogger.h"



DZxmlParser::DZxmlParser(const char* filename)
{
	if (doc.LoadFile(filename) != XML_SUCCESS)
	{
		DZ_LOG_STR(DZ_LOG_WARN, "Unable to read XML configuration file", filename);
		exit(-2);
	}
	DZ_LOG_STR(DZ_LOG_TRACE, "Got configuration file", filename);
	currentState = 0;
	currentTexture = 0;
	currentObject = 0;
}

XMLElement* DZxmlParser::getFirstState()
{
	currentState = doc.FirstChildElement("DZENGINE")->FirstChildElement("STATE");
	return currentState;
}

XMLElement* DZxmlParser::getNextState()
{
	if (currentState == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "currentState is not set");
	}
	else
	{
		currentState = currentState->NextSiblingElement();
	}
	return currentState;
}

XMLElement* DZxmlParser::getFirstTexture()
{
	XMLElement* element;

	currentTexture = 0;

	if (currentState == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "currentState is not set");
	}
	else
	{
		element = currentState->FirstChildElement("TEXTURES");
		if (element == 0)
		{
			DZ_LOG(DZ_LOG_WARN, "No available textures");
		}
		else
		{
			currentTexture = element->FirstChildElement("TEXTURE");
			DZ_LOG1(DZ_LOG_TRACE, "Got texture; id =", currentTexture->UnsignedAttribute("id"));
		}
	}
	return currentTexture;
}

XMLElement* DZxmlParser::getNextTexture()
{
	if (currentTexture == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current texture");
	}
	else
	{
		currentTexture = currentTexture->NextSiblingElement();
	}
	return currentTexture;
}

XMLElement* DZxmlParser::getFirstObject()
{
	XMLElement* element;

	currentObject = 0;

	if (currentState == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "currentState is not set");
	}
	else
	{
		element = currentState->FirstChildElement("OBJECTS");
		if (element == 0)
		{
			DZ_LOG(DZ_LOG_WARN, "No available objects");
		}
		else
		{
			currentObject = element->FirstChildElement("OBJECT");
		}
	}
	return currentObject;
}

XMLElement* DZxmlParser::getNextObject()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
	}
	else
	{
		currentObject = currentObject->NextSiblingElement();
	}
	return currentObject;
}



XMLElement* DZxmlParser::getMap()
{
	currentMap = doc.FirstChildElement("map");
	return currentMap;
}

XMLElement* DZxmlParser::getFirstTileset()
{
	currentTileset = getMap()->FirstChildElement("tileset");
	return currentTileset;
}

XMLElement* DZxmlParser::getNextTileset()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
	}
	else
	{
		currentTileset = currentTileset->NextSiblingElement();
	}
	return currentTileset;
}

XMLElement* DZxmlParser::getImage()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
		currentImage = 0;
	}
	else
	{
		currentImage = currentTileset->FirstChildElement("image");
	}
	return currentImage;
}

XMLElement* DZxmlParser::getFirstLayer()
{
	currentLayer = getMap()->FirstChildElement("layer");
	return currentLayer;
}

XMLElement* DZxmlParser::getNextLayer()
{
	if (currentLayer == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current layer");
	}
	else
	{
		currentLayer = currentLayer->NextSiblingElement();
	}
	return currentLayer;
}

XMLElement* DZxmlParser::getFirstTile()
{
	if (currentLayer == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current layer");
		currentTile = 0;
	}
	else
	{
		currentTile = currentLayer->FirstChildElement("data")->FirstChildElement("tile");
	}
	return currentTile;
}

XMLElement* DZxmlParser::getNextTile()
{
	if (currentTile == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tile");
	}
	else
	{
		currentTile = currentTile->NextSiblingElement();
	}
	return currentTile;
}


unsigned int DZxmlParser::getStateID()
{
	if (currentState == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No Current state");
		return 0;
	}

	return currentState->UnsignedAttribute("id");
}


const char* DZxmlParser::getStateLevel()
{
	if (currentState == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No Current state");
		return 0;
	}

	return currentState->Attribute("level");
}


unsigned int DZxmlParser::getTextureID()
{
	if (currentTexture == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current texture");
		return 0;
	}

	return currentTexture->UnsignedAttribute("id");
}

const char* DZxmlParser::getTextureFilename()
{
	if (currentTexture == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current texture");
		return 0;
	}

	return currentTexture->Attribute("filename");
}

unsigned int DZxmlParser::getObjectID()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->UnsignedAttribute("id");
}

DZ_COLLISION_TYPE DZxmlParser::getCollisionType()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return DZ_COLLISION_NONE;
	}

	if (strcmp("none", currentObject->Attribute("collision")) == 0)
	{
		return DZ_COLLISION_NONE;
	}
	if (strcmp("box", currentObject->Attribute("collision")) == 0)
	{
		return DZ_COLLISION_BOX;
	}
	if (strcmp("circular", currentObject->Attribute("collision")) == 0)
	{
		return DZ_COLLISION_CIRCULAR;
	}
	return DZ_COLLISION_NONE;
}

float DZxmlParser::getObjectXposition()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("POSITION")->FloatAttribute("x");
}

float DZxmlParser::getObjectYposition()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("POSITION")->FloatAttribute("y");
}

float DZxmlParser::getObjectXvelocity()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("VELOCITY")->FloatAttribute("x");
}

float DZxmlParser::getObjectYvelocity()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("VELOCITY")->FloatAttribute("y");
}

float DZxmlParser::getObjectXacceleration()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("ACCELERATION")->FloatAttribute("x");
}

float DZxmlParser::getObjectYacceleration()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("ACCELERATION")->FloatAttribute("y");
}


float DZxmlParser::getObjectXrotationCenter()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("ROTATION_CENTER")->FloatAttribute("x");
}

float DZxmlParser::getObjectYrotationCenter()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("ROTATION_CENTER")->FloatAttribute("y");
}

float DZxmlParser::getObjectAngularPosition()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("ANGLE")->FloatAttribute("p");
}

float DZxmlParser::getObjectAngularVelocity()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("ANGLE")->FloatAttribute("v");
}

float DZxmlParser::getObjectAngularAcceleration()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("ANGLE")->FloatAttribute("a");
}

unsigned int DZxmlParser::getObjectWidth()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("WIDTH")->UnsignedAttribute("w");
}

unsigned int DZxmlParser::getObjectHeight()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("HEIGHT")->UnsignedAttribute("h");
}

unsigned int DZxmlParser::getObjectNumFrames()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("NUMFRAMES")->UnsignedAttribute("n");
}

unsigned int DZxmlParser::getObjectCurrentRow()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("CURRENTROW")->UnsignedAttribute("r");
}

unsigned int DZxmlParser::getObjectCurrentFrame()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("CURRENTFRAME")->UnsignedAttribute("f");
}

unsigned int DZxmlParser::getObjectNumRows()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("NUMROWS")->UnsignedAttribute("nr");
}

unsigned int DZxmlParser::getObjectTextureID()
{
	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return 0;
	}

	return currentObject->FirstChildElement("TEXTUREID")->UnsignedAttribute("id");
}

SDL_RendererFlip DZxmlParser::getObjectFlipValue()
{
	const char* flag;

	if (currentObject == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current object");
		return SDL_FLIP_NONE;
	}

	flag = currentObject->FirstChildElement("FLIP")->Attribute("flag");

	if (strcmp("SDL_FLIP_NONE", flag) == 0)
	{
		return SDL_FLIP_NONE;
	}
	else if (strcmp("SDL_FLIP_HORIZONTAL", flag) == 0)
	{
		return SDL_FLIP_HORIZONTAL;
	}
	else
	{
		return SDL_FLIP_VERTICAL;
	}
}


unsigned int DZxmlParser::getMapWidth()
{
	if (currentMap == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current map");
		return 0;
	}
	return currentMap->UnsignedAttribute("width");
}

unsigned int DZxmlParser::getMapHeight()
{
	if (currentMap == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current map");
		return 0;
	}
	return currentMap->UnsignedAttribute("height");
}

unsigned int DZxmlParser::getMapTileWidth()
{
	if (currentMap == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current map");
		return 0;
	}
	return currentMap->UnsignedAttribute("tilewidth");
}

unsigned int DZxmlParser::getMapTileHeight()
{
	if (currentMap == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current map");
		return 0;
	}
	return currentMap->UnsignedAttribute("tileheight");
}

unsigned int DZxmlParser::getTilesetID()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
		return 0;
	}
	return currentTileset->UnsignedAttribute("name");
}

unsigned int DZxmlParser::getTilesetTileWidth()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
		return 0;
	}
	return currentTileset->UnsignedAttribute("tilewidth");
}

unsigned int DZxmlParser::getTilesetTileHeight()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
		return 0;
	}
	return currentTileset->UnsignedAttribute("tileheight");
}

unsigned int DZxmlParser::getTilesetSpacing()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
		return 0;
	}
	return currentTileset->UnsignedAttribute("spacing");
}

unsigned int DZxmlParser::getTilesetMargin()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
		return 0;
	}
	return currentTileset->UnsignedAttribute("margin");
}

unsigned int DZxmlParser::getTilesetFirstGID()
{
	if (currentTileset == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tileset");
		return 0;
	}
	return currentTileset->UnsignedAttribute("firstgid");
}

const char*  DZxmlParser::getImageSourceFile()
{
	if (currentImage == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current image");
		return 0;
	}

	return currentImage->Attribute("source");
}

unsigned int DZxmlParser::getImageWidth()
{
	if (currentImage == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current image");
		return 0;
	}
	return currentImage->UnsignedAttribute("width");
}

unsigned int DZxmlParser::getImageHeight()
{
	if (currentImage == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current image");
		return 0;
	}
	return currentImage->UnsignedAttribute("height");
}

unsigned int  DZxmlParser::getLayerID()
{
	if (currentLayer == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current layer");
		return 0;
	}
	return currentLayer->UnsignedAttribute("name");
}

unsigned int DZxmlParser::getLayerWidth()
{
	if (currentLayer == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current layer");
		return 0;
	}
	return currentLayer->UnsignedAttribute("width");
}

unsigned int DZxmlParser::getLayerHeight()
{
	if (currentLayer == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current layer");
		return 0;
	}
	return currentLayer->UnsignedAttribute("height");
}

unsigned int DZxmlParser::getTileGID()
{
	if (currentTile == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "No current tile");
		return 0;
	}
	return currentTile->UnsignedAttribute("gid");
}

