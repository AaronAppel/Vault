#pragma once

struct MemNode;

class Mem1FrameAllocator
{
public:
	Mem1FrameAllocator(size_t size);
    ~Mem1FrameAllocator();

    void* Add(size_t size); // #TODO Find a better way to return the desired type, not just void*. Could use templating
    void Remove(void* object);

    void Pop();
    void Clear();

private:
    MemBlock m_Block;

    MEMBYTE* m_Top;
    char* m_Marker;
    MemNode* m_Markers;
};
