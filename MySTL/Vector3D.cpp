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

Vector3D& Vector3D::operator=(const Vector3D& rhs) {

	if (this != &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
	}
	return *this;
}

Vector3D& Vector3D::operator-(const Vector3D& rhs) {

	
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	
	return *this;
}
Vector3D& Vector3D::operator+(const Vector3D& rhs) {


	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;

	return *this;
}
Vector3D& Vector3D::operator*(const float& rhs) {


	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;

	return *this;
}
Vector3D& Vector3D::operator/(const float& rhs) {


	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;

	return *this;
}

ostream& operator<<(ostream& strm, const Vector3D &a) {
	strm << "(" << a.x << "," << a.y << "," << a.z << ")";
	return strm;
}