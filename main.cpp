#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include "RB_Tree.h"

using namespace std;

int main()
{
    RBtree a;
    int n;

    while(true){
        cout<<"Enter x (delete if find, insert if notfind, -1 if exit)";
        cin>>n;
        if(n==-1)
            return 0;
        else{
            if (a.RBfind(n)==NULL)
                {a.RBinsert(n);}
            else
                a.RBdelete(a.RBfind(n));
            a.Output();
        }
    }
    return 0;
}
