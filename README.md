# DZgameEngine
Object Oriented Game Engine based on SDL and OpenGL

The engine is completely object oriented, it is written in C++, and it is
platform independent. It uses the SDL library v.2.x and in the future it
will be extended to also support OpenGL.

Games can be built by providing a list of objects that represent all the
possible items used by the game: backgrounds, moveable physical objects,
characters, tiles, and so forth.

Each object provides methods to update their status and position in the
game, and to draw themselves on the screen. Drawing, in particular, can be
achieved with different technologies, which can be plugged in the object
classes by the mean of wrappers to the actual graphical interface.

The engine also supports a state machine, which states can represent
specific scenarios of the game or game levels. Support will also be
provided to play music and sounds, and to access external I/O resources,
like keyboard, mouse, joystick, touch screen, and so forth.

In order to achieve the best performance, the game engine tries to avoid
as much a possible the use of C++ libraries. Instead, the engine provides
its own classes for data manipulation and other necessities, that are
designed for speed and not for generalized usage.

For further information, please visit http://www.dazzlingsolutions.com.

=========================================================================
# Coding style requirements to write code for DZgameEngine

- Use TAB to indent lines.
- Set TAB to 4 spaces.
- Be consistent with the {} style used in the file being edited. Please
  do not mix up different styles.
- Class attributes are represented in 'camel' notation.
  Examples: bitmapArray, statusPtri, DZstateMachine.
- Local variables are represented in lower case letters; if the variable
  name contains multiple elements, they are separated with underscores. 
  Examples: local_variable, bitmap_ptr.
- Pointers shall all have a suffix _ptr or Ptr.

=========================================================================
# SDL-2.x and TinyXML-2 License

/* zlib.h -- interface of the 'zlib' general purpose compression library
  version 1.2.2, October 3rd, 2004

  Copyright (C) 1995-2004 Jean-loup Gailly and Mark Adler

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Jean-loup Gailly jloup@gzip.org
  Mark Adler madler@alumni.caltech.edu

*/

