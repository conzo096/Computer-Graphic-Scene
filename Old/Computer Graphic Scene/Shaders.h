/* Shader class by Conner Weatherston. Last edited 17/05/2016.
 * This class handles the creation, linking, building and deletion
 * of OpenGL shaders. 
 */
#pragma once
#include "include\GL\glew.h"
#include <iostream>
#include <vector>
#include<iostream>
#include<fstream>
class Shaders
{
private:
	std::string ReadShader(char *filename);
	GLuint BuildShader(GLenum shaderType,
		std::string source,
		char* shaderName);
public:
	Shaders();
	~Shaders();
	GLuint CreateShader(char* vertexFilename,
		char* fragmentFilename);
};

