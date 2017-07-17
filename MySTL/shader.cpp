#include "shader.h"
#include <glew.h>
#include <iostream>
#include <vector>

using namespace std;

void Shader::createShader(const string& source, int type) {
	int shader = glCreateShader(type);

	const char *c_str = source.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);

	int compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		char* log = new char[length];
		glGetShaderInfoLog(shader, length, &length, &log[0]);
		cout << log << endl;
		return;
	}
	
	glAttachShader(id, shader);
	glDeleteShader(shader);
}

void Shader::addUniforms(const string& source) {
	int i = 0;
	while ((i = source.find("uniform", i + 1)) != -1) {
		int end = source.find(';', i + 1), start = source.rfind(' ', end);
		string name = source.substr(start + 1, end - start - 1);
		uniforms[name] = glGetUniformLocation(id, name.c_str());
	}
}

Shader::Shader(const string& vertex, const string& fragment) {
	id = glCreateProgram();
	
	createShader(vertex, GL_VERTEX_SHADER);
	createShader(fragment, GL_FRAGMENT_SHADER);

	glLinkProgram(id);
	glValidateProgram(id);

	int linked;
	glGetProgramiv(id, GL_LINK_STATUS, &linked);
	if (!linked) {
		int length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];

		glGetProgramInfoLog(id, length, &length, log);
		cout << log << endl;
	}

	addUniforms(vertex + fragment);
	glBindAttribLocation(id, 0, "position");
}

void Shader::bind() { glUseProgram(id); }
void Shader::unbind() { glUseProgram(0); }

void Shader::loadUniform(const string& name, int v) { glUniform1i(uniforms[name], v); }
void Shader::loadUniform(const string& name, float v) { glUniform1f(uniforms[name], v); }
void Shader::loadUniform(const string& name, const vec2& v) { glUniform2f(uniforms[name], v.x, v.y); }
void Shader::loadUniform(const string& name, const vec3& v) { glUniform3f(uniforms[name], v.x, v.y, v.z); }
void Shader::loadUniform(const string& name, const mat4& v) { glUniformMatrix4fv(uniforms[name], 1, true, (const float*) v); }
void Shader::loadUniform(const string& name, const Texture& v) {
	v.bind();
	loadUniform(name, (int) v.unit);
}
