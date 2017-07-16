#include "quaternion.h"

quaternion::quaternion(const vec3& axis, float angle) {
	float sin = std::sin(angle / 2);
	
	x = axis.x * sin;
	y = axis.y * sin;
	z = axis.z * sin;
	w = cos(angle / 2);
}

quaternion& quaternion::operator+=(const quaternion& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}
quaternion& quaternion::operator-=(const quaternion& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

quaternion& quaternion::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}
quaternion& quaternion::operator/=(float f) {
	x /= f;
	y /= f;
	z /= f;
	w /= f;

	return *this;
}

quaternion quaternion::operator*(const quaternion& r) const {
	return quaternion(
		x * r.w + w * r.x + y * r.z - z * r.y,
		y * r.w + w * r.y + z * r.x - x * r.z,
		z * r.w + w * r.z + x * r.y - y * r.x,
		w * r.w - x * r.x - y * r.y - z * r.z
	);
}
quaternion quaternion::operator*(const vec3& r) const {
	return quaternion(
		w * r.x + y * r.z - z * r.y,
		w * r.y + z * r.x - x * r.z,
		w * r.z + x * r.y - y * r.x,
		- x * r.x - y * r.y - z * r.z
	);
}

quaternion& quaternion::operator*=(const quaternion& r) {
	x = x * r.w + w * r.x + y * r.z - z * r.y;
	y = y * r.w + w * r.y + z * r.x - x * r.z;
	z = z * r.w + w * r.z + x * r.y - y * r.x,
	w = w * r.w - x * r.x - y * r.y - z * r.z;

	return *this;
}
quaternion& quaternion::operator*=(const vec3& r) {
	x = w * r.z + x * r.y - y * r.x;
	y = -x * r.x - y * r.y - z * r.z;
	z = w * r.x + y * r.z - z * r.y;
	w = w * r.y + z * r.x - x * r.z;
	
	return *this;
}

quaternion::quaternion(const mat4& m) {
	float trace = m[0][0] + m[1][1] + m[2][2];

	if (trace > 0) {
		float s = 0.5f / std::sqrt(trace + 1);
		w = 0.25f / s;
		x = (m[1][2] - m[2][1]) * s;
		y = (m[2][0] - m[0][2]) * s;
		z = (m[0][1] - m[1][0]) * s;
	}
	else if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) {
		float s = 2 * std::sqrt(1 + m[0][0] - m[1][1] - m[2][2]);
		w = (m[1][2] - m[2][1]) / s;
		x = 0.25f * s;
		y = (m[1][0] + m[0][1]) / s;
		z = (m[2][0] + m[0][2]) / s;
	}
	else if (m[1][1] > m[2][2]) {
		float s = 2 * std::sqrt(1 + m[1][1] - m[0][0] - m[2][2]);
		w = (m[2][0] - m[0][2]) / s;
		x = (m[1][0] + m[0][1]) / s;
		y = 0.25f * s;
		z = (m[2][1] + m[1][2]) / s;
	}
	else {
		float s = 2 * std::sqrt(1 + m[2][2] - m[1][1] - m[0][0]);
		w = (m[0][1] - m[1][0]) / s;
		x = (m[2][0] + m[0][2]) / s;
		y = (m[1][2] + m[2][1]) / s;
		z = 0.25f * s;
	}

	float length = std::sqrt(x * x + y * y + z * z + w * w);
	w /= length;
	x /= length;
	y /= length;
	z /= length;
}

// code taken from some shit website
quaternion nLerp(const quaternion& q, quaternion& r, float factor, bool shortestPath) {
	quaternion correctedDest;

	if (shortestPath && dot(q, r) < 0) correctedDest = r * -1;
	else correctedDest = r;
	
	return normalize((r - q) * factor + q);
}
quaternion sLerp(const quaternion& q, const quaternion& r, float factor, bool shortestPath) {
	static const float EPSILON = 1e3;

	float cos = dot(q, r);
	quaternion corrected;

	if (shortestPath && cos < 0) {
		cos *= -1;
		corrected = r * -1;
	}
	else corrected = r;

	if (std::abs(cos) > 1 - EPSILON)
		return nLerp(q, corrected, factor, false);

	float sin = std::sqrt(1 - cos * cos);
	float angle = std::atan2(sin, cos);
	float invSin = 1 / sin;

	float srcFactor = sinf((1 - factor) * angle) * invSin;
	float destFactor = sinf((factor)* angle) * invSin;

	return quaternion(q * srcFactor + corrected * destFactor);
}

quaternion::operator vec3() const { return vec3(x, y, z); }
quaternion::operator mat4() const { return mat4::rotation(*this); }

vec3 quaternion::getRight() { return vec3::RIGHT.rotate(*this); }
vec3 quaternion::getLeft() { return vec3::LEFT.rotate(*this); }
vec3 quaternion::getUp() { return vec3::UP.rotate(*this); }
vec3 quaternion::getDown() { return vec3::DOWN.rotate(*this); }
vec3 quaternion::getForward() { return vec3::FORWARD.rotate(*this); }
vec3 quaternion::getBack() { return vec3::BACK.rotate(*this); }
