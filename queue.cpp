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
   int size()
   {
    return top+1;
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
    public:
    Lnode* top = nullptr;//不带头结点的链栈
    int len;
    //不必考虑栈的长度
    SList()
    {
        len = 0;
    }
    ~SList()
    {
        while(!isEmpty())
        {
            pop();
        }
    }
    bool isEmpty()
    {
        return top==nullptr;
    }
    bool push(int val)
    {
        Lnode* p = new Lnode(val);//new
        p->next=top;
        top = p;
        len++;
        return true;
    }
    bool pop()
    {
        if(isEmpty())return false;
        Lnode* p = top;
        top = top->next;
        len--;
        delete p;
        return true;
    }
    int Top()
    {
        if(isEmpty())
        {
            throw runtime_error("stack is empty");
        }
        return top->value;
    }
    int size()
    {
        return len;
    }


};

class queue
{
    //FIFO
    public:
    int arr[Maxsize];
    int front;//队头
    int rear;//队尾
    queue()
    {
        front=0;
        rear=0;
    }
    ~queue(){};
    bool isEmpty()
    {
        return front==rear;
    }
    bool isFull()
    {
        return (rear+1)%Maxsize==front;
    }
    bool push(int val)
    {
        //从队尾插入
        if(isFull())return false;//队列满了
        arr[rear]=val;
        rear = (rear+1)%Maxsize;
        return true;
    }
    bool pop()
    {
        if(isEmpty())return false;//队列空
        front = (front+1)%Maxsize;
        return true;
    }
    int Top()
    {
        if(isEmpty())
        {
            throw runtime_error("队列为空");
        }
        return arr[front];
    }
    int size()
    {
        return (rear-front+Maxsize)%Maxsize;
    }
};

int main()
{

    /*
    Stack St;
    St.push(3);
    cout<<St.Top()<<endl;
    St.push(4);
    cout<<St.Top()<<endl;
    St.pop();
    cout<<St.Top()<<endl;
    St.pop();
    cout<<St.Top()<<endl;
    */

    queue Q;
    Q.push(3);
    cout<<Q.Top()<<endl;
    Q.push(4);
    Q.pop();
    cout<<Q.Top()<<endl;

    SList Sl;
    Sl.push(5);
    cout<<Sl.Top()<<endl;
    Sl.push(6);
    cout<<Sl.Top()<<endl;



    return 0;
}