#ifndef _InstructionBlock_H_
#define _InstructionBlock_H_

#include <vcruntime_string.h> // memcpy

class InstructionBlock
{
public:
    InstructionBlock::InstructionBlock(int numBytes) : m_Size(numBytes)
    {
        m_Block = new unsigned char[numBytes];
        memset(m_Block, m_NullValue, numBytes);
        m_Index = m_Block;
    }

    ~InstructionBlock()
    {
        delete m_Block;
    }

    void InstructionBlock::PushBack(const char* data)
    {
        *m_Index = *data;
        m_Index++;
        m_BytesStored++;
    }

    void InstructionBlock::PushBack(char data)
    {
        *m_Index = data;
        m_Index++;
        m_BytesStored++;
    }

    // void InstructionBlock::PushBack(int data) {}

    int Size() { return m_Size; }
    int BytesStored() { return m_BytesStored; }
    int GetEffectiveSize() // number of non-null bytes
    {
        int i = m_Size - 1;
        while (i > -1)
        {
            if (m_Block[i] != m_NullValue)
                 break;
            i--;
        }
        return i + 1;
    }

    void SetDataStart(unsigned char* data, int numBytes) { m_Block = data; m_Size = numBytes; }
    unsigned char* DataStart() { return m_Block; }

private:
    const int m_NullValue = 255;
    int m_Size = 0;
    int m_BytesStored = 0;
    unsigned char* m_Index = nullptr;
    unsigned char* m_Block = nullptr;
};

#endif // _InstructionBlock_H_