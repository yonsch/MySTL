#pragma once

#include <string>
#include <map>
#include "math3d.h"

class Shader
{
	unsigned int id = 0;
	std::map<const char*,  int> uniforms;
	void createShader(const std::string& shader, int type);
public:
	inline Shader() {}
	Shader(const std::string& vertex, const std::string& fragment);
	void bind();
	void unbind();

	void loadUniform(const char* name, int value);
	void loadUniform(const char* name, float value);
	void loadUniform(const char* name, const vec2& value);
	void loadUniform(const char* name, const vec3& value);
	void loadUniform(const char* name, const mat4& value);
};