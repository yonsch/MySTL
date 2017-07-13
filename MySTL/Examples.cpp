#include "Examples.h"

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
	vecs.push_back(Vector3D(0, 0, 0));
	vecs.push_back(Vector3D(60, 0, 0));
	vecs.push_back(Vector3D(60, 0, 10));
	vecs.push_back(Vector3D(10, 0, 20));
	vecs.push_back(Vector3D(10, 0, 60));
	vecs.push_back(Vector3D(70, 0, 110));
	vecs.push_back(Vector3D(50, 0, 110));
	vecs.push_back(Vector3D(10, 0, 80));
	vecs.push_back(Vector3D(0, 0, 80));
	STLMesh m = STLMesh(STLMesh::revolve(vecs, 100), "header");
	string p = "C:\\Users\\Yonch\\Desktop\\revolve.stl";
	m.toFile(p);
}


void makeCurve() {




	vector<Vector3D> vecs = STLMesh::curve(-50, 50, 300, true, true, f);
	STLMesh m = STLMesh(STLMesh::revolve(vecs, 40), "header");
	string p = "C:\\Users\\Yonch\\Desktop\\curve.stl";
	m.toFile(p);
}


float f(float x) {
	return (1 / (1 + pow(2.7182f, (-x) / 10))) * 20 + 10.0;
}
