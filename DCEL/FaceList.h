#include "DCELFace.h"

using namespace std;
class FaceList
{
public:
	FaceList();
	~FaceList();
	DCELFace* head;
	DCELFace* tail;

	void addToList(DCELFace* newFace);
	int length();
	void removeFromList(DCELFace* face);
};

FaceList::FaceList() : head(NULL)
{
}

FaceList::~FaceList()
{
}
//! CREATE FACES
/*!
 * Add to the list
 * */
void FaceList::addToList(DCELFace* newFace) {
	if (head)
	{
		tail->next = newFace;
		DCELFace *walker = newFace;
		while (walker->next) walker = walker->next;
		tail = walker;
	}
	else {
		head = newFace;
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
//! CREATE FACES
/*!
 * Remove From the list
 * */
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
}



