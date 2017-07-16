#include "shader.h"
#include <glew/glew.h>
#include <iostream>
#include <vector>

using namespace std;

int createShader(const string& shader, int type) {
	int id = glCreateShader(type);

	const char *c_str = shader.c_str();
	glShaderSource(id, 1, &c_str, NULL);
	glCompileShader(id);

	int compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* log = new char[length];
		glGetShaderInfoLog(id, length, &length, &log[0]);
		cout << log << endl;
	}

	return id;
}

Shader::Shader(const string& vertex, const string& fragment) {
	int vertexID = createShader(vertex, GL_VERTEX_SHADER);
	int fragmentID = createShader(fragment, GL_FRAGMENT_SHADER);

	id = glCreateProgram();

	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);

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


	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	glBindAttribLocation(id, 0, "position");
}

void Shader::bind() { glUseProgram(id); }
void Shader::unbind() { glUseProgram(0); }
