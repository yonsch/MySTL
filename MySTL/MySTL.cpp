#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"

using namespace std;

int main() {
	
	/*example of pyramid
	vector<Vector3D> vecs;
	vecs.push_back(Vector3D(0, 50, 0));
	vecs.push_back(Vector3D(10, 30, 100));
	vecs.push_back(Vector3D(40, 30, 40));
	vecs.push_back(Vector3D(20, 10, 70));
	
	string p = "C:\\Users\\Yonch\\Desktop\\pyramid.stl";
	STLMesh m = STLMesh(STLMesh::pyramid(vecs),"header");
	m.toFile(p);
	*/
	
	
	
	/*example of prism
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
	STLMesh m = STLMesh(STLMesh::prism(vecs, z),"header");
	m.toFile(p);
	*/


	/*example of revolve*/
	vector<Vector3D> vecs;
	vecs.push_back(Vector3D(70, 0, 0));
	vecs.push_back(Vector3D(70, 0, 30));
	vecs.push_back(Vector3D(90, 0, 50));
	vecs.push_back(Vector3D(110, 0, 30));
	vecs.push_back(Vector3D(110, 0, 0));
	STLMesh m = STLMesh(STLMesh::revolve(vecs, 100),"some header");
	string p = "C:\\Users\\Yonch\\Desktop\\revolve.stl";
	m.toFile(p);
	


	cout << "Done."<<endl;
	cin.get();
	return 0;
}


