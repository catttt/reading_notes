#ifndef STACKOUTORDER__H__
#define STACKOUTORDER__H__
#include <stdio.h>
#include <stdlib.h>

#define ElementType int

typedef struct StackNodeOutOrder
{
    /* data */
    ElementType Data;
    StackNodeOutOrder *Next;
} *StackNodeOO;

class StackOutOrder
{
private:
    /* data */
    StackNodeOO stack;
public:
    StackOutOrder(/* args */);
    ~StackOutOrder();
    bool IsEmpty();
    bool Push(ElementType e);
    ElementType Pop();

};

StackOutOrder::StackOutOrder(/* args */)
{
    stack = (StackNodeOO)malloc(sizeof(StackNodeOutOrder));
}

StackOutOrder::~StackOutOrder()
{

}
bool StackOutOrder::IsEmpty()
{
    if(stack->Next==0)
        return true;
    return false;
}

bool StackOutOrder::Push(ElementType e)
{
    StackNodeOO newNode = (StackNodeOO)malloc(sizeof(StackNodeOutOrder));
    StackNodeOO tmp;
    newNode->Data = e;

    tmp = stack;
    stack = newNode;
    newNode->Next = tmp;
    return true;
}

ElementType StackOutOrder::Pop()
{
    if(IsEmpty())
    {
        printf("stack is empty");
        return 0;//!!
    }
    StackNodeOO tmp = stack;
    stack = stack->Next;
    ElementType e = tmp->Data;
    free(tmp);
    return e;
}








#endif