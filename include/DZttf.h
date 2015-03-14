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


#ifndef DZTTF_H
#define DZTTF_H


#include "SDL_ttf.h"

/*****************************************************************
 *
 * Class:		DZttf
 *
 * Description:	This class handles a TTF font and returns
 *				textures with the specified font and background
 *				that can be rendered at will.
 *				Multiple objects can be instantiated from
 *				this class: one object per font type.
 *
 * Interface:	openFontFile  - opens the font file
 *				setStyle      - set the style of the
 *								font to one or more
 *								of the following:
 *								normal, bold, italic,
 *								underline, strikethrough
 *				solidText     - generate texture with
 *								solid text (fast but low
 *								resolution)
 *				shadedText    - generate texture with
 *								shaded text
 *				blendedText   - generate texture with
 *								blended text (high resolution
 *								but slower than the previous
 *								two)
 *				setColor      - set the font color
 *				setBackground - set the background color for
 *								the shaded text
 *				getTextSize   - returns the width and height
 *								of the rectangular texture
 *								containing the text
 *
 ****************************************************************/
class DZttf
{
	public:
		enum STYLE
		{
			BOLD 			= TTF_STYLE_BOLD,
			ITALIC			= TTF_STYLE_ITALIC,
			UNDERLINE		= TTF_STYLE_UNDERLINE,
			STRIKETHROUGH	= TTF_STYLE_STRIKETHROUGH,
			NORMAL 			= TTF_STYLE_NORMAL
		};

		//--------------------------------------------------------
		// Name:		DZttf::DZttf
		// Description:	constructor
		// Arguments:
		//--------------------------------------------------------
		DZttf();

		//--------------------------------------------------------
		// Name:		DZttf::~DZttf
		// Description:	destructor
		// Arguments:	n.a.
		//--------------------------------------------------------
		~DZttf();

		//--------------------------------------------------------
		// Name:		DZttf::openFontFile
		// Description:	loads font from file
		// Arguments:	file		font file name
		//				point_size	font size to be used
		//				index		font face index, if file
		//							contains multiple fonts
		//--------------------------------------------------------
		bool openFontFile(const char* file, int point_size, long index = 0);

		//--------------------------------------------------------
		// Name:		DZttf::setStyle
		// Description:	set font style according with enum STYLE
		// Arguments:	style - more styles can be OR-ed together
		//--------------------------------------------------------
		void setStyle(int style);

		//--------------------------------------------------------
		// Name:		DZttf::solidText
		// Description:	returns a texture with the specified text;
		//				font color needs to be defined with setColor();
		//				background is transparent;
		//				fast acting function, but suffers in font details
		// Arguments:	text - the text to be embedded in the texture
		//--------------------------------------------------------
		SDL_Texture* solidText(const char* text);

		//--------------------------------------------------------
		// Name:		DZttf::shadedText
		// Description:	returns a texture with the specified text;
		//				font color is specified by setColor();
		//				background color is specified by setBackground()
		// Arguments:	text - the text to be embedded in the texture
		//--------------------------------------------------------
		SDL_Texture* shadedText(const char* text);

		//--------------------------------------------------------
		// Name:		DZttf::blendedText
		// Description:	returns a texture with the specified text;
		//				font color is specified by setCOlor();
		//				background is transparent;
		//				this method is the high resolution version of
		//				solidText() and it takes longer to be rendered
		// Arguments:	text - the text to be embedded inthe texture
		//--------------------------------------------------------
		SDL_Texture* blendedText(const char* text);

		//--------------------------------------------------------
		// Name:		DZttf::setColor
		// Description:	defines the foreground color of the font
		// Arguments:	red
		//				green
		//				blue
		//				alpha
		//--------------------------------------------------------
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

		//--------------------------------------------------------
		// Name:		DZttf::setBackground
		// Description:	defines the backgroundcolor for the text;
		//				it is only used for shaded text
		// Arguments:	red
		//				green
		//				blue
		//				alpha
		//--------------------------------------------------------
		void setBackground(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

		//--------------------------------------------------------
		// Name:		DZttf::getTextSize
		// Description:	returns in the variables width and height
		//				the size of the rectangle containing the text;
		//				this information is needed to correctly
		//				render the texture embedding the text;
		//				returns true if width and height are successfully
		//				filled.
		// Arguments:	text   - the text of which we are measuring the size
		//				width  - the returned width of the text rectangular
		//						 area
		//				height - the returned height of the text rectangular
		//						 area
		//--------------------------------------------------------
		bool getTextSize(const char* text, int* width, int* height);

	protected:
	private:
		bool		initialized;
		TTF_Font*	font;
		SDL_Color	font_color;
		SDL_Color	font_background;

		SDL_Texture*	getTexture(SDL_Surface* surface);
};

#endif // DZTTF_H
