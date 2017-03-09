#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
using namespace std;
#define RBTElemType int
#define Status int
typedef enum Color {RED,BLACK} Color;
typedef struct RBTNode
{
    RBTElemType key;
    Color color;
    struct RBTNode *parent,*left,*right;
} RBTNode;
typedef struct RBTree
{
    RBTNode* root;
    RBTNode* nil;
} RBTree;

Status RBTreeInit(RBTree &T);
Status LeftRotate(RBTree &T,RBTNode* x);
Status RightRotate(RBTree &T,RBTNode* x);
Status RBTreeInsert(RBTree &T,RBTNode* z);
Status RBTreeInsertFixup(RBTree &T,RBTNode* z);
Status RBTreeTransplant(RBTree &T,RBTNode* u,RBTNode *v);
RBTNode* TreeMinimum(RBTree T,RBTNode* x);
Status RBTreeDelete(RBTree &T,RBTNode* z);
Status RBTreeDeleteFixup(RBTree &T,RBTNode* x);
Status PreOrderTraverseTree(RBTNode *x);
void printspace(int space);
void coutWithColor(RBTElemType key,Color color);
int TraverseAtLevel(RBTree T,RBTNode* x, int level,int space);
Status LevelOrderTraverseTree(RBTree T);

int main()
{
    RBTree T;
    RBTreeInit(T);
    RBTNode node[6]={0};
    node[0].key=41;
    node[1].key=38;
    node[2].key=31;
    node[3].key=12;
    node[4].key=19;
    node[5].key=8;
    cout<<"insert node:";
    for(int i=0;i<6;i++)
    cout<<node[i].key<<"  ";
    cout<<endl;
    RBTreeInsert(T,&node[0]);
    RBTreeInsert(T,&node[1]);
    RBTreeInsert(T,&node[2]);
    RBTreeInsert(T,&node[3]);
    RBTreeInsert(T,&node[4]);
    RBTreeInsert(T,&node[5]);
    LevelOrderTraverseTree(T);
    cout<<"delete node:"<<node[1].key<<endl;
    RBTreeDelete(T,&node[1]);
    LevelOrderTraverseTree(T);
    cout<<"delete node:"<<node[2].key<<endl;
    RBTreeDelete(T,&node[2]);
    LevelOrderTraverseTree(T);

    char *a;
    cin>>a;
    return 0;
}

