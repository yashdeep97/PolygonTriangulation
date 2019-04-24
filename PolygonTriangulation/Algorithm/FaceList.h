#include "DCELFace.h"

using namespace std;
class FaceList
{
public:
	FaceList();
	~FaceList();

	/// head of the face list
	DCELFace* head;

	/// tail of he face list
	DCELFace* tail;

	/**
	 * Add a set of faces to the list.
	 * @param newFace : pointer to the face list that has to be inserted.
	*/
	void addToList(DCELFace* newFace);

	/**
	 * Returns the length of the face list.
	*/
	int length();

	/**
	 * Remove the face from the face list
	 * @param face : face to be deleted.
	*/
	void removeFromList(DCELFace* face);
};

FaceList::FaceList() : head(NULL)
{
}

FaceList::~FaceList()
{
}

void FaceList::addToList(DCELFace* newFace) {
	if (head)
	{
		tail->next = newFace;
		// use walker if it is a set of subdivisions to insert all of them and set the tail accoringly.
		DCELFace *walker = newFace;
		while (walker->next) walker = walker->next;
		tail = walker;
	}
	else {
		head = newFace;
		//first element in list is not set of subdivisions, thus no need for the extra steps used above.
		tail = newFace;
	}
}

int FaceList::length() {
	if (head) {
		DCELFace* walker = head;
		int length = 1;
		while (walker->next) {
			walker = walker->next;
			length++;
		}
		return length - 1;
	}
	else return 0;
}

void FaceList::removeFromList(DCELFace* face) {
	if (face == head) {
		head = head->next;
		return;
	}
	DCELFace* walker = head;
	while (walker) {
		if (walker->next == face)
			break;
		walker = walker->next;
	}
	walker->next = walker->next->next;
	return;
}



