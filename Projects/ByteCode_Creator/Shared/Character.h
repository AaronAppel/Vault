#ifndef _Character_H_
#define _Character_H_

#include "Item.h"

class Item;

class Character
{
public:
	Character() {}
	~Character() {}

	void Update()
	{

	}

    void SetName(std::string name) { m_Name = name; }
    std::string GetName() { return m_Name; }

    void SetMaxEnergy(int energy) { m_Energy = energy; }
    int GetMaxEnergy() { return m_Energy; }

private:
    std::string m_Name = "test";
    int m_Energy, m_Hunger, m_Thirst;
    void* m_Work = nullptr;
    Item* m_Item = nullptr;
};

#endif // _Character_H_