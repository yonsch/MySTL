#include "Face.h"
#include <iostream>

using namespace std;

Face::Face(vec3 v1, vec3 v2, vec3 v3) : v1(v1), v2(v2), v3(v3) {
	vec3 u = v2 - v1, v = v3 - v1;
	n = normalize(cross(u, v));
}

extern ostream& operator<<(ostream& strm, const Face &f) {
	return strm << "<" << f.n << "," << f.v1 << "," << f.v2 << "," << f.v3 << ">";
}

/*
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
*/

Face::operator vector<float>() const {
	vector<float> v(12);
	v[0] = n.x;
	v[1] = n.y;
	v[2] = n.z;
	v[3] = v1.x;
	v[4] = v1.y;
	v[5] = v1.z;
	v[6] = v2.x;
	v[7] = v2.y;
	v[8] = v2.z;
	v[9] = v3.x;
	v[10] = v3.y;
	v[11] = v3.z;

	return v;
}