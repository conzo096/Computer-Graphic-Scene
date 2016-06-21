/* By Conner Weatherston. Last edited 17/07/2016.
 * This class contains methods and variables for scaling, rotating and translating an object.
 */
#pragma once
namespace BarnabusFramework
{
	class Transformation
	{
		// Transformations for model.
		glm::vec3 scale;
		glm::quat orientation;
		glm::vec3 position;
	public:
		Transformation();
		~Transformation();

		void SetPosition(glm::vec3 pos) { position = pos; };

		void SetScale(glm::vec3 axis) { scale = axis; };
		void Translate(glm::vec3 translation) { position += translation; };
		void SetRotate(const glm::vec3 &rotation) { Rotate(glm::quat(rotation)); };
		void Rotate(const glm::quat & q);

		glm::mat4 TransformMatrix();
	};
}
