#ifndef _Interpreter_H_
#define _Interpreter_H_

#include "InstructionBlock.h"
#include "CompilerStack.h"
#include "Item.h"
#include "Character.h"

class InstructionBlock;
class Item;

class Interpreter
{
public:
    Interpreter() { m_Block = new InstructionBlock(20); } // TODO: Choose a better starting size
    ~Interpreter() { delete m_Block; }

    Item* InterperateItem(const char* itemFile);
    Character* InterperateCharacter(const char* itemFile);

private:
    InstructionBlock* m_Block = nullptr;
    VMStack m_Stack;
};

#endif // _Interpreter_H_