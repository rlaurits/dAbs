
#include <iostream>
#include <cstdio>
#include "BSTMap.h"
//#include <string>
#include <cstdlib>
using namespace std;

int main() {
    BSTMap<char, int> *bst;

    cout<<bst-> size()<<endl;

    bst-> insert(std::make_pair('a', 10));

    cout<<bst-> size()<<endl;

}
