//队列和栈
#include<iostream>
#define Maxsize 100

using namespace std;

class Stack
{
   public:
   int arr[Maxsize];//数组栈
   int top;//栈顶指针
   Stack()//构造函数
   {
    top = -1;
   }
   ~Stack()
   {

   }
   public:
   bool isEmpty()
   {
    return top==-1;
   }
   bool isFull()
   {
    return top == Maxsize-1;
   }
   bool push(int val)
   {
    if(isFull())return false;
    top++;
    arr[top] = val;
    return true;
   }
   bool pop()//需不需要返回数据呢
   {
    if(isEmpty())return false;
    top--;
    return true;
   }
   int Top()
   {
    if(isEmpty())
    {
        throw runtime_error("stack is empty, cannot get top");
    };
    return arr[top];
   }



};

struct Lnode
{
    int value;
    Lnode* next;
    Lnode(int val):value(val),next(nullptr){};
};

class SList//链栈
{
    pubilc:
    Lnode* top = nullptr;//不带头结点的链栈
    //不必考虑栈的长度
    SList()
    {

    }
    ~SList()
    {

    }
    bool isEmpty()
    {
        return top==nullptr;
    }
    bool push(int val)
    {
        Lnode* p = Lnode(val);
        p->next=top;
        top = p;
        return true;
    }
    bool pop()
    {
        if(isEmpty())return false;
        Lnode* p = top;
        top = top->next;
        delete p;
    }
    int Top()
    {
        if(isEmpty)
        {
            throw runtime_error("stack is empty");
        }
        return top->val;
    }


}

class queue
{
    //FIFO
    public:
    int arr[Maxsize];
    int top;//队头
    int rear;//队尾
    queue()
    {
        top=0;
        rear=0;
    }
    ~queue(){};
    bool isEmpty()
    {
        if(top==rear)
    }
}

int main()
{

    Stack St;
    St.push(3);
    cout<<St.Top()<<endl;
    St.push(4);
    cout<<St.Top()<<endl;
    St.pop();
    cout<<St.Top()<<endl;
    St.pop();
    cout<<St.Top()<<endl;





    return 0;
}