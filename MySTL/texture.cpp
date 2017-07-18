#include "texture.h"
#include <SDL.h>

Texture::Texture(const void* pixels, int width, int height, int unit, int internalformat, int format, int type) : unit(unit) {
	glGenTextures(1, &id);
	bind();
	
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	glTexImage2D(target, 0, internalformat, width, height, 0, format, type, pixels);
	unbind();
}

void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(target, id);
}

void Texture::unbind() const {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(target, 0);
}
