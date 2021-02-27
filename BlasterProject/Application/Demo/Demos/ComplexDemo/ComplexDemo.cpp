#include "ComplexDemo.hpp"

ComplexDemo::ComplexDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize) : Demo(pWindow, pGlContext, "Complex Demo", pSceneSize, { 400, 600 }), m_scene(Camera(pSceneSize.x, pSceneSize.y)) {
	m_rays = nullptr;
	m_pixels = nullptr;
}

ComplexDemo::~ComplexDemo() {
	delete[] m_rays;
	m_rays = nullptr;
}

void ComplexDemo::init() {
	// Scene construction
	// Complex scene

	double sphereRadius = 10.0;

	m_scene.addPrimitive(
		new Sphere(
			Vector3(0,0,-20),
			sphereRadius,
			Material(
				{ 255, 0, 0, 255 },
				0.2,
				1.0,
				0.8,
				100.0
			)
		)
	);

	// The point light source is situated at 20.0 units from the sphere surface
	double radiusLight = sphereRadius * 4.0;

	m_scene.addLightSource(
		new DirectionalLight(
			Vector3(-0.5, 0.5, 1.0),
			{
				100,
				100,
				100,
				255
			}
		)
	);

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


	}

	int wh = m_scene.camera().width() * m_scene.camera().height();
	int pitch = wh * sizeof(RGBQUAD);

	int i;
#pragma omp single
	SDL_LockTexture(m_textureScene, nullptr, (void**)&_pixels, &pitch);

#pragma omp for
	for (i = 0; i < wh; i++) {
		RGBQUAD color = m_scene.getPixelColor(m_rays[i]);

		_pixels[i] = SDL_MapRGBA(m_format, color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
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

		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::Text("Material");

		if (ImGui::Button("Render")) {
			_render = true;
		}

		ImGui::End();
	}
	return _render;
}