#include<iostream>

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
    private:    

    void preorder(trNode* root)//前序遍历打印
    {
        if(root==nullptr)return;
        cout<<root->val<<" ";
        preorder(root->left);
        preorder(root->right);
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
    T.preorder();




    return 0;
}