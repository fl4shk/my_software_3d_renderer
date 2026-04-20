#ifndef src_misc_includes_hpp
#define src_misc_includes_hpp

// src/misc_includes.hpp

#include <memory>
#include <cstring>

#include "liborangepower_src/misc/misc_includes.hpp"
#include "liborangepower_src/misc/misc_types.hpp"
//#include "liborangepower_src/misc/misc_output_funcs.hpp"
#include "liborangepower_src/misc/misc_utility_funcs.hpp"
#include "liborangepower_src/misc/misc_bitwise_funcs.hpp"
#include "liborangepower_src/misc/misc_defines.hpp"
#include "liborangepower_src/gen_class_innards_defines.hpp"
#include "liborangepower_src/strings/string_conversion_stuff.hpp"
//#include "liborangepower_src/strings/sconcat_etc.hpp"
#include "liborangepower_src/containers/defer_call_stuff.hpp"
#include "liborangepower_src/concepts/misc_concepts.hpp"
#include "liborangepower_src/concepts/math_concepts.hpp"
#include "liborangepower_src/concepts/std_container_concepts.hpp"
#include "liborangepower_src/concepts/std_stream_concepts.hpp"
#include "liborangepower_src/concepts/is_specialization_concepts.hpp"
#include "liborangepower_src/game_stuff/engine_key_status_class.hpp"
//#include "liborangepower_src/time/time_stuff.hpp"
#include "liborangepower_src/math/vec2_classes.hpp"
#include "liborangepower_src/math/vec3_classes.hpp"
#include "liborangepower_src/math/cx_fixed_pt_class.hpp"
//#include "liborangepower_src/math/vec4_classes.hpp"
#include "liborangepower_src/misc/misc_includes.hpp"

#include "tiny_fs.h"

//#include "liborangepower_src/sdl2/sdl.hpp"
//#include "liborangepower_src/sdl2/dpi_stuff.hpp"
//#include "liborangepower_src/sdl2/keyboard_stuff.hpp"
//#include "liborangepower_src/sdl2/sdl_video.hpp"
//#include "liborangepower_src/sdl2/sdl_render.hpp"
//#include "liborangepower_src/sdl2/sdl_surface.hpp"
//#include "liborangepower_src/sdl2/sdl_rect.hpp"
//#include "liborangepower_src/misc/misc_output_funcs.hpp"

using namespace liborangepower::misc_output;
using namespace liborangepower::integer_types;
using namespace liborangepower::misc_util;
using namespace liborangepower::bitwise;
using namespace liborangepower::strings;
using namespace liborangepower::containers;
using liborangepower::math::Vec2;
using liborangepower::math::Vec3;
//using liborangepower::math::MyFixedPt;
using liborangepower::math::CxFixedI24p8;
using liborangepower::math::CxFixedI20p12;
using liborangepower::math::CxFixedI16p16;
using liborangepower::math::CxFixedPt;

#include "FixedPtClasses.hpp"

//using MyFixedPt = CxFixedI16p16;
//using MyRwFixedPt = CxFixedI16p16;

//using MyFixedPt = PureFixedPt<i32, 14>;
//using MyFixedPt = PureFixedI20p12;

using MyFixedPt = float;//double;
using MyRwFixedPt = float;//double;

//using MyFixedPt = PureFixedPt<i32, 16>;
//using MyRwFixedPt = PureFixedPt<i32, 28>;
//static constexpr size_t MY_RW_FRAC_SHIFT = (
//  i64(MyRwFixedPt::FRAC_WIDTH) - i64(MyFixedPt::FRAC_WIDTH)
//);

constexpr inline MyFixedPt mult_cx_rw(
    MyFixedPt a, MyRwFixedPt rw
) {
    MyFixedPt ret;
    //ret.data = (
    //  (i64(a.data) * i64(rw.data))
    //  >> MyRwFixedPt::FRAC_WIDTH
    //  // the two fractional widths are added to one another
    //);
    ret = a * rw;
    return ret;
}
constexpr inline MyRwFixedPt my_recip(
    MyFixedPt a
) {
    MyRwFixedPt ret;
    //ret.data = (
    //  i64(
    //      a.recip_ldbl()
    //      * (1 << MyRwFixedPt::FRAC_WIDTH)
    //  )
    //);
    //ret = MyRwFixedPt(1.0 / double(a));
    ret = MyRwFixedPt(1) / a;
    return ret;
}

//using liborangepower::math::MyFixedPt;
namespace concepts = liborangepower::concepts;
//namespace sdl = liborangepower::sdl;

//#include <SDL_events.h>
//#include <SDL_image.h>

