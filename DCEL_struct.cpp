#include<bits/stdc++.h>
using namespace std;

struct halfEdge;

struct point{
    double x;
    double y;
};

struct vertex {
    point coordinates;
    struct halfEdge *incidentEdge; 
};

struct face {
    struct halfEdge *startEdge;  
};

struct halfEdge {
    struct halfEdge *prev;  
    struct halfEdge *next;  
    struct halfEdge *twin;  
    struct vertex *origin;     
    struct face *incidentFace;      
};

int main()
{
  return 0;
}
