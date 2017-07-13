#include "Vector3D.h"
#include <iostream>

using namespace std;

Vector3D::Vector3D() :
	x(0),
	y(0),
	z(0)
{

}

Vector3D::~Vector3D() {

}

Vector3D::Vector3D(float xCoord, float yCoord, float zCoord) :
	x(xCoord),
	y(yCoord),
	z(zCoord)
{

}

Vector3D::Vector3D(const Vector3D& v) :
	x(v.x),
	y(v.y),
	z(v.z)
{

}

Vector3D Vector3D::operator-(const Vector3D& rhs) {
	Vector3D v;
	v.x = x - rhs.x;
	v.y = y - rhs.y;
	v.z = z - rhs.z;
	return v;
}

Vector3D Vector3D::operator+(const Vector3D& rhs) {
	Vector3D v;
	v.x = x + rhs.x;
	v.y = y + rhs.y;
	v.z = z + rhs.z;
	return v;
}
Vector3D Vector3D::operator*(const float& rhs) {
	Vector3D v;
	v.x = x * rhs;
	v.y = y * rhs;
	v.z = z * rhs;
	return v;
}
Vector3D Vector3D::operator/(const float& rhs) {
	Vector3D v;
	v.x = x / rhs;
	v.y = y / rhs;
	v.z = z / rhs;
	return v;
}

ostream& operator<<(ostream& strm, const Vector3D &a) {
	strm << "(" << a.x << "," << a.y << "," << a.z << ")";
	return strm;
}