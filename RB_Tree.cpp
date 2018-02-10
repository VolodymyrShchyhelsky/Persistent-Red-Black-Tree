#include <bits/stdc++.h>
#include "RB_Tree.h"

using namespace std;

Tree* RBtree::grandparent(Tree *point)
{
    if( (point!=NULL) && (point->father!=NULL) )
        return point->father->father;
    else
        return NULL;
}

Tree* RBtree::uncle(Tree *point)
{
    Tree *g=grandparent(point);
    if( (g==NULL) )
        return NULL;
    if (point->father==g->left)
        return g->right;
        else
        return g->left;
}

Tree* RBtree::brother(Tree *point)
{
    if(point==point->father->left)
        return point->father->right;
    else
        return point->father->left;
}



void RBtree::rotate_left(Tree *x)
{
    Tree *y=x->right;

    y->father=x->father;

    if(x->father!=NULL)
    {
        if(x==x->father->left)
            x->father->left=y;
        else
            x->father->right=y;
    }
    else root=y;

    x->right=y->left;
    if(y->left!=NULL)
        y->left->father=x;

    x->father=y;
    y->left=x;
}

void RBtree::rotate_right(Tree *y)
{
    Tree *x=y->left;

    x->father=y->father;

    if(y->father!=NULL)
    {
        if(y==y->father->left)
            y->father->left=x;
        else
            y->father->right=x;
    }
    else root=x;

    y->left=x->right;
    if(x->right!=NULL)
        x->right->father=y;

    y->father=x;
    x->right=y;
}


void RBtree::insertFix(Tree *n)
{
    if(n->father==NULL) ///1
        {n->color=b; }//cout<<1<<endl;}
    else

    if(n->father->color==b) ///2
        {/*cout<<2<<endl;*/ return;}
    else

    if(uncle(n)!=NULL && n->father->color==r && uncle(n)->color==r) ///3
    {
        cout<<3<<endl;
        n->father->color=b;
        uncle(n)->color=b;
        grandparent(n)->color=r;
        insertFix(grandparent(n));
    }
    else
    {
        cout<<4<<endl;
        if(n==n->father->right && n->father==grandparent(n)->left) ///4;
        {
            rotate_left(n->father);
            n=n->left;
        }
        else
        if(n==n->father->left && n->father==grandparent(n)->right)
        {
            rotate_right(n->father);
            n=n->right;
        }

        cout<<5<<endl;
        n->father->color=b; ///5
        grandparent(n)->color=r;
        if(n==n->father->left && n->father==grandparent(n)->left)
            rotate_right(grandparent(n));
        else
            rotate_left(grandparent(n));
    }

}

void RBtree::deleteFix(Tree *n)
{
    if(n!=root) ///1
    {
        if(brother(n)->color==r) ///2
        {
            cout<<2<<endl;
            n->father->color=r;
            brother(n)->color=b;
            if(n==n->father->left)
                rotate_left(n->father);
            else
                rotate_right(n->father);
        }

        if(n->father->color==b &&
           brother(n)->color==b &&
           brother(n)->left->color==b &&
           brother(n)->right->color==b)  ///3
           {
               cout<<3<<endl;
                brother(n)->color=r;
                deleteFix(n->father);
           }
           else
            {

            if(n->father->color==r &&
               brother(n)->color==b &&
               brother(n)->left->color==b &&
               brother(n)->right->color==b) ///4
               {
                   cout<<4<<endl;
                    brother(n)->color=r;
                    n->father->color=b;
               }
            else
            {
                if(brother(n)->color==b) ///5
                {
                    cout<<5<<endl;
                    if(n==n->father->left &&
                       brother(n)->left->color==r &&
                       brother(n)->right->color==b)
                       {
                            brother(n)->color=r;
                            brother(n)->left->color=b;
                            rotate_right(brother(n));
                       }
                     else
                     if(n==n->father->right &&
                       brother(n)->left->color==b &&
                       brother(n)->right->color==r)
                       {
                            brother(n)->color=r;
                            brother(n)->left->color=b;
                            rotate_left(brother(n));
                       }
                }
                cout<<6<<endl;
                brother(n)->color=n->father->color; //6
                n->father->color=b;
                if(n==n->father->left)
                {
                    brother(n)->right->color=b;
                    rotate_left(n->father);
                }
                else{
                    brother(n)->left->color=b;
                    rotate_right(n->father);
                }
            }
            }
    }
}


void RBtree::Output(Tree *point, int prob=0){
    for(int i=0;i<prob;++i) cout<<"_";
    cout<<point->data<<" "<<point->color<<' '<<endl;

    if(point->left)
        Output(point->left,prob+1);
    if(point->right)
        Output(point->right,prob+1);
}


void RBtree::Output()
{
    Output(root);
}

Tree* RBtree::RBfind(int x)
{
    Tree *point=root;
    while(point!=NULL){
        if(point->data==x)
            return point;
        else{
            if(point->data>x)
                point=point->left;
            else
                point=point->right;
        }
    }
    return nullptr;
}

void RBtree::RBinsert(int x)
{
    Tree *n =new Tree(x);

    if(root==NULL)
        root=n;
    else
    {
        Tree *point=root;
        while(1){
            if(point->data>x)
            {
                if(point->left!=NULL)
                    point=point->left;
                else{
                    n->father=point;
                    point->left=n;
                    break;
                }
            }
            else
            {
                if(point->right!=NULL)
                    point=point->right;
                else{
                    n->father=point;
                    point->right=n;
                    break;
                }
            }
        }
     }
    insertFix(n);
}


void RBtree::RBdelete(Tree *z)
{
    Tree *x,*y;

    if(z==NULL)
        return;

    if(z->left==NULL && z->right==NULL)
        {
            if(z->father->left==z)
                z->father->left=NULL;
            else
                z->father->right=NULL;
            free(z);
            return;
        }

    if(z->left==NULL || z->right==NULL)
        y=z;
    else
    {
        y=z->right;
        while(y->left!=NULL)
            y=y->left;
    }

    if(y->left!=NULL)
        x=y->left;
    else
        x=y->right;
//cout<<y->data<<endl;
    if(x) x->father=y->father;
    if(y->father!=NULL)
    {
    if(y==y->father->left)
        y->father->left=x;
    else
        y->father->right=x;
    }
    else
        root=x;

    if(y!=z) z->data=y->data;
    if(y->color==b){
        if(x->color==r)
            x->color=b;
        else
            deleteFix(x);
    }
    free(y);
}

