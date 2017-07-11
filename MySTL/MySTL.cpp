#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"

using namespace std;

int main() {

	STLMesh m("C:\\Users\\Yonch\\Desktop\\neck.stl");
	//for (int i = 0; i < 20; i++) {
		//cout << m.faces[i] << endl;
	//}
	m.toFile("C:\\Users\\Yonch\\Desktop\\h.stl");
	cin.get();
	return 0;
}


