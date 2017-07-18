#pragma once

#include <glew.h>
#include "texture.h"

class Texture;
class FrameBuffer
{
	unsigned int width, height, id;
public:
	FrameBuffer(int width, int height, int n, Texture* textures);

	inline FrameBuffer() {}
	inline ~FrameBuffer() { //glDeleteFramebuffers(1, &id); }
	}

	void bind();
	inline void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
};
