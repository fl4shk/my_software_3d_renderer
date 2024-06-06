#include "MyDisplay.hpp"
//--------
Display::Display()
	: window(
		SDL_CreateWindow(
			"My Software 3D Renderer",	// title
			SDL_WINDOWPOS_CENTERED,		// x
			SDL_WINDOWPOS_CENTERED,		// y
			SCREEN_SIZE_2D.x,			// WIDTH
			SCREEN_SIZE_2D.y,			// HEIGHT
			(							// flags
				SDL_WINDOW_SHOWN
				//| SDL_WINDOW_RESIZABLE
			)
		)
	),
	renderer(
		SDL_CreateRenderer(
			window,	// window
			-1,		// index
			0			// flags
		)
	),
	texture(
		SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STATIC,
			SCREEN_SIZE_2D.x,
			SCREEN_SIZE_2D.y
		)
	),
	pixels({
		std::unique_ptr<Uint32[]>(
			new Uint32[SCREEN_SIZE_2D.x * SCREEN_SIZE_2D.y]
		),
		std::unique_ptr<Uint32[]>(
			new Uint32[SCREEN_SIZE_2D.x * SCREEN_SIZE_2D.y]
		),
	})
{
	for (auto& item: pixels) {
		std::memset(
			item.get(),
			0,
			SCREEN_SIZE_2D.x * SCREEN_SIZE_2D.y * sizeof(Uint32)
		);
	}
}
Display::~Display() {
}
//--------
void MyDisplay::_update_engine_key_status() {
	_engine_key_status.update(
		_key_status_umap,
		sdl::EngineKeycUmap<SnesKeyKind>({
			{SnesKeyKind::B, SDLK_k},
			{SnesKeyKind::Y, SDLK_j},
			{SnesKeyKind::Select, SDLK_a},
			{SnesKeyKind::Start, SDLK_RETURN},
			{SnesKeyKind::DpadUp, SDLK_e},
			{SnesKeyKind::DpadDown, SDLK_d},
			{SnesKeyKind::DpadLeft, SDLK_s},
			{SnesKeyKind::DpadRight, SDLK_f},
			{SnesKeyKind::A, SDLK_l},
			{SnesKeyKind::X, SDLK_i},
			{SnesKeyKind::L, SDLK_o},
			{SnesKeyKind::R, SDLK_p},
			{SnesKeyKind::ExitSim, SDLK_ESCAPE},
		})
	);
}
MyDisplay::MyDisplay()
	: Display(),
	_engine_key_status(int32_t(SnesKeyKind::Lim))
{
}

MyDisplay::~MyDisplay() {
}
void MyDisplay::refresh() {
	//--------
	SDL_UpdateTexture(
		texture,
		NULL,
		pixels.at(active_pixels).get(),
		sizeof(Uint32) * SCREEN_SIZE_2D.x // pitch
		//sizeof(Uint32) * HALF_SIZE_2D.x // pitch
		//sizeof(Uint32) * SCREEN_SIZE_2D.x * SCREEN_SIZE_2D.y
	);
	//for (size_t j=0; j<SCREEN_SIZE_2D.y; ++j) {
	//	for (size_t i=0; i<SCREEN_SIZE_2D.x; ++i) {
	//		
	//	}
	//}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	//std::memset(pixels.get(), 0, HALF_SIZE_2D.x * sizeof(Uint32));
	active_pixels = (active_pixels + 1) % pixels.size();
	std::memset(
		pixels.at(active_pixels).get(),
		0,
		SCREEN_SIZE_2D.x * SCREEN_SIZE_2D.y * sizeof(Uint32)
		//HALF_SIZE_2D.x * HALF_SIZE_2D.y * sizeof(Uint32)
	);
	//--------
	//--------
};
void MyDisplay::handle_sdl_events() {
	bool ksm_perf_total_backup = true;
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			_do_exit = true;
		} else if (
			liborangepower::sdl::handle_key_events(
				e,
				_key_status_umap, 
				ksm_perf_total_backup
			)
		) {
		}
	}
	_update_engine_key_status();
	if (_engine_key_status.key_down_now(SnesKeyKind::ExitSim)) {
		_do_exit = true;
	}
}
