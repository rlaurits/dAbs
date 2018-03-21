
#include <iostream>
#include <cstdio>
#include "FileLinkedList.h"
using namespace std;

int main() {
    FileLinkedList<int> *fll = &FileLinkedList<int>("testFile.txt");
    
    /*
    for(fll-> const_iterator iter = fll-> begin; iter != fll-> end; ++iter) {
        cout<<*iter<<'\n';
    }
    */
}
