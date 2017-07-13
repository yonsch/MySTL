#ifndef STLMesh_H
#define STLMesh_H
#include <string>
#include <vector>
#include "Face.h"

using namespace std;

class STLMesh {

public:
	string header;
	int triCount;
	vector<Face> faces;

	STLMesh();
	~STLMesh();

	STLMesh(string);
	STLMesh(vector<Face>,string);

	float btof(unsigned char, unsigned char, unsigned char, unsigned char);
	void toFile(string);
	unsigned char * STLMesh::writeFloat(float);

	STLMesh operator* (const float& rhs);

	
	static vector<Face> pyramid(vector<Vector3D>);
	static vector<Face> prism(vector<Vector3D>, Vector3D);
	static vector<Face> revolve(vector<Vector3D>,float);
	static bool goodAngle(Vector3D, Vector3D, Vector3D);

private:

};

#endif