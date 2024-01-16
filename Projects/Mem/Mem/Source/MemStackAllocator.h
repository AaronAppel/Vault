#ifndef _MemStackAllocator_H_
#define _MemStackAllocator_H_

struct MemNode;

class MemStackAllocator
{
public:
    MemStackAllocator(std::size_t size);
    ~MemStackAllocator();

    void* Add(std::size_t size); // TODO: Find a way to return the proper type, not just void*
    void Remove(void* object);

    void Pop();
    void Clear();

private:
    MemBlock m_Block;

    MEMBYTE* m_Top;
    char* m_Marker; //
    MemNode* m_Markers;
};

#endif //!_MemStackAllocator_H_