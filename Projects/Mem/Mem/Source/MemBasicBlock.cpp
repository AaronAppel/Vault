#include "Mem.h"

#ifdef _Mem_H_
// MemFlagBlock(int, int) object size, max # of objects
MemBasicBlock::MemBasicBlock(int cellSize, int cellCount)
{ // init data[] and status[]
	m_CellSize = cellSize; // the size in BYTEs of one object
	m_CellCount = cellCount; // max # of objects

	// allocate enough RAM for all cells and their boolean flags
	m_Data = (MEMBYTE*)Procure_RAM(sizeof(MEMBYTE) * m_CellSize * m_CellCount + sizeof(bool) * m_CellCount); // cells + flags
	// faster to memset() than loop through values (estimated 30%)
	memset(m_Data, 0, sizeof(MEMBYTE) * m_CellSize * m_CellCount); // 1st*, value, numBytes

	// allocate and init Status array
	m_Status = (bool*)m_Data + sizeof(MEMBYTE) * m_CellSize * m_CellCount; // offset of cells
	memset(m_Status, eCell_Open, sizeof(bool) * m_CellCount);
}

MemBasicBlock::~MemBasicBlock()
{ // cleanup
	Release_RAM(m_Data);
	Release_RAM(m_Status);
}

void* MemBasicBlock::Add() // return location of an empty cell
{
	for (int i = 0; i < m_CellCount; i++)
	{
		if (m_Status[i] == eCell_Open) // find open cell
		{
			m_Status[i] = eCell_Closed; // close cell
			return &m_Data[i * m_CellSize]; // return location of open cell
		}
	}
	return nullptr; // block is full
}

void MemBasicBlock::Remove(void* object)
{
	for (int cell = 0; cell < m_CellCount * m_CellSize; cell += m_CellSize) // move m_CellSize BYTEs in array
	{
		if (&m_Data[cell] == object) // same object*?
		{
			m_Status[cell / m_CellSize] = eCell_Open; // allow memory to be overwritten
													  // TODO: call destructor?
			return;
		}
	}
}

void MemBasicBlock::GetRange(int* first, int* last)
{
	*first = (int)&m_Data[0]; // 1st cell in block
	*last = (int)(*first + (m_CellCount * m_CellSize) - m_CellSize); // last cell in block
}
#endif