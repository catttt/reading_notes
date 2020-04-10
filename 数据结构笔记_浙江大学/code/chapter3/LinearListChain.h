#ifndef LINEARLISTCHAIN__H__
#define LINEARLISTCHAIN__H__
#include <stdio.h>
#include <stdlib.h>

#define ElementType int

typedef struct LCNode *PtrToLCNode;


struct LCNode
{
    /* data */
    ElementType Data;
    PtrToLCNode Next;
};

typedef PtrToLCNode CPosition;
typedef PtrToLCNode CList;

class LinearListChain
{
private:
    /* data */
    CList node;
public:
    LinearListChain(/* args */);
    ~LinearListChain();
    int Length();
    ElementType FindKth(int k);
    CPosition Find(ElementType e);
    int Insert(ElementType e,int i);
    int Delete(int i); 
};

LinearListChain::LinearListChain(/* args */)
{
    node = (CList)malloc(sizeof(struct LCNode));
}

LinearListChain::~LinearListChain()
{
    CPosition p,tmp;
    p = node;
    while (p)
    {
        /* code */
        tmp = node->Next;
        free(p);
        p =tmp;
    }
    
}

int LinearListChain::Length()
{
    int cnt =0;
    CPosition p = node;
    while (p)
    {
        /* code */
        p = p->Next;
        cnt++;
    }
    return cnt;
}

ElementType LinearListChain::FindKth(int k)
{
    CPosition p = node;
    while ((p)&&(--k))
    {
        /* code */
        p = p->Next;
    }
    
    if (k==0)
    {
        /* code */
        return p->Data;
    }
    printf("not find");
    return -1;

}

CPosition LinearListChain::Find(ElementType e)
{
    CPosition p = node;
    while (p && p->Data!=e)
    {
        /* code */
        p = p->Next;
    }
    if (p)
    {
        /* code */
        return p;
    }

    printf("not find");
    return 0;
}

int LinearListChain::Insert(ElementType e,int i)
{
    CPosition tmp = (CPosition)malloc(sizeof(struct LCNode));
    tmp->Data = e;

    CPosition p = node;
    CPosition pre;
    
    if (i == 1)
    {
        /* code */
        if (!p->Next)
        {
            /* code */
            p->Data = e;
            free(tmp);
            return 1;
        }
        
        pre = node;
        node = tmp;
        tmp->Next = pre;
        return 1;
    }
    
    i--;
    while (--i && p)
    {
        /* code */
        pre = p;
        p = p->Next;
    }

    if (p)
    {
        /* code */
        tmp->Next = p->Next;
        p->Next = tmp;
        return 1;
    }
    return -1;
}


int LinearListChain::Delete(int i)
{
    CPosition p = node;
    CPosition pre;
    int cnt =0;

    if (i==1)
    {
        /* code */
        node = p->Next;
        free(p);
        return 1;
    }
    

    while (--i && p)
    {
        /* code */
        pre = p;
        p = p->Next;
    }

    if(p)
    {
        pre->Next = p->Next;
        free(p);
        return 1;
    }
    return -1;
}








#endif