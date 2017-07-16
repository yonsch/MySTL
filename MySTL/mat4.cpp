#include "mat4.h"
#include <iterator>

using namespace std;

// memory-safe assignment
mat4& mat4::operator=(mat4 other) {
	mat4 temp(other);
	swap(temp.m, m);

	return *this;
}

mat4::mat4(const mat4& copy) {
	m = new float[16];
	memcpy(m, copy.m, 16 * sizeof(float));
}

mat4 mat4::operator*(const mat4& r) const {
	float* res = new float[16];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			int row = i * 4;
			float& f = res[row + j];
			f = 0;
			for (int k = 0; k < 4; k++) f += m[row + k] * r.m[k * 4 + j];
		}
	
	return mat4(res);
}

mat4& mat4::operator*=(const mat4& r) {
	mat4 t(*this);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			int row = i * 4;
			float& f = m[row + j];
			f = 0;
			for (int k = 0; k < 4; k++) f += t.m[row + k] * r.m[k * 4 + j];
		}

	return *this;
}

vec3 mat4::operator*(const vec3& r) const {
	return vec3(
		m[0] * r.x + m[1] * r.y + m[2] * r.z + m[3],
		m[4] * r.x + m[5] * r.y + m[6] * r.z + m[7],
		m[8] * r.x + m[9] * r.y + m[10] * r.z + m[11]
	);
}

mat4 mat4::transpose() const {
	float* t = new float[16] { 
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15] 
	};
	
	return mat4(t);
}

mat4 mat4::scale(const vec3& scale) {
	mat4 m;
	m.m[0] = scale.x;
	m.m[5] = scale.y;
	m.m[10] = scale.z;

	return m;
}

mat4 mat4::scale(float scale) {
	mat4 m;
	m.m[0] = scale;
	m.m[5] = scale;
	m.m[10] = scale;

	return m;
}

mat4 mat4::translation(const vec3& t) {
	mat4 m;
	m.m[3] += t.x;
	m.m[7] += t.y;
	m.m[11] += t.z;

	return m;
}

mat4 mat4::translation(float x, float y, float z) {
	mat4 m;
	m.m[3] += x;
	m.m[7] += y;
	m.m[11] += z;

	return m;
}

ostream& operator<<(ostream& strm, const mat4 &m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) strm << m[i][j] << '\t';
		strm << endl;
	}
	return strm;
}

mat4 mat4::perspective(float fov, float ar, float near, float far) {
	float* m = new float[16] { 0 };
	float tan = std::tan(fov / 2);
	float range = near - far;

	m[0] = -1 / (tan * ar);
	m[5] = 1 / tan;
	m[10] = (near + far) / range;
	m[11] = 2 * far * near / range;
	m[14] = -1;
	m[15] = 0;

	return mat4(m);
}

mat4 mat4::rotation(const quaternion& r) {
	return mat4(new float[16] {
		1 - 2 * (r.y * r.y + r.z * r.z), 2 * (r.x * r.y - r.z * r.w), 2 * (r.x * r.z + r.y * r.w), 0,
			2 * (r.x * r.y + r.z * r.w), 1 - 2 * (r.x * r.x + r.z * r.z), 2 * (r.y * r.z - r.x * r.w), 0,
			2 * (r.x * r.z - r.y * r.w), 2 * (r.y * r.z + r.x * r.w), 1 - 2 * (r.x * r.x + r.y * r.y), 0,
			0, 0, 0, 1
	});
}

mat4 mat4::rotation(const vec3& axis, float angle) { return rotation(quaternion(axis, angle)); }

mat4::operator quaternion() const { return quaternion(*this); }
