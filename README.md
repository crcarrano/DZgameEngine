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


