#pragma once
#include "Transformation.h"
#include "Material.h"
namespace BarnabusFramework
{
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
	class Model
	{

	private:
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

		// Tranformation information
		Transformation transform;
		Material material;

	public:
		Model();
		Model(const std::string &filename);
		~Model();

	
		void Render(); // Renders the mesh.
		// 
		bool AddBuffer(const std::vector<glm::vec4>  &buffer, GLuint index);
		bool AddBuffer(const std::vector<glm::vec3>  &buffer, GLuint index);
		bool AddBuffer(const std::vector<glm::vec2>  &buffer, GLuint index);
		bool AddIndexBuffer(const std::vector<GLuint> &buffer);

		// Accessors.
		void SetType(GLenum t) { type = t; };
		void SetTransform(Transformation trans) { transform = trans; };
		void SetMaterial(Material mat) { material = mat; };


		Transformation GetTransform() { return transform; };
		Material GetMaterial() { return material; };
	};
}
