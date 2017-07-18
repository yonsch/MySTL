#include "frame_buffer.h"
#include <vector>
#include <iostream>

using namespace std;

FrameBuffer::FrameBuffer(int width, int height, int n, Texture* textures) : width(width), height(height) {
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, width, height);

	vector<unsigned int> attachments;
	for (int i = 0, j = 0; i < n; i++) {
		if (textures[i].target != GL_TEXTURE_2D) continue;  // temporarily ignore non-2D textures
		textures[i].bind();
		attachments.push_back(GL_COLOR_ATTACHMENT0 + (j++));
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachments.back(), GL_TEXTURE_2D, textures[i].id, 0);
		textures[i].unbind();
	}

	glDrawBuffers(attachments.size(), &attachments[0]);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "oops... " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << endl;
	
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
	
	unbind();
}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
