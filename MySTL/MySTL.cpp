#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"

using namespace std;

int main() {
	
	vector<Vector3D> vecs;
	/*
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
	
	cout << "hi";
	*/

	vecs.push_back(Vector3D(0, 0, 50));
	vecs.push_back(Vector3D(10, 0, 30));
	vecs.push_back(Vector3D(40, 0, 10));
	vecs.push_back(Vector3D(0, 0, 0));

	STLMesh m = STLMesh::revolve(vecs, 40);


	string p = "C:\\Users\\Yonch\\Desktop\\revolve.stl";
	m.toFile(p);
	cout << "hi";
	cin.get();
	return 0;
}


