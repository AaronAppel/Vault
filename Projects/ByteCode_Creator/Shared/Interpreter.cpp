#include "Interpreter.h"
#include "FileUtils.h"
#include "enums.h"
#include "PrintFuncs.h"
#include <string>

Item* Interpreter::InterperateItem(const char* itemFile)
{
    // file values
    char* data = nullptr;
    std::string dir;
    dir.append("Data/Items/");
    dir.append(itemFile);

    // read file
    if (FileExists(dir.c_str()))
        data = LoadFile(dir.c_str());
    else
        return nullptr; // error reading file

    m_Block->SetDataStart((unsigned char*)data, 20); // TODO: Calculate size

    // setup item
    Item* item = new Item();
    std::string name;
    name.append(itemFile);
    item->SetName(name.substr(0, name.size() - 4 - 1)); // extension - period

    // read instruction block
    int size = 4;
    for (unsigned char* byte = m_Block->DataStart(); byte < m_Block->DataStart() + size; byte++)
    {
        switch (*byte)
        {
        case Inst_Literal:
            byte++;
            m_Stack.PushBack(*byte); // push next char value
            break;
        case Inst_Value:
            byte++;
            switch (*byte) // pop top char value
            {
            case IStat_Cost:
                item->SetCost(m_Stack.Pop());
                break;
            };
            break;
        }
    }

    return item;
}

Character* Interpreter::InterperateCharacter(const char* charFile)
{
    // file values
    char* data = nullptr;
    std::string dir;
    dir.append("Data/Characters/");
    dir.append(charFile);

    // read file
    if (FileExists(dir.c_str()))
        data = LoadFile(dir.c_str());
    else
        return nullptr; // error reading file

    m_Block->SetDataStart((unsigned char*)data, 20); // TODO: Calculate size

    // setup character
    Character* person = new Character();
    std::string name;
    name.append(charFile);
    person->SetName(name.substr(0, name.size() - 4 - 1)); // extension - period

    // read instruction block
    unsigned char* size = m_Block->DataStart() + m_Block->GetEffectiveSize(); // increment char* by number of valid bytes
    for (unsigned char* byte = m_Block->DataStart(); byte < size; byte++)
    {
        switch (*byte)
        {
        case Inst_Literal:
            byte++;
            m_Stack.PushBack(*byte); // push next char value
            break;
        case Inst_Value:
            byte++;
            switch (*byte) // pop top char value
            {
            case CStat_EnergyMax:
                person->SetMaxEnergy(m_Stack.Pop());
                break;
            };
            break;
        }
    }

    return person;
}