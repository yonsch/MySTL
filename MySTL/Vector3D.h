#ifndef Vector3D_H
#define Vector3D_H
#include <string>
using namespace std;

class Vector3D {

public:
	float x;
	float y;
	float z;

	Vector3D();
	~Vector3D();

	Vector3D(float xCoord, float yCoord, float zCoord);
	Vector3D(const Vector3D& v);
	Vector3D& operator= (const Vector3D& rhs);

	string toString();

private:

};

#endif