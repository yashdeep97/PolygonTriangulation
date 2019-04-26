#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include "miscellaneous.h"
#include <stack>
using namespace std;

/// Triangulation of y-monotone polygons
class Triangulate{
	public:
	/**
	 * Static function to triangulate y-monotone polygons.
	*/
	static void triangulate() {
		sleep(1);
		cout<<"Starting Triangulation"<<endl;
		dface* d_itr = Faces.head;
		vector<pair<dvertex *, dvertex *> > pendingDiagonals;
		while (d_itr) {
			if (d_itr->boundaryLength() > 3 && d_itr->bordered) {
				vector<pair<dvertex *, int> >::iterator it;
				vector<pair<dvertex *, int> > list = d_itr->sortedVertices();
				(*(list.end() - 1)).second = -1;
				// Stack to store vertices during triangulation.
				stack<pair<dvertex *, int> > s;

				it = list.begin();
				s.push((*it));
				it++;
				s.push((*it));
				it++;
				for (; it != list.end(); it++)
				{
					if ((*it).second != s.top().second)  {
						while (s.size() > 1) {
							pendingDiagonals.push_back(make_pair(s.top().first, (*it).first));
							s.pop();
						}
						s.pop();
						s.push((*(it - 1)));
						s.push((*it));
					}
					else {
						pair<dvertex *, int> lastPoint;
						lastPoint = s.top();
						s.pop();
						while (!s.empty()) {
							if ((*it).second == 1) {
								dedge *edgeWalker = (*it).first->edge;
								while (edgeWalker->face != d_itr) edgeWalker = edgeWalker->twin->next;
								if (orientation(edgeWalker->next->origin, (*it).first, s.top().first) == CLOCKWISE) {
									pendingDiagonals.push_back(make_pair(s.top().first, (*it).first));
									lastPoint = s.top();
									s.pop();
								}
								else break;
							}
							else if ((*it).second == -1) {
								dedge *edgeWalker = (*it).first->getEdgeOnFace(d_itr);
								if (orientation(edgeWalker->getPrev()->origin, (*it).first, s.top().first) == ANTICLOCKWISE) {
									pendingDiagonals.push_back(make_pair(s.top().first, (*it).first));
									lastPoint = s.top();
									s.pop();
								}
								else break;
							}
						}
						s.push(lastPoint);
						s.push((*it));
					}
				}
			}
			d_itr = d_itr->next;
		}
		for (unsigned int i = 0; i < pendingDiagonals.size(); i++) {
			addLine(pendingDiagonals[i].first, pendingDiagonals[i].second, window);
			insertDiagonal(pendingDiagonals[i].first, pendingDiagonals[i].second);
			sleep(1);
		}
	}

};


#endif
