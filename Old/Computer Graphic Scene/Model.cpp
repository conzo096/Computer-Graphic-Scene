#include "Model.h"



Model::Model()
{
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	orientation = glm::quat(0, 0, 0, 1);
}

Model::Model(char * filename) : Model()
{
	this->model = ModelManager(std::string(filename));
}

void Model::Scale(glm::vec3 axis)
{
}

void Model::Translate(glm::vec3 translation)
{
	// Add the translation to the current position.
	this->position += translation;
}

void Model::Rotate(float angle, glm::vec3 axis)
{
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
	glBindVertexArray(model.vao);
	if (model.index_buffer != 0)
	{
		// Bind index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.index_buffer);
		// Draw elements
		glDrawElements(model.type, model.indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(model.type, 0, model.vertices);
	}
}

Model::~Model()
{
}
