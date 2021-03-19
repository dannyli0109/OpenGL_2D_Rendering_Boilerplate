#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(glm::vec2 size, unsigned char* data, int channels)
{
	Create(size, data, channels);
}

Texture::Texture(std::string filename)
{
	int width, height, channels;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	glm::vec2 size = { width, height };
	Create(size, data, channels);
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind(int textureUnit)
{
	glBindTextureUnit(textureUnit, id);
}

void Texture::Destroy()
{
	if (initialised)
	{
		glDeleteTextures(1, &id);
		initialised = false;
	}
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::operator==(const Texture& other)
{
	return id == other.id;
}

void Texture::Create(glm::vec2 size, unsigned char* data, int channels)
{
	if (initialised)
	{
		Destroy();
	}
	initialised = true;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int width = size.x;
	int height = size.y;

	Console* console = Console::GetInstance();

	if (data)
	{
		if (channels == 1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			GLint swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
			glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
		}
		else if (channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			*console << "unknown texture type" << true;
		}
	}
	else {
		*console << "Fail to load texture" << true;
	} 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}
