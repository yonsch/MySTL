#include <iostream>
#include "Vector3D.h"
#include "Face.h"
using namespace std;

int main() {

	Vector3D vec1 = Vector3D(1.f, 1.f, 1.f);
	Vector3D vec2 = Vector3D(2.f, 2.f, 2.f);
	Vector3D vec3 = Vector3D(3.f, 3.f, 3.f);
	Face fac = Face(vec1, vec2, vec3);
	//cout << fac.toString() << endl;
	cout << fac << endl;
	cin.get();
	return 0;
}


