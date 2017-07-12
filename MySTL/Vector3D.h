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
	Vector3D& operator- (const Vector3D& rhs);
	Vector3D& operator+ (const Vector3D& rhs);
	Vector3D& operator* (const float& rhs);
	Vector3D& operator/ (const float& rhs);

	
	string toString();

private:

};

std::ostream& operator<<(ostream& strm, const Vector3D &a);

#endif