//static constexpr double MATH_PI = double(M_PI); //double(3.141592653589793);
static constexpr double MATH_PI = double(3.14159265358979323846);
static constexpr Vec2<size_t>
    SCREEN_SIZE_2D{
        .x=(
            //640
            320u
        ),
        .y=(
            //480
            240
        ),
        //.x=800,
        //.y=600,
        //.x=32,
        //.y=20,
    };
static constexpr Vec2<MyFixedPt>
    HALF_SCREEN_SIZE_2D{
        .x=MyFixedPt(SCREEN_SIZE_2D.x) / MyFixedPt(2),
        .y=MyFixedPt(SCREEN_SIZE_2D.y) / MyFixedPt(2),
    };
static constexpr std::array<Vec2<MyFixedPt>, 4>
    SCREEN_POLYGON{
        Vec2<MyFixedPt>{
            .x=MyFixedPt(0),
            .y=MyFixedPt(0),
        },
        Vec2<MyFixedPt>{
            .x=MyFixedPt(SCREEN_SIZE_2D.x - 1),
            .y=MyFixedPt(0),
        },
        Vec2<MyFixedPt>{
            .x=MyFixedPt(SCREEN_SIZE_2D.x - 1),
            .y=MyFixedPt(SCREEN_SIZE_2D.y - 1),
        },
        Vec2<MyFixedPt>{
            .x=MyFixedPt(0),
            .y=MyFixedPt(SCREEN_SIZE_2D.y - 1),
        },
    };

extern "C" {
void melted_moon_print(const char* str);
void melted_moon_write(const void* buf, size_t count);
} // extern "C"

inline void mm_printout_base(const char* arg) {
    melted_moon_print(arg);
}
inline void mm_printout_base(char arg) {
    const char buf[2] = {arg, '\0'};
    melted_moon_print(buf);
}
inline void mm_printout_base(double arg) {
    static constexpr size_t BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(char) * BUF_SIZE);
    buf[snprintf(
        buf, BUF_SIZE,
        "%f",
        //"%e",
        arg
    )] = '\0';
    melted_moon_print(buf);
}
template<std::unsigned_integral UIntT>
inline void mm_printout_base(UIntT arg) {
    static constexpr size_t BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(char) * BUF_SIZE);
    buf[snprintf(
        buf, BUF_SIZE,
        "%llu",
        (unsigned long long int)arg
    )] = '\0';
    melted_moon_print(buf);
}
template<std::signed_integral SIntT>
inline void mm_printout_base(SIntT arg) {
    static constexpr size_t BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(char) * BUF_SIZE);
    buf[snprintf(
        buf, BUF_SIZE,
        "%lli",
        (long long int)arg
    )] = '\0';
    melted_moon_print(buf);
}
template<typename... ArgTypes>
void mm_printout(const ArgTypes&... args);

template<typename T>
inline void mm_printout_base(const Vec2<T>& arg) {
    mm_printout(
        "{",
            arg.x, ", ",
            arg.y,
        "}"
    );
}
template<typename T>
inline void mm_printout_base(const Vec3<T>& arg) {
    mm_printout(
        "{",
            arg.x, ", ",
            arg.y, ", ",
            arg.z,
        "}"
    );
}

template<typename... ArgTypes>
void mm_printout(const ArgTypes&... args) {
    (..., mm_printout_base(args));
}

//inline u64 to_bits(double val) {
//    u64 ret;
//    memcpy(&ret, &val, sizeof(val));
//    return ret;
//}
inline u32 to_bits(float val) {
    u32 ret;
    memcpy(&ret, &val, sizeof(val));
    return ret;
}

inline Vec2<u32> to_bits(const Vec2<float>& val) {
    Vec2<u32> ret;
    for (size_t i=0; i<ret.SIZE; ++i) {
        ret.at(i) = to_bits(val.at(i));
    }
    return ret;
}
inline Vec2<u64> to_bits(const Vec2<double>& val) {
    Vec2<u64> ret;
    for (size_t i=0; i<ret.SIZE; ++i) {
        ret.at(i) = to_bits(val.at(i));
    }
    return ret;
}

inline Vec3<u32> to_bits(const Vec3<float>& val) {
    Vec3<u32> ret;
    for (size_t i=0; i<ret.SIZE; ++i) {
        ret.at(i) = to_bits(val.at(i));
    }
    return ret;
}
inline Vec3<u64> to_bits(const Vec3<double>& val) {
    Vec3<u64> ret;
    for (size_t i=0; i<ret.SIZE; ++i) {
        ret.at(i) = to_bits(val.at(i));
    }
    return ret;
}

#ifdef __SNOWHOUSECPU__
#define my_printout(...) \
    do { \
        mm_printout(__VA_ARGS__); \
    } while (0)
#else
#define my_printout(...) \
    do { \
        printout(__VA_ARGS__); \
    } while (0)
#endif

#endif      // src_misc_includes_hpp
