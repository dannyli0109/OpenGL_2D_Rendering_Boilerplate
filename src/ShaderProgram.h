#pragma once
#include "Graphics.h"
#include <string>
#include "Utilities.h"
#include "Console.h"
class ShaderProgram
{
public:
	ShaderProgram() = default;
	ShaderProgram(std::string vertexFileName, std::string fragmentFileName);

	~ShaderProgram();

	//We don't want to be duplicating our shader around - that will screw us over.
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator= (const ShaderProgram& other) = delete;

	//Moving it around is fine though, we just have to do it properly.
	ShaderProgram(ShaderProgram&& other);
	ShaderProgram& operator= (ShaderProgram&& other);

	bool IsLoaded() const { return loaded; }

	void UseShader();

	GLuint GetUniformLocation(std::string varName);

	void SetUniform(std::string varName, float value);
	void SetUniform(std::string varName, glm::vec3 value);
	void SetUniform(std::string varName, glm::mat4 value);

private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	bool loaded = false;
};

