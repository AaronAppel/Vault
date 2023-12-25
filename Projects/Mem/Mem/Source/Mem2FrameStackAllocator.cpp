#include "Mem.h"

static int g_StepValue = 1;

Mem2FrameStackAllocator::Mem2FrameStackAllocator(size_t size)
{
    // block1
    m_Blocks[0].InitNonUniform(size);
    m_Tops[0] = m_Blocks[0].GetFirst(); // top starts as first value
    // block2
    m_Blocks[1].InitNonUniform(size);
    m_Tops[1] = m_Blocks[1].GetFirst(); // top starts as first value
}

Mem2FrameStackAllocator::~Mem2FrameStackAllocator()
{
    // Release_RAM(m_Block1); // TODO: Delete all MemNodes
    // Release_RAM(m_Block2); // TODO: Delete all MemNodes
}

void* Mem2FrameStackAllocator::Add(size_t size)
{
    m_Blocks[m_CurrentFrame];
    m_Tops[m_CurrentFrame] += size; // increase position of m_Top*
    return (void*)(m_Tops[m_CurrentFrame] - size); // return address of cell
}

void Mem2FrameStackAllocator::NewFrame()
{
    m_CurrentFrame = !m_CurrentFrame; // swap buffers
    m_Tops[m_CurrentFrame] = (MEMBYTE*)&m_Blocks[m_CurrentFrame]; // reset top of stack
}

void Mem2FrameStackAllocator::Clear()
{
    m_Tops[0] = (MEMBYTE*)&m_Blocks[0];
    m_Tops[1] = (MEMBYTE*)&m_Blocks[1];
    m_Blocks[0].NullData();
    m_Blocks[1].NullData();
}