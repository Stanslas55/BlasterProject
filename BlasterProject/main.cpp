#pragma once
#include <iostream>
#include <chrono>
//#include <vld.h>

#include "Vector3/Vector3.hpp"
#include "PrimitiveObjects/PrimitiveObject.h"	

#include "Tests.h"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"

int main(int argc, char* argv[]) {	

	Camera cam(1920, 1080);
	//Camera cam(420 * 4 / 3, 420);

	Scene scene = Scene(cam);

	Sphere* a = new Sphere(Vector3(0.0, -20.0, -50.0), 5.0);
	Sphere* b = new Sphere(Vector3(-20.0, 0.0, -50.0), 20.0);
	Sphere* c = new Sphere(Vector3(30.0, 0.0, -70.0), 5.0);

	scene.addPrimitive(a);
	scene.addPrimitive(b);
	scene.addPrimitive(c);

	FIBITMAP* image = nullptr;

	auto start = std::chrono::high_resolution_clock::now();
	scene.takePictureNaive(&image);
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "elapsed time: " << duration << "ms\n";
	
	FreeImage_Save(FIF_BMP, image, "out.bmp");

	return EXIT_SUCCESS;
}