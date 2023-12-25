#ifndef _Mem_H_
#define _Mem_H_

// Resources:
// https://www.ibm.com/developerworks/aix/tutorials/au-memorymanager/index.html
// http://www.piko3d.net/tutorials/placement-new-operator/
// http://www.drdobbs.com/cpp/calling-constructors-with-placement-new/232901023
// http://www.modernescpp.com/index.php/overloading-operator-new-and-delete
// http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka14267.html
// http://en.cppreference.com/w/cpp/memory/new/operator_new
// http://www.stroustrup.com/bs_faq2.html#placement-delete
// https://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new
// http://www.swedishcoding.com/2008/08/31/are-we-out-of-memory./

/////////////////// Mem ///////////////////

// Mem is a memory management library meant to make memory management
// easy and beneficial in almost any c++ project.
//
// Mem is currently a WIP project.

/////////////////// Mem ///////////////////

// TODO:s
// error checking
// access violation guards
// auto size increase
// memory/cell alignment
// allocators + blocks

//////////////////////////////////////// 40

// Includes:
// System
#include <new> // extra new access
#include <cstring> // memset

/* Mem */
#include "MemSmrtPtr.h"

// Blocks
#include "MemBlock.h"
#include "MemFlagBlock.h"
#include "MemBasicBlock.h"

// Allocators
#include "MemStackAllocator.h"
#include "MemPoolAllocator.h"
#include "Mem1FrameStackAllocator.h"
#include "Mem2FrameStackAllocator.h"

// Mem defines
#define Mem_Null 0
#define Mem_NonUniform 0

#if Mem_Release
#define Mem_Inline inline
#else
#define Mem_Inline ;
#endif // Mem_Release

// Mem enums
enum eCellStatus // represents a cell's state
{
	eCell_Closed = 0,
	eCell_Open
};

typedef char MEMBYTE; // Mem standardized BYTE value

struct MemNode
{
	// no constructor / destructor
	void* m_Value = nullptr;
	MemNode* m_Next = nullptr;
};

struct MemSizeNode
{
	// no constructor / destructor
	MemBlock* m_Value = nullptr;
	MemNode* m_Next = nullptr;
	int size = 0;
};

MemNode* NewNode();
MemBlock* NewBlock(std::size_t size);
MemBlock* NewBlock(int cellSize, int cellCount);
MemBasicBlock* NewBasicBlock(std::size_t size);

MemStackAllocator* NewStackAllocator(std::size_t size);
MemPoolAllocator* NewPoolAllocator(std::size_t cellSize, std::size_t cellCount);

// New + Delete operator overrides
/* THIS IS THE ONLY PLACE NEW AND DELETE SHOULD BE SEEN IN MEM */
/* USE PROCURE() AND RELEASE FUNCTIONS */
void* operator new(std::size_t size);
void operator delete(void* object);

void* operator new[](std::size_t size);
void operator delete[](void* object);

// Private/Internal
void* Procure_RAM(std::size_t size); // TODO: hide in .cpp file to prevent end user access
void Release_RAM(void* object);

// External access
namespace Mem
{
	// Allocators
	// Create allocators
	MemStackAllocator* new_Stack(std::size_t sizeInBytes);
	MemPoolAllocator* new_Pool(std::size_t cellSize, std::size_t cellCount);

	// Delete allocators
	void delete_Stack(MemStackAllocator* stack);
	void delete_Pool(MemPoolAllocator* pool);

	// Utility
	void dump_mem(); // empty all pools
	void delete_mem(); // release all RAM allocated by Mem
}
#endif // !_Mem_H_

