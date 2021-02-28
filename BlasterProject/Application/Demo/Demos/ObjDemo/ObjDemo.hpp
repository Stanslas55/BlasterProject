#pragma once

#include <sstream>
#include "SDL.h"
#include "Vector3/Vector3.hpp"

#include "Application/Demo/Demo.hpp"

class ObjDemo : public Demo {

private:

	Scene m_scene;

	Ray* m_rays;

	Uint32* m_pixels;

	std::string m_pathModel;
	Material* m_materialModel = nullptr;
	Vector3 m_positionModel = Vector3::zero;

	static const std::string m_cubePath;
	static Material m_cubeMaterial;
	static const Vector3 m_cubePosition;

	static const std::string m_bunnyPath;
	static Material m_bunnyMaterial;
	static const Vector3 m_bunnyPosition;

	static const std::string m_teapotPath;
	static Material m_teapotMaterial;
	static const Vector3 m_teapotPosition;

	static const std::string m_suzannePath;
	static Material m_suzanneMaterial;
	static const Vector3 m_suzannePosition;

	static Material m_defaultMaterial;
	static const Vector3 m_defaultPosition;

	std::chrono::high_resolution_clock::time_point m_start;
	std::chrono::high_resolution_clock::time_point m_end;

public:

	ObjDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize);

	~ObjDemo();

	void init();

	void eventHandler(SDL_Event pEvent);

	void update(double pDeltaTime);

	void render();

	bool parametersWindowRender();

};