#include "triangulate.h"
using namespace std;

int main() {
	getPolygon("input.txt");
	split_into_monotone();
	triangulate();
	printPolygon();
}