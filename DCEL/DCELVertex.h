using namespace std;

class DCELVertex  
{
	public:
		DCELVertex();
		~DCELVertex();

		/// x coordinate of the vertex.
		double x;
		/// y coordinate of the vertex.
		double y;

		/// Half edge that has this vertex as the origin.
		DCELHalfEdge* edge;

		/**
		 * Gets the edge which is incident edge for a face.
		 * @param DCEL face
		 * @return DCEL edge
		*/
		DCELHalfEdge* getEdgeOnFace(DCELFace* face);

		/**
		 * Set coordinates for the vertex of DCEL.
		 * @param a : x coordinate of vertex 
		 * @param b : y coordinate of vertex
		 */
		void setCoords(double a, double b);

		/**
		 * Prints coordinates of the vertex.
		*/
		void print();

		/// type of the vertex: start, end, split, etc.
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


DCELHalfEdge* DCELVertex::getEdgeOnFace(DCELFace *face)
{
	DCELHalfEdge *edgeWalker = edge;
	while (edgeWalker->face != face){
		edgeWalker = edgeWalker->twin->next;
	}
	return edgeWalker;
}