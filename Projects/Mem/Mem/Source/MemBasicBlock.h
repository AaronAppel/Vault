#ifndef _MemBasicBlock_H_
#define _MemBasicBlock_H_

typedef char MEMBYTE;

class MemBasicBlock
{
public:
	// MemBlock(int, int) object size, max # of objects
    MemBasicBlock(int cellSize, int cellCount);
	~MemBasicBlock();
	// return location of an empty cell
	void* Add();
	void Remove(void* object);
	void GetRange(int* start, int* end);

private:
	int m_CellSize = -1; // the size in BYTEs of one object
	int m_CellCount = 0; // max # of objects
	MEMBYTE* m_Data = nullptr; // RAM block
	bool* m_Status = nullptr; // cell status
};

#endif // !_MemBasicBlock_H_
