
#include <iostream>
#include <cstdio>
#include "FileLinkedList.h"
using namespace std;

int main() {
    FileLinkedList<int> *fll = new FileLinkedList<int>("testFile.txt");

    //fll-> push_back(50);
    //fll-> push_back(42);
    //fll-> push_back(36);
    for(int i = 1; i <= 4; ++i) {
        fll-> push_back(i);
        cout<<"sz: "<<fll-> size()<<'\n';
        
    }
    fll-> push_back(10);

    fll-> pop_back();
        
    for(auto iter = fll-> begin(); iter != fll-> end(); ++iter) {
        cout<<*iter<<'\n';
    }
    
}
