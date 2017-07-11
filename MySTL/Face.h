#ifndef Face_H
#define Face_H

#include <vector>
#include "Vector3D.h"

class Face {





public:

	Face();

	Face(Vector3D v1, Vector3D v2, Vector3D v3,Vector3D n);

	Vector3D v1;
	Vector3D v2;
	Vector3D v3;
	Vector3D n;

	string toString();

	vector<float> getFloats();


};

std::ostream& operator<<(ostream& strm, const Face &a);

#endif