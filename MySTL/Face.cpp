#include "Face.h"
#include <iostream>
#include <math.h>
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

Face::Face(Vector3D p1, Vector3D p2, Vector3D p3) {
	v1 = p1;
	v2 = p2;
	v3 = p3;
	Vector3D u = p2 - p1;
	Vector3D v = p3 - p1;
	float x = u.y * v.z - u.z * v.y;
	float y = u.z * v.x - u.x * v.z;
	float z = u.x * v.y - u.y * v.x;
	float d = sqrt(x*x + y*y + z*z);
	n = Vector3D(x/d,y/d,z/d);
}

ostream& operator<<(ostream& strm, const Face &a) {
	strm << "<" << a.n << "," << a.v1 << "," << a.v2 << "," << a.v3 << ">";
	return strm;
}

vector<float> Face::getFloats() {
	vector<float> arr(12);
	arr[0] = n.x;
	arr[1] = n.y;
	arr[2] = n.z;
	arr[3] = v1.x;
	arr[4] = v1.y;
	arr[5] = v1.z;
	arr[6] = v2.x;
	arr[7] = v2.y;
	arr[8] = v2.z;
	arr[9] = v3.x;
	arr[10] = v3.y;
	arr[11] = v3.z;
	
	return arr;
}


Face Face::operator*(const float& rhs) {
	Face f;
	f.v1 = v1*rhs;
	f.v2 = v2*rhs;
	f.v3 = v3*rhs;
	f.n = n;	
	return f;
}