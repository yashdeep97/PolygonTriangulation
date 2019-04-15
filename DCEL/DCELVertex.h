using namespace std;
class DCELVertex  
{
public:
	DCELVertex();
	~DCELVertex();

	double x;
	double y;
	DCELHalfEdge* edge;
	DCELHalfEdge* getEdgeTo(DCELVertex* v);
	DCELHalfEdge* getEdgeOnFace(DCELFace* face);
	void setCoords(double a, double b);
	void print();
	int type;
	int index;
	
	DCELVertex* next;
	DCELVertex* prev;
};

DCELVertex::DCELVertex(): x(0.0), y(0.0), edge(NULL), prev(NULL), next(NULL), type(0), index(0)
{
}
DCELVertex::~DCELVertex()
{

}

void DCELVertex::setCoords(double a, double b) {
	x = a;
	y = b;
}

void DCELVertex::print() {
	cout<<x<<" "<<y<<endl;
}

DCELHalfEdge* DCELVertex::getEdgeTo(DCELVertex* v)
{
	DCELHalfEdge* rval = NULL;

	if (edge) {
		if (edge->twin->origin == v) {
			rval = edge;
		} else {
			DCELHalfEdge* test = edge->twin->next;
			while (rval == NULL && test != edge) {
				if (test->twin->origin == v) {
					rval = test;
				} else {
					test = test->twin->next;
				}
			}
		}
	}
	return rval;
}

DCELHalfEdge* DCELVertex::getEdgeOnFace(DCELFace *face)
{
	DCELHalfEdge *edgeWalker = edge;
	while (edgeWalker->face != face) edgeWalker = edgeWalker->twin->next;
	return edgeWalker;
}