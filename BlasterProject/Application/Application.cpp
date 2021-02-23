#include "Application.hpp"

Application::Application(int pWidth, int pHeight) {

	if (!SDL_WasInit(SDL_INIT_EVERYTHING))
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			throw std::exception::exception("Unable to initialize SDL");
		}
	
	if (SDL_CreateWindowAndRenderer(pWidth, pHeight, SDL_WINDOW_SHOWN, &m_window, &m_renderer) < 0)
		throw std::exception::exception("Unable to create SDL Window and Renderer");

	if (!m_window || !m_renderer)
		throw std::exception::exception("Unable to create SDL Window and Renderer");

	SDL_SetWindowTitle(m_window, "Project Blaster");

	if (!(m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, pWidth, pHeight)))
		throw std::exception::exception("Unable to create SDL Texture");
}

Application::~Application() {

	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;

	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	
	SDL_Quit();
}

int Application::mainLoop() {

	while (!_quit) {

		eventHandler();

		update();
	}

	return EXIT_SUCCESS;
}

void Application::eventHandler() {

	SDL_Event e;

	_events.mouseState = SDL_GetMouseState(&_events.mousePosition.x, &_events.mousePosition.y);

	while (SDL_PollEvent(&e)) {

		switch (e.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (e.key.state == SDL_PRESSED) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					_quit = true;
					return;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}

	}

}

void Application::update() {
}

void Application::render() {

}


