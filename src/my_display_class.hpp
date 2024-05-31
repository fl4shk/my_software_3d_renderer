#ifndef src_my_display_class_hpp
#define src_my_display_class_hpp

// src/my_display_class.hpp

#include "misc_includes.hpp"
//#include "rgb444_class.hpp"
#include "texture_class.hpp"
#include "transform_class.hpp"
#include "tri_class.hpp"
#include "rast_class.hpp"

class Display {
public:		// variables
	sdl::Window window;
	sdl::Renderer renderer;
	sdl::Texture texture;
	std::unique_ptr<Uint32[]> pixels;
public:		// functions
	Display();
	virtual ~Display();
	inline void set(
		const Vec2<size_t>& pos,
		Uint32 col
	) {
		pixels[pos.y * SIZE_2D.x + pos.x] = col;
	}
	inline void set(
		size_t idx,
		Uint32 col
	) {
		pixels[idx] = col; 
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

	GEN_GETTER_BY_CON_REF(do_exit);
protected:		// variables and helper functions
	//uint32_t _misc_visib_timer = 0;
	//bool _visib_enable = false;
	//bool _last_visib = false;
	//Vec2<Uint32> _temp_cnt{0, 0};
	//bool _did_first_refresh = false;
public:		// functions
};

#endif		// src_my_display_class_hpp
