// 线性表的顺序存储
#ifndef LinearList__H__
#define LinearList__H__

#include "iostream"
#include "stdio.h"
#include <stdlib.h>

#define MAXSIZE 1000
#define ERROR -1

typedef int ElementType;
typedef int Position;
typedef struct LNode *PtrToNode;

struct LNode
{
    /* data */
    ElementType Data[MAXSIZE];
    Position Last;
};

typedef PtrToNode List;

class LinearList
{
private:
    /* data */
    List L;
public:
    LinearList(/* args */);
    ~LinearList();
    Position Find(ElementType x);
    bool Insert(ElementType x,Position i);
    bool Delete(Position i);
};

LinearList::LinearList(/* args */)
{
    L = (List)malloc(sizeof (struct LNode));
    L->Last = -1;
}

LinearList::~LinearList()
{
    free(L);
}

Position LinearList::Find(ElementType x)
{
    Position i =0;
    while (i<=L->Last && L->Data[i]!=x)
    {
        /* code */
        i++;
    }
    if (x>L->Last)
    {
        /* code */
        return ERROR; //not find
    }
    return i;
}

bool LinearList::Insert(ElementType x,Position i)
{
    Position j;
    if (L->Last == MAXSIZE)
    {
        /* code */
        printf("list is full");
        return false;
    }
    if (i<1 || i>L->Last+2)
    {
        /* code */
        printf("error position");
        return false;
    }
    for (j = L->Last; j >= i-1; j--)
    {
        /* code */
        L->Data[j+1] = L->Data[j];
    }
    L->Data[i-1] = x;
    L->Last++;
    return true;
}

bool LinearList::Delete(Position i)
{
    Position j;
    if (i<1 || i> L->Last + 1)
    {
        /* code */
        printf("Element is not exit in this Position");
        return false;
    }
    for (j = i-1; j < L->Last; j++)
    {
        /* code */
        L->Data[j] = L->Data[j+1];
    }
    L->Last--;
    return true;
}

#endif
