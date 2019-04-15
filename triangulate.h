#include "monotone.h"
using namespace std;

void triangulate() {
	DCELFace* walker = Faces.head;
	vector<pair<DCELVertex *, DCELVertex *> > pendingDiagonals;
	while (walker) {
		if (walker->boundaryLength() > 3 && walker->bordered) {
			vector<pair<DCELVertex *, int> >::iterator it;
			vector<pair<DCELVertex *, int> > list = walker->sortedVertices();
			(*(list.end() - 1)).second = -1;
			stack<pair<DCELVertex *, int> > stck;
			it = list.begin();
			stck.push((*it));
			it++;
			stck.push((*it));
			it++;
			for (; it != list.end(); it++)
			{
				if ((*it).second != stck.top().second)  {
					while (stck.size() > 1) {
						pendingDiagonals.push_back(make_pair(stck.top().first, (*it).first));
						stck.pop();
					}
					stck.pop();
					stck.push((*(it - 1)));
					stck.push((*it));
				}
				else {
					pair<DCELVertex *, int> lastPoint;
					lastPoint = stck.top();
					stck.pop();
					while (!stck.empty()) {
						if ((*it).second == 1) {
							DCELHalfEdge *edgeWalker = (*it).first->edge;
							while (edgeWalker->face != walker) edgeWalker = edgeWalker->twin->next;
							if (orientation(edgeWalker->next->origin, (*it).first, stck.top().first) == CLOCKWISE) {
								pendingDiagonals.push_back(make_pair(stck.top().first, (*it).first));
								lastPoint = stck.top();
								stck.pop();
							}
							else break;
						}
						else if ((*it).second == -1) {
							DCELHalfEdge *edgeWalker = (*it).first->getEdgeOnFace(walker);
							if (orientation(edgeWalker->getPrev()->origin, (*it).first, stck.top().first) == ANTICLOCKWISE) {
								pendingDiagonals.push_back(make_pair(stck.top().first, (*it).first));
								lastPoint = stck.top();
								stck.pop();
							}
							else break;
						}
					}
					stck.push(lastPoint);
					stck.push((*it));
				}
			}
		}
		walker = walker->next;
	}
	for (int i = 0; i < pendingDiagonals.size(); i++) {
		insertDiagonal(pendingDiagonals[i].first, pendingDiagonals[i].second);
	}
}