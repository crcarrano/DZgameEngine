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
 * 03-13-2015	file created                                              *
 **************************************************************************/

#include "DZinitState.h"
#include "DZengine.h"


void DZinitState::onEnter()
{
	textureManagerPtr = new DZtextureManager;
	if (textureManagerPtr == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Could not allocate texture manager");
		return;
	}

	textureManagerPtr->load("assets/DZengine_logo.png", 0);
}

void DZinitState::update()
{
}

void DZinitState::render()
{
	textureManagerPtr->draw(0, 0, 0, 0, 0, 0, DZengine::getWindowWidth(), DZengine::getWindowHeight());
}
