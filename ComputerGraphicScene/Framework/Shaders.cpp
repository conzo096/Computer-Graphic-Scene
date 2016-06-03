#include "stdafx.h"
#include "Shaders.h"


namespace BarnabusFramework
{
	Shaders::Shaders()
	{
	}

	Shaders::~Shaders()
	{
	}

	std::string Shaders::ReadShader(char * filename)
	{
		std::string shaderCode;
		std::ifstream file(filename, std::ios::in);

		if (!file.good())
		{
			std::cerr << "Can't read file " << filename << std::endl;
			std::terminate();
		}
		file.seekg(0, std::ios::end);
		shaderCode.resize((unsigned int)file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&shaderCode[0], shaderCode.size());
		file.close();
		return shaderCode;
	}

	GLuint Shaders::BuildShader(GLenum shaderType, std::string source, char * shaderName)
	{
		// Used to check shader is built properly.
		int compile_result = 0;
		// Create a new shader.
		GLuint shader = glCreateShader(shaderType);
		const char *shader_code_ptr = source.c_str();
		const int shader_code_size = source.size();

		glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
		// Build shader.
		glCompileShader(shader);
		// Check shader is built properly.
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
		// Check Shader build correctly.
		if (compile_result == GL_FALSE)
		{
			int info_log_length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> shader_log(info_log_length);
			glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
			std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
			return 0;
		}
		return shader;
	}
	GLuint Shaders::CreateShader(char * vertexFilename, char * fragmentFilename)
	{
		// Read shader files and save code.
		std::string vertexShader = ReadShader(vertexFilename);
		std::string fragmentShader = ReadShader(fragmentFilename);

		GLuint vertex_shader = BuildShader(GL_VERTEX_SHADER, vertexShader, "vert shader");
		GLuint fragment_shader = BuildShader(GL_FRAGMENT_SHADER, fragmentShader, "frag shader");

		int link_result = 0;
		// Create the program handle, attatch the shaders and link it.
		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &link_result);
		// Check for link errors.
		if (link_result == GL_FALSE)
		{
			int info_log_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> program_log(info_log_length);
			glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
			std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
			return 0;
		}
		return program;
	}
}