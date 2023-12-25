#include "TestSuite1.h"

#include <iostream> // For cout and cin
#include <intrin.h> // For __debugbreak

#include "Main.h"
#include "TestUtils.h"
#include "TestClasses.h"

void GenTest1(); // Simple

void SimpleStack1(); // Stack
void SimpleStack2();

void SimpleHeap1(int scale); // Heap
void SimpleHeap2(int scale);

void ComplexHeap1(int scale); // More complex
void ComplexHeap2(int scale);
void ComplexHeap3(int scale);

#if EXPERIMENTAL_MODE
// Mem
void MemStackAllocTest(int sizeInBytes);
void MemPoolAllocTest(int sizeInBytes);
#endif

void NewStackAllocTest(int sizeInBytes);
void NewPoolAllocTest(int sizeInBytes);

class MyClass1;
struct MyClass2;
struct MyClass3;

void ObjectSizes()
{
	OutputPrint("Size of Class 1: %i", sizeof(MyClass1));
	// ConsolePrint("Size of Class 1: %i", sizeof(MyClass1));
	OutputPrint("Size of Class 2: %i", sizeof(MyClass2));
	OutputPrint("Size of Class 3: %i", sizeof(MyClass3));
}

bool Test_RunCase(int testCase)
{
    try
    {
        // able to play all test cases sequentially by sending 0 as an argument
        int size = (testCase > 0) ? 1 : 7; // TODO: Define Cases_MAX
        int startIndex = (testCase > 0) ? testCase : 1;

        int scale;
        std::cout << "Scale: " << std::endl;
	    std::cin >> scale;

        for (int i = startIndex; i < size + startIndex; i++)
        {
            StartTest(); // reset timer
            switch (i)
            {
            case 1: GenTest1(); break;
                // Stack
            case 2: SimpleStack1(); break;
            case 3: SimpleStack2(); break;
                // Heap
            case 4: SimpleHeap1(scale); break;
            case 5: SimpleHeap2(scale); break;
                // Complex
            case 6: ComplexHeap1(scale); break;
            case 7: ComplexHeap2(scale); break;
            case 8: ComplexHeap3(scale); break;
#if EXPERIMENTAL_MODE
                // Mem
            case 9: MemStackAllocTest(scale); break;
            case 10: MemPoolAllocTest(scale); break;
#else
            case 9: NewStackAllocTest(scale); break;
            case 10: NewPoolAllocTest(scale); break;
#endif
            }
            EndTest(); // print process time
           std::cout << "Test " << i << " Completed" << std::endl;
            system("pause");
        }
        return true;
    }
    catch (const std::exception&)
    {
        return false; // error during test
    }
}

bool Test_ResetEnvironment()
{
    if (true) // TODO: Reset test environment
    {
        return true; // success
    }
    else
    {
        return false; // failure
    }
}

void GenTest1()
{
    MyClass1* temp = new MyClass1();
    MyClass1* temp2 = new MyClass1();
    delete temp2; // delete 2nd first
    delete temp;
}
/////////////// Stress Tests ///////////////
// Stack
void SimpleStack1()
{
    const int stackScale = 10000; // max < 1,000,000 or stack overflow
    MyClass1* test[stackScale];
    // newing
    for (int i = 0; i < stackScale; i++)
    {
        test[i] = new MyClass1(); // add to memory blocks
    }
    // deleting
    for (int i = 0; i < stackScale; i++)
    {
        delete test[i]; // remove from memory blocks
    }
}

