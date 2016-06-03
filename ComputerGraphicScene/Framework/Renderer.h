#pragma once
#include "stdafx.h"

namespace BarnabusFramework
{
	class Renderer
	{
	private:
		std::function<bool()> init;
		std::function<bool()> loadContent;
		std::function<bool(float deltaTime)> update;
		std::function<bool()> render;
		// Current window the renderer is using.
		GLFWwindow * currentWindow;
		// The screen dimenions of the current window.
		int width, height;
		float windowRatio;
	public:
		Renderer();
		~Renderer();
		void SetUpOpenGL();
		void SetInit(std::function<bool()> value) { init = value; };
		void SetContent(std::function<bool()> value) { loadContent = value; };
		void SetUpdate(std::function<bool(float deltaTime)> value) { update = value; };
		void SetRender(std::function<bool()> value) { render = value; };
		void Run();
	};
}
