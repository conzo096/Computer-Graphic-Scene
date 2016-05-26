#include "Model.h"



Model::Model()
{
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	orientation = glm::quat(1, 0, 0, 0);
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


Model::~Model()
{
}
