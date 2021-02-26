#pragma once

#include <chrono>

#include "SDL.h"
#include <glad/glad.h>
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/Utils/Utils.hpp"
#include "Scene/Scene.hpp"

static Uint32* m_pixels;
static int _res;
static SDL_Event e;
static bool _quit;

struct Events {
	SDL_Point mousePosition = { 0, 0 };
	Uint32 mouseState = 0;
};

class Demo {

protected:

	SDL_Window* m_windowScene;				/*< Window of the scene. */
	SDL_Point m_windowSceneSize;			/*< Size of m_windowScene. Should be the same as m_scene's camera. */
	SDL_Renderer* m_rendererScene;			/*< Renderer of the scene. */
	SDL_Texture* m_textureScene;			/*< Texture of the scene. */

	SDL_Window* m_windowParams;				/*< Parameter window. */
	SDL_Point m_windowParamsize;			/*< Size of m_windowParams. */
	SDL_GLContext m_glParams;				/*< OpenGL context of the parameter window. */

	bool _update = true;					/*< Update boolean. */
	bool _render = true;					/*< Render boolean. */
	
	struct Events {
		SDL_Point mousePosition = { 0, 0 };
		Uint32 mouseState = 0;
	} _events;								/*< Event structure. */

	SDL_PixelFormat* m_format;				/*< Pixel format. */

	double m_deltaTime;						/*< Delta time between two frames. */

public:

	Demo(SDL_Window* pWindow, SDL_GLContext& glContext, std::string pSceneName, SDL_Point pSceneSize, SDL_Point pParamSize);

	~Demo();

	virtual void init() = 0;

	int mainLoop();

	void eventLoop();

	virtual void eventHandler(SDL_Event pEvent);

	virtual void update(double pDeltaTime) = 0;

	virtual void render() = 0;

	void parametersManager(SDL_Event* e);

	virtual void parametersWindowRender();
};

