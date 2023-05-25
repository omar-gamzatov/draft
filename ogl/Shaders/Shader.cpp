#include "Shader.h"

Shader::Shader(const GLchar* vertPath, const GLchar* fragPath) {
	std::string vertCode;
	std::string fragCode;
	std::ifstream vertShaderFile;
	std::ifstream fragShaderFile;

	vertShaderFile.exceptions(std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		vertShaderFile.open(vertPath);
		fragShaderFile.open(fragPath);
		std::stringstream vertStream, fragStream;

		vertStream << vertShaderFile.rdbuf();
		fragStream << fragShaderFile.rdbuf();

		vertShaderFile.close();
		fragShaderFile.close();

		vertCode = vertStream.str();
		fragCode = fragStream.str();
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR::SHADER::SHADER_SOURCE::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar* vertShaderCode = vertCode.c_str();
	const GLchar* fragShaderCode = fragCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertShaderCode, NULL);
	glCompileShader(vertex);
	//handle error
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
	}

	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragShaderCode, NULL);
	glCompileShader(fragment);
	//handle error
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
	}

	//shader programm
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	//handle error
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(this->Program);
}
