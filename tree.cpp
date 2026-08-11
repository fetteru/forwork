#include<iostream>

#include<vector>

using namespace std;

struct trNode
{
    int val;
    trNode* left;
    trNode* right;
    trNode(int value):val(value),left(nullptr),right(nullptr){};
};


class Tree
{
    public:
    trNode* root = nullptr;

    int deepth;
    Tree(){
        deepth = 0;

    }
    ~Tree()
    {

    }
    bool isEmpty()
    {
        return root==nullptr;
    }
    //插入操作
    void add(int val)
    {
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


};





int main()
{
    Tree T;
    T.add(5);
    T.add(3);
    T.add(4);
    T.add(5);
    T.add(6);
    T.add(7);
    T.add(1);
    //T.preorder();
    T.Bfs_tr();
    




    return 0;
}