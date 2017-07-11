#include "Face.h"
#include <iostream>

using namespace std;

Face::Face() {
	Vector3D v;
	v1 = v;
	v2 = v;
	v3 = v;
}

Face::Face(Vector3D p1, Vector3D p2, Vector3D p3, Vector3D no) {
	v1 = p1;
	v2 = p2;
	v3 = p3;
	n = no;
}


string Face::toString() {
	return "<" + v1.toString() + "," + v2.toString() + "," + v3.toString() + ">";
}

ostream& operator<<(ostream& strm, const Face &a) {

	strm << "<" << a.v1 << "," << a.v2 << "," << a.v3 << ">";
	return strm;
}

vector<float> Face::getFloats() {
	vector<float> arr(12);
	arr[0] = v1.x;
	arr[1] = v1.y;
	arr[2] = v1.z;
	arr[3] = v2.x;
	arr[4] = v2.y;
	arr[5] = v2.z;
	arr[6] = v3.x;
	arr[7] = v3.y;
	arr[8] = v3.z;
	arr[9] = n.x;
	arr[10] = n.y;
	arr[11] = n.z;
	
	//cout << v1.x << endl;

	for (int j = 0; j < 12; j++) {
		float f = arr[j];
		//output.write((char *)&f, sizeof(float));
		//cout << f << endl;
	}

	return arr;
}