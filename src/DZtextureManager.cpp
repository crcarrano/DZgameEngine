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
 * 03-09-2015	file created                                               *
 ***************************************************************************/

#include "DZtextureManager.h"
#include <fstream>
#include "SDL_image.h"
#include "DZlogger.h"
#include "DZengine.h"

using namespace std;

DZtextureManager::DZtextureManager()
{
	DZ_LOG(DZ_LOG_TRACE, "Creating Texture Manager");

	// the application uses at least 1 texture
	textureMapPtr = new DZarray<SDL_Texture*>(1);

	if (textureMapPtr == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Unable to instantiate Testure Manager");
		exit(-1);
	}
}

DZtextureManager::~DZtextureManager()
{
	DZ_LOG(DZ_LOG_TRACE, "Destroying Texture Manager");

	if (textureMapPtr != 0)
	{
		unsigned int size = textureMapPtr->getSize();

		for (unsigned int i = 0 ; i < size ; i++)
		{
			if ((*textureMapPtr)[i] != 0)
			{
				DZ_LOG(DZ_LOG_TRACE, "Destroying texture");
				SDL_DestroyTexture((*textureMapPtr)[i]);
			}
		}

		delete textureMapPtr;
	}
}


bool DZtextureManager::load(string fileName, unsigned int id)
{
	DZ_LOG(DZ_LOG_TRACE, "Loading texture");

	if ((*textureMapPtr)[id] != 0)
	{
		DZ_LOG1(DZ_LOG_WARN, "Texture ID already in use ", id);
		return false;
	}

	SDL_Surface* tempSurface_ptr = IMG_Load(fileName.c_str());

	if(tempSurface_ptr == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Could not load texture from file");
		return false;
	}

	SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(DZengine::getRenderer(), tempSurface_ptr);
	SDL_FreeSurface(tempSurface_ptr);

	// everything went ok, add the texture to our list
	if(texture_ptr != 0)
	{
		(*textureMapPtr)[id] = texture_ptr;
		return true;
	}

	// reaching here means something went wrong
	DZ_LOG(DZ_LOG_WARN, "Could not create texture from surface");

	return false;
}

bool DZtextureManager::store(SDL_Texture* texture, unsigned int id)
{
	if ((*textureMapPtr)[id] == 0)
	{
		(*textureMapPtr)[id] = texture;
		return true;
	}
	DZ_LOG1(DZ_LOG_WARN, "Texture ID alread in use ", id);
	return false;
}


void DZtextureManager::draw(unsigned int id,
						    unsigned int x,
			   				unsigned int y,
						    unsigned int cx,
						    unsigned int cy,
						    unsigned int angle,
						    unsigned int width,
						    unsigned int height,
						    SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Point center;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	center.x = cx;
	center.y = cy;

	SDL_RenderCopyEx(DZengine::getRenderer(), (*textureMapPtr)[id], &srcRect, &destRect, angle, &center, flip);
}


void DZtextureManager::drawFrame(unsigned int id,
			         unsigned int x,
			         unsigned int y,
				 unsigned int cx,
				 unsigned int cy,
				 unsigned int angle,
			         unsigned int width,
			         unsigned int height,
			         unsigned int currentRow,
			         unsigned int currentFrame,
			         SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Point center;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = width;
	srcRect.h = height;
	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	center.x = cx;
	center.y = cy;

	SDL_RenderCopyEx(DZengine::getRenderer(), (*textureMapPtr)[id], &srcRect, &destRect, angle, &center, flip);
}


void DZtextureManager::drawTile(unsigned int id, SDL_Rect* src, SDL_Rect* dst)
{
	SDL_RenderCopy(DZengine::getRenderer(), (*textureMapPtr)[id], src, dst);
}



SDL_Texture* DZtextureManager::getTexture(unsigned int id)
{
	if (id < textureMapPtr->getSize())
	{
		return (*textureMapPtr)[id];
	}

	return 0;
}


void DZtextureManager::setColorModulation(unsigned int id, Uint8 red, Uint8 green, Uint8 blue)
{
	(void) SDL_SetTextureColorMod(getTexture(id), red, green, blue);
}


void DZtextureManager::setAlphaBlending(unsigned int id, Uint8 alpha)
{
	if (alpha > 100)
	{
		// values too high; set to the max
		alpha = 100;
	}
	(void) SDL_SetTextureAlphaMod(getTexture(id), alpha);
}


void DZtextureManager::setAlphaBlendingMode(unsigned int id, bool turn_on)
{
	if (turn_on == true)
	{
		(void) SDL_SetTextureBlendMode(getTexture(id), SDL_BLENDMODE_BLEND);
	}
	else
	{
		(void) SDL_SetTextureBlendMode(getTexture(id), SDL_BLENDMODE_NONE);
	}
}



