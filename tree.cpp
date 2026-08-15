#include<iostream>
#include<stdexcept>
#include<algorithm>
#include<vector>

using namespace std;

struct trNode
{
    int val;
    trNode* left;
    trNode* right;
    trNode(int value):val(value),left(nullptr),right(nullptr){};
}


class Tree//二叉排序树
{
    private:
    trNode* root = nullptr;


    Tree(){

    }
    ~Tree()
    {
        destroy(root);
    }
    bool isEmpty()
    {
        return root==nullptr;
    }
    //插入操作
    void add(int val)
    {
        if(search(val))
        {
            throw runtime_error("can't insert existed val");
        }
        trNode* node = new trNode(val);
        if(isEmpty())
        {
            root = node;
            return;
        }
        trNode* p = root;
        trNode* parent = nullptr;
        while(p!=nullptr)
        {
            parent = p;
            if(node->val<p->val)
            {
                p = p->left;
            }
            else
            {
                p = p->right;
            }
        }
        if(node->val<parent->val)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }

        
    }
    void preorder()
    {
        preorder(root);
    }
    void midorder()
    {
        midorder(root);
    }
    void postorder()
    {
        postorder(root);
    }
    void Bfs_tr()
    {
        Bfs_tr(root);
    }
    bool search(int val)
    {
        trNode* p = root;
        if(p==nullptr)return false;
        while(p!=nullptr)
        {
            if(val==p->val)return true;
            else if(val<p->val)
            {
                p=p->left;
            }
            else
            {
                p=p->right;
            }
        }
        return false;
    }
    int height()
    {
        return heigh(root);
    }
    int size()
    {
        return size(root);
    }
    int numOfleaf()
    {
        return numOfleaf(root);
    }
    bool DelforT(int val)
    {
        trNode* s = new trNode(0);
        s->left = root;
        trNode* parent = s;
        trNode* p = root;
        bool flag = false;//false:p是parent的左孩子

        while(p!=nullptr&&p->val!=val)
        {
            parent = p;
            if(val < p->val)
            {
               p = p->left;
               flag = false;
            }
            else
            {
               p = p->right;
               flag = true;
            }
        }
        if(p==nullptr)
        {
            delete s;
            return false;
        }

        if(p->left==nullptr||p->right==nullptr)
        {
            trNode* child = p->left?p->left:p->right;
            if(flag)
            {
                parent->right = child;
            }
            else
            {
                parent->left = child;
            }
            delete p;
        }
        else
        {
        //p结点的左右孩子都不为空
            trNode* succParent = p;
            trNode* succ = p->right;
            while(succ->left!=nullptr)
            {
            succParent = succ;
            succ = succ->left;
            }
            p->val = succ->val;
            if(succParent==p)succParent->right = succ->right;
            else succParent->left = succ->right;
            delete succ;
        }

        
        root = s->left;//同步根指针
        delete s;
        return true;

    }
    bool DelforTr(int val)
    {
        //实现二叉树的删除
        trNode** cur = &root;
        while(*cur!=nullptr&&val!=(*cur)->val )
        {
            
            if(val<(*cur)->val)
            { 
                cur = &((*cur)->left);
            }
            else
            {
                cur = &((*cur)->right);
            }

        }
        if(*cur == nullptr)//没找到
        {
            return false;
        }
        trNode* p = *cur;

        if(p->left==nullptr||p->right==nullptr)
        {
            *cur = (p->left?p->left:p->right);
            delete p;
        }
        else
        {
            //两个孩子，找直接后继（中序后继）
            trNode** succSlot = &(p->right);
            while((*succSlot)->left!=nullptr)
              succSlot = &((*succSlot)->left);
            trNode* succ = *succSlot;
            p->val = succ->val;
            *succSlot = succ->right;
            delete succ;
        }
        


        return true;
        
    }
    private:    

    void preorder(trNode* root)//前序遍历打印，根左右
    {
        if(root==nullptr)return;
        cout<<root->val<<" ";
        preorder(root->left);
        preorder(root->right);
    }
    void midorder(trNode* root)//中序遍历打印，左中右
    {
        if(root==nullptr)return;
        midorder(root->left);
        cout<<root->val<<" ";
        midorder(root->right);

    }
    void postorder(trNode* root)//后序遍历
    {
        if(root==nullptr)return;
        postorder(root->left);
        postorder(root->right);
        cout<<root->val<<" ";
    }
    void Bfs_tr(trNode* root)//层序遍历，广度优先
    {
        //用队列实现树的层序遍历
        vector<trNode*> Q;
        if(root==nullptr)return;
        Q.emplace_back(root);
        while(!Q.empty())//加入队列,只有上一层全部指针全部尾nullptr才停止
        {
            trNode* l = Q.front()->left;
            trNode* r = Q.front()->right;
            if(l != nullptr)
            {
                Q.emplace_back(l);
            }
            if(r != nullptr)
            {
                Q.emplace_back(r);
            }
            cout<<Q.front()->val<<" ";
            Q.erase(Q.begin());
        }

    }
    int height(trNode* root)
    {
        if(root==nullptr)return 0;
        if(root->left==nullptr&&root->right==nullptr)
        {
            return 1;//出口
        }
        else
        {
            return max(heigh(root->left),heigh(root->right))+1;
        }

    }
    int size(trNode* root)//统计节点数
    {
       if(root==nullptr)return 0;
       else return size(root->left)+size(root->right)+1;
    }
    int numOfleaf(trNode* root)
    {
        if(root==nullptr)return 0;
        if(root->left==nullptr&&root->right==nullptr)
        {
            return 1;
        }
        else
        {
           return numOfleaf(root->left)+numOfleaf(root->right);
        }
    }
    void destroy(trNode* node)
    {
        if(node==nullptr)return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};





int main()
{
    Tree T;
    T.add(5);
    T.add(3);
    T.add(4);
    T.add(9);
    T.add(6);
    T.add(7);
    T.add(1);
    T.add(8);
    //T.preorder();
    T.Bfs_tr();
    cout<<endl;
    int h = T.height();
    cout<<h<<endl;
    cout<<T.size()<<endl;
    cout<<T.numOfleaf()<<endl;
    T.DelforT(3);
    T.Bfs_tr();
    




    return 0;
}