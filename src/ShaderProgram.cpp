#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexFileName, std::string fragmentFileName)
{
	loaded = true;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	Console* console = Console::GetInstance();

	std::string vertexSource = LoadFileAsString(vertexFileName);
	std::string fragmentSource = LoadFileAsString(fragmentFileName);

	const char* vertexSourceC = vertexSource.c_str();
	glShaderSource(vertexShader, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShader);

	GLchar errorLog[512];
	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//Something failed with the vertex shader compilation
		(*console) << "Vertex shader " << vertexFileName << " failed with error:" << true;
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		*console << errorLog << true;
		loaded = false;
	}
	else
	{
		(*console) << vertexFileName << " compiled successfully." << true;
	}

	const char* fragmentSourceC = fragmentSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentSourceC, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//Something failed with the fragment shader compilation
		*console << "Fragment shader " << fragmentFileName << " failed with error:" << true;
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		*console << errorLog << true;
		loaded = false;
	}
	else
	{
		*console << fragmentFileName << " compiled successfully." << true;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		*console << "Error linking shaders " << vertexFileName << " and " << fragmentFileName << true;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);
		*console << errorLog << true;
		loaded = false;
	}


	if (loaded)
	{
		*console << "Shader program linked successfully" << true;
	}
	else
	{
		//If there was a problem, tell OpenGL that we don't need those resources after all.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}
}

ShaderProgram::~ShaderProgram()
{
	if (loaded)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}
}

ShaderProgram::ShaderProgram(ShaderProgram&& other)
{
	if (&other == this)	//Don't do the move if we're moving this shader to itself.
	{
		return;
	}

	if (loaded)
	{
		//If the shader we're moving over the top of is an old valid shader, it should be deleted.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}

	this->shaderProgram = other.shaderProgram;
	this->fragmentShader = other.fragmentShader;
	this->vertexShader = other.vertexShader;
	this->loaded = other.loaded;

	other.loaded = false;	//Invalidate the other shader - it's about to have its destructor called, and we need it to not call the glDelete functions.
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other)
{
	if (&other == this)	//Don't do the move if we're moving this shader to itself.
	{
		return *this;
	}
	if (loaded)
	{
		//If the shader we're moving over the top of is an old valid shader, it should be deleted.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}
	this->shaderProgram = other.shaderProgram;
	this->fragmentShader = other.fragmentShader;
	this->vertexShader = other.vertexShader;
	this->loaded = other.loaded;

	other.loaded = false;	//Invalidate the other shader - it's about to have its destructor called, and we need it to not call the glDelete functions.
	return *this;
}

void ShaderProgram::UseShader()
{
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::GetUniformLocation(std::string varName)
{
	return glGetUniformLocation(shaderProgram, varName.c_str());
}

void ShaderProgram::SetUniform(std::string varName, float value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1f(varLoc, value);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec3 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform3f(varLoc, value.x, value.y, value.z);
}

void ShaderProgram::SetUniform(std::string varName, glm::mat4 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniformMatrix4fv(varLoc, 1, GL_FALSE, &value[0][0]);
}