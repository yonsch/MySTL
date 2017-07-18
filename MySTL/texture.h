#pragma once

#include <glew.h>
#include "frame_buffer.h"
#include "shader.h"

class Texture
{
public:
	unsigned int id, unit, target=GL_TEXTURE_2D;
	Texture(const void* pixels, int width, int height, int unit, int internalformat, int format, int type);
public:
	inline Texture(const void* pixels, int width, int height, int unit = 0) :
		Texture (pixels, width, height, unit, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE) {}
	inline Texture(int width, int height, int unit=0, int internalformat=GL_RGBA, int format=GL_RGBA, int type=GL_UNSIGNED_BYTE) :
		Texture(nullptr, width, height, unit, internalformat, format, type) {}

	inline Texture() {}
	inline ~Texture() { //glDeleteTextures(1, &id); }
	}

	inline void bind() const;
	inline void unbind() const;

	friend class FrameBuffer;
	friend class Shader;
};

