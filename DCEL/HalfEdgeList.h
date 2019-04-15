#include "DCELHalfEdge.h"
#include "DCELVertex.h"
#include "FaceList.h"


using namespace std;
class HalfEdgeList
{
public:
	HalfEdgeList(void);
	~HalfEdgeList(void);

	DCELHalfEdge* head;
	DCELHalfEdge* tail;
	int globalEdgeCount;

	void addToList(DCELHalfEdge* newEdge);
	void removeFromList(DCELHalfEdge* edge);
	DCELHalfEdge* addTwinTo(DCELHalfEdge* edge, DCELHalfEdge* LaggingTwin);
	DCELFace* addEdgeBetween(DCELVertex* v1, DCELVertex* v2, DCELFace* face);
protected:
	bool status;
};

HalfEdgeList::HalfEdgeList(void) : globalEdgeCount(0), head(NULL), tail(NULL), status(false)
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
//! GETTTING THE HALF EDGE LIST
/*!
 * Adding a twin
 * */
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

void HalfEdgeList::removeFromList(DCELHalfEdge* edge)
{
	edge->getPrev()->next = edge->twin->next;
	edge->twin->getPrev()->next = edge->next;
	delete edge->twin;
	delete edge;
}
//! GETTTING THE HALF EDGE LIST
/*!
 * Hepler For Handling End Vertex. Walk around the path and add vertices that are in the Hal Edge Vetices List
 *
 * */
DCELFace* HalfEdgeList::addEdgeBetween(DCELVertex* v1, DCELVertex* v2, DCELFace* face)
{
	DCELHalfEdge* walker = face->edge;
	while (1) {
		if (walker->next->origin == v1)
			break;
		walker = walker->next;
	}

	DCELHalfEdge* halfEdge = new DCELHalfEdge();
	halfEdge->origin = v2;
	halfEdge->meta = ++globalEdgeCount;
	halfEdge->next = walker->next;
	
	DCELHalfEdge* twinWalker = face->edge;
	while (1) {
		if (twinWalker->next->origin == v2)
			break;
		twinWalker = twinWalker->next;
	}

	DCELHalfEdge* twinEdge = new DCELHalfEdge();
	twinEdge->origin = v1;
	twinEdge->meta = ++globalEdgeCount;
	twinEdge->next = twinWalker->next;
	
	walker->next = twinEdge;
	twinWalker->next = halfEdge;
	
	halfEdge->twin = twinEdge;
	twinEdge->twin = halfEdge;


	DCELFace* firstHalf = new DCELFace();
	firstHalf->edge = halfEdge;
	walker = halfEdge;
	do {
		walker->face = firstHalf;
		walker = walker->next;
	} while(walker != halfEdge);

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

