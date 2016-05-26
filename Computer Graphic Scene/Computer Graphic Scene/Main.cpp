// Main class for computer graphic scene.
#include "include\GL\glew.h"
#include "include\GLFW\glfw3.h"
#include "Model.h"
#include "Shaders.h"
#include "Camera.h"
#include "include\glm\glm.hpp"
#include "include\glm\gtc\type_ptr.hpp"
#include <iostream>
#include <chrono>
using namespace std;
using namespace glm;
GLFWwindow* window;
int width, height;
float windowRatio;
Model model;
Camera camera;
GLuint shader;

void keyManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// This method handles key presses.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		model.scale += glm::vec3(1, 1, 1);
}

bool Initalize()
{
	if (!glewInit())
		exit(EXIT_FAILURE);
	glewExperimental = GL_TRUE;
	if (!glfwInit())
		exit(EXIT_FAILURE);
	// Create window.
	window = glfwCreateWindow(800, 600, "My scene", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &width, &height);
	windowRatio = width / (float)height;
	// initalise background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Check window is initalized.
	if (!window)
	{
		std::cerr << "ERROR: Window creation failed.\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// need to make current window.
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glfwSetKeyCallback(window, keyManager);
	return true;
}
bool LoadContent()
{
	model = Model("Torus2.obj");
	Shaders shaderLoader;
	camera = Camera();
	// This method initalizes the free camera.
	camera.position = glm::vec3(0.0f, 8.0f, 0.0f);
	camera.target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera.projection = glm::perspective(glm::quarter_pi<float>(), windowRatio, 2.414f, 1000.0f);
	
	
	shader = shaderLoader.CreateShader("Shaders\\BasicVert.vert",
		"Shaders\\BasicFrag.frag");

	return true;
}
bool Update(float deltaTime)
{
	glViewport(0, 0, width, height);
	camera.Update(deltaTime);
	return true;
}

bool Render()
{
	glm::mat4 M = model.TransformMatrix();
	glm::mat4 V = camera.view;
	glm::mat4 P = camera.projection;
	glm::mat4 MVP = P*V*M;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	// Select what shader you want to use.
	glUseProgram(shader);
	GLint loc = glGetUniformLocation(shader, "mvp");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MVP));

	// Bind the vertex array object for the 
	glBindVertexArray(model.model.vao);
	if (model.model.index_buffer != 0)
	{
		// Bind index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,model.model.index_buffer);
		// Draw elements
		glDrawElements(GL_TRIANGLES,model.model.indicesCount , GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, model.model.vertices);
	}

//	glLoadIdentity();
//	glOrtho(-windowRatio, windowRatio, -1.f, 1.f, 1.f, -1.f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
//	glBegin(GL_TRIANGLES);
//	glColor3f(1.f, 0.f, 0.f);
//	glVertex3f(-0.6f, -0.4f, 0.f);
//	glColor3f(0.f, 1.f, 0.f);
//	glVertex3f(0.6f, -0.4f, 0.f);
//	glColor3f(0.f, 0.f, 1.f);
//	glVertex3f(0.f, 0.6f, 0.f);
//	glEnd();
	glfwSwapBuffers(window);
	glfwPollEvents();
	return true;
}

bool Run()
{
	LoadContent();
	// Monitor the elapsed time per frame
	auto current_time_stamp = std::chrono::system_clock::now();
	auto prev_time_stamp = std::chrono::system_clock::now();
	while (!glfwWindowShouldClose(window))
	{
		// Get current time
		current_time_stamp = std::chrono::system_clock::now();
		// Calculate elapsed time
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_stamp - prev_time_stamp).count();
		auto seconds = static_cast<float>(elapsed) / 1000.0f;
		Update(seconds);
		Render();
		prev_time_stamp = current_time_stamp;
	}
	glfwDestroyWindow(window);
	// Finished with glfw.
	glfwTerminate();
	return true;
}

void main()
{
	Initalize();
	Run();
}
