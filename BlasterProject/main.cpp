#pragma once
#include <iostream>
#include <chrono>

#ifndef NDEBUG
#include <vld.h>
#endif // !NDEBUG

#include "Vector3/Vector3.hpp"
#include "PrimitiveObjects/PrimitiveObject.h"
#include "LightSource/LightSource.hpp"

#include "Tests.h"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"

int main(int argc, char* argv[]) {	

	RGBQUAD black = { 0, 0, 0, 255 };

	Camera cam(1920, 1080, black);
	//Camera cam(1280, 720, black);
	//Camera cam(420 * 4 / 3, 420, black);
	//Camera cam(4, 3, black);

	Scene scene = Scene(cam);

	scene.addPrimitive(
		new Sphere(
			Vector3(-20.0, 0.0, -50.0), 
			10.0, 
			Material(
				{ 255, 0, 0, 255 },
				0.4,
				1.0,
				1.0,
				100.0
			)
		)
	);

	scene.addPrimitive(
		new Sphere(
			Vector3(-10.0, 0.0, -20.0),
			3.0, 
			Material(
				{ 255, 0, 255, 255 },
				0.4,
				0.8,
				0.5,
				100.0
			)
		)
	);

	scene.addPrimitive(
		new Tri(
			Vector3(-20, 0, -50),
			Vector3(10, 10, -30),
			Vector3(0, -5, -20),
			Material(
				{ 255, 0, 0, 255 },
				0.4,
				0.8,
				0.5,
				100.0
			)
		)
	);

	//scene.addPrimitive(new Sphere(Vector3(20.0, -10.0, -40.0), 0.1, Material({0, 0, 0, 255})));

	/*if (false) {
		scene.addLightSource(
			new DirectionalLight(
				Vector3(-20.0, 0.0, -80.0),
				{ 255, 255, 255, 255 }
			)
		);
	}
	else {
		scene.addLightSource(
			new PointLight(
				Vector3(0.0, 0.0, -20.0),
				{ 255, 255, 255, 255 }
			)
		);
	}*/
	
	scene.addLightSource(
		new DirectionalLight(
			Vector3(-0.5, 0.0, 1.0),
			{ 255, 255, 255, 255 }
		)
	);

	FIBITMAP* image = nullptr;

	auto start = std::chrono::high_resolution_clock::now();
	scene.takePictureNaive(&image);
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "elapsed time: " << duration << "ms\n";
	
	FreeImage_Save(FIF_PNG, image, "out.png");

	return EXIT_SUCCESS;
}