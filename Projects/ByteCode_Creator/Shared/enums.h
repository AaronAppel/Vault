#ifndef _enums_H_
#define _enums_H_

enum eInstructions
{
	Inst_Literal = 0,
    // Inst_Literal1b, // char
    // Inst_Literal2b, // short
    // Inst_Literal4b, // int
    Inst_Value, // stats, etc
    Inst_Func, // func* assignement

    // math
    Inst_Addition,
    Inst_Subtraction,
    Inst_Multiplication,
    Inst_Division,
    Inst_Squared,

    Inst_Stop,
	Inst_Max
};

enum eItemFuncs
{
	Item_OnPickup = 0,
	Item_OnDrop,
	Item_OnAction, // work

	Item_Max
};

enum eItemStats
{
	IStat_Cost = 0,

	IStat_Max
};

enum eCharacterFuncs
{
	Char_Energy = 0,
	Char_Eat,
	Char_Drink,
	Char_ChopWood,
	Char_Farm,

	Char_Max
};

enum eCharacterStats
{
	CStat_EnergyMax = 0,
	CStat_AppetiteMax,
	CStat_HydrationMax,

	CStat_Max
};

#endif // _enums_H_