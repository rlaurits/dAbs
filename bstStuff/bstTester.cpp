
#include <iostream>
#include <cstdio>
#include "BSTMap.h"
#include <cstdlib>
using namespace std;

struct argh {
    int x;
    char c;
};

int main() {
    BSTMap<char, int> *bst;
    
    argh *bleh = new argh;
    bleh-> x = 73;
    bleh-> c = 'F';
    cout<<bleh-> x<<endl;

    int wah = 42;
    int *ptr = &wah;
    cout<<*ptr<<endl;

    cout<<bst-> size()<<endl;

    bst-> insert(std::make_pair('a', 10));

    cout<<bst-> size()<<endl;

}
