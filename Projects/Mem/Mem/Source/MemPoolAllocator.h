#ifndef _MemPoolAllocator_H_
#define _MemPoolAllocator_H_

class MemNode;

class MemPoolAllocator
{
public:
    MemPoolAllocator(std::size_t cellSize, std::size_t cellCount);
    ~MemPoolAllocator();

    void* Add(std::size_t size); // TODO: Find a way to return the proper type, not just void*
    void Remove(void* object);

    void Clear();

private:
    MemBlock* m_Block = nullptr;

    MemNode* m_OpenList = nullptr;
    MemNode* m_ClosedList = nullptr;
};

#endif //!_MemPoolAllocator_H_