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


#include "DZttf.h"
#include "DZlogger.h"
#include "DZengine.h"


DZttf::DZttf()
{
	if (TTF_WasInit() == 0)
	{
		if (TTF_Init() == -1)
		{
			DZ_LOG(DZ_LOG_WARN, "Could not init SDL_ttf library");
			initialized = false;
			return;
		}
	}

	initialized = true;
	font = 0;
	font_color.r = 255;
	font_color.g = 255;
	font_color.b = 255;
	font_color.a = 255;
	font_background.r = 0;
	font_background.g = 0;
	font_background.b = 0;
	font_background.a = 0;
}

DZttf::~DZttf()
{
	if (initialized)
	{
		if (font != 0)
		{
			TTF_CloseFont(font);
		}
		if (TTF_WasInit() != 0)
		{
			TTF_Quit();
		}
	}
}

bool DZttf::openFontFile(const char* file, int point_size, long index)
{
	if (!initialized)
	{
		DZ_LOG(DZ_LOG_WARN, "Attempt to open font file with SDL_ttf not initialized");
		return false;
	}

	if (index == 0)
	{
		font = TTF_OpenFont(file, point_size);
	}
	else
	{
		font = TTF_OpenFontIndex(file, point_size, index);
	}

	if (font == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Failed to open font file");
		return false;
	}

	return true;
}

void DZttf::setStyle(int style)
{
	if (!initialized)
	{
		DZ_LOG(DZ_LOG_WARN, "Attempt to use when SDL_ttf not initialized");
		return;
	}

	TTF_SetFontStyle(font, style);
}

SDL_Texture* DZttf::getTexture(SDL_Surface* surface)
{
	if (!initialized)
	{
		DZ_LOG(DZ_LOG_WARN, "Attempt to use when SDL_ttf not initialized");
		return 0;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(DZengine::getRenderer(), surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* DZttf::solidText(const char* text)
{
	if (!initialized)
	{
		DZ_LOG(DZ_LOG_WARN, "Attempt to use when SDL_ttf not initialized");
		return 0;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, font_color);
	return getTexture(surface);
}

SDL_Texture* DZttf::shadedText(const char* text)
{
	if (!initialized)
	{
		DZ_LOG(DZ_LOG_WARN, "Attempt to use when SDL_ttf not initialized");
		return 0;
	}

	SDL_Surface* surface = TTF_RenderText_Shaded(font, text, font_color, font_background);
	return getTexture(surface);
}

SDL_Texture* DZttf::blendedText(const char* text)
{
	if (!initialized)
	{
		DZ_LOG(DZ_LOG_WARN, "Attempt to use when SDL_ttf not initialized");
		return 0;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(font, text, font_color);
	return getTexture(surface);
}

void DZttf::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	font_color.r = red;
	font_color.g = green;
	font_color.b = blue;
	font_color.a = alpha;
}

void DZttf::setBackground(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	font_background.r = red;
	font_background.g = green;
	font_background.b = blue;
	font_background.a = alpha;
}

bool DZttf::getTextSize(const char* text, int* width, int* height)
{
	if (!initialized)
	{
		DZ_LOG(DZ_LOG_WARN, "Attempt to use when SDL_ttf not initialized");
		return false;
	}

	if (TTF_SizeText(font, text, width, height) != 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Could not determine text size");
		return false;
	}
	return true;
}


