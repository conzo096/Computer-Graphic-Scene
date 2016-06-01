// Main class for computer graphic scene.
#define GL_FORCE_RADIANS
#define GLFW_INCLUDE_GLU
#define GLFW_DLL
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
double cursor_x, cursor_y;

void keyManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// This method handles key presses.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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
	width = width;
	height =height;
	windowRatio = static_cast<float>(width) / static_cast<float>(height);
	// initalise background colour.
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
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
	// Enable textures
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_CUBE_MAP);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
	// Enable smoothing
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_MULTISAMPLE);
	// Enable offsetting - avoids depth conflicts
	glPolygonOffset(1.0f, 1.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glEnable(GL_POLYGON_OFFSET_POINT);
	// Enable seamless cube maps
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glfwSetKeyCallback(window, keyManager);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(window, &cursor_x, &cursor_y);
	return true;
}
bool LoadContent()
{
	model = Model("Torus2.obj");
	model.position = vec3(-10, 0, -1);
	Shaders shaderLoader;
	camera = Camera();
	// This method initalizes the free camera.
	camera.position = glm::vec3(-10.0f, 0.0f, 0.0f);
	camera.target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera.projection = glm::perspective(glm::quarter_pi<float>(), windowRatio, 2.414f, 1000.0f);

	shader = shaderLoader.CreateShader("Shaders\\BasicVert.vert",
		"Shaders\\BasicFrag.frag");

	return true;
}
bool Update(float deltaTime)
{
	glViewport(0, 0, width, height);
	// Stores last updates cursor position as well as updating this frames cursor position.
	double current_x;
	double current_y;
	// Get cursor position.
	glfwGetCursorPos(window, &current_x, &current_y);
	// Calculate delta of cursor positions from last frame
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios - gets actual change in orientation
	delta_x *= width;
	delta_y *= height;
	// Rotate the free camera.
	camera.Rotate(static_cast<float>(delta_x), static_cast<float>(-delta_y)); // flipped y to revert the invert.
	if (glfwGetKey(window, GLFW_KEY_W))
		camera.Move(glm::vec3(0.0f, 0.0f, 5.0f) * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S))
		camera.Move(glm::vec3(0.0f, 0.0f, -5) * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A))
		camera.Move(glm::vec3(-5.0f, 0.0f, 0.0f) * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D))
		camera.Move(glm::vec3(5.0f, 0.0f, 0.0f) * deltaTime);

	camera.Update(deltaTime);
	if (glfwGetKey(window,GLFW_KEY_1))
		model.scale += glm::vec3(1, 1, 1);
	return true;
}

bool Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glm::mat4 M = model.TransformMatrix();
	glm::mat4 V = camera.view;
	glm::mat4 P = camera.projection;
	glm::mat4 MVP = P*V*M;
	// Select what shader you want to use.
	glUseProgram(shader);
	GLint loc = glGetUniformLocation(shader, "MVP");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MVP));
	model.Render();

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
