#include "triangulate.h"
using namespace std;

int main() {
	getPolygon("test.txt");
	split_into_monotone();
	triangulate();
	// printPolygon();
}