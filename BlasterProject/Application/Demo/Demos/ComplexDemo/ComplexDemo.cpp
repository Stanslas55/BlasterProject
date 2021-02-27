#include "ComplexDemo.hpp"

ComplexDemo::ComplexDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize) : Demo(pWindow, pGlContext, "Real-Time Demo", pSceneSize, { 400, 600 }), m_scene(Camera(pSceneSize.x, pSceneSize.y)) {
	m_rays = new Ray[pSceneSize.x * pSceneSize.y];
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
			Vector3(0,0,0),
			sphereRadius,
			Material(
				{ 255, 255, 255, 255 },
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
}

void ComplexDemo::eventHandler(SDL_Event pEvent) {
	
}

void ComplexDemo::update(double pDeltaTime) {

#pragma omp master
{
	Uint32 format;
	SDL_QueryTexture(m_textureScene, &format, nullptr, nullptr, nullptr);
}
	int wh = m_scene.camera().width() * m_scene.camera().height();
	int pitch = wh * sizeof(RGBQUAD);

	int i;
#pragma omp single
	SDL_LockTexture(m_textureScene, nullptr, (void**)&m_pixels, &pitch);

#pragma omp for
	for (i = 0; i < wh; i++) {
		RGBQUAD color = m_scene.getPixelColor(m_rays[i]);

		m_pixels[i] = SDL_MapRGBA(m_format, color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
	}

#pragma omp single
	SDL_UnlockTexture(m_textureScene);

	_render = true;

}

void ComplexDemo::render() {

	if (!_render)
		return;

	_render = false;

	SDL_RenderClear(m_rendererScene);
	SDL_RenderCopy(m_rendererScene, m_textureScene, nullptr, nullptr);
	SDL_RenderPresent(m_rendererScene);
}

void ComplexDemo::parametersWindowRender() {
	// start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_windowParams);
	ImGui::NewFrame();

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

		static ImVec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		if (ImGui::ColorEdit4("Color", (float*)&color), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoOptions) {
			m_scene.objects()[0]->material().color() = {
				BYTE(color.x * 255),
				BYTE(color.y * 255),
				BYTE(color.z * 255),
				BYTE(color.w * 255)
			};
		}

		static float k[4] = {
			float(m_scene.objects()[0]->material().ka()),
			float(m_scene.objects()[0]->material().kd()),
			float(m_scene.objects()[0]->material().ks()),
			float(m_scene.objects()[0]->material().ke())
		};

		if (ImGui::SliderFloat("kA", &k[0], 0.0f, 1.0f))
			m_scene.objects()[0]->material().ka() = double(k[0]);

		if (ImGui::SliderFloat("kD", &k[1], 0.0f, 1.0f))
			m_scene.objects()[0]->material().kd() = double(k[1]);

		if (ImGui::SliderFloat("kS", &k[2], 0.0f, 1.0f))
			m_scene.objects()[0]->material().ks() = double(k[2]);

		if (ImGui::SliderFloat("kE", &k[3], 0.0f, 100.0f))
			m_scene.objects()[0]->material().ke() = double(k[3]);

		Vector3 li = m_scene.lightSources()[0]->intensity();
		static ImVec4 cli(
			li.z() / 255,
			li.y() / 255,
			li.x() / 255,
			1.0f
		);

		if (ImGui::ColorEdit4("Light Color", (float*)&cli), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoAlpha) {
			m_scene.lightSources()[0]->intensity() = Vector3(
				cli.z * 255.0,
				cli.y * 255.0,
				cli.x * 255.0
			);
		}

		ImGui::End();
	}
}