#ifndef src_my_display_class_hpp
#define src_my_display_class_hpp

// src/my_display_class.hpp

#include "MiscIncludes.hpp"
//#include "Rgb444.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Tri.hpp"
#include "Rast.hpp"

class Display {
public:		// variables
	sdl::Window window;
	sdl::Renderer renderer;
	sdl::Texture texture;
	std::array<std::unique_ptr<Uint32[]>, 2> pixels;
	// `active_pixels` is used for double buffering
	size_t active_pixels = 0;
public:		// functions
	Display();
	virtual ~Display();
	inline void set(
		const Vec2<size_t>& pos,
		Uint32 col
	) {
		pixels.at(active_pixels)[pos.y * SCREEN_SIZE_2D.x + pos.x] = col;
	}
	inline void set(
		size_t idx,
		Uint32 col
	) {
		pixels.at(active_pixels)[idx] = col; 
	}
	//inline void set(
	//	const Vec2<size_t>& pos,
	//	const Rgb444& col
	//) {
	//	set(pos, col.to_u32());
	//}
};

enum class SnesKeyKind: uint32_t {
	B = 0,
	Y = 1,
	Select = 2,
	Start = 3,
	DpadUp = 4,
	DpadDown = 5,
	DpadLeft = 6,
	DpadRight = 7,
	A = 8,
	X = 9,
	L = 10,
	R = 11,
	ExitSim = 12,
	Lim = 13,
};

class MyDisplay: public Display {
public:		// variables
protected:	// variables
	sdl::KeyStatusUmap _key_status_umap;
	liborangepower::game::EngineKeyStatus _engine_key_status;
	bool _do_exit = false;
	//std::vector<Tri> _tri_vec;
protected:		// functions
	void _update_engine_key_status();
public:		// functions
	MyDisplay();

	virtual ~MyDisplay();
	void refresh();
	void handle_sdl_events();
	//void push_tri(const Tri& to_push);
	inline bool key_up_now(const SnesKeyKind& key_kind) const {
		return engine_key_status().key_up_now(key_kind);
	}
	inline bool key_down_now(const SnesKeyKind& key_kind) const {
		return engine_key_status().key_down_now(key_kind);
	}

	GEN_GETTER_BY_CON_REF(do_exit);
	GEN_GETTER_BY_CON_REF(engine_key_status);
protected:		// variables and helper functions
	//uint32_t _misc_visib_timer = 0;
	//bool _visib_enable = false;
	//bool _last_visib = false;
	//Vec2<Uint32> _temp_cnt{0, 0};
	//bool _did_first_refresh = false;
public:		// functions
};

#endif		// src_my_display_class_hpp
