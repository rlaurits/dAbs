
#include <iostream>
#include <cstdio>
#include "HashMap.h"
#include <string>
#include <cstdlib>
using namespace std;

int hashFunc(const value_type input, const HashMap<int> hm) {
    void srand(input.first);
    int loc = rand() % hm.size()
    return loc;
}

int main() {
    HashMap<int, string, std::function<int(key_type)>> *hm (hashFunc);


}    
