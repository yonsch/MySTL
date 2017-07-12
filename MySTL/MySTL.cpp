#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"

using namespace std;

int main() {

	
	/*
	Vector3D a = Vector3D(40, 30, 0);
	Vector3D b = Vector3D(0, 0, 0);
	Vector3D c = Vector3D(80, 20, 0);
	Vector3D d = Vector3D(60, 100, 0);
	vector<Vector3D> vecs;
	vecs.push_back(a);
	vecs.push_back(b);
	vecs.push_back(c);
	vecs.push_back(d);
	float height = 40.0;
	Vector3D h = Vector3D(0, 0, height);
	vector<Vector3D> copies;
	for (int i = 0; i < 4; i++) {
		copies.push_back(vecs[i]+h);
	}
	*/

	
	vector<Vector3D> vecs;
	vecs.push_back(Vector3D(0, 50, 0));
	vecs.push_back(Vector3D(10, 30, 0));
	vecs.push_back(Vector3D(40, 30, 0));
	vecs.push_back(Vector3D(20, 10, 0));
	vecs.push_back(Vector3D(40, -10, 0));
	vecs.push_back(Vector3D(10, -10, 0));
	vecs.push_back(Vector3D(0, -30, 0));
	vecs.push_back(Vector3D(-10, -10, 0));
	vecs.push_back(Vector3D(-40, -10, 0));
	vecs.push_back(Vector3D(-20, 10, 0));
	vecs.push_back(Vector3D(-40, 30, 0));
	vecs.push_back(Vector3D(-10, 30, 0));


	string p = "C:\\Users\\Yonch\\Desktop\\prism.stl";
	//STLMesh::pyramid(a, b, c, d, p);
	Vector3D z = Vector3D(10, 10, 20);
	STLMesh m = STLMesh::prism(vecs, z);
	m.toFile(p);
	
	/*
	if (STLMesh::goodAngle(a, b, c)) {
		cout << "yes" << endl;
	}
	else {
		cout << "fuck" << endl;
	}
	if (STLMesh::goodAngle(b, c, d)) {
		cout << "yes" << endl;
	}
	else {
		cout << "fuck" << endl;
	}
	if (STLMesh::goodAngle(c, d, e)) {
		cout << "yes" << endl;
	}
	else {
		cout << "fuck" << endl;
	}
	if (STLMesh::goodAngle(d, e, f)) {
		cout << "yes" << endl;
	}
	else {
		cout << "fuck" << endl;
	}
	if (STLMesh::goodAngle(e, f, g)) {
		cout << "yes" << endl;
	}
	else {
		cout << "fuck" << endl;
	}
	if (STLMesh::goodAngle(f, g, h)) {
		cout << "yes" << endl;
	}
	else {
		cout << "fuck" << endl;
	}
	*/
	cout << "hi";

	cin.get();
	return 0;
}


