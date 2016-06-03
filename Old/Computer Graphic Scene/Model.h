/* Model class by Conner Weatherston. Last edited 17/05/2016.
 * This class is for a model object in the scene. It stores its own matrices and material information.
 */
#pragma once
#include "ModelManager.h"
#include "include\glm\gtc\quaternion.hpp"
#include "include\glm\gtc\matrix_transform.hpp"
class Model
{
	//ModelTransforms matrixInfo;
	//Materials materialsInfo;
public:
	ModelManager model;
	glm::vec3 scale;
	glm::quat orientation;
	glm::vec3 position;
	// Constructors.
	Model();
	Model(char* filename);
	void Scale(glm::vec3 axis);
	void Translate(glm::vec3 translation);
	void Rotate(float angle, glm::vec3 axis);
	glm::mat4 TransformMatrix();
	void Render();
	//Model(char* filename);
	//Model(char* filename);
	//Model(char* filename);
	~Model();


};

