#ifndef DEDGES_H
#define DEDGES_H

#include "dedge.h"
#include "dvertex.h"
#include "dfaces.h"


using namespace std;

/// This class defines a linked list to store all the edges.
class dedges
{
public:
	dedges(void);
	~dedges(void);

	/// head of the Edge list
	dedge* head;

	/// tail of the Edge list
	dedge* tail;

	/// Total number of edges
	int num_edges;

	/**
	 * Add a new edge to list
	 * @param newEdge : The DCEL half edge to be added to the list
	*/
	void addToEdges(dedge* newEdge);

	// void removeFromList(dedge* edge);

	/**
	 * Adds the twin of an edge to the Edge list. Also sets the 
	 * next and origin parameters for the previous twin added to the list.
	 * @param edge : The edge whose twin has to be inserted.
	 * @param LaggingTwin : previous twin added to the Edge list.
	 * @return The twin added to list to be stored into LagingTwin.
	*/
	dedge* addTwin(dedge* edge, dedge* LaggingTwin);

	/**
	 * Add an edge between the given vertices and create 2 subdivisions out of the face.
	 * @param v1 : 1st vertex
	 * @param v2 : 2nd vertex
	 * @param face : the new edge is a diagonal of this face.
	 * @return the 2nd subdivision
	*/
	dface* addEdgeBetween(dvertex* v1, dvertex* v2, dface* face);

};

dedges::dedges(void) : head(NULL), tail(NULL), num_edges(0)
{
}

dedges::~dedges(void)
{
}

void dedges::addToEdges(dedge* newEdge)
{
	newEdge->ID = ++num_edges;

	if (head)
	{
		tail->next = newEdge;
		tail = newEdge;
	}
	else {
		head = newEdge;
		tail = newEdge;
	}
}

dedge* dedges::addTwin(dedge* edge, dedge* LaggingTwin) {
	dedge *twinEdge = new dedge();
	twinEdge->ID = ++num_edges;
	twinEdge->twin = edge;
	if (LaggingTwin) {
		LaggingTwin->origin = twinEdge->twin->origin;
		twinEdge->next = LaggingTwin;
	}
	edge->twin = twinEdge;
	return twinEdge;
}

dface* dedges::addEdgeBetween(dvertex* v1, dvertex* v2, dface* face)
{
	// Get edge that goes to v1.
	dedge* d_itr = face->edge;
	while (1) {
		if (d_itr->next->origin == v1)
			break;
		d_itr = d_itr->next;
	}

	//new edge with v2 as origin
	dedge* halfEdge = new dedge();
	halfEdge->origin = v2;
	halfEdge->ID = ++num_edges;
	halfEdge->next = d_itr->next;
	
	// get edge that goes to v2
	dedge* twinWalker = face->edge;
	while (1) {
		if (twinWalker->next->origin == v2)
			break;
		twinWalker = twinWalker->next;
	}

	//twin of the new edge
	dedge* twinEdge = new dedge();
	twinEdge->origin = v1;
	twinEdge->ID = ++num_edges;
	twinEdge->next = twinWalker->next;
	
	// set next edges for the new polygon vertices
	d_itr->next = twinEdge;
	twinWalker->next = halfEdge;
	
	halfEdge->twin = twinEdge;
	twinEdge->twin = halfEdge;

	// create new face for 1st subdivision.
	dface* firstHalf = new dface();
	firstHalf->edge = halfEdge;
	d_itr = halfEdge;
	do {
		d_itr->face = firstHalf;
		d_itr = d_itr->next;
	} while(d_itr != halfEdge);

	// create new face for 2nd subdivision.
	dface* secHalf = new dface();
	secHalf->edge = twinEdge;
	twinEdge->face = secHalf;
	d_itr = twinEdge;
	do {
		d_itr->face = secHalf;
		d_itr = d_itr->next;
	} while(d_itr != twinEdge);

	secHalf->next = firstHalf;
	return secHalf;
}

#endif