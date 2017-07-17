#pragma once

#include <string>
#include <map>
#include "math3d.h"
#include "texture.h"

class Texture;
class Shader
{
	unsigned int id = 0;
	std::map<std::string,  int> uniforms;
	void createShader(const std::string& shader, int type);
	void addUniforms(const std::string& source);
public:
	inline Shader() {}
	Shader(const std::string& vertex, const std::string& fragment);
	void bind();
	void unbind();

	void loadUniform(const std::string& name, int value);
	void loadUniform(const std::string& name, float value);
	void loadUniform(const std::string& name, const vec2& value);
	void loadUniform(const std::string& name, const vec3& value);
	void loadUniform(const std::string& name, const mat4& value);
	void loadUniform(const std::string& name, const Texture& value);
};