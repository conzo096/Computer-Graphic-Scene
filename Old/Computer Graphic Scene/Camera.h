#pragma once
#include "include\glm\glm.hpp"
#include "include\glm\gtx\euler_angles.hpp"
#include "include\glm\gtc\matrix_transform.hpp"
#include "include\glm\glm.hpp"
#include "include\glm\gtc\type_ptr.hpp"
#include <iostream>

using namespace glm;
class Camera
{
public:
	glm::vec3 position;
	// direction/target same?
	glm::vec3 direction;
	glm::vec3 target;
	// Up direction of the camera.a
	glm::vec3 up;
	// translation of camera since the last frame.
	glm::vec3 translation;
	// Current rotation on the x-axis (pitch)
	float pitch = 0.0f;
	// Current rotation on the y-axis (yaw)
	float yaw = 0.0f;
	// The currently built view matrix since the last frame update
	glm::mat4 view;
	// The currently built projection matrix since the last call to set_projection
	glm::mat4 projection;
	// Plane information?
	Camera();
	~Camera();
	void Update(float deltaTime);
	void Move(glm::vec3 movement);
	void Rotate(float deltaYaw, float deltaPitch);
};

