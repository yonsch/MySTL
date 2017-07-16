#include "vec3.h"
#include <iostream>

using namespace std;

vec3& vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}
vec3& vec3::operator-=(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

vec3& vec3::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;

	return *this;
}
vec3& vec3::operator/=(float f) {
	x /= f;
	y /= f;
	z /= f;

	return *this;
}

vec3 cross(const vec3& l, const vec3& r) {
	return vec3(
		l.y * r.z - l.z * r.y,
		l.z * r.x - l.x * r.z,
		l.x * r.y - l.y * r.x
	);
}