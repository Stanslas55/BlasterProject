#include "ComplexDemo.hpp"

void addTetrahedron(Scene& pScene, const Vector3& pPosition) {
	Vector3 A = pPosition + Vector3(sqrt(8.0 / 9.0), 0.0, -1.0 / 3.0);
	Vector3 B = pPosition + Vector3(-sqrt(2.0 / 9.0), sqrt(2.0 / 3.0), -1.0 / 3.0);
	Vector3 C = pPosition + Vector3(-sqrt(2.0 / 9.0), -sqrt(2.0 / 3.0), -1.0 / 3.0);
	Vector3 D = pPosition + Vector3(0.0, 0.0, 1.0);

	pScene.addPrimitive(
		new Tri(
			A, B, C,
			Material::randomMaterial()
		)
	);
	pScene.addPrimitive(
		new Tri(
			B, C, D,
			Material::randomMaterial()
		)
	);
	pScene.addPrimitive(
		new Tri(
			C, D, A,
			Material::randomMaterial()
		)
	);
	pScene.addPrimitive(
		new Tri(
			D, A, B,
			Material::randomMaterial()
		)
	);
}

ComplexDemo::ComplexDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize) : Demo(pWindow, pGlContext, "Complex Demo", pSceneSize, { 400, 600 }), m_scene(Camera(pSceneSize.x, pSceneSize.y)) {
	m_rays = nullptr;
	m_pixels = nullptr;
}

ComplexDemo::~ComplexDemo() {
	delete[] m_rays;
	m_rays = nullptr;
}

void ComplexDemo::init() {
	m_rays = m_scene.getRayArray();

	_render = true;
}

void ComplexDemo::eventHandler(SDL_Event pEvent) {

}

