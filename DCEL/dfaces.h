#include "dface.h"

using namespace std;
class dfaces
{
public:
	dfaces();
	~dfaces();

	/// head of the face list
	dface* head;

	/// tail of he face list
	dface* tail;

	/**
	 * Add a set of faces to the list.
	 * @param newFace : pointer to the face list that has to be inserted.
	*/
	void addToEdges(dface* newFace);

	/**
	 * Returns the length of the face list.
	*/
	int length();

	/**
	 * Remove the face from the face list
	 * @param face : face to be deleted.
	*/
	void removeFromList(dface* face);
};

dfaces::dfaces() : head(NULL)
{
}

dfaces::~dfaces()
{
}

void dfaces::addToEdges(dface* newFace) {
	if (head)
	{
		tail->next = newFace;
		// use d_itr if it is a set of subdivisions to insert all of them and set the tail accoringly.
		dface *d_itr = newFace;
		while (d_itr->next) d_itr = d_itr->next;
		tail = d_itr;
	}
	else {
		head = newFace;
		//first element in list is not set of subdivisions, thus no need for the extra steps used above.
		tail = newFace;
	}
}

int dfaces::length() {
	if (head) {
		dface* d_itr = head;
		int length = 1;
		while (d_itr->next) {
			d_itr = d_itr->next;
			length++;
		}
		return length - 1;
	}
	else return 0;
}

void dfaces::removeFromList(dface* face) {
	if (face == head) {
		head = head->next;
		return;
	}
	dface* d_itr = head;
	while (d_itr) {
		if (d_itr->next == face)
			break;
		d_itr = d_itr->next;
	}
	d_itr->next = d_itr->next->next;
	return;
}



