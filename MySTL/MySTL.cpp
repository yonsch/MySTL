#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"

using namespace std;


void makePyramid();
void makePrism();
void makeRevolve();

int main() {
	
	makePyramid();
	makePrism();
	makeRevolve();

	cout << "Done."<<endl;
	cin.get();
	return 0;
}




void makePyramid() {
	vector<Vector3D> vecs;
	vecs.push_back(Vector3D(0, 50, 0));
	vecs.push_back(Vector3D(10, 30, 100));
	vecs.push_back(Vector3D(40, 30, 40));
	vecs.push_back(Vector3D(20, 10, 70));

	string p = "C:\\Users\\Yonch\\Desktop\\pyramid.stl";
	STLMesh m = STLMesh(STLMesh::pyramid(vecs), "header");
	m.toFile(p);
}

void makePrism() {
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
	Vector3D z = Vector3D(10, 10, 20);
	STLMesh m = STLMesh(STLMesh::prism(vecs, z), "header");
	m.toFile(p);
}

void makeRevolve() {
	vector<Vector3D> vecs;
	vecs.push_back(Vector3D(70, 0, 0));
	vecs.push_back(Vector3D(70, 0, 30));
	vecs.push_back(Vector3D(90, 0, 50));
	vecs.push_back(Vector3D(110, 0, 30));
	vecs.push_back(Vector3D(110, 0, 0));
	STLMesh m = STLMesh(STLMesh::revolve(vecs, 100), "header");
	string p = "C:\\Users\\Yonch\\Desktop\\revolve.stl";
	m = m*0.5f;
	m.toFile(p);
}
