#ifndef STACKORDERSTORE__H__
#define STACKORDERSTORE__H__

#include <stdio.h>
#include <stdlib.h>


#define ElementType int
#define Position int

typedef struct StackNode
{
    /* data */
    ElementType *Data;
    Position Top;
    int MaxSize;
} StackOrder;

class StackOrderStore
{
private:
    /* data */
    StackOrder s; 
public:
    StackOrderStore(int MaxSize);
    ~StackOrderStore();
    bool IsFull();
    bool IsEmpty();
    bool Push(ElementType e);
    ElementType Pop();
};

StackOrderStore::StackOrderStore(int MaxSize)
{
    s.Data = (ElementType*)malloc(sizeof(ElementType)*MaxSize);
    s.MaxSize = MaxSize;
    s.Top = -1;
}

StackOrderStore::~StackOrderStore()
{
    free(s.Data);
}

bool StackOrderStore::IsFull()
{
    return (s.Top == s.MaxSize);
}
bool StackOrderStore::IsEmpty()
{
    return (s.Top == -1);
}

bool StackOrderStore::Push(ElementType e)
{
    if (IsFull())
    {
        /* code */
        printf("stack full");
        return false;
    }
    
    s.Data[++s.Top] = e;
    return true;
}
ElementType StackOrderStore::Pop()
{
    if (IsEmpty())
    {
        /* code */
        printf("stack is empty");
        return 0;//null
    }
    
    return s.Data[s.Top--];
}

#endif