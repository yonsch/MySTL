#pragma once

#include "math3d.h"

class Transform 
{
public:
	vec3 pos, scl = vec3(1);
	quaternion rot;
	mat4 mat;
	bool modified = false; 
	const bool inverse;
public:
	inline Transform(bool inverse = false) : inverse(inverse) {}

	inline operator mat4() {
		if (modified) {
			if (inverse) mat = mat4::scale(vec3(1) / scl) * mat4::rotation(conjugate(rot)) * mat4::translation(-pos);
			else mat = mat4::translation(pos) * (mat4::rotation(rot) * mat4::scale(scl));
			modified = false;
		}
		return mat;
	}

	inline Transform& move(const vec3& v) {
		modified = true;
		pos += v;
		return *this;
	}
	inline Transform& move(float x, float y, float z) {
		modified = true;
		pos.x += x; pos.y += y; pos.z += z;
		return *this;
	}

	inline Transform& scale(const vec3& v) {
		modified = true;
		scl = scl * v;
		return *this;
	}
	inline Transform& scale(float s) {
		modified = true;
		scl *= s;
		return *this;
	}

	inline Transform& rotate(const quaternion& q) {
		modified = true;
		rot = normalize(q * rot);
		return *this;
	}
	inline Transform& rotate(const vec3& axis, float angle) {
		modified = true;
		rot = normalize(quaternion(normalize(axis), angle) * rot);
		
		return *this;
	}
};
