#ifndef Face_H
#define Face_H

#include <vector>
#include "Vector3D.h"

class Face {
public:
	Vector3D v1;
	Vector3D v2;
	Vector3D v3;
	Vector3D n;

	Face();
	Face(Vector3D v1, Vector3D v2, Vector3D v3,Vector3D n);
	Face(Vector3D v1, Vector3D v2, Vector3D v3);
	string toString();
	vector<float> getFloats();

	Face operator* (const float& rhs);
};

std::ostream& operator<<(ostream& strm, const Face &a);

#endif