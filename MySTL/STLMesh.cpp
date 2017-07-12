#include <string>
#include <vector>
#include "STLMesh.h"
#include <fstream>
#include <iterator>
#include <vector>
#include "iostream"
#include <math.h>

using namespace std;

STLMesh::STLMesh() {
	path = "";
	fileName = "";
	header = "";
	triCount = 0;
	vector<Face> faces;
}

STLMesh::~STLMesh() {

}

STLMesh::STLMesh(string p) {

	//copies file to buffer
	ifstream input(p, ios::binary);
	vector<char> buffer((istreambuf_iterator<char>(input)),(istreambuf_iterator<char>()));

	//read header of file
	for (int i = 0; i < 80; i++) {
		header += buffer[i];
	}


	//read triangle count from file
	triCount = int((unsigned char)(buffer[80])|
		(unsigned char)(buffer[81]) << 8 |
		(unsigned char)(buffer[82]) << 16 |
		(unsigned char)(buffer[83]) <<24);

	
	//read triangles
	for (int i = 0; i < triCount; i++) {
		int p = 84 + i * 50;
		Vector3D n = Vector3D(btof(buffer[p], buffer[p + 1], buffer[p + 2], buffer[p + 3]),
			btof(buffer[p + 4], buffer[p + 5], buffer[p + 6], buffer[p + 7]),
			btof(buffer[p + 8], buffer[p + 9], buffer[p + 10], buffer[p + 11]));
		p += 12;
		Vector3D v1 = Vector3D(btof(buffer[p], buffer[p + 1], buffer[p + 2], buffer[p + 3]),
			btof(buffer[p + 4], buffer[p + 5], buffer[p + 6], buffer[p + 7]),
			btof(buffer[p + 8], buffer[p + 9], buffer[p + 10], buffer[p + 11]));
		p += 12;
		Vector3D v2 = Vector3D(btof(buffer[p], buffer[p + 1], buffer[p + 2], buffer[p + 3]),
			btof(buffer[p + 4], buffer[p + 5], buffer[p + 6], buffer[p + 7]),
			btof(buffer[p + 8], buffer[p + 9], buffer[p + 10], buffer[p + 11]));
		p += 12;
		Vector3D v3 = Vector3D(btof(buffer[p], buffer[p + 1], buffer[p + 2], buffer[p + 3]), 
			btof(buffer[p + 4], buffer[p + 5], buffer[p + 6], buffer[p + 7]), 
			btof(buffer[p + 8], buffer[p + 9], buffer[p + 10], buffer[p + 11]));
		
		
		Face f = Face(v1, v2, v3, n);
		faces.push_back(f);
	}
}

float STLMesh::btof(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3)
{
	unsigned char b[] = { b0, b1, b2, b3 };
	float result;
	memcpy(&result, &b, sizeof(result));
	return result;
}

unsigned char * STLMesh::writeFloat(float f) {
		unsigned char b[4] = {};
		memcpy(&b, &f, sizeof(f));
		return b;
}



void STLMesh::toFile(string path) {
	fileName = path;
	ofstream output(fileName, ios::binary);

	//write header
	output << header;
	unsigned char z = 0;
	for (int i = 0; i < 80 - header.size(); i++) {
		output << z;
	}

	//write tri count
	for (int i = 0; i < 4; i++) 
		output << (unsigned char) (triCount >> (i * 8));

	//write each face
	for (int i = 0; i < triCount; i++) {
		Face fac = faces[i];
		vector<float> v = fac.getFloats();
		for (int j = 0; j < 12; j++) {
			float f = v[j];
			output.write( (char *)&f, sizeof(float));
		}
		output << (unsigned char) 0 << (unsigned char) 0;
	}
}

STLMesh& STLMesh::operator*(const float& rhs) {

	vector<Face> newFaces;
	for (int i = 0; i < faces.size(); i++) {
		newFaces.push_back(faces[i] * rhs);
	}

	this->faces = newFaces;
	this->path = path;
	this->fileName = fileName;
	this->triCount = triCount;
	this->header = header;

	return *this;
}





void STLMesh::pyramid(Vector3D a, Vector3D b, Vector3D c, Vector3D d, string path) {
	Face f1 = Face(a, b, c);
	Face f2 = Face(d, b, a);
	Face f3 = Face(c, b, d);
	Face f4 = Face(c, d, a);
	vector<Face> faces;
	faces.push_back(f1);
	faces.push_back(f2);
	faces.push_back(f3);
	faces.push_back(f4);
	STLMesh m;
	m.faces = faces;
	m.path = "C:\\Users\\Yonch\\Desktop\\f.stl";
	m.header = "please work";
	m.triCount = m.faces.size();
	m.toFile(path);
}


