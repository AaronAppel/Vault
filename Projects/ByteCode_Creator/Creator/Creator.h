#ifndef _Creator_H_
#define _Creator_H_

/////////////// Intro ///////////////
//
// L2_ByteCode is a prove of concept test I was experimenting with.
// I tried using to 2 separate applications to create, transfer, and
// read values from an object created at runtime.
//
// The idea came from an article I found written by Rob Nystrom:
// http://gameprogrammingpatterns.com/bytecode.html
//
// I wanted to add modding or user creation functionality to future apps
// in a safe and fast way. The concept can be expanded upon almost
// infinitely so I created a bare minimum working example that I will
// refer to in the future.
//
// Disclaimer: This is not professional code I am writing. There are
// globals galore, but this was a quick project to learn a concept
// so it is good enough for now.
/////////////////////////////////////

/////////////// Creator ///////////////
//
// This project is used to create objects at runtime with a nice
// GUI window. A user can create objects with custom values and fields
// that get compiled down into raw byte values to be read by the VM
// in the Game project during runtime.
//
// The idea is that a user can create a custom spell for a character
// in the game easily to "mod" the game to their liking. This is really
// just an extension or editor for the Game.
///////////////////////////////////////

#include <string>

// enums
#include "enums.h"

// utility
#include "FileUtils.h"

// 3rd party libraries
#include "SetupLibraries.h"

// graphics
#include "Graphics\SetupGraphics.h"

// game
#include "Item.h"
#include "Character.h"

// compilitation
#include "InstructionBlock.h"
#include "Compiler.h"

#endif // !_Creator_H_
