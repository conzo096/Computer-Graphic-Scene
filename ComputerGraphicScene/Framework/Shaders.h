#pragma once
namespace BarnabusFramework
{
	class Shaders
	{
	private:
		GLuint id; // The id of the program.
		std::string ReadShader(char *filename);
		GLuint BuildShader(GLenum shaderType,
			std::string source,
			char* shaderName);
	public:
		Shaders();
		~Shaders();
		GLuint GetId() { return id; };
		GLuint GetUniformLocation(char *filename);
		void CreateShader(char* vertexFilename,
			char* fragmentFilename);

	};
}
