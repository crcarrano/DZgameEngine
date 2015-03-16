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
 * 03-15-2015	Added call to IMG_Quit() when shutting down the			  *
 * 				application												  *
 * 03-10-2015	removed comments for missing classes					  *
 * 03-07-2015	file created                                              *
 **************************************************************************/

#include "DZengine.h"
#include "DZlogger.h"
#include "DZinitState.h"
#include "DZstateMachine.h"


SDL_Renderer*	DZengine::rendererPtr;
DZstateMachine*	DZengine::fsmPtr;
DZinputHandler*	DZengine::inputHandlerPtr;
unsigned int	DZengine::windowWidth;
unsigned int	DZengine::windowHeight;


//--------------------------------------------------------------------------

DZengine::DZengine()
{
	DZ_LOG(DZ_LOG_TRACE, "Creating engine");
	inputHandlerPtr = 0;
	rendererPtr = 0;
	fsmPtr = 0;
	isLoopActive = false;
}

//--------------------------------------------------------------------------

DZengine::~DZengine()
{
	DZ_LOG(DZ_LOG_TRACE, "Destroying engine");

	if (inputHandlerPtr != 0)
	{
		delete inputHandlerPtr;
	}

	shutdown();
}

//--------------------------------------------------------------------------

void DZengine::exec()
{
	unsigned int	frame_start;
	unsigned int	frame_time;

	DZ_LOG(DZ_LOG_TRACE, "Entering...");

	while (isLoopActive)
	{
		frame_start = SDL_GetTicks();

		event_handler();	// recognize and store new events
		update();			// process events
		render();			// render new frame

		frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frame_time));
		}
	}
}

//--------------------------------------------------------------------------

bool DZengine::init(const char* title, int x_pos, int y_pos, int width, int height, int flags)
{
	DZ_LOG(DZ_LOG_TRACE, "Entering...");

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DZ_LOG(DZ_LOG_INFO, "SDL init successful");

		// init the window
		windowPtr = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);

		if(windowPtr != 0) // window init success
		{
			DZ_LOG(DZ_LOG_INFO, "window creation successful");

			windowWidth = width;
			windowHeight = height;

			rendererPtr = SDL_CreateRenderer(windowPtr, -1, 0);

			if(rendererPtr != 0) // renderer init success
			{
				DZ_LOG(DZ_LOG_INFO, "renderer creation successful");
			}
			else
			{
				DZ_LOG(DZ_LOG_WARN, "renderer init failed");
				return false; // renderer init fail
			}
		}
		else
		{
			DZ_LOG(DZ_LOG_WARN, "window init failed");
			return false; // window init fail
		}
	}
	else
	{
		DZ_LOG(DZ_LOG_WARN, "SDL init failed");
		return false; // SDL init fail
	}

	// initialize input handler object and search for joysticks
	inputHandlerPtr = new DZinputHandler();
	inputHandlerPtr->joystick_init();

	// create state machine and initialize default state
	fsmPtr = new DZstateMachine();
	fsmPtr->newState(new DZinitState());

	DZ_LOG(DZ_LOG_INFO, "init successfully completed");
	// everything inited successfully, start the main loop
	isLoopActive = true;

	return true;
}

//--------------------------------------------------------------------------

void DZengine::shutdown()
{
	DZ_LOG(DZ_LOG_TRACE, "Entering...");

	SDL_DestroyWindow(windowPtr);
	SDL_DestroyRenderer(rendererPtr);
	IMG_Quit();
	SDL_Quit();
}

//--------------------------------------------------------------------------

void DZengine::event_handler()
{
	inputHandlerPtr->eventHandler(this);
}

//--------------------------------------------------------------------------

void DZengine::update()
{
	fsmPtr->update();
}

//--------------------------------------------------------------------------

void DZengine::render()
{
	SDL_SetRenderDrawColor(rendererPtr, 0,0,0,0);
	SDL_RenderClear(rendererPtr);
	fsmPtr->render();
	SDL_RenderPresent(rendererPtr);
}

//--------------------------------------------------------------------------

void DZengine::quit()
{
	isLoopActive = false;
}

//--------------------------------------------------------------------------

SDL_Renderer* DZengine::getRenderer()
{
	return rendererPtr;
}

//--------------------------------------------------------------------------

DZstateMachine* DZengine::getStateMachine()
{
	return fsmPtr;
}

//--------------------------------------------------------------------------

DZinputHandler* DZengine::getInput()
{
	return inputHandlerPtr;
}


unsigned int DZengine::getWindowWidth()
{
	return windowWidth;
}


unsigned int DZengine::getWindowHeight()
{
	return windowHeight;
}


