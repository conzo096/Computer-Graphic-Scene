#pragma once
#include <functional>
class SceneManager
{

private:
	// The Set up function.
	std::function<bool(float)> initScene;
	// The Set up function.
	std::function<bool(float)> loadScene;
	// The update function
	std::function<bool(float)> updateScene;
	// The render function
	std::function<bool(float)> renderScene;
public:
	SceneManager();
	~SceneManager();
	void SetContent(std::function<bool(float)> init) { initScene = init; }
	void SetScene(std::function<bool(float)> content) { loadScene = content; }

	void SetUpdate(std::function<bool(float)> update) { updateScene = update; }
	void SetRender(std::function<bool(float)> render) { renderScene = render; }

	bool LoadContent();
	bool UpdateScene();
	bool RenderScene();
	void RunScene();
};

