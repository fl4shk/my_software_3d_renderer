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
#include "liborangepower_src/math/vec2_classes.hpp"
#include "liborangepower_src/math/vec3_classes.hpp"
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
namespace concepts = liborangepower::concepts;
namespace sdl = liborangepower::sdl;

#include <SDL_events.h>
#include <SDL_image.h>

#endif		// src_misc_includes_hpp