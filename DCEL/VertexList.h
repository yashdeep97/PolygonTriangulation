#include <iostream>
using namespace std;
class VertexList
{
public:
	VertexList(void);
	~VertexList(void);

	DCELVertex* head;
	DCELVertex* tail;

	void addToList(DCELVertex* newVertex);
	int length;
	void removeFromList(DCELVertex* vertex);
	void echo();
};

VertexList::VertexList(void) : head(NULL), tail(NULL), length(0)
{
}

VertexList::~VertexList(void)
{
}

void VertexList::echo() {
	DCELVertex* walker = head;
	int i = 0;
	while (1) {
		walker->index = i++;
		cout << walker->x << " " << walker->y << " 0" << endl;
		if (walker->next)
			walker = walker->next;
		else break;
	}
}

void VertexList::addToList(DCELVertex* newVertex)
{
	length++;
	if ( head ) {
		if ((head->y < newVertex->y) || (head->y == newVertex->y && head->x > newVertex->x)) {
			newVertex->next = head;
			head = newVertex;
			return;
		}
		DCELVertex* walker = head;
		while (walker->next) {
			if ((walker->next->y < newVertex->y) || (walker->next->y == newVertex->y && walker->next->x > newVertex->x)) break;
			walker = walker->next;
		}
		newVertex->next = walker->next;
		walker->next = newVertex;
	}
	else {
		head = newVertex;
		tail = newVertex;
	}
}

void VertexList::removeFromList(DCELVertex* vertex)
{
	length--;
	if (head) {
		DCELVertex* walker = head;
		if (walker == vertex) {
			head = walker->next;
			delete walker;
		}
		while (walker->next != vertex && walker->next != NULL) {
			walker = walker->next;
		}
		if (walker->next = vertex) {
			walker->next = vertex->next;
			delete vertex;
		}
	}
}
