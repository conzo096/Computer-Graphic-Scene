#include "stdafx.h"
#include "Model.h"

namespace BarnabusFramework
{
	Model::Model()throw(...) :
		vao(0),
		vertices(0),
		index_buffer(0),
		indicesCount(0),
		type(GL_TRIANGLES)
	{
		glewInit();
	}

	Model::Model(std::string & filename) : Model()
	{
		LoadMesh(filename);
	}


	Model::~Model()
	{
	}

	void Model::LoadMesh(const std::string & filename)
	{
		// Create model importer
		Assimp::Importer loadModel;
		// Read in the model data
		const aiScene *model = loadModel.ReadFile(filename, aiProcess_Triangulate
			| aiProcess_GenSmoothNormals
			| aiProcess_ValidateDataStructure
			| aiProcess_FindInvalidData);
		// Check that data has been read in correctly
		if (!model)
		{
			// Display error
			std::cerr << "Data incorrectly read in at" << filename << std::endl;
			std::cerr << loadModel.GetErrorString() << std::endl;
			// Throw exception
			throw std::runtime_error("Error reading in model file");
		}
		// Vectors to store model data.
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> tex_coords;
		std::vector<glm::vec4> colours;
		std::vector<GLuint> indices;
		int vertex_begin = 0;
		// Loop throw each sub-mesh.
		for (unsigned int i = 0; i < model->mNumMeshes; i++)
		{
			// Get the sub-mesh.
			aiMesh *modelMesh = model->mMeshes[i];
			// get the vertex positions.
			for (unsigned int j = 0; j < modelMesh->mNumVertices; j++)
			{
				aiVector3D position = modelMesh->mVertices[j];
				// Convert the aiVector3D to glm vector3.
				glm::vec3 convertedPosition = glm::vec3(position.x, position.y, position.z);
				// push back to positions vector.
				positions.push_back(convertedPosition);
			}

			// Check if there is normals data in sub-mesh.
			if (modelMesh->HasNormals() == true)
			{
				for (unsigned int j = 0; j < modelMesh->mNumVertices; j++)
				{
					aiVector3D normal = modelMesh->mNormals[j];
					// Convert from aivector3D to glm vector3.
					glm::vec3 convertedNormal = glm::vec3(normal.x, normal.y, normal.z);
					// push back to normals vector.
					normals.push_back(convertedNormal);
				}
			}
			// Check if sub-mesh has texture information.
			if (modelMesh->HasTextureCoords(0) == true)
			{
				for (unsigned int j = 0; j < modelMesh->mNumVertices; j++)
				{
					aiVector3D textureCoords = modelMesh->mTextureCoords[0][j];
					// Convert texture coordinates.
					glm::vec2 convertedTextureCoords = glm::vec2(textureCoords.x, textureCoords.y);
					// push back to texCoords.
					tex_coords.push_back(convertedTextureCoords);
				}
			}
			// Check sub-mesh for colour information.
			if (modelMesh->HasVertexColors(0) == true)
			{
				for (unsigned int j = 0; j < modelMesh->mNumVertices; j++)
				{
					aiColor4D VertexColour = modelMesh->mColors[0][j];
					// convert from aiColour4D to glm vec4.
					glm::vec4 convertedVertexColour = glm::vec4(VertexColour.r, VertexColour.g, VertexColour.b, VertexColour.a);
					colours.push_back(convertedVertexColour);
				}
			}
			else if (modelMesh->HasVertexColors(0) == false)
			{
				// No colour, push back grey.
				colours.push_back(glm::vec4(0.7, 0.7, 0.7, 1));
			}
			// If we have face information, then add to index buffer
			if (modelMesh->HasFaces() == true)
			{
				for (unsigned int k = 0; k < modelMesh->mNumFaces; k++)
				{
					aiFace modelFace = modelMesh->mFaces[k];
					for (unsigned int l = 0; l < 3; l++)
						indices.push_back(vertex_begin + modelFace.mIndices[l]);
				}
			}
			vertex_begin += modelMesh->mNumVertices;
		}
		// Add position, normals, texture_coordinates and colour info to correct buffers.
		AddBuffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
		AddBuffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);
		if (normals.size() != 0)
			AddBuffer(normals, BUFFER_INDEXES::NORMAL_BUFFER);
		if (tex_coords.size() != 0)
			AddBuffer(tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
		if (indices.size() != 0)
			AddIndexBuffer(indices);
	}

