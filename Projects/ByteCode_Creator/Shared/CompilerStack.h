#ifndef _VMStack_H_
#define _VMStack_H_

#include <assert.h>

class VMStack
{
public:
    void PushBack(char value)
    {
        assert(m_Index < 100);
        m_Stack[m_Index++] = value++;
    };

    char Pop()
    {
        assert(m_Index > 0);
        return m_Stack[--m_Index];
    }

    void Reset() { m_Index = 0; };
    int Size() { return m_Index; };

private:
    int m_Index = 0;
    char m_Stack[100];
};


#endif // _CompilerStack_H_