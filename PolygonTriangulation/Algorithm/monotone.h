#ifndef MONOTONE_H
#define MONOTONE_H

#include <iostream>
#include "miscellaneous.h"

using namespace std;

#define REGULAR_VERTEX 0
#define START_VERTEX 1
#define END_VERTEX 2
#define MERGE_VERTEX 3
#define SPLIT_VERTEX 4
#define COLLINEAR 1 
#define CLOCKWISE 2
#define ANTICLOCKWISE 3

/// Global MainWindow object
MainWindow *window;

/**
 * Custom comparator function to arrange vertices in the priority queue.
*/
class func {
public:
  bool operator() (dedge* e1, dedge* e2) {
    if(e1->origin->y == e2->origin->y){
      return e1->origin->x > e2->origin->x;
    }
    return e1->origin->y < e2->origin->y;
  }
};

/// priority queue to store all the vertices.
set<dedge *, func>tree;

int vlen;

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
 * Check the relative position of two vertices.
 * (ie. if one is below another) 
 */
bool below(dvertex* v1, dvertex* v2) {
  if (v1->y != v2->y)
    return v1->y > v2->y;
  else
    return v1->x < v2->x;
}
bool left_edgeto_vertex(const dedge* e1, const dedge* e2) {
  return (e1->origin->y > e2->origin->y) && (e1->origin->x < e2->origin->x);
}

/**
 * Check whether the vertex is a START_VERTEX or a END_VERTEX, 
 * or a SPLIT_VERTEX or a MERGE_VERTEX or a REGULAR_VERTEX.
 */
void form_vertex_type() {
  dvertex *v = Vertices.head;
  vlen = Vertices.length;
  for (int i = 0; i < vlen; i++) {
    if (below(v, v->edge->twin->origin) && below(v, v->edge->getPrev()->origin)) {
      if (orientation(v->edge->twin->origin, v, v->edge->getPrev()->origin) == CLOCKWISE){
            v->type = START_VERTEX; // Interior angle less than 180.
      }
      else{
          v->type = SPLIT_VERTEX; // Interior angle greater than 180.
      }
    }
    else if (below(v->edge->twin->origin, v) && below(v->edge->getPrev()->origin, v)) {
      if (orientation(v->edge->twin->origin, v, v->edge->getPrev()->origin) == CLOCKWISE)
        v->type = END_VERTEX; // Interior angle less than 180.
      else 
        v->type = MERGE_VERTEX; // Interior angle greater than 180.
    }
    else 
      v->type = REGULAR_VERTEX;

    v = v->next;
  }
}

/**
 * Function For handling START_VERTEX
 */
void HANDLE_START_VERTEX(dvertex *v) {
  tree.insert(v->edge);
  v->edge->helper = v;
}

/**
 * Hepler For Handling END_VERTEX
 */
void HANDLE_END_VERTEX(dvertex *v) {
  if (v->edge->getPrev()->helper)
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      addLine(v, v->edge->getPrev()->helper, window);
      insertDiagonal(v, v->edge->getPrev()->helper);
      sleep(1);
    }
  tree.erase(v->edge->getPrev());
}

/**
 * Hepler For Handling SPLIT_VERTEX
 */
void HANDLE_SPLIT_VERTEX(dvertex *v) {
  set<dedge *, func>::iterator it;
  it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
  if (it != tree.begin()) {
    it--;
  }
  dedge *s = *it;
  addLine(v, s->helper, window);
  insertDiagonal(v, s->helper);
  sleep(1);
  s->helper = v;
  tree.insert(v->edge);
  v->edge->helper = v;
}

/**
 * Hepler For Handling MERGE_VERTEX
 */
void HANDLE_MERGE_VERTEX(dvertex *v) {
  if (v->edge->getPrev()->helper)
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      addLine(v, v->edge->getPrev()->helper, window);
      insertDiagonal(v, v->edge->getPrev()->helper);
      sleep(1);
    }
  tree.erase(v->edge->getPrev());
  set<dedge *, func>::iterator it;
  it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
  if (it != tree.begin()) {
    it--;
  }
  dedge *s = *it;
  if (s->helper)
    if (s->helper->type == MERGE_VERTEX) {
      addLine(v, s->helper, window);
      insertDiagonal(v, s->helper);
      sleep(1);
    }
  s->helper = v;
}

/**
 * Hepler For Handling REGULAR_VERTEX
 */
void HANDLE_REGULAR_VERTEX(dvertex *v) {
  if (below(v, v->edge->twin->origin)) {
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      addLine(v, v->edge->getPrev()->helper, window);
      insertDiagonal(v, v->edge->getPrev()->helper);
      sleep(1);
    }
    tree.erase(v->edge->getPrev());
    tree.insert(v->edge);
    v->edge->helper = v;
  }
  else {
    set<dedge *, func>::iterator it;
    it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
    if (it != tree.begin()) {
      it--;
    }
    dedge *s = *it;
    if (s->helper->type == MERGE_VERTEX) {
      addLine(v, s->helper, window);
      insertDiagonal(v, s->helper);
      sleep(1);
    }
    s->helper = v;
  }
}

/**
 * Split into y-montone polygons
 */
void split_into_monotone(MainWindow *w) {
  cout<<"Converting to y-monotone polygons"<<endl;
  window = w;
  form_vertex_type();
  dvertex *v = Vertices.head;
  while (v) {
   if (v->type == START_VERTEX) HANDLE_START_VERTEX(v);
   else if (v->type == SPLIT_VERTEX) HANDLE_SPLIT_VERTEX(v);
   else if (v->type == END_VERTEX) HANDLE_END_VERTEX(v);
   else if (v->type == MERGE_VERTEX) HANDLE_MERGE_VERTEX(v);
   else if (v->type == REGULAR_VERTEX) HANDLE_REGULAR_VERTEX(v);
    v = v->next;
  }
  cout<<"Finished converting to y-monotone polygons"<<endl;
}

#endif