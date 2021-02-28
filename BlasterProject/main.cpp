#pragma once
#include <iostream>
#include <chrono>

#ifndef NDEBUG
//#include <vld.h>
#endif // !NDEBUG

#include "Application/Application.hpp"

int main(int argc, char* argv[]) {
	SDL_SetMainReady();

	Application app = Application();
	app.mainLoop();

	return EXIT_SUCCESS;
}