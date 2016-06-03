#pragma once
namespace BarnabusFramework
{
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
}
