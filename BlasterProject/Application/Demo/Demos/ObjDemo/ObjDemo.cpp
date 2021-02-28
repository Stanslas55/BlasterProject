#include "ObjDemo.hpp"

const std::string ObjDemo::m_cubePath = "./ObjFiles/cube.obj";
Material ObjDemo::m_cubeMaterial = Material(
	{ 255, 0, 0, 255 },
	0.4,
	1.0,
	0.6,
	80.0
);
const Vector3 ObjDemo::m_cubePosition = Vector3(-0.5, -0.5, -5.0);

const std::string ObjDemo::m_bunnyPath = "./ObjFiles/bunny.obj";
Material ObjDemo::m_bunnyMaterial = Material(
	{ 255, 255, 255, 255 },
	0.7,
	0.8,
	0.0,
	0.0
);
const Vector3 ObjDemo::m_bunnyPosition = Vector3(0.0, -0.12, -0.3);

const std::string ObjDemo::m_teapotPath = "./ObjFiles/teapot.obj";
Material ObjDemo::m_teapotMaterial = Material(
	{ 255, 255, 255, 255 },
	0.5,
	1.0,
	1.0,
	100.0
);
const Vector3 ObjDemo::m_teapotPosition = Vector3(0.0, -1.8, -7.0);

const std::string ObjDemo::m_suzannePath = "./ObjFiles/suzanne.obj";
Material ObjDemo::m_suzanneMaterial = Material(
	{ 135, 92, 35, 255 },
	0.6,
	0.8,
	0.8,
	30.0
);
const Vector3 ObjDemo::m_suzannePosition = Vector3(0.0, 0.0, -4.0);

Material ObjDemo::m_defaultMaterial = Material::defaultMaterial;
static const Vector3 m_defaultPosition = Vector3(0.0, 0.0, -5.0);

ObjDemo::ObjDemo(SDL_Window* pWindow, SDL_GLContext& pGlContext, SDL_Point pSceneSize) : Demo(pWindow, pGlContext, "Obj Demo", pSceneSize, { 400, 600 }), m_scene(Camera(pSceneSize.x, pSceneSize.y)) {
	m_rays = nullptr;
	m_pixels = nullptr;

}

ObjDemo::~ObjDemo() {
	delete[] m_rays;
	m_rays = nullptr;
}

void ObjDemo::init() {
	// Scene construction
	// Obj scene
	
	m_materialModel = &m_cubeMaterial;
	m_pathModel = m_cubePath;
	m_positionModel = m_cubePosition;

	m_scene.addLightSource(
		new DirectionalLight(
			Vector3(-1.0, 1.0, 0.5),
			{ 150, 150, 150, 255 },
			ConstantAttenuation(0.7)
		)
	);

	m_rays = m_scene.getRayArray();

	_render = true;
}

void ObjDemo::eventHandler(SDL_Event pEvent) {
	
}

void ObjDemo::update(double pDeltaTime) {

	if (!_render)
		return;

#pragma omp master 
	{
		m_start = std::chrono::high_resolution_clock::now();
		// Update here
		m_scene.reset(false);

		m_scene.addModel(
			new Model(
				m_positionModel,
				m_pathModel,
				*m_materialModel
			)
		);
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
	m_end = std::chrono::high_resolution_clock::now();

#pragma omp single
	SDL_UnlockTexture(m_textureScene);
}

void ObjDemo::render() {

	if (!_render)
		return;

	_render = false;

	SDL_RenderClear(m_rendererScene);
	SDL_RenderCopy(m_rendererScene, m_textureScene, nullptr, nullptr);
	SDL_RenderPresent(m_rendererScene);
}

bool ObjDemo::parametersWindowRender() {
	
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
		ImGui::Text("Model");

		if (ImGui::RadioButton("Cube", m_pathModel == m_cubePath)) {
			m_materialModel = &m_cubeMaterial;
			m_pathModel = m_cubePath;
			m_positionModel = m_cubePosition;
		}
		if (ImGui::RadioButton("Suzanne", m_pathModel == m_suzannePath)) {
			m_materialModel = &m_suzanneMaterial;
			m_pathModel = m_suzannePath;
			m_positionModel = m_suzannePosition;
		}
		if (ImGui::RadioButton("Bunny", m_pathModel == m_bunnyPath)) {
			m_materialModel = &m_bunnyMaterial;
			m_pathModel = m_bunnyPath;
			m_positionModel = m_bunnyPosition;
		}
		if (ImGui::RadioButton("Teapot", m_pathModel == m_teapotPath)) {
			m_materialModel = &m_teapotMaterial;
			m_pathModel = m_teapotPath;
			m_positionModel = m_teapotPosition;
		}

		ImGui::Text("Material");

		ImVec4 color = { m_materialModel->color().rgbRed / 255.0f, m_materialModel->color().rgbGreen / 255.0f, m_materialModel->color().rgbBlue / 255.0f, 1.0f };

		if (ImGui::ColorEdit4("Color", (float*)&color), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoOptions) {
			m_materialModel->color() = {
				BYTE(color.x * 255),
				BYTE(color.y * 255),
				BYTE(color.z * 255),
				BYTE(color.w * 255)
			};
		}

		float k[4] = {
			float(m_materialModel->ka()),
			float(m_materialModel->kd()),
			float(m_materialModel->ks()),
			float(m_materialModel->ke())
		};

		if (ImGui::SliderFloat("kA", &k[0], 0.0f, 1.0f))
			m_materialModel->ka() = double(k[0]);

		if (ImGui::SliderFloat("kD", &k[1], 0.0f, 1.0f))
			m_materialModel->kd() = double(k[1]);

		if (ImGui::SliderFloat("kS", &k[2], 0.0f, 1.0f))
			m_materialModel->ks() = double(k[2]);

		if (ImGui::SliderFloat("kE", &k[3], 0.0f, 100.0f))
			m_materialModel->ke() = double(k[3]);
		
		Vector3 li = m_scene.lightSources()[0]->intensity();
		static ImVec4 cli(
			float(li.z()) / 255.0f,
			float(li.y()) / 255.0f,
			float(li.x()) / 255.0f,
			1.0f
		);

		if (ImGui::ColorEdit4("Light Color", (float*)&cli), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoAlpha) {
			m_scene.lightSources()[0]->intensity() = Vector3(
				cli.z * 255.0,
				cli.y * 255.0,
				cli.x * 255.0
			);
		}

		if (ImGui::Button("Render")) {
			_render = true;
		}

		if (_render)
			ImGui::Text("Rendering...");
		else {
			std::stringstream ss;
			ss << "Rendering done in: " << std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() / 1000.0 << " seconds";
			ImGui::Text(ss.str().c_str());
		}

		ImGui::End();
	}
	return _render;
}