#include <iostream>
#include <stdlib.h>
#include<math.h>
using namespace std;
#define TTElemType char
#define Status int
typedef struct TTNode
{
    TTElemType key;
    int priority;
    struct TTNode *parent,*left,*right;
} TTNode;
typedef struct TreapTree
{
    TTNode* root;
} TreapTree;
int SchrageRandomNumber(int &n);
int Partition(TTNode node[],int low,int high);
void QSort(TTNode node[],int low,int high);
Status TreapTreeInit(TreapTree &T);
Status LeftRotate(TreapTree &T,TTNode* x);
Status RightRotate(TreapTree &T,TTNode* x);
Status TreapTreeInsert(TreapTree &T,TTNode *z);
Status TreapTreeFixup(TreapTree &T,TTNode* z);
Status TreapTreeTransplant(TreapTree &T,TTNode* u,TTNode* v);
TTNode* TreeMinimum(TTNode* x);
Status TreapTreeDelete(TreapTree &T,TTNode *z);
void printspace(int space);
int TraverseAtLevel(TTNode* x, int level,int space);
Status LevelOrderTraverseTree(TreapTree T);

int main()
{
    int seed = 1; // n 为种子，需提前设置
    TTNode node[8]={{0,0,0,0},{'G',4,0,0,0},{'B',7,0},{'H',5,0},{'A',10,0},{'E',23,0},{'K',65,0},{'I',73,0}};
    for(int i=1;i<=7;i++)
    {
        cout<<"node key:"<<node[i].key<<" priority:"<<node[i].priority<<endl;
    }
    QSort(node,1,7);
    TreapTree T;
    TreapTreeInit(T);
    for(int i=1;i<=7;i++)
    {
        TreapTreeInsert(T,&node[i]);
    }
    LevelOrderTraverseTree(T);

    TTNode x={'C',25,0};
    cout<<"insert node key:"<<x.key<<" priority:"<<x.priority<<endl;
    TreapTreeInsert(T,&x);
    LevelOrderTraverseTree(T);
    TTNode y={'D',9,0};
    cout<<"insert node key:"<<y.key<<" priority:"<<y.priority<<endl;
    TreapTreeInsert(T,&y);
    LevelOrderTraverseTree(T);
    TTNode z={'F',2,0};
    cout<<"insert node key:"<<z.key<<" priority:"<<z.priority<<endl;
    TreapTreeInsert(T,&z);
    LevelOrderTraverseTree(T);
    TTNode u={'T',SchrageRandomNumber(seed)%100,0};
    cout<<"insert node key:"<<u.key<<" with a random priority:"<<u.priority<<endl;
    TreapTreeInsert(T,&u);
    LevelOrderTraverseTree(T);
    cout<<"delete node key:"<<z.key<<" priority:"<<z.priority<<endl;
    TreapTreeDelete(T,&z);
    LevelOrderTraverseTree(T);
    cout<<"delete node key:"<<x.key<<" priority:"<<x.priority<<endl;
    TreapTreeDelete(T,&x);
    LevelOrderTraverseTree(T);

    char *a;
    cin>>a;
    return 0;
}

