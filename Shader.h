#pragma once

#include <iostream>
//#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Shader
{
public:
	Shader(string , string);
	~Shader();

	void SetMat4(const GLchar*, glm::mat4);
	void SetVec3(const GLchar*, float, float, float);
	void SetVec3(const GLchar*, glm::vec3);
	void SetInt(const GLchar*, int);
	void SetFloat(const GLchar*, float);
	void UseProgram();

private:
	GLuint shaderProgram;
};

Shader::Shader(string vPath, string fPath)
{
	ifstream vFile(vPath, ios::in);
	ifstream fFile(fPath, ios::in);

	stringstream vStringStream;
	stringstream fStringStream;
	vStringStream << vFile.rdbuf();
	fStringStream << fFile.rdbuf();

	vFile.close();
	fFile.close();

	string vShaderCode = vStringStream.str();
	string fShaderCode = fStringStream.str();

	const char* cVertexCode = vShaderCode.c_str();
	const char* cFragmentCode = fShaderCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &cVertexCode, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &cFragmentCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{

}

void Shader::SetMat4(const GLchar* unstr, glm::mat4 value)
{
	GLint loc = glGetUniformLocation(shaderProgram, unstr);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetInt(const GLchar* unstr, int value)
{
	GLint loc = glGetUniformLocation(shaderProgram, unstr);
	glUniform1i(loc, value);
}

void Shader::SetFloat(const GLchar* unstr, float value)
{
	GLint loc = glGetUniformLocation(shaderProgram, unstr);
	glUniform1f(loc, value);
}

void Shader::SetVec3(const GLchar* unstr, float x, float y, float z)
{
	GLint loc = glGetUniformLocation(shaderProgram, unstr);
	glUniform3f(loc, x, y , z);
}
void Shader::SetVec3(const GLchar* unstr, glm::vec3 value)
{
	GLint loc = glGetUniformLocation(shaderProgram, unstr);
	glUniform3fv(loc, 1, glm::value_ptr(value));
}

void Shader::UseProgram()
{
	glUseProgram(shaderProgram);
}