#include "Demo.hpp"

Demo::Demo(SDL_Window* pWindow, SDL_GLContext& pGlContext, std::string pSceneName, SDL_Point pSceneSize, SDL_Point pParamSize) {

	if (!SDL_WasInit(SDL_INIT_VIDEO))
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			throw std::exception::exception("Unable to initialize SDL");
		}

	m_windowParamsize = pParamSize;

	/*if (!(m_windowParams = SDL_CreateWindow("Parameters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowParamsize.x, m_windowParamsize.y, videoFlags)))
		throw std::exception::exception("Unable to create Params SDL Window");*/

	m_windowParams = pWindow;
	SDL_SetWindowSize(m_windowParams, m_windowParamsize.x, m_windowParamsize.y);

	m_glParams = pGlContext;

	glViewport(0, 0, m_windowParamsize.x, m_windowParamsize.y);

	// colors are set in RGBA, but as float
	ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);
	glClearColor(background.x, background.y, background.z, background.w);

	// Scene Context

	m_windowSceneSize = pSceneSize;

	if (!(m_windowScene = SDL_CreateWindow(pSceneName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowSceneSize.x, m_windowSceneSize.y, 0)))
		throw std::exception::exception("Unable to create Scene SDL Window");

	if (!(m_rendererScene = SDL_CreateRenderer(m_windowScene, -1, SDL_RENDERER_ACCELERATED)))
		throw std::exception::exception("Unable to create Scene SDL Renderer");

	if (!(m_textureScene = SDL_CreateTexture(m_rendererScene, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_windowSceneSize.x, m_windowSceneSize.y)))
		throw std::exception::exception(std::string("Unable to create SDL Texture " + std::string(SDL_GetError())).c_str());

	//m_pixels = new RGBQUAD[m_windowSceneSize.x * m_windowSceneSize.y]{0};

	m_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	_events = Events();

	_render = true;
}

Demo::~Demo() {

	SDL_DestroyRenderer(m_rendererScene);
	m_rendererScene = nullptr;

	SDL_DestroyWindow(m_windowScene);
	m_windowScene = nullptr;
}

int Demo::mainLoop() {

	init();

	m_deltaTime = 0.0;
	_quit = false;

	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

#pragma omp parallel shared(_pixels, start, end, _quit)
{
#pragma omp barrier
	while (!_quit) {
		start = std::chrono::high_resolution_clock::now();

#pragma omp master
		_render = eventLoop();
#pragma omp barrier

		if (!_quit)
			update(m_deltaTime);

#pragma omp single
		if (!_quit)
			render();
#pragma omp barrier

		end = std::chrono::high_resolution_clock::now();

#pragma omp single
		m_deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
#pragma omp barrier
	}
}
	return EXIT_SUCCESS;
}

bool Demo::eventLoop() {

	while (SDL_PollEvent(&e) && !_quit)
	{
		_render = parametersManager(&e);

		switch (e.type)
		{
		case SDL_QUIT:
			_quit = true;
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				_quit = true;
				break;
			}
			break;
		}

		eventHandler(e);
	}

	return _quit;
}

void Demo::eventHandler(SDL_Event pEvent) {
	std::cerr << "Demo::eventHandler() method not implemented" << std::endl;
	return;
}

bool Demo::parametersManager(SDL_Event* e) {
	ImGui_ImplSDL2_ProcessEvent(e);

	// start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_windowParams);
	ImGui::NewFrame();

	_render = parametersWindowRender();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(m_windowParams);
	
	return _render;
}

bool Demo::parametersWindowRender() {
	std::cerr << "Demo::parametersWindowRender() not implemented" << std::endl;
	return false;
}