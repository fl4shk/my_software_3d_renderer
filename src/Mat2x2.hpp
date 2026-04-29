#ifndef src_mat2x2_class_hpp
#define src_mat2x2_class_hpp

#include <cmath>
#include "MiscIncludes.hpp"

template<typename T>
class Mat2x2 final {
public:     // constants
    static constexpr Vec2<size_t>
        SIZE_2D{
            .x=2u,
            .y=2u,
        };
public:     // variables
    std::array<
        std::array<T, SIZE_2D.x>,
        SIZE_2D.y
    > m;
public:     // functions
    //[[gnu::noinline]]
    T det() const {
        return (
            m[0][0] * m[1][1]
            - m[0][1] * m[1][0]
        );
    }
};

template<typename T>
static constexpr Mat2x2<T> MAT2X2_IDENTITY{
    .m={
        {
            {T(1), T(0)},
            {T(0), T(1)},
        }
    }
};

//template<typename T>
//[[gnu::noinline]]
//void mm_printout_base(const Mat2x2<T>& mat) {
//    static constexpr Vec2<size_t> SIZE_2D = mat.SIZE_2D;
//    //my_printout_base(
//    //);
//    //for (size_t j=0; j<SIZE_2D.y; ++j) {
//    //    for (size_t i=0; i<SIZE_2D.x; ++i) {
//    //        my_printout(mat.m[j][i], " ");
//    //    }
//    //    my_printout(" ");
//    //}
//}

#endif      // src_mat2x2_class_hpp
