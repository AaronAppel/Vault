#ifndef _MemFlagBlock_H_
#define _MemFlagBlock_H_

typedef char MEMBYTE;

class MemFlagBlock
{
public:
	// MemBlock(int, int) object size, max # of objects
	MemFlagBlock(int cellSize, int cellCount);
	~MemFlagBlock();
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

#endif // !_MemFlagBlock_H_
