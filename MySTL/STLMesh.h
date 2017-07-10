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

	STLMesh(string p);

	float btof(unsigned char, unsigned char, unsigned char, unsigned char);



private:

};

//std::ostream& operator<<(ostream& strm, const STLMesh &a);

#endif