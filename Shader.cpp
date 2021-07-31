#include "Shader.h"

Shader::Shader(const char* vertextPath, const char* fragmentPath)
{
	std::string vertextCode;
	std::string fragemntCode;
	std::ifstream vShaderFIle;
	std::ifstream fShaderFIle;
	vShaderFIle.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fShaderFIle.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	try
	{
		vShaderFIle.open(vertextPath);
		fShaderFIle.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFIle.rdbuf();
		fShaderStream << fShaderFIle.rdbuf();
		vShaderFIle.close();
		fShaderFIle.close();
		vertextCode = vShaderStream.str();
		fragemntCode = fShaderStream.str();
		 
	}
	catch (std::ifstream::failure e)  // NOLINT(misc-throw-by-value-catch-by-reference)
	{
		// ReSharper disable once StringLiteralTypo
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertextCode.c_str();
	const char* fShaderCode = fragemntCode.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);

	glCompileShader(vertex); 
	
	fragment = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);

	glCompileShader(fragment);
	ID = glCreateProgram();
	glAttachShader(ID,vertex);
	glAttachShader(ID,fragment);
	glLinkProgram(ID);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	
}

void Shader::use() const
{
	glUseProgram(ID);
}

// ReSharper disable once CppInconsistentNaming
void Shader::setBool(const std::string& name, const bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, const int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setFloat(const std::string& name, const float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), (value));
}
