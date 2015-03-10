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

#ifndef DZTEXTUREMANAGER_H
#define DZTEXTUREMANAGER_H

#include "SDL.h"
#include "DZarray.h"




/*****************************************************************
 *
 * Class:		DZtextureManager
 *
 * Description:	stores in memory and handles all the textures
 *				used by the application
 *
 * Interface:	load		- load the texture in memory
 *				draw		- draw the texture
 *				drawFrame	- draw a frame from a
 *							  texture map
 *
 ****************************************************************/
class DZtextureManager
{
	public:
		DZtextureManager();

		~DZtextureManager();

		bool load(string fileName, unsigned int id);

		bool store(SDL_Texture* texture, unsigned int id);

		// draws a whole texture
		void draw(unsigned int id,
			  unsigned int x,
			  unsigned int y,
			  unsigned int cx,
			  unsigned int cy,
			  unsigned int angle,
			  unsigned int width,
			  unsigned int height,
			  SDL_RendererFlip flip = SDL_FLIP_NONE);

		// draws a frame of an animation texture set
		void drawFrame(unsigned int id,
			       unsigned int x,
			       unsigned int y,
			       unsigned int cx,
			       unsigned int cy,
			       unsigned int angle,
			       unsigned int width,
			       unsigned int height,
			       unsigned int currentRow,
			       unsigned int currentFrame,
			       SDL_RendererFlip flip = SDL_FLIP_NONE);

		// draws a tile from a tileset
		void drawTile(unsigned int id, SDL_Rect* src, SDL_Rect* dst);

		// color modulation modifies the actual texture colors with the
		// following formula:
		// src_color = src_color * (color/255);
		void setColorModulation(unsigned int id,
					Uint8 red,
					Uint8 green,
					Uint8 blue);

		// alpha blending controls the transparency of the texture:
		// alpha = 0 is maximum translarency
		// alpha = 255 is maximum opacity
		void setAlphaBlending(unsigned int id, Uint8 alpha);

		// turns on/off alpha blending; for setAlphaBlending() to work,
		// alpha blending needs to be turned on for the texture
		void setAlphaBlendingMode(unsigned int id, bool turn_on);

		SDL_Texture* getTexture(unsigned int id);

	protected:
	private:
		DZarray<SDL_Texture*>*	textureMapPtr;
};

#endif // DZTEXTUREMANAGER_H
