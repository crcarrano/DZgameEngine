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

#include "SDL.h"


#define DZ_FOREVER_TIMER	0xffffffff

/*****************************************************************
 *
 * Class:		DZtimer
 *
 * Description:	SDL timer wrapper. Provides regular timer
 * 				capability plus the possibility to repeat the
 * 				timer a predefined amount of times, or repeat
 * 				forever.
 * 				This is a virtual class. In order to use a timer
 * 				a new derived timer class needs to be created
 * 				and the processTimer() method needs to be created
 * 				specifically to handle the timer expiration.
 * 				The processTimer() method is automatically called by 
 * 				DZinputHandler::eventHandler() when the timer expires.
 *
 * Interface:	DZtimer()		The constructor of the class.
 * 								A timer is started by instantiating
 * 								an object from the derived timer class:
 * 								new DZtimerXXX(interval, repeat_value);
 * 								If the repeat_value is set to
 * 								DZ_FOREVER_TIMER, the timer restarts
 * 								continuously until the timer object is
 * 								deleted.
 *
 * 				processTimer()	This method needs to be defined in
 * 								the derived class. It is supposed
 * 								to process the timer expiration
 * 								event from the event handler.
 * 								The method can access the derived
 * 								class attributes and methods using
 * 								the pointer passed to it.
 *
 ****************************************************************/


class DZtimer
{
	public:
		//--------------------------------------------------------
		// Name:		DZtimer::DZtimer
		// Description:	class constructor
		// Arguments:	interval		- the length of the timer
		// 				repeat_value	- how many times the timer
		// 								  restarts automatically
		//--------------------------------------------------------
		DZtimer(Uint32 interval, Uint32 repeat_value);

		//--------------------------------------------------------
		// Name:		DZtimer::~DZtimer
		// Description:	class destructor
		// Arguments:	none
		//--------------------------------------------------------
		virtual ~DZtimer();

		//--------------------------------------------------------
		// Name:		DZtimer::processTimer
		// Description:	the timer event handler - it needs to
		// 				be redefined in the derived class
		// Arguments:	timer - pointer to the timer class
		//--------------------------------------------------------
		virtual void processTimer(DZtimer* timer);

		//--------------------------------------------------------
		// Name:		DZtimer::timerCallback
		// Description:	callback function used within SDL to
		// 				generate the timer event with the
		// 				appropriate information. It also takes care
		// 				of restarting the timer, if necessary.
		// Arguments:	interval	- the length of the timer
		// 				param		- pointer to the derived class
		//--------------------------------------------------------
		static Uint32	timerCallback(Uint32 interval, void* param);

	protected:
		SDL_TimerID	timerID;		// the timer ID
		Uint32		length;			// the duration of the timer in msec
		Uint32		repeat;			// if repeat == 0 timer is destroyed after it expires
									// if repeat != 0 timer restarts after it expires for
									// 						repeat amount of times
									// if repeat == DZ_FOREVER_TIMER timer restarts
									// 						after it expires until it is
									// 						destroyed.

	private:
};
