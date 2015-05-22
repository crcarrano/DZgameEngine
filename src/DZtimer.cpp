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

#include "DZtimer.h"
#include "DZlogger.h"
#include "DZproject.h"


DZtimer::DZtimer(Uint32 interval, Uint32 repeat_value)
{
	DZ_LOG2(DZ_LOG_TRACE, "create timer (interval, repeat)", interval, repeat_value);
	length = interval;
	repeat = repeat_value;
	timerID = SDL_AddTimer(length, DZtimer::timerCallback, this);
}

DZtimer::~DZtimer()
{
	DZ_LOG2(DZ_LOG_TRACE, "deleting timer (Interval, repeat)", length, repeat);
	if (timerID != 0)
	{
		SDL_RemoveTimer(timerID);
	}
}

Uint32 DZtimer::timerCallback(Uint32 interval, void* param)
{
	DZ_LOG(DZ_LOG_TRACE, "Entering...");

	DZtimer* timer = (DZtimer*) param;
	SDL_Event event;
	SDL_UserEvent user_event;

	user_event.type = SDL_USEREVENT;
	user_event.code = (Sint32) DZ_USER_EVENT_TIMER;
	user_event.data1 = (void*) timer;
	user_event.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = user_event;

	SDL_PushEvent(&event);

	switch (timer->repeat)
	{
		case 0:
			timer->timerID = 0;
			delete timer;
			break;

		case DZ_FOREVER_TIMER:
			timer->timerID = SDL_AddTimer(timer->length, timer->timerCallback, timer);
			break;

		default:
			timer->repeat--;
			timer->timerID = SDL_AddTimer(timer->length, timer->timerCallback, timer);
			break;
	}

	return interval;
}

void DZtimer::processTimer(DZtimer* timer)
{
	DZ_LOG(DZ_LOG_WARN, "Derived DZtimer class not instantiated - using base class");
}