void ComplexDemo::update(double pDeltaTime) {

	if (!_render)
		return;

#pragma omp master 
	{
		// Update here
		// Scene construction

		m_start = std::chrono::high_resolution_clock::now();

		m_scene.reset();

		// Tetrahedrons
		{
			for (int i = 0; i < 100; i++) {

				Vector3 pos;

				pos.z() = -(30.0 + double(rand() / double(RAND_MAX)) * 50.0);
				pos.x() = (double(rand() / double(RAND_MAX)) * 2.0 - 1.0) * 60.0;
				pos.y() = (double(rand() / double(RAND_MAX)) * 2.0 - 1.0) * 30.0;

				addTetrahedron(m_scene, pos);
			}
		}

		// Spheres
		{
			for (int i = 0; i < 100; i++) {
				m_scene.addPrimitive(
					new Sphere(
						Vector3(
							(double(rand() / double(RAND_MAX)) * 2.0 - 1.0) * 60.0,
							(double(rand() / double(RAND_MAX)) * 2.0 - 1.0) * 30.0,
							-(100.0 + double(rand() / double(RAND_MAX)) * 50.0)
						),
						double(rand() / double(RAND_MAX)) * 10.0,
						Material::randomMaterial()
					)
				);
			}
		}

		// Teapot
		{
			m_scene.addModel(
				new Model(
					Vector3(6.0, -5.0, -20.0),
					"ObjFiles/teapot.obj",
					Material::randomMaterial()
				)
			);
		}

		// Suzanne
		{
			m_scene.addModel(
				new Model(
					Vector3(-4, -2, -8),
					"ObjFiles/suzanne.obj",
					//Material::defaultMaterial
					Material::randomMaterial()
				)
			);

			m_scene.addLightSource(
				new PointLight(
					Vector3(-4, -4, 0),
					{
						220,
						20,
						60,
						100
					},
					QuadraticAttenuation()
					//AttenuationFunction()
					//ConstantAttenuation(0.7)
				)
			);
		};
		// Woman chest
		{
			Vector3 chestPosition(-12, 12, -25);

			//left
			m_scene.addPrimitive(
				new Sphere(
					Vector3(-2, -0, -5) + chestPosition,
					2.0,
					Material({ 224, 205, 169, 255 }, 1, 1, 1, 100)
				)
			);

			m_scene.addPrimitive(
				new Sphere(
					Vector3(-2, -0, -3.53) + chestPosition,
					0.6,
					Material({ 254, 191, 210, 255 }, 1, 1, 1, 100)
				)
			);

			m_scene.addPrimitive(
				new Sphere(
					Vector3(-2, -0, -3.1) + chestPosition,
					0.2,
					Material({ 253, 108, 158, 255 }, 1, 1, 1, 100)
				)
			);

			//right
			m_scene.addPrimitive(
				new Sphere(
					Vector3(1.2, -0, -5) + chestPosition,
					2.0,
					Material({ 224, 205, 169, 255 }, 1, 1, 1, 100)
				)
			);

			m_scene.addPrimitive(
				new Sphere(
					Vector3(1.2, -0, -3.53) + chestPosition,
					0.6,
					Material({ 254, 191, 210, 255 }, 1, 1, 1, 100)
				)
			);

			m_scene.addPrimitive(
				new Sphere(
					Vector3(1.2, -0, -3.1) + chestPosition,
					0.2,
					Material({ 253, 108, 158, 255 }, 1, 1, 1, 100)
				)
			);
		};

		// Pokeball
		{
			// Beginning of the pokeball
			Vector3 pokeballPosition(10.0, 3.0, -16.0);

			m_scene.addPrimitive(    //red 
				new Sphere(
					Vector3(0, 0.09, -10) + pokeballPosition,
					2.0,
					Material({ 217, 1, 0, 255 }, 0.8, 0.7, 1, 100)
				)
			);

			m_scene.addPrimitive(    // white
				new Sphere(
					Vector3(0, -0.09, -10) + pokeballPosition,
					2.0,
					Material({ 255, 255, 255, 255 }, 0.8, 0.7, 1, 100)
				)
			);

			m_scene.addPrimitive(    // black center
				new Sphere(
					Vector3(0, 0, -10) + pokeballPosition,
					2.0030,
					Material({ 0, 0, 0, 255 }, 0.8, 0.7, 1, 100)
				)
			);

			m_scene.addPrimitive(    // black button
				new Sphere(
					Vector3(0, 0, -8.1) + pokeballPosition,
					0.4,
					Material({ 0, 0, 0, 255 }, 0.8, 0.7, 1, 100)
				)
			);

			m_scene.addPrimitive(    // white
				new Sphere(
					Vector3(0, -0, -7.94) + pokeballPosition,
					0.28,
					Material({ 255, 255, 255, 255 }, 0.8, 0.7, 1, 100)
				)
			);
			// End of the pokeball


			m_scene.addLightSource(
				new PointLight(
					Vector3(1.5, 1.5, -6) + pokeballPosition,
					{
						50,
						50,
						50,
						255
					},
					AttenuationFunction()
				)
			);
		};

		// Lights
		{
			for (int i = 0; i < 4; i++) {

				if (i & 1) {
					m_scene.addLightSource(
						new PointLight(
							Vector3(
								(double(rand() / double(RAND_MAX)) * 2.0 - 1.0) * 60.0,
								(double(rand() / double(RAND_MAX)) * 2.0 - 1.0) * 30.0,
								-double(rand() / double(RAND_MAX)) * 80
							),
							{
								(BYTE)((rand() / double(RAND_MAX)) * 255),
								(BYTE)((rand() / double(RAND_MAX)) * 255),
								(BYTE)((rand() / double(RAND_MAX)) * 255),
								255
							},
							ConstantAttenuation((rand() / double(RAND_MAX)))
						)
					);
				}
				else {
					m_scene.addLightSource(
						new DirectionalLight(
							Vector3(
								double(rand() / double(RAND_MAX)),
								double(rand() / double(RAND_MAX)),
								double(rand() / double(RAND_MAX))
							),
							{
								(BYTE)((rand() / double(RAND_MAX)) * 255),
								(BYTE)((rand() / double(RAND_MAX)) * 255),
								(BYTE)((rand() / double(RAND_MAX)) * 255),
								255
							},
							ConstantAttenuation((rand() / double(RAND_MAX)))
						)
					);
				}
			}
		}
	}

	int wh = m_scene.camera().width() * m_scene.camera().height();
	int pitch = wh * sizeof(RGBQUAD);

#pragma omp single
	SDL_LockTexture(m_textureScene, nullptr, (void**)&_pixels, &pitch);

	int i;

#pragma omp for
	for (i = 0; i < wh; i++) {
		RGBQUAD color = m_scene.getPixelColor(m_rays[i]);

		_pixels[i] = SDL_MapRGBA(m_format, color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
	}

#pragma omp master
	{
		m_pixels = _pixels;
		m_end = std::chrono::high_resolution_clock::now();
	}

#pragma omp single
	SDL_UnlockTexture(m_textureScene);
}

void ComplexDemo::render() {

	if (!_render)
		return;

	_render = false;

	SDL_RenderClear(m_rendererScene);
	SDL_RenderCopy(m_rendererScene, m_textureScene, nullptr, nullptr);
	SDL_RenderPresent(m_rendererScene);
}

bool ComplexDemo::parametersWindowRender() {

	// a window is defined by Begin/End pair
	{
		int sdl_width = 0, sdl_height = 0;
		SDL_GetWindowSize(m_windowParams, &sdl_width, &sdl_height);

		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
		ImGui::SetNextWindowSize(
			ImVec2(static_cast<float>(sdl_width - 20), static_cast<float>(sdl_height - 20)),
			ImGuiCond_Always
		);

		// create a window and append into it
		ImGui::Begin("Parameters", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse);

		if (ImGui::Button("Render")) {
			_render = true;
		}

		if (_render) {
			ImGui::Text("Rendering... (5-6 minutes max)");
		}
		else {
			std::stringstream ss;
			ss << "Rendering done in: " << std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() / 1000.0 << " seconds";
			ImGui::Text(ss.str().c_str());

			if (ImGui::Button("Save Picture as 'out.png'")) {
				m_scene.savePicture("out.png", (RGBQUAD*)m_pixels);
			}
		}

		ImGui::End();
	}
	return _render;
}