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

	/// Twin of the DCEL half edge
	DCELHalfEdge* twin;

	/// next DCEL half edge
	DCELHalfEdge* next;

	/// Face to the left of the edge
	DCELFace* face;

	/// origin of the half edge
	DCELVertex* origin;

	/// helper vertex used in the algorithm to convert polygon to y-monotone polygon
	DCELVertex* helper;

	/**
	 * Get previous edge.
	*/
	DCELHalfEdge* getPrev();
	
	/// unique ID of the half edge
	int meta;
};

DCELHalfEdge::DCELHalfEdge() :
twin(NULL), next(NULL), face(NULL), origin(NULL), meta(0), helper(NULL)
{
}

DCELHalfEdge::~DCELHalfEdge()
{

}

DCELHalfEdge* DCELHalfEdge::getPrev()
{
	DCELHalfEdge* rval = twin->next->twin;
	
	while (rval->next != this) {
		rval = rval->next->twin;
	}

	return rval;
}
