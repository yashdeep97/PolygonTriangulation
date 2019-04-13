#include<bits/stdc++.h>
using namespace std;

struct half_edge;

struct vertex {
    pair<int,int> cord;
    struct half_edge *rep; 
};

struct face {
    struct half_edge *rep;  
};

struct half_edge {
    struct half_edge *prev;  
    struct half_edge *next;  
    struct half_edge *twin;  
    struct vertex *tail;     
    struct face *left;      
};

int main()
{
  return 0;
}
