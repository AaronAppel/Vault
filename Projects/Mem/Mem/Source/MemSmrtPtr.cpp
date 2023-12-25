#include "Mem.h"

template <class T>
MemSmrtPtr<T>::MemSmrtPtr(void* location)
{
    m_Value = location;
}

template <class T>
MemSmrtPtr<T>::~MemSmrtPtr()
{
}

template <class T>
void MemSmrtPtr<T>::Shift(int difference)
{
    m_Value; // shift by difference, in bytes
}

template <class T>
void MemSmrtPtr<T>::ReAssign(void* location)
{
    m_Value; // = location; // change value but only from valid source
}

template <class T>
void MemSmrtPtr<T>::operator=(const T) const
{
    // nothing
    int bp = 1; // TODO: Test
}

template <class T>
T MemSmrtPtr<T>::operator->() const // allow access to m_Value but prevent address changes
{
    return (T)m_Value;
}

void Test()
{
    int* thing = nullptr;
    MemSmrtPtr<int*> test(thing);

    MemSmrtPtr<int*> thing2 = test; // TODO: Test what is returned
}