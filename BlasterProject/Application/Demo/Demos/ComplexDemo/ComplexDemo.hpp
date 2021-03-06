#pragma once

#include <sstream>
#include "SDL.h"
#include "Vector3/Vector3.hpp"

#include "Application/Demo/Demo.hpp"

class ComplexDemo : public Demo {

private:

	Scene m_scene;

	Ray* m_rays;

	Uint32* m_pixels;

	std::chrono::high_resolution_clock::time_point m_start;
	std::chrono::high_resolution_clock::time_point m_end;

public:

	ComplexDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize);

	~ComplexDemo();

	void init();

	void eventHandler(SDL_Event pEvent);

	void update(double pDeltaTime);

	void render();

	bool parametersWindowRender();

};