#pragma once
#include "stdafx.h"

namespace BarnabusFramework
{
	class FreeCamera
	{
	private:
		// Current position of the camera.
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
		// Up direction of the camera.
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		// translation of camera since the last frame.
		glm::vec3 translation;
		// Current rotation on the x-axis (pitch)
		float pitch = 0.0f;
		// Current rotation on the y-axis (yaw)
		float yaw = 0.0f;
		// The currently built view matrix.
		glm::mat4 view;
		// The currently built projection matrix.
		glm::mat4 projection;
	public:
		FreeCamera();
		~FreeCamera();

		void SetPosition(glm::vec3 pos) { position = pos; };
		void SetTarget(glm::vec3 targ) { target = targ; };
		void SetUp(glm::vec3 u) { up = u; };
		void SetProjection(float fov, float aspect, float near, float far) { projection = glm::perspective(fov, aspect, near, far); };

		glm::vec3 GetPosition() { return position; };
		glm::vec3 GetTarget() { return target; };
		glm::mat4 GetView() { return view; };
		glm::mat4 GetProjection() { return projection; };

		// Plane information?
		void Update(float deltaTime);
		void Move(glm::vec3 movement);
		void Rotate(float deltaYaw, float deltaPitch);
	};
}
