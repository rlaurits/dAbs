#include <iostream>
#include <cstdio>

struct Node{
  double data;
  int prev;
  int next;
};

int main(){

  FILE* f =fopen("LLtest.bin","w+");

  Node sentinel;
  sentinel.data=2.3;
  sentinel.prev=0; 
  sentinel.next=0;

  fwrite(&sentinel, sizeof(Node),1,f);
  int freelist = -1;

  fseek(f, sizeof(Node), SEEK_SET);
  fwrite(&freelist, sizeof(int), 1,f);

  int sz=0;
  fseek(f, sizeof(Node)+sizeof(int), SEEK_SET);
  fwrite(&sz , sizeof(int),1,f);

  
}
