#include "Mem.h"

static int g_StepValue = 1;

Mem1FrameAllocator::Mem1FrameAllocator(size_t size)
{
    m_Block.InitNonUniform(size);
    m_Block.SetData(99);
    m_Top = m_Block.GetFirst(); // top starts as first value
    m_Marker = m_Top; // set marker to start of block
    m_Markers = NewNode();
}

Mem1FrameAllocator::~Mem1FrameAllocator()
{
    Release_RAM(m_Markers); // TODO: Delete all MemNodes
}

void* Mem1FrameAllocator::Add(size_t size)
{
    memset(m_Top, g_StepValue++, size);
    m_Marker = m_Top; // move marker up
    m_Top += size; // increase position of m_Top*
    return (void*)(m_Top - size); // return address
}
//
void Mem1FrameAllocator::Remove(void* object)
{
    // value check
    if (object == m_Marker)
    {
        memset(m_Marker, g_StepValue++, m_Top - m_Marker);
        m_Top = m_Marker; // decrease
        m_Marker; // roll back marker... Must support more than 1 marker
    }
    else
    {
        // invalid top value
        // could be a pointer to other memory
        // could be a value that is in the stack but is not the top
    }
}

void Mem1FrameAllocator::Pop()
{
    memset(m_Marker, g_StepValue++, m_Top - m_Marker);
    m_Top = m_Marker; // revert to top marker address
    m_Marker; // roll back marker
}

void Mem1FrameAllocator::Clear()
{
    m_Top = m_Block.GetFirst(); // move m_Top
    m_Marker = m_Top; // reset m_Marker
    m_Block.NullData();
}