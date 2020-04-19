#ifndef QUEUEORDER__H__
#define QUEUEORDER__H__
#include <stdio.h>
#include <stdlib.h>

#define ElementType int

typedef struct QueueOrderNode
{
    /* data */
    ElementType *Data;
    int Front,Rear;
    int MaxSize;
} *PtrQueueOrderNode;


class QueueOrder
{
private:
    /* data */
    QueueOrderNode q;
public:
    QueueOrder(int MaxSize);
    ~QueueOrder();
    bool IsFull();
    bool IsEmpty();
    bool AddQ(ElementType e);
    ElementType DeleteQ();
};

QueueOrder::QueueOrder(int MaxSize)
{
    q.MaxSize = MaxSize;
    q.Data = (ElementType*)malloc(sizeof(ElementType)*q.MaxSize);
    q.Front = 0;
    q.Rear = 0;
}

QueueOrder::~QueueOrder()
{
    free(q.Data);
}

bool QueueOrder::IsFull()
{
    return (q.Front==(q.Rear+1)%q.MaxSize);
}
bool QueueOrder::IsEmpty()
{
    return (q.Front == q.Rear);
}
bool QueueOrder::AddQ(ElementType e)
{
    if(IsFull())
    {
        printf("queue is full");
        return false;
    }
    q.Rear = (q.Rear+1)%q.MaxSize;
    q.Data[q.Rear] = e;
    return true;
}
ElementType QueueOrder::DeleteQ()
{
    if(IsEmpty())
    {
        printf("queue is empty");
        return 0;//!!
    }
    q.Front = (q.Front+1)%q.MaxSize;
    ElementType e = q.Data[q.Front];
    return e;
}





#endif