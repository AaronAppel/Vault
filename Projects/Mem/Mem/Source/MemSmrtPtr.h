#ifndef _MemSmrtPtr_H_
#define _MemSmrtPtr_H_

// https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
// https://www.tutorialspoint.com/cplusplus/class_member_access_operator_overloading.htm

class MemStackAllocator; // requires an allocator to instantiate

template <class T>
class MemSmrtPtr
{
public:
    MemSmrtPtr(void* location);
    ~MemSmrtPtr();

    void Shift(int difference);
    void ReAssign(void* location);

    void Clone() {};

    void operator=(const T) const; // prevent value copying
    T operator->() const; // allow access to m_Value but prevent address changes

private:
    MemStackAllocator* m_Allocator = nullptr;
    void* m_Value = nullptr; // pointer to 1 byte
};

#endif //!_MemSmrtPtr_H_