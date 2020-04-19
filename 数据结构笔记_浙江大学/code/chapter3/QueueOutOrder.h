#ifndef QUEUEOUTORDER__H__
#define QUEUEOUTORDER__H__

#include <stdlib.h>
#include <stdio.h>

#define ElementType int

typedef struct QueueOutOrderNode
{
    /* data */
    ElementType Data;
    QueueOutOrderNode *Next;
} *PtrQueueOONode;


class QueueOutOrder
{
private:
    /* data */
    PtrQueueOONode Front,Rear;
public:
    QueueOutOrder(/* args */);
    ~QueueOutOrder();
    bool IsEmpty();
    bool AddQ(ElementType e);
    ElementType DeleteQ();
};

QueueOutOrder::QueueOutOrder(/* args */)
{
    Front = 0;
    Rear = 0;
}

QueueOutOrder::~QueueOutOrder()
{
}

bool QueueOutOrder::IsEmpty()
{
    if(Front == 0)
    {
        printf("queue is empty");
        return true;
    }
    return false;
}

bool QueueOutOrder::AddQ(ElementType e)
{
    PtrQueueOONode newNode = (PtrQueueOONode)malloc(sizeof(QueueOutOrderNode));
    newNode->Data = e;

    if(IsEmpty())
    {
        Front = newNode;
        Rear = newNode;
    }else
    {
        /* code */
        Rear->Next = newNode;
        Rear = Rear->Next;
    }
    return true;
}

ElementType QueueOutOrder::DeleteQ()
{
    ElementType tmp;
    if(IsEmpty())
    {
        printf("queue is empty");
        return 0;//!!
    }else
    {
        /* code */
        tmp = Front->Data;
        if (Front->Next)
        {
            Front = Front->Next;
        }else
        {
            /* code */
            Front = 0;
            Rear = 0;
        }
        
        return tmp;
    }
    
}




#endif