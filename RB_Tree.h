#include <bits/stdc++.h>

using namespace std;

typedef enum {b,r} COL;

struct Tree{
        Tree *left;
        Tree *right;
        Tree *father;
        COL color;
        int data;
        Tree(int x) : left(NULL) , right(NULL) , father(NULL) , color(r) , data(x){}
} ;

class RBtree{

private:

    Tree *root=NULL;
    Tree *grandparent(Tree *point);
    Tree *uncle(Tree *point);
    Tree *brother(Tree *point);
    void rotate_left(Tree *x);
    void rotate_right(Tree *y);
    void insertFix(Tree *n);
    void deleteFix(Tree *n);
    void Output(Tree *point, int prob);

public:

    void Output();
    Tree *RBfind(int x);
    void RBinsert(int x);
    void RBdelete(Tree *z);

};