Status RBTreeInit(RBTree &T)
{
    T.nil=(RBTNode *)malloc(sizeof(RBTNode));
    T.nil->key=0;
    T.nil->color=BLACK;
    T.nil->parent=NULL;
    T.nil->left=NULL;
    T.nil->right=NULL;
    T.root=T.nil;
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
Status LeftRotate(RBTree &T,RBTNode* x)
{
    RBTNode *y;
    y=x->right;
    x->right=y->left;
    if(y->left!=T.nil)
    {
        y->left->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==T.nil)
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
Status RightRotate(RBTree &T,RBTNode* x)
{
    RBTNode *y;
    y=x->left;
    x->left=y->right;
    if(y->right!=T.nil)
    {
        y->right->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==T.nil)
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
Status RBTreeInsert(RBTree &T,RBTNode* z)
{
    RBTNode* y=T.nil;
    RBTNode* x=T.root;
    while(x!=T.nil)
    {
        y=x;
        if(z->key<x->key)
        {
            x=x->left;
        }
        else
        {
            x=x->right;
        }
    }
    z->parent=y;
    if(y==T.nil)
    {
        T.root=z;
    }
    else if(z->key<y->key)
    {
        y->left=z;
    }
    else
    {
        y->right=z;
    }
    z->left=T.nil;
    z->right=T.nil;
    z->color=RED;
    RBTreeInsertFixup(T,z);
    return 0;
}
Status RBTreeInsertFixup(RBTree &T,RBTNode* z)
{
    RBTNode* y;
    while(z->parent->color==RED)
    {
        if(z->parent==z->parent->parent->left)
        {
            y=z->parent->parent->right;
            if(y->color==RED)
            {
                z->parent->color=BLACK;
                y->color=BLACK;
                z->parent->parent->color=RED;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->right)
                {
                    z=z->parent;
                    LeftRotate(T,z);
                }
                z->parent->color=BLACK;
                z->parent->parent->color=RED;
                RightRotate(T,z->parent->parent);
            }
        }
        else
        {
            y=z->parent->parent->left;
            if(y->color==RED)
            {
                z->parent->color=BLACK;
                y->color=BLACK;
                z->parent->parent->color=RED;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->left)
                {
                    z=z->parent;
                    RightRotate(T,z);
                }
                z->parent->color=BLACK;
                z->parent->parent->color=RED;
                LeftRotate(T,z->parent->parent);
            }
        }
    }
    T.root->color=BLACK;
    return 0;
}


Status RBTreeTransplant(RBTree &T,RBTNode* u,RBTNode *v)
{
    if(u->parent==T.nil)
    {
        T.root=v;
    }
    else if(u==u->parent->left)
    {
        u->parent->left=v;
    }
    else
    {
        u->parent->right=v;
    }
    v->parent=u->parent;
    return 0;
}
RBTNode* TreeMinimum(RBTree T,RBTNode* x)
{
    while(x->left!=T.nil)
        x=x->left;
    return x;
}
Status RBTreeDelete(RBTree &T,RBTNode* z)
{
    RBTNode *y=z,*x;
    Color yOriginalColor=y->color;
    if(z->left==T.nil)
    {
        x=z->right;
        RBTreeTransplant(T,z,z->right);
    }
    else if(z->right==T.nil)
    {
        x=z->left;
        RBTreeTransplant(T,z,z->left);
    }
    else
    {
        y=TreeMinimum(T,z->right);
        yOriginalColor=y->color;
        x=y->right;
        if(y->parent==z)
        {
            x->parent=y;
        }
        else
        {
            RBTreeTransplant(T,y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        RBTreeTransplant(T,z,y);
        y->left=z->left;
        y->left->parent=y;
        y->color=z->color;
    }
    if(yOriginalColor==BLACK)
    {
        RBTreeDeleteFixup(T,x);
    }
    return 0;
}
Status RBTreeDeleteFixup(RBTree &T,RBTNode* x)
{
    RBTNode *w;
    while(x!=T.root&&x->color==BLACK)
    {
        if(x==x->parent->left)
        {
            w=x->parent->right;
            if(w->color==RED)
            {
                w->color=BLACK;
                x->parent->color=RED;
                LeftRotate(T,x->parent);
                w=x->parent->right;
            }
            if(w->left->color==BLACK&&w->right->color==BLACK)
            {
                w->color=RED;
                x=x->parent;
            }
            else
            {
                if(w->right->color==BLACK)
                {
                    w->left->color=BLACK;
                    w->color=RED;
                    RightRotate(T,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color=BLACK;
                w->right->color=BLACK;
                LeftRotate(T,x->parent);
                x=T.root;
            }
        }
        else
        {
            w=x->parent->left;
            if(w->color==RED)
            {
                w->color=BLACK;
                x->parent->color=RED;
                RightRotate(T,x->parent);
                w=x->parent->left;
            }
            if(w->right->color==BLACK&&w->left->color==BLACK)
            {
                w->color=RED;
                x=x->parent;
            }
            else
            {
                if(w->left->color==BLACK)
                {
                    w->right->color=BLACK;
                    w->color=RED;
                    LeftRotate(T,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color=BLACK;
                w->left->color=BLACK;
                RightRotate(T,x->parent);
                x=T.root;
            }
        }
    }
    x->color=BLACK;
    return 0;
}
Status PreOrderTraverseTree(RBTNode *x)
{
    if(x!=NULL)
    {
        cout<<x->key<<" ";
        PreOrderTraverseTree(x->left);
        PreOrderTraverseTree(x->right);
    }
    return 0;
}
void printspace(int space)
{
    for(int i=0; i<space; i++)
        cout<<" ";
}
void coutWithColor(RBTElemType key,Color color)
{
    if(color==RED)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    }
    cout<<key;
}
int TraverseAtLevel(RBTree T,RBTNode* x, int level,int space)
{
    if (level==0)
    {
        if (x==T.nil)
        {
            printspace(space+2);
            printspace(space);
            return 0;
        }
        else
        {
            printspace(space);
            coutWithColor(x->key,x->color);
            printspace(space);
            return 1;
        }
    }
    else
    {
        return TraverseAtLevel(T,x!=T.nil?x->left:T.nil, level-1,space)+TraverseAtLevel(T,x!=T.nil?x->right:T.nil, level-1,space);
    }
}
Status LevelOrderTraverseTree(RBTree T)
{
    int i = 0;
    for (i = 0; ; i++)
    {
        if (!TraverseAtLevel(T, T.root, i, (32-2*pow(2,i))/pow(2,i+1)))
            break;
        cout<<endl;
    }
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    return 0;
}
