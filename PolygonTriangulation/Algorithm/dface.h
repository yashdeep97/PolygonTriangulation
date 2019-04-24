class dface
{
	public:
		dface();
		~dface();

		/// Arbitrary half edge used as the starting point for the face.
		dedge* edge;

		/// Whether the border for the face exists.
		bool bordered;

		/// Next face in the list.
		dface* next;

		/**
		 * Gives the number of edges that form the boundary.
		 * @return Number of edges
		*/
		int boundaryLength();

		/**
		 * Splits the polygon into left and right parts.
		 * Sorts the vertices according to their y-coordinates.
		 * The integer in the pair represents whether the vertex 
		 * is the highest(0), lies in the left part(-1) or the 
		 * right part(1).
		 * @return the vector of sorted vertices.
		*/
		vector<pair<dvertex *, int> > sortedVertices();
};

dface::dface() : edge(NULL), bordered(true), next(NULL)
{
}

dface::~dface() {

}

int dface::boundaryLength() {
	int length = 0;
	dedge* d_itr = edge;
	do {
		d_itr = d_itr->next;
		length++;
	} while (d_itr != edge);
	return length;
}

vector<pair<dvertex *, int> > dface::sortedVertices() {
	vector<pair<dvertex*, int> > list;
	dvertex* highest = edge->origin;
	dedge* d_itr = edge;
	dedge *left, *right;

	do {	
		if (d_itr->origin->y > highest->y || (d_itr->origin->y == highest->y && d_itr->origin->x < highest->x)) {
			highest = d_itr->origin;
		}
		d_itr = d_itr->next;	
	} while (d_itr != edge);
	
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
