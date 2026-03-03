#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
//顺序表

#define Maxsize 100

typedef struct {
   int data[Maxsize];
   int length;
}Sqlist;//静态分配

//初始化一个空表
void Initlist(Sqlist &L)
{
    L.length = 0;
}
//返回表长
int length(Sqlist L)
{
    return L.length;
}
//按数值查找
int locateElem(Sqlist L, int e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.data[i]==e)
        return i+1;
    };
    return 0;
}
//按位查找
int GetElem(Sqlist L,int i)
{
    if(i<1||i>L.length)
    {
    printf("范围溢出\n");
    return -1;
    }

    else
    return L.data[i-1];
}

//插入操作
bool ListInsert(Sqlist &L,int i, int e)
{
    //判断i是否合法，判断顺序表是否full
    if(i<1||i>L.length+1||L.length == Maxsize)
    return false;
    for(int j = L.length;j >= i;j--)//后移，后面开始
    {
        L.data[j]=L.data[j-1];//循环到data[i-1]
    }
    L.data[i-1]=e;
    L.length++;
    return true;
}

//删除操作
bool ListDelete(Sqlist &L,int i,int &e)
{
    if(i<1||i>L.length)
    {
        return false;
    }
    e = L.data[i-1];
    for(int j=i;j<L.length;j++)//注意这段代码是把顺序表的值前移,从前面开始
    {
          L.data[j-1] = L.data[j];//data[i-1]
    }
    L.length--;
    return true;
}

//从头打印顺序表
void PrintList(Sqlist L)
{
    for(int i=0;i<L.length;i++)
    {
        printf("%d ",L.data[i]);
    }
    printf("\n");
}

//判空操作
bool EmptyList(Sqlist L)
{
    if(L.length==0)
    return true;
    else
    return false;
}

//销毁顺序表
bool DestroyList(Sqlist &L)
{
    L.length = 0;
    return true;
}

int main()
{
   Sqlist L;
   Initlist(L);
   printf("%d\n",L.length);
   printf("%d\n",EmptyList(L));
   ListInsert(L,1,1);
   ListInsert(L,2,2);
   ListInsert(L,2,3);
   printf("%d\n",length(L));

   PrintList(L);
   printf("%d\n",GetElem(L,3));
   printf("%d\n",locateElem(L,2));
   return 0;
}