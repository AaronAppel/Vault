#include "Mem.h"

// TODO: put in error checking for empty lists (empty or full block)

MemPoolAllocator::MemPoolAllocator(std::size_t cellSize, std::size_t cellCount)
{
    m_Block = NewBlock(cellSize, cellCount);

	// setup 1st head node
	MemNode* nodes = (MemNode*)Procure_RAM(sizeof(MemNode) * cellCount); // allocate nodes
	m_OpenList = &nodes[0];
	m_OpenList->m_Next = nullptr;

	m_OpenList->m_Value = (MemBlock*)m_Block->GetCellLocation(cellCount - 1);

	// add nodes for the rest of the list
	for (size_t i = 0; i < cellCount - 1; i++)
	{
		MemNode* temp = &nodes[i + 1]; // pull another node from the array
		temp->m_Next = m_OpenList;

		temp->m_Value = (MemBasicBlock*)m_Block->GetCellLocation(cellCount - 2 - i);
        m_OpenList = temp; // update m_OpenList pointer
	}
}
//
MemPoolAllocator::~MemPoolAllocator()
{
	// call destructors
	// release block RAM
    Release_RAM(m_Block);
    // release open and closed list nodes
    MemNode* it = m_OpenList;
    while (it != nullptr) // past the end yet?
    {
        MemNode* temp = it; // save current node*
        it = it->m_Next; // save next node*
        Release_RAM(temp); // delete current node*
    }
    it = m_ClosedList;
    while (it != nullptr) // past the end yet?
    {
        MemNode* temp = it; // save current node*
        it = it->m_Next; // save next node*
        Release_RAM(temp); // delete current node*
    }
}
//
void* MemPoolAllocator::Add(size_t size)
{
	// get first open node
    MemNode* temp = m_OpenList;

    // ASSERT
    if (temp == nullptr) // is there an open node?
        return nullptr;

    // remove from open list
    m_OpenList = temp->m_Next; // move top down stack

    // add to closed list
    temp->m_Next = m_ClosedList;
    m_ClosedList = temp; // move newly closed node to top of closed list

	// return newly closed node
    return temp->m_Value;
}
//
void MemPoolAllocator::Remove(void* object)
{
	// look through closed list for node
    MemNode* it = m_ClosedList;
    MemNode* tail = nullptr;
    while (it != nullptr) // past the end yet?
    {
        if (it->m_Value == object)
        {
            if (tail == nullptr) // is object == m_Closed?
            {
                // remove from closed list
                m_ClosedList = m_ClosedList->m_Next;

                // add to open list
                it->m_Next = m_OpenList;
                m_OpenList = it;

                return;
            }
            // TODO: call destructor
            // remove current node from closed list
            tail->m_Next = it->m_Next; // remove it* node from list

            // add to open list
            it->m_Next = m_OpenList;
            m_OpenList = it;
            return;
        }
        tail = it; // increment tail*
        it = it->m_Next; // increment node*
    }
}
//
void MemPoolAllocator::Clear()
{
	// destructors
	// return all nodes to open list
}