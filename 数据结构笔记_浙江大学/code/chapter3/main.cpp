#include <iostream>
#include"LinearList.h"

using namespace std;

int main(void)
{
    //顺序存储线性表
    LinearList *l = new LinearList();
    l->Insert(1,1);
    l->Insert(2,2);
    l->Insert(3,3);
    l->Insert(4,3);
    l->Insert(5,2);
    l->Insert(6,1);
    l->Delete(1);
    l->Delete(3);
    l->Delete(5);
    //链式存储线性表


    return 0;
}
