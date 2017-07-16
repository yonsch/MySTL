#pragma once

#include "math3d.h"
#include <array>
#include <iostream>

class mat4
{
	float* m;
	inline mat4(float m[16]) { this->m = m; }
public:
	inline mat4() { m = new float[16] { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; }
	mat4(const mat4& copy);

	inline ~mat4() { delete[] m; }

	mat4& operator=(mat4 other);

	// enable matrix access (e.g. matrix[1][0])
	inline const float* operator[](unsigned int row) const { return m + row * 4; }
	inline float* operator[](unsigned int row) { return m + row * 4; }

	explicit inline operator const float*() const { return m; }
	explicit inline operator float*() { return m; }

	explicit operator quaternion() const;

	vec3 operator*(const vec3& r) const;
	mat4 operator*(const mat4& r) const;
	
	mat4& operator*=(const mat4& r);

	mat4 transpose() const;

	static mat4 perspective(float fov, float aspectRatio, float near, float far);
	// to transform (move, rotate, scale) a matrix, 
	// right-multiply it by one of these
	static mat4 scale(float scale);
	static mat4 scale(const vec3& scale);
	static mat4 translation(float x, float y, float z);
	static mat4 translation(const vec3& scale);
	static mat4 rotation(const quaternion& q);
	static mat4 rotation(const vec3& axis, float angle);
};

std::ostream& operator<<(std::ostream& strm, const mat4 &m);
