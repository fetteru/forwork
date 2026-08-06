#include<iostream>

using namespace std;

struct Lnode
{
    int value;//默认值
    Lnode* next;
    Lnode(int v=0):value(v),next(nullptr){};
};

class List
{
    public:
     int length = 0;
     Lnode* header = new Lnode;
     Lnode* rear = nullptr;
    List()
    {
           header->value = 0;
           header->next = NULL;
           rear = header;
    }
    ~List()
    {
        while(!isEmpty())
        {
            del();
        }
        delete header;

    }
    public:
     bool isEmpty()
     {
        return header->next == nullptr;
     }
     void print()
     {
        Lnode* t = header->next;
        while(t!=nullptr)
        {
            cout<<t->value<<" ";
            t = t->next;
        }
        cout<<endl;
     }
     bool add(int n)//在header插入节点，头插法
     { 
      Lnode* p = new Lnode;
      p->value = n;
      p->next = header->next;
      if(isEmpty()) rear = p;
      header->next = p;
      length++;
      return true;
     }
     bool del()//从头节点删去一个结点
     {
        if(isEmpty())
        {
            cout<<"删除失败"<<endl;
            return false;
        }
        Lnode* p = header->next;
        if(p->next==nullptr)rear=header;//p是最后一个节点；
        header->next = p->next;
        delete p;
        length--;
        return true;
     }
     bool popBack()//尾部删除
     {
        if(isEmpty())return false;//删除这个节点，必须找到他的前面节点，因为需要操作他前面节点的next指针
        Lnode* p = header;
        while(p->next!=rear)
        {
            p = p->next;
        }
        Lnode* q = rear;
        p->next = q->next;
        rear = p;
        delete q;
        length--;
        return true;

     }
     int size()
     {
        return length; 
     }
     bool pushBack(int val)
     {
        Lnode* p = new Lnode(val);
        rear->next = p;
        rear = p;
        length++;
        return true;

     }
     int gethead()
     {
        if(isEmpty())return false;
        return header->next->value;
     }
     int getend()//获取尾部结点的值
     {
        if(isEmpty())return false;
        return rear->value;
     }
     int get(int pos)
     {
        //x应该属于1~length;
        if(pos<1||pos>length)return false;
        Lnode* p = header;
        while(pos)
        {
            p=p->next;
            pos--;
        }
        
        int val = p->value;
        return val;
     }
     bool insert(int pos,int val)
     {
         if(pos<1||pos>length)return false;
         if(pos==length)
         {
            pushBack(val);
            return true;
         }
         Lnode* p = new Lnode(val);
         Lnode* q = header;
         pos--;
         while(pos)
         {
            q=q->next;
            pos--;
         }
         p->next = q->next;
         q->next = p;
         length++;
         return true;


     }
     int find(int val)//按值查找
     {
      int pos = 1;
      Lnode* p = header->next;
      while(p != nullptr&&val != p->value)
      {
         pos++;
         p = p->next;
      }
      if(pos<=length)return pos;
      else return -1;//-1表示没找到

     }
     bool remove(int val)
     {
      if(isEmpty())return false;//空表
      Lnode* p = header;
      while(p->next != nullptr)//还有下个结点
      {
         if(p->next->value==val)//找到了
         {
            Lnode* q = p->next;
            p->next = q->next;
            if(rear==q)rear = p;
            delete q;
            length--;
            return true;
         }
         p = p->next;
      }
      return false;


     }//按值删除
     bool reverse()
     {
      //这是一个带哨兵结点和尾节点的链表
      if(isEmpty())return true;//空链表翻转还是空链表，不必操作
      Lnode* p = header->next;
      while(1)
      {
         Lnode* q = p->next;
         if(q==nullptr)break;
         p->next = q->next;
         q->next = header->next;
         header->next = q;
      }
      rear = p;
      return true;

     }//反转链表
     bool clear()
     {
        while(!isEmpty())
        {
         del();
        }
        return true;
     };//清空链表

};




int main()
{
   List L;

   L.add(4);

   L.add(9);

   L.add(55);

   L.print();
   L.del();

   L.add(43);
   L.print();
   cout<<L.rear->value<<endl;
   L.pushBack(12);
   L.print();
   L.print();
   L.insert(3,99);
   L.insert(4,33);
   L.insert(6,31);
   L.print();
   int val = L.get(6);
   int pos1 = L.find(31);
   L.remove(4);
   L.print();
   int pos2 = L.find(4);
   cout<<val<<endl<<pos1<<endl<<pos2<<endl;//打印val
   L.reverse();
   L.print();
   L.clear();
   L.print();

   return 0;

}