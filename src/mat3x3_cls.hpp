#ifndef src_mat3x3_cls_hpp
#define src_mat3x3_cls_hpp

#include "misc_includes.hpp"

class Mat3x3 final {
public:		// constants
	static constexpr Vec2<size_t>
		SIZE_2D{
			.x=3u,
			.y=3u,
		};
public:		// variable
	std::array<
		std::array<double, SIZE_2D.x>,
		SIZE_2D.y
	> m;
};

#endif		// src_mat3x3_cls_hpp
