#include "stdafx.h"
#include "Renderer.h"
namespace BarnabusFramework
{
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
	}


	void Renderer::SetUpOpenGL()
	{
		// initalise glew and glfw liberies.
		// Turn on glewExperimental for...
		if (!glfwInit())
			exit(EXIT_FAILURE);

		// Create a simple window for the Scene.
		currentWindow = glfwCreateWindow(800, 600, "My Scene", NULL, NULL);
		// Make current window the main context.
		glfwMakeContextCurrent(currentWindow);
		glfwGetFramebufferSize(currentWindow, &width, &height);
		// Get window ratio. Need to cast width and height to float for accurate result.
		windowRatio = static_cast<float>(width) / static_cast<float>(height);
		// Set the swap interval.
		glfwSwapInterval(1);
		// Check if window initalised properly.
		if (!currentWindow)
		{
			// If window not initalised, display error and close.
			std::cerr << "ERROR: Window creation failed.\n";
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			exit(EXIT_FAILURE);
		// Initalise background colour. - Currently yellow, because why not.
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

		// Set window hints for GLFW
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		// Enable required server-side GL capability.
		glEnable(GL_PROGRAM_POINT_SIZE);
		// Enable Textures.
		glEnable(GL_TEXTURE_1D);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_CUBE_MAP);
		// Enable seamless cube maps.
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		// Enable blending.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Enable depth testing.
		glEnable(GL_DEPTH_TEST);
		// Enable offsetting - avoids depth conflicts
		glPolygonOffset(1.0f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glEnable(GL_POLYGON_OFFSET_POINT);
		// Enable clipping.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		// Enable smoothing
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_MULTISAMPLE);

	}

	void Renderer::Run()
	{
		SetUpOpenGL();
		// Call the user defined function.
		if (!init())
		{
			std::cout << "User initalisation finished!\n";
		}
		// initalise current time and last time.
		auto currentTime = std::chrono::system_clock::now();
		auto previousTime = std::chrono::system_clock::now();
		// Load the Content required for the scene.
		if (loadContent() != NULL)
		{
			std::cout << "Content loaded!\n";
		}
		// Now Enter a loop that will keep going until the user quits. 
		while (!glfwWindowShouldClose(currentWindow))
		{
			if(glfwGetKey(currentWindow,GLFW_KEY_ESCAPE))
					return glfwSetWindowShouldClose(currentWindow, GL_TRUE);


			// Get current time
			currentTime = std::chrono::system_clock::now();
			// Calculate elapsed time
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
			auto seconds = static_cast<float>(elapsed) / 1000.0f;


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			// Call update function
			if (update != NULL)
			{
				update(seconds);
			}
			// Finally render Scene
			if (render != NULL)
			{
				render();
				// Swap the buffers
				glfwSwapBuffers(currentWindow);

				// Poll events
				glfwPollEvents();
			}// Update previous time with the current time.
			previousTime = currentTime;

		}
		// Once the while loop finishes, the program should close down.
		glfwDestroyWindow(currentWindow);
		// Terminate glfw.
		glfwTerminate();

	}
}