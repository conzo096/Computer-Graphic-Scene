#include "stdafx.h"
#include "Transformation.h"

namespace BarnabusFramework
{
	Transformation::Transformation()
	{
		position = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);
	}


	Transformation::~Transformation()
	{
	}
	void Transformation::Rotate(const glm::quat &q)
	{
		orientation = orientation * q;
		orientation = glm::normalize(orientation);
	}

	glm::mat4 Transformation::TransformMatrix()
	{
		/* Order is Rotate * Scale * Translate.
		*
		*/
		glm::mat4 T = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);
		glm::mat4 R = glm::mat4_cast(orientation);
		glm::mat4 RST = T*R*S;
		return RST;
	}
}