STLMesh STLMesh::prism(vector<Vector3D> layer, Vector3D h) {

	vector<Face> faces;

	//create vertices:
	
	vector<Vector3D> copies;
	Vector3D v;
	for (int i = 0; i < layer.size(); i++) {
		v = layer[i];
		copies.push_back(v+h);
	}

	//create faces:

	//two layers:
	Face f;

	vector<Vector3D> copyOfLayer = layer;
	vector<Vector3D> copyOfCopies = copies;

	//goodAngle is defined on the bottom of this file
	
	Vector3D a;
	Vector3D b;
	Vector3D c;
	int index = 0;
	while (copyOfLayer.size() > 3) {
		a = copyOfLayer[index % copyOfLayer.size()];
		b = copyOfLayer[(index+1) % copyOfLayer.size()];
		c = copyOfLayer[(index+2) % copyOfLayer.size()];
		if (goodAngle(a,b,c)) {
			copyOfLayer.erase(copyOfLayer.begin() + (index + 1) % copyOfLayer.size());
			index++;
			faces.push_back(Face(a,b,c));
		}
		else {
			index++;
		}
	}
	faces.push_back(Face(copyOfLayer[0], copyOfLayer[1], copyOfLayer[2]));


	index = 0;
	while (copyOfCopies.size() > 3) {
		a = copyOfCopies[index % copyOfCopies.size()];
		b = copyOfCopies[(index + 1) % copyOfCopies.size()];
		c = copyOfCopies[(index + 2) % copyOfCopies.size()];
		if (goodAngle(a, b, c)) {
			copyOfCopies.erase(copyOfCopies.begin() + (index + 1) % copyOfCopies.size());
			index++;
			faces.push_back(Face(a, b, c));
			

		}
		else {
			index++;
		}
	}
	faces.push_back(Face(copyOfCopies[0], copyOfCopies[1], copyOfCopies[2]));

	

	//sides:

	int size = layer.size();
	for (int i = 0; i < size; i++) {
		f = Face(layer[i], copies[i], layer[(i + 1)%size]);
		faces.push_back(f);
		f = Face(layer[(i+1)%size], copies[(i+1)%size], copies[i]);
		faces.push_back(f);
	}

	STLMesh mesh;
	mesh.faces = faces;
	mesh.triCount = faces.size();

	for (int i = 0; i < faces.size() - 2; i++) {
		cout << faces[i]<<endl;
	}

	return mesh;
}
bool STLMesh::goodAngle(Vector3D i, Vector3D j, Vector3D k) {
	Vector3D a = k - j;
	Vector3D b = i - j;
	float z = a.x*b.y - a.y*b.x;
	float sizeA = sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	float sizeB = sqrt(b.x*b.x + b.y*b.y + b.z*b.z);
	return  (z / (sizeA*sizeB)) < 0;
}

STLMesh STLMesh::revolve(vector<Vector3D> vecs, float res) {
	float PI = 3.14159265359;
	vector<vector<Vector3D>> vertices;

	//create point cloud
	for (int layer = 0; layer < vecs.size(); layer++) {
		vector<Vector3D> v;
		vertices.push_back(v);
		for (int i = 0; i < res; i++) {
			vertices[layer].push_back(Vector3D(vecs[layer].x * cos(2 * i*PI / res), vecs[layer].x * sin(2 * i * PI / res), vecs[layer].z));
		}
	}


	//make triangles
	Face f;
	vector<Face> faces;
	int iterations = ((vecs[0].x == 0) && (vecs[vecs.size() - 1]).x == 0) ? vertices.size() - 1 : vertices.size();
	for (int layer = 0; layer < iterations; layer++) {
		for (int i = 0; i < res; i++) {
			f = Face(vertices[layer][i], vertices[(layer + 1) % vertices.size()][i], vertices[layer][(i + 1) % vertices[layer].size()]);
			faces.push_back(f);
			f = Face(vertices[layer][(i + 1) % vertices[layer].size()], vertices[(layer + 1) % vertices.size()][(i + 1) % vertices[layer].size()], vertices[(layer + 1) % vertices.size()][i]);
			faces.push_back(f);
		}
	}
	STLMesh s;
	s.faces = faces;
	s.triCount = faces.size();
	return s;
}