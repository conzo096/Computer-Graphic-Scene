/* Model Manager Class by Conner Weatherston. Last edited 17/05/2016
 * This class loads in a 3D model Object.
 *
 */
#pragma once
#include "include\GL\glew.h"
#include "include\GLFW\glfw3.h"
#include "include\glm\glm.hpp"
#include "include\assimp\Importer.hpp"  
#include "include\assimp\scene.h"       
#include "include\assimp\postprocess.h"    
#include <vector>
#include <map>
#include <assert.h>
#include <iostream>
#include <fstream>

enum BUFFER_INDEXES
{
	// The position data
	POSITION_BUFFER = 0,
	// The colour data
	COLOUR_BUFFER = 1,
	// The surface normals
	NORMAL_BUFFER = 2,
	// The binormals for the surfaces
	BINORMAL_BUFFER = 3,
	// The tangents for the surfaces
	TANGENT_BUFFER = 4,
	// Texture coordinates 0
	TEXTURE_COORDS_0 = 10,
	// Texture coordinates 1
	TEXTURE_COORDS_1 = 11,
	// Texture coordinates 2
	TEXTURE_COORDS_2 = 12,
};



class ModelManager
{
public:
	ModelManager();
	ModelManager(std::string &filename);
	~ModelManager();
	// The OpenGL ID of the vertex array object
	GLuint vao;
	// The OpenGL IDs of the buffers used within the vertex array object
	std::map<GLuint, GLuint> buffers;
	// The OpenGL ID of the index buffer
	GLuint index_buffer;
	// The number of vertices in the model
	GLuint vertices;
	// The number of indices
	GLuint indicesCount;
	//GLuint model;
	GLenum type;

	// Methods for mesh.
	void loadMesh(const std::string &filename);
	bool AddBuffer(const std::vector<glm::vec4>  &buffer, GLuint index);
	bool AddBuffer(const std::vector<glm::vec3>  &buffer, GLuint index);
	bool AddBuffer(const std::vector<glm::vec2>  &buffer, GLuint index);
	bool add_index_buffer(const std::vector<GLuint> &buffer);
};
