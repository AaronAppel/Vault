#pragma once

typedef char MEMBYTE;

struct MemBlock
{
public:
    MemBlock() {}; // default constructor
	// MemBlock(int, int) object size, max # of objects
	MemBlock(int cellSize, int cellCount);
    MemBlock(int blockSize);
	~MemBlock();

    void InitUniform(int cellSize, int cellCount);
    void InitNonUniform(int blockSize);

    MEMBYTE* GetFirst();
	int GetCount();
	int GetCellSize();
	void GetRange(int* start, int* last); // return addresses of the first and last cells
	void* GetCellLocation(int index);
    int GetBlockSize();

    void NullCell(int index);
    void NullData(); // assign Mem_Null to each cell
    void SetData(int value); // assign a value to each cell

    // #TODO Private members are currently public
	int m_CellSize = -1; // the size in BYTEs of one object. 0 means non-uniform size
	int m_CellCount = 0; // max # of objects
    size_t m_BlockSize = -1; // size of block in bytes
	MEMBYTE* m_Data = nullptr; // RAM block
};
