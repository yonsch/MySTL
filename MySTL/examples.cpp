#include "examples.h"

#include <string>
#include <vector>

using namespace std;

void makePyramid() {
	vector<vec3> vecs;
	vecs.push_back(vec3(0, 50, 0));
	vecs.push_back(vec3(10, 30, 100));
	vecs.push_back(vec3(40, 30, 40));
	vecs.push_back(vec3(20, 10, 70));

	string p = "C:\\Users\\Yonch\\Desktop\\pyramid.stl";
	STLMesh m = STLMesh(STLMesh::pyramid(vecs), "header");
	m.toFile(p);
}

void makePrism() {
	vector<vec3> vecs;
	vecs.push_back(vec3(0, 50, 0));
	vecs.push_back(vec3(10, 30, 0));
	vecs.push_back(vec3(40, 30, 0));
	vecs.push_back(vec3(20, 10, 0));
	vecs.push_back(vec3(40, -10, 0));
	vecs.push_back(vec3(10, -10, 0));
	vecs.push_back(vec3(0, -30, 0));
	vecs.push_back(vec3(-10, -10, 0));
	vecs.push_back(vec3(-40, -10, 0));
	vecs.push_back(vec3(-20, 10, 0));
	vecs.push_back(vec3(-40, 30, 0));
	vecs.push_back(vec3(-10, 30, 0));
	string p = "C:\\Users\\Yonch\\Desktop\\prism.stl";
	vec3 z = vec3(10, 10, 20);
	STLMesh m = STLMesh(STLMesh::prism(vecs, z), "header");
	m.toFile(p);
}

void makeRevolve() {
	vector<vec3> vecs;
	vecs.push_back(vec3(0, 0, 0));
	vecs.push_back(vec3(60, 0, 0));
	vecs.push_back(vec3(60, 0, 10));
	vecs.push_back(vec3(10, 0, 20));
	vecs.push_back(vec3(10, 0, 60));
	vecs.push_back(vec3(70, 0, 110));
	vecs.push_back(vec3(50, 0, 110));
	vecs.push_back(vec3(10, 0, 80));
	vecs.push_back(vec3(0, 0, 80));
	STLMesh m = STLMesh(STLMesh::revolve(vecs, 100), "header");
	string p = "C:\\Users\\Yonch\\Desktop\\revolve.stl";
	m.toFile(p);
}


void makeCurve() {




	vector<vec3> vecs = STLMesh::curve(-50, 50, 300, true, true, f);
	STLMesh m = STLMesh(STLMesh::revolve(vecs, 40), "header");
	string p = "C:\\Users\\Yonch\\Desktop\\curve.stl";
	m.toFile(p);
}


float f(float x) {
	return (1 / (1 + pow(2.7182f, (-x) / 10))) * 20 + 10.0f;
}