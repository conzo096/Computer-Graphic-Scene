#pragma once
#include "stdafx.h"

namespace BarnabusFramework
{
	class Renderer
	{
	private:
		std::function<bool()> init;
		std::function<bool()> loadContent;
		std::function<bool(float)> update;
		std::function<bool()> render;
		// Current window the renderer is using.
		GLFWwindow* currentWindow;
		// The screen dimenions of the current window.
		int width, height;
		float windowRatio;
	public:
		Renderer();
		~Renderer();
		void SetUpOpenGL();
		void SetInit(std::function<bool()> value) { init = value; };
		void SetContent(std::function<bool()> value) { loadContent = value; };
		void SetUpdate(std::function<bool(float)> value) { update = value; };
		void SetRender(std::function<bool()> value) { render = value; };

		GLFWwindow * GetWindow() { return currentWindow; };
		int GetWindowWidth() { return width; };
		int GetWindowHeight() { return height; };
		float GetWindowRatio() { return windowRatio; };


		void Run();
	};
}
