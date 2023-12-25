#include "Mem.h"

// Test Suite: https://docs.google.com/spreadsheets/d/1jTUkyR5gydvoQFJbC1zu8zuevgt93_Dfd0rcuK2l0_I/edit

// Variables
int defaultSize = 1000; // can change dynamically for performance
const int g_DefaultStackSize = 40;
const int g_DefaultStackCount = 10;
const int g_DefaultCatchCount = 100;
MemStackAllocator* g_MemStack = NewStackAllocator(g_DefaultStackSize);
MemPoolAllocator* g_MemPool = NewPoolAllocator(g_DefaultStackSize / g_DefaultStackCount, g_DefaultStackCount);
MemPoolAllocator g_CatchPool(g_DefaultCatchCount / 10, 10);

// Internal memory allocation helpers
MemNode* NewNode()
{
	return (MemNode*)Procure_RAM(sizeof(MemNode));
}

MemBlock* NewBlock(std::size_t blockSize)
{
	void* temp = Procure_RAM(sizeof(MemBlock)); // new block of cells
    //temp = g_MemPool->Add(sizeof(MemBlock)); // new block of cells
	return new (temp) MemBlock(blockSize); // call constructor
}

MemBlock* NewBlock(int cellSize, int cellCount)
{
    void* temp = Procure_RAM(sizeof(MemBlock)); // new block of cells
    return new (temp) MemBlock(cellSize, cellCount); // call constructor
}

MemBasicBlock* NewBasicBlock(std::size_t size)
{
    void* temp = Procure_RAM(sizeof(MemBasicBlock)); // new block of cells
    //temp = g_MemPool->Add(sizeof(MemBasicBlock)); // new block of cells
    return new (temp) MemBasicBlock(size, defaultSize); // call constructor
}

MemStackAllocator* NewStackAllocator(std::size_t size)
{
    // TODO: Allocation check. This should only create the base MemStackAllocator
    // and the MemBlock(). Then MemBlock asks for more RAM.
    MemStackAllocator* temp = (MemStackAllocator*)Procure_RAM(sizeof(MemStackAllocator));
    new (temp) MemStackAllocator(size);
    return temp;
}

MemPoolAllocator* NewPoolAllocator(std::size_t cellSize, std::size_t cellCount)
{
    // TODO: Allocation check. This should only create the base MemStackAllocator
    // and the MemBlock(). Then MemBlock asks for more RAM.
    MemPoolAllocator* temp = (MemPoolAllocator*)Procure_RAM(sizeof(MemPoolAllocator));
    new (temp) MemPoolAllocator(cellSize, cellCount);
    return temp;
}

// New + Delete operator overrides
/* THIS IS THE ONLY PLACE NEW AND DELETE SHOULD BE SEEN IN MEM */
/* THIS IS THE ONLY PLACE MALLOC AND FREE SHOULD BE SEEN IN MEM */
/* USE PROCURE() AND RELEASE FUNCTIONS */
void* operator new(std::size_t size) // handle constructor call
{
	return g_CatchPool.Add(size); // TODO: call constructors
}

void operator delete(void* object)
{
	g_CatchPool.Remove(object); // call destructor
}

void* operator new[](std::size_t size)
{
	return g_CatchPool.Add(size); // ask for new sizeof(array)
}

void operator delete[](void* object)
{
	// TODO: Ensure the whole array gets freed
	g_CatchPool.Remove(object); // call destructor
}
// Private/Internal
void* Procure_RAM(std::size_t size)
{
	return (void*)malloc(size); // ask OS for RAM
}

void Release_RAM(void* object)
{
	free(object); // return RAM to OS
}

// Test namespace Mem
namespace Mem
{
	// Create allocators
    MemStackAllocator* new_Stack(std::size_t sizeInBytes)
	{
        return NewStackAllocator(sizeInBytes);
	}

	MemPoolAllocator* new_Pool(std::size_t cellSize, std::size_t cellCount)
	{
		return NewPoolAllocator(cellSize, cellCount);
	}
    // Release allocators
    void delete_Stack(MemStackAllocator* stack)
    {
        Release_RAM(stack);
    }

	void delete_Pool(MemPoolAllocator* pool)
	{
		Release_RAM(pool);
	}
	// Utility
	void dump_mem() // empty all pools
	{
		// TODO:
	}
    // Clean up
	void delete_mem() // release all RAM allocated by Mem back to the OS
	{
		// TODO:
        Release_RAM(g_MemStack); // MemStack for Mem specific calls
        Release_RAM(g_MemPool); // MemPool for Mem specific calls
	}
}