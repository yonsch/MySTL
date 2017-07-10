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
	cout << buffer.size() << endl;



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
		Vector3D v1 = Vector3D(btof(p, p + 1, p + 2, p + 3), btof(p + 4, p + 5, p + 6, p + 7), btof(p + 8, p + 9, p + 10, p + 11));
		p += 12;
		Vector3D v2 = Vector3D(btof(p, p + 1, p + 2, p + 3), btof(p + 4, p + 5, p + 6, p + 7), btof(p + 8, p + 9, p + 10, p + 11));
		p += 12;
		Vector3D v3 = Vector3D(btof(p, p + 1, p + 2, p + 3), btof(p + 4, p + 5, p + 6, p + 7), btof(p + 8, p + 9, p + 10, p + 11));
		p += 12;
		Vector3D n = Vector3D(btof(p, p + 1, p + 2, p + 3), btof(p + 4, p + 5, p + 6, p + 7), btof(p + 8, p + 9, p + 10, p + 11));
		Face f = Face(v1, v2, v3, n);
		faces.push_back(f);
	}


	//ofstream output("C:\\Users\\Yonch\\Desktop\\copy.stl", ios::binary);



	//for (int i = 0; i < buffer.size(); i++)
	//{
	//	output << buffer[i];
	//}
	
}

float STLMesh::btof(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3)
{
	unsigned char b[] = { b3, b2, b1, b0 };
	float result;
	memcpy(&result, &b, sizeof(result));
	return result;
}


//std::ostream& operator<<(ostream& strm, const STLMesh &a);

