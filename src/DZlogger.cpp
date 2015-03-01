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
 * 03-01-2015	file created                                              *
 **************************************************************************/


#include "DZlogger.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>

using namespace std;


// allocation of static variables
ofstream	DZlogger::logfile;
DZlogger	DZlogger_instance;
DZlogger*	DZlogger::InstancePtr = &DZlogger_instance;


// Instantiator of this singleton class
DZlogger* DZlogger::Instance()
{
	return InstancePtr;
}


// constructor
DZlogger::DZlogger()
{
	// store log file name
	strcpy(FileName, DZ_LOG_FILE);

	// Initialize SDL error strings
	SDL_SetError("");

	// open log file
	logfile.open(FileName, ios::out);

	DZ_LOG(DZ_LOG_TRACE, "DZlogger successfully created");
}

// destructor
DZlogger::~DZlogger()
{
	DZ_LOG(DZ_LOG_TRACE, "Terminating DZlogger");

	// close log file
	logfile.close();
}


// logs text only
void DZlogger::DZlog(int level, const char* text, const char* file, const char* func, int line)
{
	if (level >= DZ_LOG_DEFAULT)
	{
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		logfile << asctime(timeinfo)
			<< LOG_LEVEL(level)
			<< file << '\n'
			<< func
			<< " - "
			<< line
			<< " - "
			<< text
			<< logSDLerror(level)
			<< "\n\n";
		logfile << flush;
	}
}

// logs text + int variable
void DZlogger::DZlog1(int level, const char* text, int var1, const char* file, const char* func, int line)
{
	if (level >= DZ_LOG_DEFAULT)
	{
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		logfile << asctime(timeinfo)
			<< LOG_LEVEL(level)
			<< file << '\n'
			<< func
			<< " - "
			<< line
			<< " - "
			<< text
			<< '\t'
			<< var1
			<< logSDLerror(level)
			<< "\n\n";
		logfile << flush;
	}
}

// logs text + 2 int variables
void DZlogger::DZlog2(int level, const char* text, int var1, int var2, const char* file, const char* func, int line)
{
	if (level >= DZ_LOG_DEFAULT)
	{
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		logfile << asctime(timeinfo)
			<< LOG_LEVEL(level)
			<< file << '\n'
			<< func
			<< " - "
			<< line
			<< " - "
			<< text
			<< '\t'
			<< var1
			<< '\t'
			<< var2
			<< logSDLerror(level)
			<< "\n\n";
		logfile << flush;
	}
}


// logs text if the test is true
void DZlogger::DZassert(bool test, const char* text, const char* file, const char* func, int line)
{
	if (test)
	{
		DZlog(DZ_LOG_ASSERT, text, file, func, line);
	}
}


const char* DZlogger::logSDLerror(int level)
{
	string error_string("");

	if (level == DZ_LOG_WARN)
	{
		error_string = "\n";
		error_string += "SDL error: ";
		error_string += SDL_GetError();

		SDL_SetError("");
	}

	return error_string.c_str();
}
