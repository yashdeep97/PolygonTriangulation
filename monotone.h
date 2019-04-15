#include <iostream>
#include "origin.h"
using namespace std;
#define REGULAR_VERTEX 0
#define START_VERTEX 1
#define END_VERTEX 2
#define MERGE_VERTEX 3
#define SPLIT_VERTEX 4
#define COLLINEAR 1 /*!< Macro defined for identifying 3 collinear points */
#define CLOCKWISE 2 /*!< Macro defined for identifying 3 points that rotate clockwise */
#define ANTICLOCKWISE 3 /*!< Macro defined for identifying 3 points that rotate anticlockwise */
class func {
public:
  bool operator() (DCELHalfEdge* e1, DCELHalfEdge* e2) {
    return e1->origin->y < e2->origin->y;
  }
};
set<DCELHalfEdge *, func>tree;

int vlen;
//! Orientation
/*! This function is used to calculate orientation of 3 points namely clockwise, anticlockwise and collinear.
 * The idea here is to to get the difference between slopes of 2 lines by assuming a particular direction as a result
 * the result obtained determines the direction of turn of the three points.
 */
int orientation(DCELVertex* a, DCELVertex* b, DCELVertex* c) {
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
//! Bool Check Below
/*!
 * Check the location of the two DCEL Vertices
 * */
bool below(DCELVertex* v1, DCELVertex* v2) {
  if (v1->y != v2->y)
    return v1->y > v2->y;
  else
    return v1->x < v2->x;
}
bool left_edgeto_vertex(const DCELHalfEdge* e1, const DCELHalfEdge* e2) {
  return (e1->origin->y > e2->origin->y) && (e1->origin->x < e2->origin->x);
}

//! form_vertex_type
/*!
 * Check whether START_VERTEX, SPLIT_VERTEX, MERGE_VERTEX, REGULAR_VERTEX
 * */
void form_vertex_type() {
  DCELVertex *v = Vertices.head;
  vlen = Vertices.length;
  for (int i = 0; i < vlen; i++) {
    if (below(v, v->edge->twin->origin) && below(v, v->edge->getPrev()->origin)) {
      if (orientation(v->edge->twin->origin, v, v->edge->getPrev()->origin) == CLOCKWISE)
        v->type = START_VERTEX;
      else
        v->type = SPLIT_VERTEX;
    }
    else if (below(v->edge->twin->origin, v) && below(v->edge->getPrev()->origin, v)) {
      if (orientation(v->edge->twin->origin, v, v->edge->getPrev()->origin) == CLOCKWISE)
        v->type = END_VERTEX;
      else 
        v->type = MERGE_VERTEX;
    }
    else 
      v->type = REGULAR_VERTEX;

    v = v->next;
  }
}
//! form_vertex_type
/*!
 * Hepler For Handling STart Vertex
 * */
void HANDLE_START_VERTEX(DCELVertex *v) {
  tree.insert(v->edge);
  v->edge->helper = v;
}
//! VERTEX HANDLING
/*!
 * Hepler For Handling End Vertex
 * */
void HANDLE_END_VERTEX(DCELVertex *v) {
  if (v->edge->getPrev()->helper)
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, v->edge->getPrev()->helper);
    }
  tree.erase(v->edge->getPrev());
}

void HANDLE_SPLIT_VERTEX(DCELVertex *v) {
  set<DCELHalfEdge *, func>::iterator it;
  it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
  if (it != tree.begin()) {
    it--;
  }
  DCELHalfEdge *s = *it;
  insertDiagonal(v, s->helper);
  s->helper = v;
  tree.insert(v->edge);
  v->edge->helper = v;
}

void HANDLE_MERGE_VERTEX(DCELVertex *v) {
  if (v->edge->getPrev()->helper)
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, v->edge->getPrev()->helper);
    }
  tree.erase(v->edge->getPrev());
  set<DCELHalfEdge *, func>::iterator it;
  it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
  if (it != tree.begin()) {
    it--;
  }
  DCELHalfEdge *s = *it;
  if (s->helper)
    if (s->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, s->helper);
    }
  s->helper = v;
}

void HANDLE_REGULAR_VERTEX(DCELVertex *v) {
  if (below(v, v->edge->twin->origin)) {
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, v->edge->getPrev()->helper);
    }
    tree.erase(v->edge->getPrev());
    tree.insert(v->edge);
    v->edge->helper = v;
  }
  else {
    set<DCELHalfEdge *, func>::iterator it;
    it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
    if (it != tree.begin()) {
      it--;
    }
    DCELHalfEdge *s = *it;
    if (s->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, s->helper);
    }
    s->helper = v;
  }
}
//! VERTEX HANDLING
/*!
 * Splitting into montone pieces in the polygon
 *
 * */
void split_into_monotone() {
  form_vertex_type();
  DCELVertex *v = Vertices.head;
  int i = 0;
  while (v) {
    if (v->type == START_VERTEX) HANDLE_START_VERTEX(v);
    else if (v->type == SPLIT_VERTEX) HANDLE_SPLIT_VERTEX(v);
    else if (v->type == END_VERTEX) HANDLE_END_VERTEX(v);
    else if (v->type == MERGE_VERTEX) HANDLE_MERGE_VERTEX(v);
    else if (v->type == REGULAR_VERTEX) HANDLE_REGULAR_VERTEX(v);
    v = v->next;
  }
}