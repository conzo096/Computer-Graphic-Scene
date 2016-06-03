#include <Barnabus.h>
using namespace BarnabusFramework;

Renderer app;
Model test;

bool init()
{
	return true;
}
bool loadContent()
{
	test.SetType(GL_QUADS);
	std::vector<glm::vec3> positions
	{
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f)
	};
	test.AddBuffer(positions,BUFFER_INDEXES::POSITION_BUFFER);
	std::vector<glm::vec2> tex_coords
	{
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	};
	test.AddBuffer(tex_coords,BUFFER_INDEXES::TEXTURE_COORDS_0);
	test.SetPosition(glm::vec3(0, 0, 0));

	return true;
}

bool update(float deltaTime)
{
	return true;
}
bool render()
{
	return true;
	test.Render();
}


void main()
{
	app = BarnabusFramework::Renderer();
	// Initalise the OpenGL framework;
	app.SetUpOpenGL();
	app.SetInit(init);
	app.SetContent(loadContent);
	app.SetUpdate(update);
	app.SetRender(render);
	app.Run();
}