using namespace std;

class dvertex  
{
	public:
		dvertex();
		~dvertex();

		/// x coordinate of the vertex.
		double x;
		/// y coordinate of the vertex.
		double y;

		/// Half edge that has this vertex as the origin.
		dedge* edge;

		/**
		 * Gets the edge which is incident edge for a face.
		 * @param DCEL face
		 * @return DCEL edge
		*/
		dedge* getEdgeOnFace(dface* face);

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

		int type;
		int index;
		
		dvertex* next;
		dvertex* prev;
};

dvertex::dvertex(): x(0.0), y(0.0), edge(NULL), type(0), index(0), next(NULL), prev(NULL)
{
}
dvertex::~dvertex()
{

}


void dvertex::setCoords(double a, double b) {
	x = a;
	y = b;
}

void dvertex::print() {
	cout<<x<<" "<<y<<endl;
}


dedge* dvertex::getEdgeOnFace(dface *face)
{
	dedge *edgeWalker = edge;
	while (edgeWalker->face != face){
		edgeWalker = edgeWalker->twin->next;
	}
	return edgeWalker;
}
