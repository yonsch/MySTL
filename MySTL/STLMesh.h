#ifndef STLMesh_H
#define STLMesh_H
#include <string>
#include <vector>
#include "Face.h"

using namespace std;

class STLMesh {

public:
	string path;
	string fileName;
	string header;
	int triCount;
	vector<Face> faces;

	STLMesh();
	~STLMesh();

	STLMesh(string);

	float btof(unsigned char, unsigned char, unsigned char, unsigned char);
	void toFile(string);
	unsigned char * STLMesh::writeFloat(float);

	STLMesh& operator* (const float& rhs);

	static void sayHello();
	static void pyramid(Vector3D, Vector3D, Vector3D, Vector3D, string);


private:

};

#endif