void SimpleStack2()
{
    const int stackScale = 10000; // max <1,000,000 or stack overflow
    MyClass2* test[stackScale];
    // newing
    for (int i = 0; i < stackScale; i++)
    {
        test[i] = new MyClass2(); // add to memory blocks
    }
    // deleting
    for (int i = 0; i < stackScale; i++)
    {
        delete test[i]; // remove from memory blocks
    }
}
// Heap
void SimpleHeap1(int scale)
{
    // newing
    MyClass1* test = new MyClass1[scale]; // allocate all on heap

    // deleting
    delete[] test; // delete entire array
}
void SimpleHeap2(int scale)
{
    // newing
    MyClass2* test = new MyClass2[scale]; // allocate all on heap

    // deleting
    delete[] test; // delete entire array
}
// Complex
// Stack
// -- empty --
// Heap
void ComplexHeap1(int scale)
{
    // Test how efficient re-allocating RAM is
    // Steps
    // 1. new
    // 2. delete
    // 3. new
    // 4. delete

    // newing
    MyClass1* test = new MyClass1[scale]; // allocate all on heap

    // deleting
    delete[] test; // delete entire array

    // newing
    test = new MyClass1[scale]; // allocate all on heap

    // deleting
    delete[] test; // delete entire array
}
void ComplexHeap2(int scale)
{
    // Test how efficient re-allocating RAM is
    // Steps
    // 1. new
    // 2. delete
    // 3. new
    // 4. delete

    // 1. newing
    MyClass2* test = new MyClass2[scale]; // allocate all on heap

    // 2. deleting
    delete[] test; // delete entire array

    // 3. newing
    test = new MyClass2[scale]; // allocate all on heap

    // 4. deleting
    delete[] test; // delete entire array
    OPT_BREAK
}

void ComplexHeap3(int scale)
{
	const int scale2 = 5000;
	int* test[scale2];

	int cases = 4;
	for (std::size_t i = 0; i < cases; i++)
	{
		StartTest(); // reset timer

		switch (i)
		{
		case 0:
			for (int i = 0; i < scale2; i++)
			{
				test[i] = new int; // new
			}
			break;

		case 1:
			for (int i = 0; i < scale2; i++)
			{
				delete test[i]; // delete
			}
			break;
			// round 2
		case 2:
			for (int i = 0; i < scale2; i++)
			{
				test[i] = new int; // new
			}
			break;
		case 3:
			for (int i = 0; i < scale2; i++)
			{
				delete test[i]; // delete
			}
			break;
		}

		EndTest(); // print task time
	}
}
#if EXPERIMENTAL_MODE
// Mem
void MemStackAllocTest(int sizeInBytes)
{
	int size = 10000000;
	MemStackAllocator* t_StackAlloc = Mem::new_Stack(size);

	for (std::size_t i = 0; i < size/10; i++)
	{
		t_StackAlloc->Add(4);
	}

    char* t_TestArrayChar = (char*)t_StackAlloc->Add(size/100);

    t_StackAlloc->Remove(t_TestArrayChar);

	int* t_TestArrayInt = (int*)t_StackAlloc->Add(4 * 4000);

    t_StackAlloc->Pop(); // remove top most allocation

	char* t_TestArray3 = (char*)t_StackAlloc->Add(20000);
	t_StackAlloc->Pop();

    Mem::delete_Stack(t_StackAlloc); // release RAM
}

void MemPoolAllocTest(int sizeInBytes)
{
    const int size = 1000;
    MemPoolAllocator* pool = Mem::new_Pool(4, size);
    int* list[size];
    for (std::size_t i = 0; i < size; i++)
    {
        list[i] = (int*)pool->Add(4);
    }
    for (std::size_t i = 0; i < size; i++)
    {
        pool->Remove(list[i]);
    }

    Mem::delete_Pool(pool);
}
#endif
// New
void NewStackAllocTest(int sizeInBytes)
{
    int size = 10000000;
	for (std::size_t i = 0; i < size/10; i++)
	{
		new int;
	}

    char* t_TestArrayChar = new char[size/100];
    delete[] t_TestArrayChar;

    int* t_TestArrayInt = new int[4000];
    delete[] t_TestArrayInt;

	char* t_TestArrayChar2 = new char[20000];
	delete[] t_TestArrayChar2;
}

void NewPoolAllocTest(int sizeInBytes)
{
    const int size = 1000;
    int* list[size];
    for (std::size_t i = 0; i < size; i++)
    {
        list[i] = new int;
    }
    for (std::size_t i = 0; i < size; i++)
    {
        delete list[i];
    }
}