#include "DCELHalfEdge.h"
#include "DCELVertex.h"
#include "FaceList.h"


using namespace std;
class HalfEdgeList
{
public:
	HalfEdgeList(void);
	~HalfEdgeList(void);

	/// head of the Edge list
	DCELHalfEdge* head;

	/// tail of the Edge list
	DCELHalfEdge* tail;

	/// Total number of edges
	int globalEdgeCount;

	/**
	 * Add a new edge to list
	 * @param newEdge : The DCEL half edge to be added to the list
	*/
	void addToList(DCELHalfEdge* newEdge);

	// void removeFromList(DCELHalfEdge* edge);

	/**
	 * Adds the twin of an edge to the Edge list. Also sets the 
	 * next and origin parameters for the previous twin added to the list.
	 * @param edge : The edge whose twin has to be inserted.
	 * @param LaggingTwin : previous twin added to the Edge list.
	 * @return The twin added to list to be stored into LagingTwin.
	*/
	DCELHalfEdge* addTwinTo(DCELHalfEdge* edge, DCELHalfEdge* LaggingTwin);

	/**
	 * Add an edge between the given vertices and create 2 subdivisions out of the face.
	 * @param v1 : 1st vertex
	 * @param v2 : 2nd vertex
	 * @param face : the new edge is a diagonal of this face.
	 * @return the 2nd subdivision
	*/
	DCELFace* addEdgeBetween(DCELVertex* v1, DCELVertex* v2, DCELFace* face);

};

HalfEdgeList::HalfEdgeList(void) : globalEdgeCount(0), head(NULL), tail(NULL)
{
}

HalfEdgeList::~HalfEdgeList(void)
{
}

void HalfEdgeList::addToList(DCELHalfEdge* newEdge)
{
	newEdge->meta = ++globalEdgeCount;

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

DCELHalfEdge* HalfEdgeList::addTwinTo(DCELHalfEdge* edge, DCELHalfEdge* LaggingTwin) {
	DCELHalfEdge *twinEdge = new DCELHalfEdge();
	twinEdge->meta = ++globalEdgeCount;
	twinEdge->twin = edge;
	if (LaggingTwin) {
		LaggingTwin->origin = twinEdge->twin->origin;
		twinEdge->next = LaggingTwin;
	}
	edge->twin = twinEdge;
	return twinEdge;
}

// void HalfEdgeList::removeFromList(DCELHalfEdge* edge)
// {
// 	edge->getPrev()->next = edge->twin->next;
// 	edge->twin->getPrev()->next = edge->next;
// 	delete edge->twin;
// 	delete edge;
// }

DCELFace* HalfEdgeList::addEdgeBetween(DCELVertex* v1, DCELVertex* v2, DCELFace* face)
{
	// Get edge that goes to v1.
	DCELHalfEdge* walker = face->edge;
	while (1) {
		if (walker->next->origin == v1)
			break;
		walker = walker->next;
	}

	//new edge with v2 as origin
	DCELHalfEdge* halfEdge = new DCELHalfEdge();
	halfEdge->origin = v2;
	halfEdge->meta = ++globalEdgeCount;
	halfEdge->next = walker->next;
	
	// get edge that goes to v2
	DCELHalfEdge* twinWalker = face->edge;
	while (1) {
		if (twinWalker->next->origin == v2)
			break;
		twinWalker = twinWalker->next;
	}

	//twin of the new edge
	DCELHalfEdge* twinEdge = new DCELHalfEdge();
	twinEdge->origin = v1;
	twinEdge->meta = ++globalEdgeCount;
	twinEdge->next = twinWalker->next;
	
	// set next edges for the new polygon vertices
	walker->next = twinEdge;
	twinWalker->next = halfEdge;
	
	halfEdge->twin = twinEdge;
	twinEdge->twin = halfEdge;

	// create new face for 1st subdivision.
	DCELFace* firstHalf = new DCELFace();
	firstHalf->edge = halfEdge;
	walker = halfEdge;
	do {
		walker->face = firstHalf;
		walker = walker->next;
	} while(walker != halfEdge);

	// create new face for 2nd subdivision.
	DCELFace* secHalf = new DCELFace();
	secHalf->edge = twinEdge;
	twinEdge->face = secHalf;
	walker = twinEdge;
	do {
		walker->face = secHalf;
		walker = walker->next;
	} while(walker != twinEdge);

	secHalf->next = firstHalf;
	return secHalf;
}

