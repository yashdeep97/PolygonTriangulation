#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class DCELFace;
class DCELVertex;

class DCELHalfEdge  
{
public:
	DCELHalfEdge();
	~DCELHalfEdge();

	DCELHalfEdge* twin;
	DCELHalfEdge* next;
	DCELFace* face;
	DCELVertex* origin;
	DCELVertex* helper;
	DCELHalfEdge* getPrev();
	int meta;
};

DCELHalfEdge::DCELHalfEdge() :
twin(NULL), next(NULL), face(NULL), origin(NULL), meta(0), helper(NULL)
{
}

DCELHalfEdge::~DCELHalfEdge()
{

}
//! Half Edges
/*!
 * get Previus Vertices
 * */
DCELHalfEdge* DCELHalfEdge::getPrev()
{
	DCELHalfEdge* rval = twin->next->twin;
	
	while (rval->next != this) {
		rval = rval->next->twin;
	}

	return rval;
}
