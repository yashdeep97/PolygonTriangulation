#ifndef DEDGE_H
#define DEDGE_H

class dface;
class dvertex;

/// Each object of this class represents a DCEL edge.
class dedge  
{
public:
	dedge();
	~dedge();

	/// Twin of the DCEL half edge
	dedge* twin;

	/// next DCEL half edge
	dedge* next;

	/// Face to the left of the edge
	dface* face;

	/// origin of the half edge
	dvertex* origin;

	/// helper vertex used in the algorithm to convert polygon to y-monotone polygon
	dvertex* helper;

	/**
	 * Get previous edge.
	*/
	dedge* getPrev();
	
	/// unique ID of the half edge
	int ID;
};

dedge::dedge() : twin(NULL), next(NULL), face(NULL), origin(NULL), helper(NULL),  ID(0)
{
}

dedge::~dedge()
{

}

dedge* dedge::getPrev()
{
	dedge* rval = twin->next->twin;
	
	while (rval->next != this) {
		rval = rval->next->twin;
	}

	return rval;
}

#endif