#include <iostream>
#include "Vector3D.h"
#include "Face.h"
#include "STLMesh.h"

using namespace std;

int main() {
	STLMesh m("C:\\Users\\Yonch\\Desktop\\neck.stl");
	m.toFile("C:\\Users\\Yonch\\Desktop\\h.stl");
	cin.get();
	return 0;
}


