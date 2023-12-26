#ifndef _Main_H_
#define _Main_H_

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

/////////////// Game ///////////////
//
// This project is used a running game or app that uses the data from
// the Creator project. Users can create objects for the Game using
// the GUI editor, then these objects can be interpreted and instantiated
// during runtime directly into the game. Users can create spells, items,
// characters or whatever they want with custom behaviours. This essentially
// means that users can create a game from this almost as if they were coding
// or scripting the game from a pretty GUI.
//
// The 2 projects also use a compiler and virtual machine to read and write
// the bytecode to avoid malware and detect corrupt files while still maintaining
// runtime and RAM efficiency.
////////////////////////////////////

#include <string>

// Enums
#include "enums.h"

// Utility
#include "FileUtils.h"

// 3rd party libraries
#include "SetupLibraries.h"

// Graphics
#include "Graphics\SetupGraphics.h"

// Game
#include "Item.h"
#include "Character.h"

// Interpretation
#include "InstructionBlock.h"
#include "Interpreter.h"

#endif // !_Main_H_
