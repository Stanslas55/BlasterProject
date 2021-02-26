#include "RTDemo.hpp"

RTDemo::RTDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize) : Demo(pWindow, pGlContext, "Real-Time Demo", pSceneSize, { 400, 600 }), m_scene(Camera(pSceneSize.x, pSceneSize.y)) {
	m_collisions = nullptr;
}

RTDemo::~RTDemo() {
	delete[] m_collisions;
	m_collisions = nullptr;
}

void RTDemo::init() {
	// Scene construction
	// Real Time Demo consists of a central sphere being lightened by a moving light source

	double sphereRadius = 10.0;

	m_centerOfRotation = Vector3(0.0, 0.0, -40.0);

	m_scene.addPrimitive(
		new Sphere(
			m_centerOfRotation,
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

	m_polarSystem = Vector3(
		radiusLight,
		-M_PI/2,
		M_PI / 8
	);

	m_scene.addLightSource(
		new PointLight(
			Vector3::toCarthesian(m_polarSystem) + m_centerOfRotation,
			{
				255,
				255,
				255,
				255
			}
		)
	);

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

	m_collisions = m_scene.getCollisionArray();
}

void RTDemo::eventHandler(SDL_Event pEvent) {
	
}

void RTDemo::update(double pDeltaTime) {

#pragma omp master
{
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

		ImGui::PushFont(nullptr);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::Text("Material");

		static ImVec4 color = { 1.0f, 1.0f, 1.0f, 1.0f};

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


		//ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Platform");
		//ImGui::Text("%s", SDL_GetPlatform());
		//ImGui::Text("CPU cores: %d", SDL_GetCPUCount());
		//ImGui::Text("RAM: %.2f GB", SDL_GetSystemRAM() / 1024.0f);

		//// buttons and most other widgets return true when clicked/edited/activated
		//if (ImGui::Button("Counter button")) {
		//	std::cout << "counter button clicked\n";
		//	//counter++;
		//}
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::PopFont();

		ImGui::End();
	}

	std::shared_ptr<PointLight> l = std::static_pointer_cast<PointLight>(m_scene.lightSources()[0]);

	m_polarSystem.y() += pDeltaTime * M_PI;
	m_polarSystem.y() = (m_polarSystem.y() > 2 * M_PI) ? m_polarSystem.y() - 2 * M_PI : m_polarSystem.y();

	l->position() = Vector3::toCarthesian(m_polarSystem) + m_centerOfRotation;

	std::stringstream ss;

	ss << "Project Blaster - FPS: " << int(1.0 / m_deltaTime);

	SDL_SetWindowTitle(m_windowScene, ss.str().c_str());

	Uint32 format;
	SDL_QueryTexture(m_textureScene, &format, nullptr, nullptr, nullptr);
}
	int wh = m_scene.camera().width() * m_scene.camera().height();
	int pitch = wh * sizeof(RGBQUAD);

	int i;
#pragma omp single
	SDL_LockTexture(m_textureScene, nullptr, (void**)&m_pixels, &pitch);
//#pragma omp barrier

#pragma omp for
	for (i = 0; i < wh; i++) {
		RGBQUAD color = m_scene.getPixelColor(m_collisions[i]);

		m_pixels[i] = SDL_MapRGBA(m_format, color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
	}
	
#pragma omp single
	SDL_UnlockTexture(m_textureScene);

}

void RTDemo::render() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(m_windowParams);

	if (!_render)
		return;

	SDL_RenderClear(m_rendererScene);
	SDL_RenderCopy(m_rendererScene, m_textureScene, nullptr, nullptr);
	SDL_RenderPresent(m_rendererScene);
}
