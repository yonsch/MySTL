#include "STLMesh.h"
#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;

float readFloat(byte* b) {
	float result;
	memcpy(&result, b, sizeof(result));
	return result;
}

STLMesh::STLMesh(string p) {
	//copies file to buffer
	ifstream input(p, ios::binary);
	vector<byte> buffer((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));

	//read header of file
	for (int i = 0; i < 80; i++) {
		header += buffer[i];
	}

	//read triangle count from file
	memcpy(&triCount, &buffer[80], sizeof(triCount));

	//read triangles
	for (int i = 0; i < triCount; i++) {
		int p = 84 + i * 50;

		vec3 n(readFloat(&buffer[p]), readFloat(&buffer[p + 4]), readFloat(&buffer[p + 8]));
		p += 12;
		vec3 v1(readFloat(&buffer[p]), readFloat(&buffer[p + 4]), readFloat(&buffer[p + 8]));
		p += 12;
		vec3 v2(readFloat(&buffer[p]), readFloat(&buffer[p + 4]), readFloat(&buffer[p + 8]));
		p += 12;
		vec3 v3(readFloat(&buffer[p]), readFloat(&buffer[p + 4]), readFloat(&buffer[p + 8]));

		Face f(v1, v2, v3, n);
		faces.push_back(f);
	}
}

void STLMesh::toFile(string path) const {
	ofstream output(path, ios::binary);

	//write header
	output << header;
	byte z = 0;
	for (unsigned int i = 0; i < 80 - header.size(); i++) {
		output << z;
	}

	//write tri count
	for (int i = 0; i < 4; i++)
		output << (byte)(triCount >> (i * 8));

	//write each face
	for (int i = 0; i < triCount; i++) {
		Face fac = faces[i];
		vector<float> v = (vector<float>) fac;
		for (int j = 0; j < 12; j++) {
			float f = v[j];
			output.write((char *)&f, sizeof(float));
		}
		output << (byte)0 << (byte)0;
	}
}

STLMesh STLMesh::operator*(const float& scale) {
	vector<Face> newFaces(faces.size());
	for (unsigned int i = 0; i < faces.size(); i++) {
		newFaces[i] = faces[i] * scale;
	}

	return STLMesh(newFaces, header);
}


vector<Face> STLMesh::pyramid(vector<vec3> v) {
	vector<Face> faces;
	faces.push_back(Face(v[0], v[1], v[2]));
	faces.push_back(Face(v[3], v[1], v[0]));
	faces.push_back(Face(v[2], v[1], v[3]));
	faces.push_back(Face(v[2], v[3], v[0]));
	return faces;
}

bool goodAngle(vec3 i, vec3 j, vec3 k) {
	vec3 a = k - j;
	vec3 b = i - j;
	return cross(a, b).z < 0;
}

vector<Face> STLMesh::prism(vector<vec3> layer, vec3 h) {

	vector<Face> faces;

	//create vertices:

	vector<vec3> copies;
	vec3 v;
	for (unsigned int i = 0; i < layer.size(); i++) {
		copies.push_back(layer[i] + h);
	}

	//create faces:

	//two layers:
	Face f;

	vector<vec3> copyOfLayer = layer;
	vector<vec3> copyOfCopies = copies;

	//goodAngle is defined on the bottom of this file

	vec3 a;
	vec3 b;
	vec3 c;
	int index = 0;
	while (copyOfLayer.size() > 3) {
		a = copyOfLayer[index % copyOfLayer.size()];
		b = copyOfLayer[(index + 1) % copyOfLayer.size()];
		c = copyOfLayer[(index + 2) % copyOfLayer.size()];
		if (goodAngle(a, b, c)) {
			copyOfLayer.erase(copyOfLayer.begin() + (index + 1) % copyOfLayer.size());
			index++;
			faces.push_back(Face(a, b, c));
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
		f = Face(layer[i], copies[i], layer[(i + 1) % size]);
		faces.push_back(f);
		f = Face(layer[(i + 1) % size], copies[(i + 1) % size], copies[i]);
		faces.push_back(f);
	}
	return faces;
}

vector<Face> STLMesh::revolve(vector<vec3> vecs, float res) {
	float PI = 3.14159265359f;
	vector<vector<vec3>> vertices;

	//create point cloud
	for (unsigned int layer = 0; layer < vecs.size(); layer++) {
		vector<vec3> v;
		vertices.push_back(v);
		for (int i = 0; i < res; i++) {
			vertices[layer].push_back(vec3(vecs[layer].x * cos(2 * i*PI / res), vecs[layer].x * sin(2 * i * PI / res), vecs[layer].z));
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
	return faces;
}

vector<vec3> STLMesh::curve(float start, float end, int res, bool closeStart, bool closeEnd, float(*function)(float)) {
	float delta = (end - start) / res;
	float x;
	float z;
	vector<vec3> vecs;
	if (closeStart) {
		vecs.push_back(vec3(0, 0, start));
	}
	for (int i = 0; i < res; i++) {
		x = start + delta*(float)i;
		z = function(x);
		vecs.push_back(vec3(z, 0, x));
	}
	if (closeEnd) {
		vecs.push_back(vec3(0, 0, end - delta));
	}
	return vecs;
}

STLMesh::operator Mesh() {
	float* arr = new float[triCount * 9];
	for (int i = 0; i < triCount; i++) {
		arr[i * 9 + 0] = faces[i].v1.x;
		arr[i * 9 + 1] = faces[i].v1.y;
		arr[i * 9 + 2] = faces[i].v1.z;
		arr[i * 9 + 3] = faces[i].v2.x;
		arr[i * 9 + 4] = faces[i].v2.y;
		arr[i * 9 + 5] = faces[i].v2.z;
		arr[i * 9 + 6] = faces[i].v3.x;
		arr[i * 9 + 7] = faces[i].v3.y;
		arr[i * 9 + 8] = faces[i].v3.z;
	}

	Mesh m(arr, triCount * 9);
	return m;
}
