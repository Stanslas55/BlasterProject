#pragma once

#include <iostream>
#include "glad/glad.h"
#include "SDL.h"
#include <FreeImage.h>
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/Utils/Utils.hpp"

#include "Scene/Scene.hpp"

#include "Demo/Demos/Demos.h"

class Application {

private:

	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	int m_width;
	int m_height;

	bool _quit = false;

	enum class Page {
		MAIN_MENU,

		REAL_TIME_DEMO,
		COMPLEX_DEMO,
		OBJ_DEMO

	} m_currentPage;

	RGBQUAD* m_frame;

	GLuint m_tex[1];

	ImFont* _fontDefault;
	ImFont* _fontMin;
	ImFont* _fontTitle;
	ImFont* _fontSubtitle;
	
	SDL_Point m_targetDim;

public:

	friend class Demo;

	Scene scene;

	Application(int pWidth = 1280, int pHeight = 720);

	~Application();

	int mainLoop();

	void init();

	void eventHandler();

	void update();

	void render();

	void mainMenu();

	void restore();
};

