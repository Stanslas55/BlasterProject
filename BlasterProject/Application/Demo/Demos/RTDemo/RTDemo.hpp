#pragma once

#include <sstream>
#include "SDL.h"
#include "Vector3/Vector3.hpp"

#include "Application/Demo/Demo.hpp"

class RTDemo : public Demo {

private:

	Scene m_scene;

	Vector3 m_polarSystem;
	Vector3 m_centerOfRotation;

	Collision* m_collisions;

public:

	RTDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize);

	~RTDemo();

	void init();

	void eventHandler(SDL_Event pEvent);

	void update(double pDeltaTime);

	void render();

	bool parametersWindowRender();
};