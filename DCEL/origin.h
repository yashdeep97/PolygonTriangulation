#ifndef DCEL_ORIGIN_H
#define DCEL_ORIGIN_H

#include <bits/stdc++.h>
#include <typeinfo>
#include "dedges.h"
#include "dvertices.h"

using namespace std;


dvertices Vertices; //Head of linked-list containing Vertex Collation
dedges Edges; //Head of linked-list containing Edge Collation
dfaces Faces; //Head of linked-list containing Face Collation


//! Extract Data from Input File
/*! getPolygon is the main extractor function that builds the collations.
 *	Vertices are expected to be received in an anticlockwise order.
 */
void getPolygon(char const *filename) {
	double a, b, c;
	dvertex* firstVertex;
	// dvertex *d_itr = new dvertex();
	dedge *LaggingTwin = NULL;
	dface *inner = new dface();
	dface *outer = new dface();
	ifstream in_file;
	in_file.open(filename);
	while (in_file.is_open()) {
		int n, i = 0;
		in_file >> n;
		while (in_file >> a >> b >> c) 
		{
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

		in_file.close();
	}
	

	Edges.tail->next = Edges.head;
	Edges.head->twin->next = Edges.tail->twin;
	Edges.tail->twin->origin = firstVertex;
}

void printPolygon() {
	cout << Vertices.length << " " << Faces.length() << " 0" << endl;
	Vertices.echo();
	dface *d_itr = Faces.head;
	dedge *edge_itr;
	while (d_itr) {
		if (d_itr->bordered) {
			edge_itr = d_itr->edge;
			cout << d_itr->boundaryLength() << " ";
			do {
				cout << edge_itr->origin->index << " ";
				edge_itr = edge_itr->next;
			} while (edge_itr != d_itr->edge);
			cout << endl;
		}
		d_itr = d_itr->next;
	}
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

/**
 * Draws an edge in the GUI.
 * @param v1 : 1st vertex
 * @param v2 : 2nd vertex
 * @param w : GUI object

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
*/
#endif
