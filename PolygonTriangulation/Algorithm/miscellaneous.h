#ifndef DCEL_ORIGIN_H
#define DCEL_ORIGIN_H

#include <unistd.h>
#include <set>
#include <typeinfo>
#include "dedges.h"
#include "dvertices.h"
#include "../mainwindow.h"

#define COLLINEAR 1 
#define CLOCKWISE 2
#define ANTICLOCKWISE 3

using namespace std;


dvertices Vertices; //Head of linked-list containing Vertex Collation
dedges Edges; //Head of linked-list containing Edge Collation
dfaces Faces; //Head of linked-list containing Face Collation


//! Extract Data from Input File
/*! getPolygon is the main extractor function that builds the collations.
 *	Vertices are expected to be received in an anticlockwise order.
 */
void getPolygon(vector<point> points) {
    sleep(1);
    double a, b;
	dvertex* firstVertex;
	// dvertex *d_itr = new dvertex();
	dedge *LaggingTwin = NULL;
	dface *inner = new dface();
	dface *outer = new dface();
    cout<<"Number of points: "<<points.size()<<endl;
    for(unsigned int i = 0; i < points.size(); i++)
    {
        a = points[i].x;
        b = points[i].y;
        dvertex *next = new dvertex();
        next->setCoords(a, b);
        dedge *edge = new dedge();
        edge->origin = next;
        edge->face = inner;
        inner->edge = edge;
        Edges.addToEdges(edge);
        // Lagginin twin is the previous twin added to the edge list.
        LaggingTwin = Edges.addTwin(edge, LaggingTwin);
        LaggingTwin->face = outer;
        outer->edge = LaggingTwin;
        outer->bordered = false;
        next->edge = edge;
        if (!Vertices.length) firstVertex = next;
        Vertices.addToEdges(next);
    }

    Faces.addToEdges(outer);
    Faces.addToEdges(inner);
	
cout<<"Numver of egdes: "<<Edges.num_edges<<endl;
    Edges.tail->next = Edges.head;
    Edges.head->twin->next = Edges.tail->twin;
    Edges.tail->twin->origin = firstVertex;
}


/**
 * Find the common face between 2 vertices by iterating over the edges at each vertex.
*/
dface* commonFace(dvertex* v1, dvertex* v2) {
	dface* face = NULL;
	dedge* d_itr = v1->edge;
	dedge* twinWalker = v2->edge;
	do {
		do {
			if (d_itr->face == twinWalker->face && d_itr->face->bordered)
			{face = d_itr->face; break;}
			twinWalker = twinWalker->twin->next;
		} while (twinWalker != v2->edge);
		d_itr = d_itr->twin->next;
	} while (d_itr != v1->edge && !face);
	return face;
}

/**
 * Check if an edge exists between the 2 vertices.
*/
bool checkEdge(dvertex* v1, dvertex* v2) {
	dedge* d_itr = v1->edge;
	do {
		if (d_itr->next->origin == v2) {
			return true;
		}
		d_itr = d_itr->twin->next;
	} while (d_itr != v1->edge);
	return false;
}

/**
 * Add edge between the given vertices and divide the face.
 * @param v1 : 1st vertex
 * @param v2 : 2nd vertex
*/
void insertDiagonal(dvertex* v1, dvertex* v2) {
	if (v1 == v2) return;
	if (checkEdge(v1,v2)) return;

	dface* face = commonFace(v1, v2);
	if(face) {
		dface* newSubdivision = Edges.addEdgeBetween(v1, v2, face);
		Faces.addToEdges(newSubdivision);
		Faces.removeFromList(face);
		delete face;
	}
}

  /*! This function is used to calculate orientation of 3 points namely clockwise, anticlockwise and collinear.
  * The idea here is to to get the difference between slopes of 2 lines by assuming a particular direction as a result
  * the result obtained determines the direction of turn of the three points.
  */
  int orientation(dvertex* a, dvertex* b, dvertex* c) {
    double dif;
    dif = (b->y - a->y) * (c->x - b->x) - (b->x - a->x) * (c->y - b->y);
    if (dif == 0) {
      return COLLINEAR;
    } else if (dif > 0 ) {
      return CLOCKWISE;
    } else {
      return ANTICLOCKWISE;
    }
  }

/**
 * Draws an edge in the GUI.
 * @param v1 : 1st vertex
 * @param v2 : 2nd vertex
 * @param w : GUI object
*/
void addLine(dvertex *v1, dvertex *v2, MainWindow *w){
    vector<point> line;
    point p1;
    p1.x = v1->x;
    p1.y = v1->y;
    point p2;
    p2.x = v2->x;
    p2.y = v2->y;
    line.push_back(p1);
    line.push_back(p2);
    w->drawLines(line);
}
#endif
