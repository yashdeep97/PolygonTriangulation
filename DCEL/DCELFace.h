class DCELFace
{
public:
	DCELFace();
	~DCELFace();

	DCELHalfEdge* edge;
	bool bordered;
	DCELFace* next;
	int boundaryLength();
	vector<pair<DCELVertex *, int> > sortedVertices();
};

DCELFace::DCELFace() : edge(NULL), next(NULL), bordered(true)
{
}

DCELFace::~DCELFace() {

}

int DCELFace::boundaryLength() {
	int length = 0;
	DCELHalfEdge* walker = edge;
	do {
		walker = walker->next;
		length++;
	} while (walker != edge);
	return length;
}

vector<pair<DCELVertex *, int> > DCELFace::sortedVertices() {
	vector<pair<DCELVertex*, int> > list;
	DCELVertex* highest = edge->origin;
	DCELHalfEdge* walker = edge;
	DCELHalfEdge *left, *right;
	do {	
		if (walker->origin->y > highest->y || (walker->origin->y == highest->y && walker->origin->x < highest->x)) {
			highest = walker->origin;
		}
		walker = walker->next;	
	} while (walker != edge);
	
	list.push_back(make_pair(highest,0));
	left = highest->getEdgeOnFace(this)->next;
	right = highest->getEdgeOnFace(this)->getPrev();
	do {
		if(left->origin->y > right->origin->y || (left->origin->y == right->origin->y && left->origin->x < right->origin->x)) {
			list.push_back(make_pair(left->origin, -1));
			left = left->next;
		}
		else {
			list.push_back(make_pair(right->origin, 1));
			right = right->getPrev();
		}
	}
	while(left != right->next );
	return list;
}