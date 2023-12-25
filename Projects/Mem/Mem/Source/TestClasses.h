#ifndef _TestClasses_H_
#define _TestClasses_H_

// Test class objects
class MyClass1 // size is 4 bytes
{
public:
    MyClass1() { x = 2; }
    ~MyClass1() { x = -1; }
private:
    int x;
};
//
struct MyClass2 // size is 16 bytes
{
    int x;
    MyClass1 object();
    bool data[10];
};
//
struct MyClass3 // size is 88 bytes
{
    float data[20];
    int* stuff = new int[20];
};

#endif //!_TestClasses_H_