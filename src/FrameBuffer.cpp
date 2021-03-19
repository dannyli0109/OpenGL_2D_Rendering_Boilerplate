#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
{
	Create(width, height);
}

FrameBuffer::~FrameBuffer()
{
	Destroy();
}

void FrameBuffer::Destroy()
{
	if (initialised)
	{
		glDeleteFramebuffers(1, &fboID);
		glDeleteTextures(1, &texID);

		initialised = false;
	}
}

void FrameBuffer::Create(int width, int height)
{
	Destroy();
	initialised = true;
	glGenFramebuffers(1, &fboID);
	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texID, 0);

	Console* console = Console::GetInstance();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		*console << "Frame Buffer initialised successfully!" << true;
	}
	else {
		*console << "Frame Buffer failed to initialise" << true;
		Destroy();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void FrameBuffer::BindTexture(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
