#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"

using namespace std;

int main() {
	//STLMesh m("C:\\Users\\Yonch\\Desktop\\pyr.STL");
	//m.toFile("C:\\Users\\Yonch\\Desktop\\k.stl");
	
	Vector3D a = Vector3D(0, 0, 0);
	Vector3D b = Vector3D(0, 0, 20);
	Vector3D c = Vector3D(0, 20, 20);
	Vector3D d = Vector3D(20, 0, 20);
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
	m.toFile("C:\\Users\\Yonch\\Desktop\\f.stl");
	
	//cout << f << endl;

	

	for (int i = 0; i < 4; i++) {
		cout << m.faces[i] << endl;
	}
	
	
	cin.get();
	return 0;
}


