#pragma once

#include <iostream>
#include "math3d.h"

class quaternion
{
	inline quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
public:
	float x, y, z, w;

	inline quaternion() : quaternion(0, 0, 0, 1) {}
	inline quaternion(const quaternion& copy) : quaternion(copy.x, copy.y, copy.z, copy.w) {}

	quaternion(const vec3& axis, float angle);
	quaternion(const mat4& m);

	inline quaternion operator+(const quaternion& q) const { return quaternion(x + q.x, y + q.y, z + q.z, w + q.w); }
	inline quaternion operator-(const quaternion& q) const { return quaternion(x - q.x, y - q.y, z - q.z, w - q.w); }
	inline quaternion operator*(float f) const { return quaternion(x * f, y * f, z * f, w * f); }
	inline quaternion operator/(float f) const { return quaternion(x / f, y / f, z / f, w / f); }

	// implemented in source file
	quaternion& operator+=(const quaternion& q);
	quaternion& operator-=(const quaternion& q);
	quaternion& operator*=(float f);
	quaternion& operator/=(float f);
	// implemented in source file
	quaternion operator*(const quaternion& r) const;
	quaternion operator*(const vec3& r) const;
	quaternion& operator*=(const quaternion& r);
	quaternion& operator*=(const vec3& r);

	explicit operator vec3() const;
	explicit operator mat4() const;

	vec3 getRight();
	vec3 getLeft();
	vec3 getUp();
	vec3 getDown();
	vec3 getForward();
	vec3 getBack();

	inline friend quaternion conjugate(const quaternion& q) { return quaternion(-q.x, -q.y, -q.z, q.w); }
};

inline float length(const quaternion& q) { return std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w); }
inline quaternion normalize(const quaternion& q) { return q / length(q); }

inline float dot(const quaternion& a, const quaternion& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline std::ostream& operator<<(std::ostream& strm, const quaternion &q) {
	return strm << "(" << q.x << "i + " << q.y << "j + " << q.z << "k) + " << q.w;
}

quaternion nLerp(const quaternion& q, quaternion& r, float factor, bool shortestPath);
quaternion sLerp(const quaternion& q, const quaternion& r, float factor, bool shortestPath);
