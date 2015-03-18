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
 * 03-18-2015	Added sound system handler.								  *
 * 03-07-2015	file created                                              *
 **************************************************************************/


#ifndef DZENGINE_H
#define DZENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "DZinputHandler.h"
#include "DZxmlParser.h"
#include "DZproject.h"
#include "DZstateMachine.h"
#include "DZsoundSystem.h"


// Window flags, to be used as the last parameter in the init function
#define DZ_WIN_NO_ATTR			0							// no attributes
#define DZ_WIN_FULLSCREEN		SDL_WINDOW_FULLSCREEN		// fullscreen window
#define DZ_WIN_OPENGL			SDL_WINDOW_OPENGL			// window usable with OpenGL context
#define DZ_WIN_SHOWN			SDL_WINDOW_SHOWN            // window is visible
#define DZ_WIN_HIDDEN			SDL_WINDOW_HIDDEN           // window is not visible
#define DZ_WIN_NO_BORDER		SDL_WINDOW_BORDERLESS       // no window decoration
#define DZ_WIN_RESIZABLE		SDL_WINDOW_RESIZABLE        // window can be resized
#define DZ_WIN_MIN         	 	SDL_WINDOW_MINIMIZED        // window is minimized
#define DZ_WIN_MAX          	SDL_WINDOW_MAXIMIZED        // window is maximized
#define DZ_WIN_INPUT_GRABBED	SDL_WINDOW_INPUT_GRABBED    // window has grabbed input focus
#define DZ_WIN_INPUT_FOCUS  	SDL_WINDOW_INPUT_FOCUS      // window has input focus
#define DZ_WIN_MOUSE_FOCUS  	SDL_WINDOW_MOUSE_FOCUS      // window has mouse focus
#define DZ_WIN_FOREIGN      	SDL_WINDOW_FOREIGN          // window not created by SDL
#define DZ_WIN_ALLOW_HIGHDPI	SDL_WINDOW_ALLOW_HIGHDPI    // window should be created in
															// high-DPI mode if supported



/*****************************************************************
 *
 * Class:		DZengine
 *
 * Description:	The high level engine interface.
 *
 * Interface:	exec()				- the engine itself
 *				init()				- engine initialization
 *				quit()				- terminates the engine
 *				getRenderer()		- returns pointer to the renderer
 *				getStateMachine()	- returns pointer to the state machine
 *				getInput()			- returns pointer to the input handler
 *				getWindowWidth()	- returns width of SDL window in pixels
 *				getWindowHeight()	- returns height of SDL window in pixels
 *
 ****************************************************************/

class DZengine
{
	public:
		//--------------------------------------------------------
		// Name:		DZengine::DZengine
		// Description:	Class constructor
		// Arguments:	void
		//--------------------------------------------------------
		DZengine();

		//--------------------------------------------------------
		// Name:		DZengine::~DZengine
		// Description:	Class destructor
		// Arguments:	n/a
		//--------------------------------------------------------
		~DZengine();

		//--------------------------------------------------------
		// Name:		DZengine::init
		// Description:	Engine initialization procedures.
		//				Returns true if the initialization is
		//				successful, otherwise it returns false
		// Arguments:	title	- main window title
		//				x_pos	- x position of main window
		//				y_pos	- y position of main window
		//				width	- width of main window
		//				height	- height of main window
		//				flags	- SDL attributes of main window
		//						  (SDL_WINDOW_*)
		//--------------------------------------------------------
		bool init(const char* title, int x_pos, int y_pos, int width, int height, int flags);

		//--------------------------------------------------------
		// Name:		DZengine::exec
		// Description:	This methods executes the engine. It is
		//				the only method that is called from main().
		// Arguments:	void
		//--------------------------------------------------------
		void exec();

		//--------------------------------------------------------
		// Name:		DZengine::quit
		// Description:	Terminates the application.
		// Arguments:	void
		//--------------------------------------------------------
		void quit();

		//--------------------------------------------------------
		// Name:		DZengine::getRenderer
		// Description:	returns a pointer to the renderer
		// Arguments:	void
		//--------------------------------------------------------
		static SDL_Renderer* getRenderer();

		//--------------------------------------------------------
		// Name:		DZengine::getStateMachine
		// Description:	returns a pointer to the state machine
		// Arguments:	void
		//--------------------------------------------------------
		static DZstateMachine* getStateMachine();

		//--------------------------------------------------------
		// Name:		DZengine::getInput
		// Description:	returns a pointer to the input handler
		// Arguments:	void
		//--------------------------------------------------------
		static DZinputHandler* getInput();

		//--------------------------------------------------------
		// Name:		DZengine::getSoundSystem
		// Description:	returns a pointer to the sound system handler
		// Arguments:	void
		//--------------------------------------------------------
		static DZsoundSystem* getSoundSystem();

		//--------------------------------------------------------
		// Name:		DZengine::getWindowWidth
		// Description:	returns the window width
		// Arguments:	void
		//--------------------------------------------------------
		static unsigned int getWindowWidth();

		//--------------------------------------------------------
		// Name:		DZengine::getWindowHeight
		// Description:	returns the window height
		// Arguments:	void
		//--------------------------------------------------------
		static unsigned int getWindowHeight();

	protected:

	private:
		//--------------------------------------------------------
		// Name:		DZengine::shutdown
		// Description:	Cleanup procedures, to be run before
		//				exiting the exec() method.
		// Arguments:	void
		//--------------------------------------------------------
		void shutdown();

		//--------------------------------------------------------
		// Name:		DZengine::event_handler
		// Description:	Part of the main loop. Gets inputs from the
		//				user.
		// Arguments:	void
		//--------------------------------------------------------
		void event_handler();

		//--------------------------------------------------------
		// Name:		DZengine::update
		// Description:	Part of the main loop. Process user inputs
		//				generated by the event handler, based on
		//				previous state of the system.
		// Arguments:	void
		//--------------------------------------------------------
		void update();

		//--------------------------------------------------------
		// Name:		DZengine::render
		// Description:	Part of the main loop. Renders the new
		//				frame to the screen or window, based on
		//				the data generated by the update method.
		// Arguments:	void
		//--------------------------------------------------------
		void render();


		bool					isLoopActive;
		SDL_Window*				windowPtr;
		static unsigned int		windowWidth;
		static unsigned int		windowHeight;
		static DZinputHandler*	inputHandlerPtr;
		static SDL_Renderer*	rendererPtr;
		static DZstateMachine*	fsmPtr;
		static DZsoundSystem*	soundSystemPtr;
};

#endif // DZENGINE_H
