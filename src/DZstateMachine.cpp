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


#include "DZstateMachine.h"
#include "DZproject.h"



DZstateMachine::DZstateMachine()
{
	DZ_LOG(DZ_LOG_TRACE, "Creating FSM");
	currentState = 0;
	pausedState = 0;
	parserPtr = new DZxmlParser(DZCONFIGFILE);
}

DZstateMachine::~DZstateMachine()
{
	DZ_LOG(DZ_LOG_TRACE, "Destroying FSM");
	if (currentState != 0)
	{
		DZ_LOG(DZ_LOG_TRACE, "deleting currentState");
		currentState->onExit();
		delete currentState;

	}
	if (pausedState != 0)
	{
		DZ_LOG(DZ_LOG_TRACE, "deleting pausedState");
		pausedState->onExit();
		delete pausedState;
	}
	if (parserPtr != 0)
	{
		DZ_LOG(DZ_LOG_TRACE, "Destroying parser");
		delete parserPtr;
	}
}


void DZstateMachine::newState(DZstate* state_ptr)
{
	if (currentState != 0)
	{
		if(currentState->getStateID() == state_ptr->getStateID())
		{
			delete state_ptr;
			return;
		}

		currentState->onExit();
		delete currentState;
	}

	DZ_LOG1(DZ_LOG_TRACE, "Changing state to: ", state_ptr->getStateID());
	currentState = state_ptr;
	currentState->onEnter();
}

void DZstateMachine::update()
{
	if(currentState != 0)
	{
		currentState->update();
	}
}


void DZstateMachine::render()
{
	if(currentState != 0)
	{
		currentState->render();
	}
}

void DZstateMachine::pauseState()
{
	pausedState = currentState;
	currentState = 0;
}

void DZstateMachine::resumeState()
{
	if (pausedState == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "There is no paused state. Remaining in current state.");
		return;
	}

	if (currentState != 0)
	{
		delete currentState;
	}
	currentState = pausedState;
	pausedState = 0;
}