int SchrageRandomNumber(int &n)
{
    const int a = 16807;         // 16807 法
    const int b = 0;
    const int m = 2147483647;    // MAX_INT
    const int q = m / a;         // q = m / a;
    const int r = m % a;         // r = m % a;
    n = a * (n % q) - r * (int)(n / q) + b; // 计算 mod
    if(n < 0)
        n += m;             // 将结果调整到 0 ~ m
    return n;
}
int Partition(TTNode node[],int low,int high)
{
    node[0]=node[low];
    int priority=node[low].priority;
    while(low<high)
    {
        while(low<high&&node[high].priority>=priority)
            --high;
        node[low]=node[high];
        while(low<high&&node[low].priority<=priority)
            ++low;
        node[high]=node[low];
    }
    node[low]=node[0];
    return low;
}
void QSort(TTNode node[],int low,int high)
{
    if(low<high)
    {
        int pivotloc=Partition(node,low,high);
        QSort(node,low,pivotloc-1);
        QSort(node,pivotloc+1,high);
    }
}
Status TreapTreeInit(TreapTree &T)
{
    T.root=NULL;
    return 0;
}
/**
*     |                             |
*     y    <-left rotate(T,x)--     x
*    / \                           / \
*   x   r                         a   y
*  / \                               / \
* a   b    --right rotate(T,y)->    b   r
*/
Status LeftRotate(TreapTree &T,TTNode* x)
{
    TTNode *y;
    y=x->right;
    x->right=y->left;
    if(y->left!=NULL)
    {
        y->left->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==NULL)
    {
        T.root=y;
    }
    else if(x==x->parent->left)
    {
        x->parent->left=y;
    }
    else
    {
        x->parent->right=y;
    }
    y->left=x;
    x->parent=y;
    return 0;
}
Status RightRotate(TreapTree &T,TTNode* x)
{
    TTNode *y;
    y=x->left;
    x->left=y->right;
    if(y->right!=NULL)
    {
        y->right->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==NULL)
    {
        T.root=y;
    }
    else if(x==x->parent->right)
    {
        x->parent->right=y;
    }
    else
    {
        x->parent->left=y;
    }
    y->right=x;
    x->parent=y;
    return 0;
}
Status TreapTreeFixup(TreapTree &T,TTNode* z)
{
    while(z!=NULL&&z->parent!=NULL&&z->parent->priority>z->priority)
    {
        if(z==z->parent->left)
        {
            RightRotate(T,z->parent);
        }
        else
        {
            LeftRotate(T,z->parent);
        }
        TreapTreeFixup(T,z);
    }
    return 0;
}
Status TreapTreeInsert(TreapTree &T,TTNode *z)
{
    TTNode *y=NULL;
    TTNode *x=T.root;
    while(x!=NULL)
    {
        y=x;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    z->parent=y;
    if(y==NULL)
        T.root=z;
    else if(z->key<y->key)
        y->left=z;
    else
        y->right=z;
    TreapTreeFixup(T,z);
    return 0;
}
Status TreapTreeTransplant(TreapTree &T,TTNode* u,TTNode* v)
{
    if(u->parent==NULL)
        T.root=v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    if(v!=NULL)
        v->parent=u->parent;
    return 0;
}
TTNode* TreeMinimum(TTNode* x)
{
    while(x->left!=NULL)
        x=x->left;
    return x;
}
Status TreapTreeDelete(TreapTree &T,TTNode *z)
{
    TTNode* y;
    if(z->left==NULL)
    {
        TreapTreeTransplant(T,z,z->right);
        TreapTreeFixup(T,z->right);
    }
    else if(z->right==NULL)
    {
        TreapTreeTransplant(T,z,z->left);
        TreapTreeFixup(T,z->left);
    }
    else
    {
        y=TreeMinimum(z->right);
        if(y->parent!=z)
        {
            TreapTreeTransplant(T,y,y->right);
            y->right=z->right;
            y->right->parent=y;
            y->parent=NULL;
            TreapTreeFixup(T,y->right);
        }
        TreapTreeTransplant(T,z,y);
        y->left=z->left;
        y->left->parent=y;
        TreapTreeFixup(T,y->left);
    }
    return 0;
}

void printspace(int space)
{
    for(int i=0; i<space; i++)
        cout<<" ";
}

int TraverseAtLevel(TTNode* x, int level,int space)
{
    if (level==0)
    {
        if (x==NULL)
        {
            printspace(space+2);
            printspace(space);
            return 0;
        }
        else
        {
            printspace(space);
            cout << x->key;
            cout << x->priority;
            printspace(space);
            return 1;
        }
    }
    else
    {
        return TraverseAtLevel(x?x->left:NULL, level-1,space)+TraverseAtLevel(x?x->right:NULL, level-1,space);
    }
}
Status LevelOrderTraverseTree(TreapTree T)
{
    int i = 0;
    for (i = 0; ; i++)
    {
        if (!TraverseAtLevel(T.root, i, (64-2*pow(2,i))/pow(2,i+1)))
            break;
        cout<<endl;
    }
    cout<<endl;
    return 0;
}



