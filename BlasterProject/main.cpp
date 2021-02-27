#pragma once
#include <iostream>
#include <chrono>

#define FREEIMAGE_COLORORDER FREEIMAGE_COLORORDER_RGB

#ifndef NDEBUG
//#include <vld.h>
#endif // !NDEBUG

#include "Vector3/Vector3.hpp"
#include "PrimitiveObjects/PrimitiveObject.h"
#include "LightSource/LightSource.hpp"

#include "Tests.h"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Application/Demo/Demos/Demos.h"
#include "Application/Application.hpp"

int main(int argc, char* argv[]) {
	SDL_SetMainReady();

	Application app = Application();
	app.mainLoop();

	return EXIT_SUCCESS;
}