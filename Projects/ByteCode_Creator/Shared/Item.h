#ifndef _Item_H_
#define _Item_H_

#include <string>

class Item
{
public:
    int GetCost() { return m_Cost; }
    void SetCost(int cost) { m_Cost = cost; }

    std::string GetName() { return m_Name; }
    void SetName(std::string name) { m_Name = name; }

private:
    std::string m_Name = "test";
    int m_Cost = 0;
};

#endif // _Item_H_