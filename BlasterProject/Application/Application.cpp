#include "Application.hpp"
#include <imgui/Utils/Utils.hpp>

Application::Application(int pWidth, int pHeight) {

	if (!SDL_WasInit(SDL_INIT_VIDEO))
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			throw std::exception::exception("Unable to initialize SDL");
		}

	// set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE
	);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	Uint32 videoFlags = SDL_WINDOW_OPENGL;  //Enable OpenGL in SDL.
	videoFlags |= SDL_GL_DOUBLEBUFFER;		//Enable double buffering.
	videoFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
	videoFlags ^= SDL_WINDOW_FULLSCREEN;

	if (!(m_window = SDL_CreateWindow("Project Blaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pWidth, pHeight, videoFlags)))
		throw std::exception::exception("Unable to create SDL Window");

	m_glContext = SDL_GL_CreateContext(m_window);
	SDL_GL_MakeCurrent(m_window, m_glContext);

	SDL_GL_SetSwapInterval(-1);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		std::cerr << "[ERROR] Couldn't initialize glad" << std::endl;

	glViewport(0, 0, pWidth, pHeight);

		// setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// setup Dear ImGui style
	ImGui::StyleColorsDark();

	// setup platform/renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(m_window, m_glContext);
	ImGui_ImplOpenGL3_Init("#version 130");
	
	// colors are set in RGBA, but as float
	ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);
	glClearColor(background.x, background.y, background.z, background.w);

	m_frame = new RGBQUAD[pWidth * pHeight];

	m_width = pWidth;
	m_height = pHeight;

	m_currentPage = Page::MAIN_MENU;

	m_targetDim = { m_width, m_height };

	_fontDefault = AddDefaultFont(15);
	_fontMin = AddDefaultFont(15);
	_fontTitle = AddDefaultFont(50);
	_fontSubtitle = AddDefaultFont(24);
}

Application::~Application() {
	
	delete[] m_frame;
	m_frame = nullptr;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_glContext);

	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	
	SDL_Quit();
}

void Application::init() {
	restore();
}

int Application::mainLoop() {

	init();

	while (!_quit) {

		eventHandler();

		if(!_quit)
			update();

		if (!_quit)
			render();
	}

	return EXIT_SUCCESS;
}

void Application::eventHandler() {

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// without it you won't have keyboard input and other things
		ImGui_ImplSDL2_ProcessEvent(&event);
		// you might also want to check io.WantCaptureMouse and io.WantCaptureKeyboard
		// before processing events

		switch (event.type)
		{
		case SDL_QUIT:
			_quit = true;
			return;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				_quit = true;
				return;
			}
			break;
		}
	}
}

void Application::restore() {
	m_currentPage = Page::MAIN_MENU;
	SDL_SetWindowSize(m_window, m_width, m_height);
	SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowTitle(m_window, "Project Blaster");
}

void Application::update() {
	
	switch (m_currentPage) {
	case Page::MAIN_MENU:
		mainMenu();
		break;
	case Page::REAL_TIME_DEMO:
		{
			RTDemo rtd = RTDemo(m_window, m_glContext, m_targetDim);
			rtd.mainLoop();
			restore();
		}
		break;
	case Page::COMPLEX_DEMO:
		{
			ComplexDemo cd = ComplexDemo(m_window, m_glContext, m_targetDim);
			cd.mainLoop();
			restore();
		}
		break;
	case Page::OBJ_DEMO:
		{
			ObjDemo od = ObjDemo(m_window, m_glContext, m_targetDim);
			od.mainLoop();
			restore();
		}
		break;
	default:
		break;
	}

}

void Application::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(m_window);
}

void Application::mainMenu() {
	
	// start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	// a window is defined by Begin/End pair
	{
		// get the window size as a base for calculating widgets geometry
		int sdl_width = 0, sdl_height = 0;
		SDL_GetWindowSize(m_window, &sdl_width, &sdl_height);

		// position the controls widget in the top-right corner with some margin
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
		// here we set the calculated width and also make the height to be
		// be the height of the main window also with some margin
		ImGui::SetNextWindowSize(
			ImVec2(static_cast<float>(sdl_width - 20), static_cast<float>(sdl_height - 20)),
			ImGuiCond_Always
		);
		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

		// create a window and append into it
		ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse);

		ImGui::PushFont(_fontTitle);
		ImGuiTextCenter("Project Blaster");
		ImGui::PopFont();

		ImGui::PushFont(_fontSubtitle);

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGuiTextCenter("RayTracing - 2021 ESIEA Laval");

		float margin = sdl_width / 8.0f;
		float padding = sdl_width / 15.0f;
		float yTop = sdl_height / 3.0f;
		float yBot = sdl_height - sdl_height / 6.0f;
		
		ImVec2 buttonSize((sdl_width - (margin * 2) - padding * 2) / 3 , ((yBot - yTop) - padding) / 2 );

		ImGui::SetCursorPos(ImVec2(margin, yTop));
		if (ImGui::Button("Real Time Demo", buttonSize)) {
			m_currentPage = Page::REAL_TIME_DEMO;
		}

		ImGui::SetCursorPos(ImVec2(margin + buttonSize.x + padding, yTop));
		if (ImGui::Button("Complex Demo", buttonSize)) {
			m_currentPage = Page::COMPLEX_DEMO;
		}

		ImGui::SetCursorPos(ImVec2(margin + (buttonSize.x + padding) * 2, yTop));
		if (ImGui::Button("OBJ Demo", buttonSize)) {
			m_currentPage = Page::OBJ_DEMO;
		}
		
		ImGui::PopFont();

		// Credits
		ImGui::SetCursorPos(ImVec2(10.0f, sdl_height * 0.85f));

		ImGui::PushFont(_fontMin);
		ImGui::Text("Credits:\nCISTERNAS Nicolas\nBEUCHER Maxime\nDEROCHE Victor\nBEASSE Maxime");

		// Choose Target resolution

		ImGui::SetCursorPos(ImVec2(sdl_width - margin * 2, yBot + padding / 2));

		ImGui::BeginGroup();
		ImGui::Text("\tChoose target resolution :");
		if (ImGui::RadioButton("640x480", m_targetDim.x == 640 && m_targetDim.y == 480))
			m_targetDim = { 640, 480 };
		ImGui::SameLine();
		if (ImGui::RadioButton("1280x720", m_targetDim.x == 1280 && m_targetDim.y == 720))
			m_targetDim = { 1280, 720 };
		ImGui::SameLine();
		if (ImGui::RadioButton("1920x1080", m_targetDim.x == 1920 && m_targetDim.y == 1080))
			m_targetDim = { 1920, 1080 };
		ImGui::EndGroup();

		ImGui::PopFont();
		ImGui::End();
	}
}