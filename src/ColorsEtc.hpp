#ifndef src_colors_etc_hpp
#define src_colors_etc_hpp

#include "MiscIncludes.hpp"

//class Color final {
//public:     // variables
//    u8 r;
//    u8 g;
//    u8 b;
//};

//using Rgb555 = u16;
//using Rgb888 = u32;
class Rgb555 final {
public:     // constants
    static constexpr size_t BIT_POS_HI_B = 14ull;
    static constexpr size_t BIT_POS_LO_B = 10ull;
    static constexpr size_t BIT_POS_HI_G = 9ull;
    static constexpr size_t BIT_POS_LO_G = 5ull;
    static constexpr size_t BIT_POS_HI_R = 4ull;
    static constexpr size_t BIT_POS_LO_R = 0ull;
public:     // variables
    u16 data = 0u;
public:     // functions
    constexpr inline void set_r(u16 n_r) {
        set_bits_with_range(data, n_r, BIT_POS_HI_R, BIT_POS_LO_R);
    }
    constexpr inline u16 get_r() {
        return get_bits_with_range(data, BIT_POS_HI_R, BIT_POS_LO_R);
    }
    constexpr inline void set_g(u16 n_g) {
        set_bits_with_range(data, n_g, BIT_POS_HI_G, BIT_POS_LO_G);
    }
    constexpr inline u16 get_g() {
        return get_bits_with_range(data, BIT_POS_HI_G, BIT_POS_LO_G);
    }
    constexpr inline void set_b(u16 n_b) {
        set_bits_with_range(data, n_b, BIT_POS_HI_B, BIT_POS_LO_B);
    }
    constexpr inline u16 get_b() {
        return get_bits_with_range(data, BIT_POS_HI_B, BIT_POS_LO_B);
    }
    
};

#ifdef __SNOWHOUSECPU__
using Color = Rgb555;
#else // if !defined(__SNOWHOUSECPU__)
using Color = SDL_Color;
#endif      // __SNOWHOUSECPU__

#endif      // src_colors_etc_hpp
