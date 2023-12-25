#include "Mem.h"

// MemBlock(int, int) object size, max # of objects
MemBlock::MemBlock(int cellSize, int cellCount)
{
    MemBlock::InitUniform(cellSize, cellCount);
}
MemBlock::MemBlock(int blockSize)
{
    MemBlock::InitNonUniform(blockSize);
}
// Release_RAM back to OS
MemBlock::~MemBlock()
{ // cleanup
	Release_RAM(m_Data);
}
// Procure_RAM from OS to store cells
void MemBlock::InitUniform(int cellSize, int cellCount)
{ // init data block
    m_CellSize = cellSize; // the size in BYTEs of one object
    m_CellCount = cellCount; // max # of objects
    m_BlockSize = sizeof(MEMBYTE) * m_CellSize * m_CellCount; // size of block in bytes
    // allocate enough RAM for all cells
    m_Data = (MEMBYTE*)Procure_RAM(m_BlockSize);
    MemBlock::NullData();
}
// Procure_RAM from OS to store cells
void MemBlock::InitNonUniform(int blockSize)
{
    m_CellSize = Mem_NonUniform;
    m_CellCount = Mem_NonUniform;
    m_BlockSize = blockSize;
    // init data block
    m_Data = (MEMBYTE*)Procure_RAM(m_BlockSize); // allocate blockSize of bytes in RAM
    MemBlock::NullData();
}
// Getters + Setters
// Getters
MEMBYTE* MemBlock::GetFirst()
{
    return m_Data;
}
int MemBlock::GetCount()
{
	return m_CellCount;
}

int MemBlock::GetCellSize()
{
	return m_CellSize;
}

void MemBlock::GetRange(int* first, int* last)
{
	*first = (int)&m_Data[0]; // 1st cell in block
	*last = (int)(*first + (m_CellCount * m_CellSize) - m_CellSize); // last cell in block
}

void* MemBlock::GetCellLocation(int index)
{
	return m_Data + m_CellSize * index;
}

int MemBlock::GetBlockSize()
{
    return m_BlockSize;
}
// Setters
void MemBlock::NullCell(int index)
{
    m_Data[index] = Mem_Null;
}
void MemBlock::NullData()
{
    SetData(Mem_Null);
}

void MemBlock::SetData(int value)
{
    memset(m_Data, value, m_BlockSize); // &[0], value, numBytes
}