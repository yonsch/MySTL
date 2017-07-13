#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"
#include "Examples.h"

using namespace std;


int main() {
	
	makePyramid();
	makePrism();
	makeRevolve();
	makeCurve();

	cout << "Done."<<endl;
	cin.get();
	return 0;
}