	bool Model::AddBuffer(const std::vector<glm::vec4>& buffer, GLuint index)
	{
		// Check if vertex array object initialised
		if (vao == 0)
			// Create the vertex array object
			glGenVertexArrays(1, &vao);
		// If we have no vertices yet, set the vertices to the size of this buffer
		if (vertices == 0)
			vertices = buffer.size();
		// Now add buffer to the vertex array object.  Bind the vertex array object
		glBindVertexArray(vao);
		// Generate buffer with OpenGL
		GLuint id;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		// Set the buffer data
		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), &buffer[0], GL_STATIC_DRAW);
		// Set the vertex pointer and enable
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(index);
		// Add buffer to map
		buffers[index] = id;
		return true;
	}
	bool Model::AddBuffer(const std::vector<glm::vec3>& buffer, GLuint index)
	{
		// Check if vertex array object initialised
		if (vao == 0)
			// Create the vertex array object
			glGenVertexArrays(1, &vao);
		// If we have no vertices yet, set the vertices to the size of this buffer
		if (vertices == 0)
			vertices = buffer.size();
		// Now add buffer to the vertex array object.  Bind the vertex array object
		glBindVertexArray(vao);
		// Generate buffer with OpenGL
		GLuint id;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		// Set the buffer data
		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec3), &buffer[0], GL_STATIC_DRAW);
		// Set the vertex pointer and enable
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(index);
		// Add buffer to map
		buffers[index] = id;
		return true;
	}
	bool Model::AddBuffer(const std::vector<glm::vec2>& buffer, GLuint index)
	{
		// Check if vertex array object initialised
		if (vao == 0)
			// Create the vertex array object
			glGenVertexArrays(1, &vao);
		// If we have no vertices yet, set the vertices to the size of this buffer
		if (vertices == 0)
			vertices = buffer.size();
		// Now add buffer to the vertex array object.  Bind the vertex array object
		glBindVertexArray(vao);
		// Generate buffer with OpenGL
		GLuint id;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		// Set the buffer data
		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec2), &buffer[0], GL_STATIC_DRAW);
		// Set the vertex pointer and enable
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(index);
		// Add buffer to map
		buffers[index] = id;
		return true;
	}

	bool Model::AddIndexBuffer(const std::vector<GLuint>& buffer)
	{
		//	 Set indices to buffer size
		indicesCount = buffer.size();
		// Bind vertex array object
		glBindVertexArray(vao);
		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), &buffer[0], GL_STATIC_DRAW);
		return true;
	}

	void Model::Scale(glm::vec3 axis)
	{
		scale = axis;
	}

	void Model::Translate(glm::vec3 translation)
	{
		// Add the translation to the current position.
		this->position += translation;
	}

	void Model::Rotate(const glm::vec3 &rotation)
	{
		glm::quat rot(rotation);
		Rotate(rot);
	}
	void Model::Rotate(const glm::quat &q)
	{
		orientation = orientation * q;
		orientation = glm::normalize(orientation);
	}

	glm::mat4 Model::TransformMatrix()
	{
		/* Order is Rotate * Scale * Translate.
		*
		*/
		glm::mat4 T = glm::translate(glm::mat4(1), position);
		glm::mat4 S = glm::scale(glm::mat4(1), scale);
		glm::mat4 R = glm::mat4_cast(orientation);
		glm::mat4 RST = T*R*S;
		return RST;
	}

	void Model::Render()
	{
		// Bind the vertex array object for the 
		glBindVertexArray(vao);
		if (index_buffer != 0)
		{
			// Bind index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
			// Draw elements
			glDrawElements(type, indicesCount, GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(type, 0, vertices);
		}
	}
};