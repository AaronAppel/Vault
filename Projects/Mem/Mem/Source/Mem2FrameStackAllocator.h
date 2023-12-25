#ifndef _Mem2FrameStackAllocator_H_
#define _Mem2FrameStackAllocator_H_

// No remove or deletion interface, only NewFrame()

class MemNode;

class Mem2FrameStackAllocator
{
public:
    Mem2FrameStackAllocator(size_t size);
    ~Mem2FrameStackAllocator();

    void* Add(size_t size); // TODO: Find a way to return the proper type, not just void*

    void NewFrame();
    void Clear();

private:
    bool m_CurrentFrame = 0;
    MemBlock m_Blocks[2];
    MEMBYTE* m_Tops[2];
};

#endif //!_Mem2FrameStackAllocator_H_