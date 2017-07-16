#include "vec3.h"
#include <iostream>

using namespace std;

const vec3 vec3::RIGHT(1, 0, 0);
const vec3 vec3::LEFT(-1, 0, 0);
const vec3 vec3::UP(0, 1, 0);
const vec3 vec3::DOWN(0, -1, 0);
const vec3 vec3::FORWARD(0, 0, 1);
const vec3 vec3::BACK(0, 0, -1);

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

vec3 vec3::rotate(const quaternion& r) const { return (vec3) (r * (*this) * conjugate(r)); }
vec3 vec3::rotate(const vec3& axis, float angle) const {
	quaternion r(axis, angle);
	return (vec3)(r * (*this) * conjugate(r));
}
