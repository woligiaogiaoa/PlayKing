#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include<string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// ReSharper disable once CppInconsistentNaming
	unsigned int ID;
	// ReSharper disable once IdentifierTypo
	// ReSharper disable once CppInconsistentNaming
	// ReSharper disable once CppInconsistentNaming
	Shader(const char* vertextPath, const char* fragmentPath);

	void use() const;

	//utility functions
	// ReSharper disable once CppInconsistentNaming
	void setBool(const std::string& name,bool value  ) const;
	
	// ReSharper disable once CppInconsistentNaming
	void setInt(const std::string& name,int value  ) const;
	
	// ReSharper disable once CppInconsistentNaming
	void setFloat(const std::string& name,float value  ) const; 

protected:

private:
};


#endif
