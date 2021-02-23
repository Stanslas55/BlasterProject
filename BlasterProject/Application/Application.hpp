#pragma once

#include <iostream>
#include "SDL.h"

struct Events {
	SDL_Point mousePosition;
	Uint32 mouseState;
};

class Application {

private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;

	bool _quit = false;

	bool _render = false;

	Events _events;

public:

	Application(int pWidth = 1280, int pHeight = 720);

	~Application();

	int mainLoop();

	void eventHandler();

	void update();

	void render();
};

