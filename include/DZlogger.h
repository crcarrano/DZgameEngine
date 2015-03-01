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


#ifndef _DZ_LOGGER_H_
#define _DZ_LOGGER_H_

/*****************************************************************
 *
 * Class:		DZlogger
 *
 * Description:		C++ application logger.
 *
 *			Provides extensive logging capabilities to
 *			any C++ application. It can be used for
 *			logging traces, debug information, warnings,
 *			and general information.
 *			At compile time, a log level is chosen. All
 *			logs of equal or higher level are printed
 *			in the log file. Lower level logs are discarded.
 *			Different log levels can be chosen for
 *			alpha, beta, and production versions.
 *
 *			The output file is named according to the
 *			#define provided in this file. It is
 *			suggested to always use the .log prefix.
 *
 * Interface:		DZ_LOG(level, text)
 *				logs the text if level >= default
 *			DZ_LOG1(level, text, var)
 *				logs the text and var1 value if level >= default
 *			DZ_LOG2(level, text, var1, var2)
 *				logs the text plus var1 and var2 values if level >= default
 *			DZ_ASSERT(test, text)
 *				logs the text if test == true
 *
 ****************************************************************/
/***************************************************************************
 * Change Log                                                              *
 *-------------------------------------------------------------------------*
 * 08-07-2014	file created                                               *
 * 08-22-2014	changed the object to a static one			   *
 * 10-14-2014	added SDL error logging capability                         *
 ***************************************************************************/

#include <time.h>
#include <fstream>
//#include <cstring>

using namespace std;

// Change the name of the log file as you wish
#define DZ_LOG_FILE	"application.log"


// Application Log Level
typedef enum
{
	 DZ_LOG_TRACE		// all logs
	,DZ_LOG_DEBUG		// debug + info + warning + assert logs
	,DZ_LOG_INFO		// info + warning + assert logs
	,DZ_LOG_WARN		// warning + assert logs
	,DZ_LOG_ASSERT		// assert logs are always printed
} DZ_LOG_LEVEL;


#define LOG_LEVEL(_level) 												\
(_level == DZ_LOG_TRACE ? "LOG_TRACE - " :								\
(_level == DZ_LOG_DEBUG ? "LOG_DEBUG - " :								\
(_level == DZ_LOG_INFO ? "LOG_INFO - " :								\
"LOG_WARN - ")))


// The following #define establishes the log level built within
// the application at compile time; only logs with level greater
// than or equal to DZ_LOG_DEFAULT are printed inthe log file.
// Uncomment only one of the 4 definitions, to
// establish the minimum log level that will be printed
#define DZ_LOG_DEFAULT	DZ_LOG_TRACE
//#define DZ_LOG_DEFAULT	DZ_LOG_DEBUG
//#define DZ_LOG_DEFAULT	DZ_LOG_INFO
//#define DZ_LOG_DEFAULT	DZ_LOG_WARN


// the following macros can be used to simplify calls to the DZlogger
// methods
#define DZ_LOG(_level, _text)					\
{ DZlogger::Instance()->DZlog(_level, _text, __FILE__, __FUNCTION__, __LINE__); }

#define DZ_LOG1(_level, _text, _var1)			\
{ DZlogger::Instance()->DZlog1(_level, _text, _var1, __FILE__, __FUNCTION__, __LINE__); }

#define DZ_LOG2(_level, _text, _var1, _var2)	\
{ DZlogger::Instance()->DZlog2(_level, _text, _var1, _var2, __FILE__, __FUNCTION__, __LINE__); }

#define DZ_ASSERT(_test, _text)					\
{ DZlogger::Instance()->DZassert(_test, _text, __FILE__, __FUNCTION__, __LINE__); }


class DZlogger
{
	public:
		DZlogger();
		~DZlogger();
		static DZlogger* Instance();
		void DZlog(int level, const char* text, const char* file, const char* func, int line);
		void DZlog1(int level, const char* text, int var1, const char* file, const char* func, int line);
		void DZlog2(int level, const char* text, int var1, int var2, const char* file, const char* func, int line);
		void DZassert(bool test, const char* text, const char* file, const char* func, int line);

	protected:
	private:

		char FileName[256];					// name of the log file
		static ofstream logfile;			// log file stream
		static DZlogger* InstancePtr;		// stores the pointer to this singleton class object
		const char* logSDLerror(int level);	// print SDL log errors
};


#endif

