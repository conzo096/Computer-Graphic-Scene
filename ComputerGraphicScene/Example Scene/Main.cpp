#include <Barnabus.h>
using namespace BarnabusFramework;

Renderer app;
//Model test;
Model torus;
FreeCamera cam;
Shaders shader;
double cursor_x, cursor_y;
bool init()
{
	glfwSetInputMode(app.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwGetCursorPos(app.GetWindow(), &cursor_x, &cursor_y);
	return true;
}
bool loadContent()
{
	// This method is used to load in all the content required for the scene.


	torus = Model("Torus2.obj");
	torus.GetTransform().SetPosition(glm::vec3(0, 0, 0));
	torus.GetTransform().SetScale(glm::vec3(1, 1, 1));
	shader.CreateShader("..\\Shaders\\BasicVert.vert",
		"..\\Shaders\\BasicFrag.frag");
	cam = FreeCamera();
	cam.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	cam.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	cam.SetProjection(glm::quarter_pi<float>(), app.GetWindowRatio(), 2.414f, 1000.0f);

	return true;
}

bool update(float deltaTime)
{
	// The ratio of pixels to rotation - remember the fov
	float ratio_width = glm::quarter_pi<float>() / static_cast<float>(app.GetWindowWidth());
	float ratio_height = glm::quarter_pi<float>() / static_cast<float>(app.GetWindowHeight());
	// Stores last updates cursor position as well as updating this frames cursor position.
	double current_x,current_y;
	// Get cursor position.
	glfwGetCursorPos(app.GetWindow(), &current_x, &current_y);
	// Calculate delta of cursor positions from last frame
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios - gets actual change in orientation
	delta_x *= ratio_width;
	delta_y *= ratio_height;
	cam.Rotate(static_cast<float>(delta_x), static_cast<float>(-delta_y)); // flipped y to revert the invert.
	if (glfwGetKey(app.GetWindow(), GLFW_KEY_W))
		cam.Move(glm::vec3(0.0f, 0.0f, 5.0f)*deltaTime);
	if (glfwGetKey(app.GetWindow(), GLFW_KEY_S))
		cam.Move(glm::vec3(0.0f, 0.0f, -5.0f)*deltaTime);
	if (glfwGetKey(app.GetWindow(), GLFW_KEY_A))
		cam.Move(glm::vec3(-5.0f, 0.0f, 0.0f)*deltaTime);
	if (glfwGetKey(app.GetWindow(), GLFW_KEY_D))
		cam.Move(glm::vec3(5.0f, 0.0f, 0.0f)*deltaTime);

	cam.Update(deltaTime);
	glfwGetCursorPos(app.GetWindow(), &cursor_x, &cursor_y);

	return true;
}
bool render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glm::mat4 M = torus.GetTransform().TransformMatrix();
	glm::mat4 V = cam.GetView();
	glm::mat4 P = cam.GetProjection();
	glm::mat4 MVP = P*V*M;
	// Select what shader you want to use.
	glUseProgram(shader.GetId());
	glUniformMatrix4fv(shader.GetUniformLocation("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	torus.Render();
	return true;
}


void main()
{
	app = Renderer();
	// Initalise the OpenGL framework;
	app.SetInit(init);
	app.SetContent(loadContent);
	app.SetUpdate(update);
	app.SetRender(render);
	app.Run();
}