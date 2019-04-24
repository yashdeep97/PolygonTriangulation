#include <iostream>
using namespace std;
class dvertices
{
public:
	dvertices(void);
	~dvertices(void);

	/// Head of the Vertex list
	dvertex* head;

	/// Tail of the Vertex list
	dvertex* tail;

	/**
	 * Add a vertex to the vertex list at the correct position.
	 * (List is sorted according to the y-coordiante)
	 * @param newVertex : the pointer to the DCEL vertex that needs to be added to the list.
	*/
	void addToEdges(dvertex* newVertex);

	/// Length of the vertex linked list
	int length;

	// /**
	//  * Delete a vertex from the vertex list.
	//  * @param vertex : the pointer to the vertex that must be deleted from the list.
	// */
	// void removeFromList(dvertex* vertex);

	/**
	 * Print all the points in the vertex list.
	*/
	void echo();
};

dvertices::dvertices(void) : head(NULL), tail(NULL), length(0)
{
}

dvertices::~dvertices(void)
{
}

void dvertices::echo() {
	dvertex* d_itr = head;
	int i = 0;
	while (1) {
		d_itr->index = i++;
		cout << d_itr->x << " " << d_itr->y << " 0" << endl;
		if (d_itr->next)
			d_itr = d_itr->next;
		else break;
	}
}

void dvertices::addToEdges(dvertex* newVertex)
{
	length++;
	if ( head ) {
		if ((head->y < newVertex->y) || (head->y == newVertex->y && head->x > newVertex->x)) {
			newVertex->next = head;
			head = newVertex;
			return;
		}
		dvertex* d_itr = head;
		while (d_itr->next) {
			if ((d_itr->next->y < newVertex->y) || (d_itr->next->y == newVertex->y && d_itr->next->x > newVertex->x)) break;
			d_itr = d_itr->next;
		}
		newVertex->next = d_itr->next;
		d_itr->next = newVertex;
	}
	else {
		head = newVertex;
		tail = newVertex;
	}
}

// void dvertices::removeFromList(dvertex* vertex)
// {
// 	length--;
// 	if (head) {
// 		dvertex* d_itr = head;
// 		if (d_itr == vertex) {
// 			head = d_itr->next;
// 			delete d_itr;
// 		}
// 		while (d_itr->next != vertex && d_itr->next != NULL) {
// 			d_itr = d_itr->next;
// 		}
// 		if (d_itr->next = vertex) {
// 			d_itr->next = vertex->next;
// 			delete vertex;
// 		}
// 	}
// }
