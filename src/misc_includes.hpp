#ifndef src_misc_includes_hpp
#define src_misc_includes_hpp

// src/misc_includes.hpp

#include <memory>

#include "liborangepower_src/misc/misc_includes.hpp"
#include "liborangepower_src/misc/misc_output_funcs.hpp"
#include "liborangepower_src/misc/misc_types.hpp"
#include "liborangepower_src/misc/misc_utility_funcs.hpp"
#include "liborangepower_src/misc/misc_bitwise_funcs.hpp"
#include "liborangepower_src/misc/misc_defines.hpp"
#include "liborangepower_src/gen_class_innards_defines.hpp"
#include "liborangepower_src/strings/string_conversion_stuff.hpp"
#include "liborangepower_src/strings/sconcat_etc.hpp"
#include "liborangepower_src/containers/defer_call_stuff.hpp"
#include "liborangepower_src/concepts/misc_concepts.hpp"
#include "liborangepower_src/concepts/math_concepts.hpp"
#include "liborangepower_src/concepts/std_container_concepts.hpp"
#include "liborangepower_src/concepts/std_stream_concepts.hpp"
#include "liborangepower_src/concepts/is_specialization_concepts.hpp"
#include "liborangepower_src/game_stuff/engine_key_status_class.hpp"
#include "liborangepower_src/time/time_stuff.hpp"
#include "liborangepower_src/math/vec2_classes.hpp"
#include "liborangepower_src/math/vec3_classes.hpp"
#include "liborangepower_src/math/cx_fixed_pt_class.hpp"
//#include "liborangepower_src/math/vec4_classes.hpp"
#include "liborangepower_src/misc/misc_includes.hpp"
#include "liborangepower_src/sdl2/sdl.hpp"
#include "liborangepower_src/sdl2/dpi_stuff.hpp"
#include "liborangepower_src/sdl2/keyboard_stuff.hpp"
#include "liborangepower_src/sdl2/sdl_video.hpp"
#include "liborangepower_src/sdl2/sdl_render.hpp"
#include "liborangepower_src/sdl2/sdl_surface.hpp"
#include "liborangepower_src/sdl2/sdl_rect.hpp"
#include "liborangepower_src/misc/misc_output_funcs.hpp"

using namespace liborangepower::misc_output;
using namespace liborangepower::integer_types;
using namespace liborangepower::misc_util;
using namespace liborangepower::bitwise;
using namespace liborangepower::strings;
using namespace liborangepower::containers;
using liborangepower::math::Vec2;
using liborangepower::math::Vec3;
//using liborangepower::math::MyCxFixedPt;
using liborangepower::math::CxFixedI24p8;
using liborangepower::math::CxFixedI20p12;
using MyCxFixedPt = liborangepower::math::CxFixedI16p16;
//using MyCxFixedPt = double;
//using liborangepower::math::MyCxFixedPt;
using liborangepower::math::CxFixedPt;
namespace concepts = liborangepower::concepts;
namespace sdl = liborangepower::sdl;

#include <SDL_events.h>
#include <SDL_image.h>

static constexpr double MATH_PI = double(3.141592653589793);
static constexpr Vec2<size_t>
	SCREEN_SIZE_2D{
		.x=640,
		.y=480,
		//.x=32,
		//.y=20,
	};
static constexpr Vec2<MyCxFixedPt>
	HALF_SCREEN_SIZE_2D{
		.x=MyCxFixedPt(SCREEN_SIZE_2D.x) / MyCxFixedPt(2),
		.y=MyCxFixedPt(SCREEN_SIZE_2D.y) / MyCxFixedPt(2),
	};
static constexpr std::array<Vec2<MyCxFixedPt>, 4>
	SCREEN_POLYGON{
		Vec2<MyCxFixedPt>{
			.x=MyCxFixedPt(0),
			.y=MyCxFixedPt(0),
		},
		Vec2<MyCxFixedPt>{
			.x=MyCxFixedPt(SCREEN_SIZE_2D.x - 1),
			.y=MyCxFixedPt(0),
		},
		Vec2<MyCxFixedPt>{
			.x=MyCxFixedPt(SCREEN_SIZE_2D.x - 1),
			.y=MyCxFixedPt(SCREEN_SIZE_2D.y - 1),
		},
		Vec2<MyCxFixedPt>{
			.x=MyCxFixedPt(0),
			.y=MyCxFixedPt(SCREEN_SIZE_2D.y - 1),
		},
	};

#endif		// src_misc_includes_hpp
