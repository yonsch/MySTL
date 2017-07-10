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