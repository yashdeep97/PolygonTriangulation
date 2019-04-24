#ifndef DCEL_ORIGIN_H
#define DCEL_ORIGIN_H

#include <iostream>
#include <bits/stdc++.h>
#include <typeinfo>
#include "HalfEdgeList.h"
#include "VertexList.h"
#include "../mainwindow.h"

using namespace std;


VertexList Vertices; //Head of linked-list containing Vertex Collation
HalfEdgeList Edges; //Head of linked-list containing Edge Collation
FaceList Faces; //Head of linked-list containing Face Collation


//! Extract Data from Input File
/*! getPolygon is the main extractor function that builds the collations.
 *	Vertices are expected to be received in an anticlockwise order.
 */
void getPolygon( vector<point> points) {
	double a, b;
	DCELVertex* firstVertex;
	// DCELVertex *walker = new DCELVertex();
	DCELHalfEdge *LaggingTwin = NULL;
	DCELFace *inner = new DCELFace();
	DCELFace *outer = new DCELFace();

	for(unsigned int i = 0; i < points.size(); i++)
	{
		a = points[i].x;
		b = points[i].y;
		DCELVertex *next = new DCELVertex();
		next->setCoords(a, b);
		DCELHalfEdge *edge = new DCELHalfEdge();
		edge->origin = next;
		edge->face = inner;
		inner->edge = edge;
		Edges.addToList(edge);
		// Lagginin twin is the previous twin added to the edge list.
		LaggingTwin = Edges.addTwinTo(edge, LaggingTwin);
		LaggingTwin->face = outer;
		outer->edge = LaggingTwin;
		outer->bordered = false;
		next->edge = edge;
		if (!Vertices.length) firstVertex = next;
		Vertices.addToList(next);
	}
	Faces.addToList(outer);
	Faces.addToList(inner);

	Edges.tail->next = Edges.head;
	Edges.head->twin->next = Edges.tail->twin;
	Edges.tail->twin->origin = firstVertex;
}

void printPolygon() {
	cout << "OFF" << endl;
	cout << Vertices.length << " " << Faces.length() << " 0" << endl;
	Vertices.echo();
	DCELFace *walker = Faces.head;
	DCELHalfEdge *edgeWalker;
	while (walker) {
		if (walker->bordered) {
			edgeWalker = walker->edge;
			cout << walker->boundaryLength() << " ";
			do {
				cout << edgeWalker->origin->index << " ";
				edgeWalker = edgeWalker->next;
			} while (edgeWalker != walker->edge);
			// cout << (double)rand() / RAND_MAX << " " << (double)rand() / RAND_MAX << " " << (double)rand() / RAND_MAX;
			cout << endl;
		}
		walker = walker->next;
	}
}

/**
 * Find the common face between 2 vertices by iterating over the edges at each vertex.
*/
DCELFace* getFaceCommonTo(DCELVertex* v1, DCELVertex* v2) {
	DCELFace* face = NULL;
	DCELHalfEdge* walker = v1->edge;
	DCELHalfEdge* twinWalker = v2->edge;
	do {
		do {
			if (walker->face == twinWalker->face && walker->face->bordered){
				face = walker->face;
				break;
			}
			twinWalker = twinWalker->twin->next;
		} while (twinWalker != v2->edge);
		walker = walker->twin->next;
	} while (walker != v1->edge && !face);
	return face;
}

/**
 * Check if an edge exists between the 2 vertices.
*/
bool checkEdge(DCELVertex* v1, DCELVertex* v2) {
	DCELHalfEdge* walker = v1->edge;
	do {
		if (walker->next->origin == v2) {
			return true;
		}
		walker = walker->twin->next;
	} while (walker != v1->edge);
	return false;
}

/**
 * Add edge between the given vertices and divide the face.
 * @param v1 : 1st vertex
 * @param v2 : 2nd vertex
*/
void insertDiagonal(DCELVertex* v1, DCELVertex* v2) {
	if (v1 == v2) return;
	if (checkEdge(v1,v2)) return;

	DCELFace* face = getFaceCommonTo(v1, v2);
	if(face) {
		DCELFace* newSubdivision = Edges.addEdgeBetween(v1, v2, face);
		Faces.addToList(newSubdivision);
		Faces.removeFromList(face);
		delete face;
	}
}
#endif