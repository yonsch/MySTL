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
	Vector3D a = Vector3D(0, 0, 0);
	Vector3D b = Vector3D(0, 0, 20);
	Vector3D c = Vector3D(0, 20, 20);
	Vector3D d = Vector3D(20, 0, 20);
	string p = "C:\\Users\\Yonch\\Desktop\\ffgf.stl";
	STLMesh::pyramid(a,b,c,d, p);


	cin.get();
	return 0;
}


