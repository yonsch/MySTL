#include <string>
#include <vector>
#include "STLMesh.h"
#include <fstream>
#include <iterator>
#include <vector>
#include "iostream"

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





void STLMesh::sayHello() {
	cout << "hello" << endl;
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