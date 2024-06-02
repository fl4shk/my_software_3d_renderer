#ifndef src_vert_class_hpp
#define src_vert_class_hpp

#include "misc_includes.hpp"
#include "vec4_class.hpp"

class Vert final {
public:		// variables
	Vec4<MyCxFixedPt> v;
	Vec2<MyCxFixedPt> uv;
public:		// functions
	constexpr inline Vec2<MyCxFixedPt> v2() const {
		return Vec2<MyCxFixedPt>{
			.x=v.x,
			.y=v.y,
		};
	}
};
class VertTextureCoords final {
public:		// variables
	Vec2<MyCxFixedPt> v;
	Vec2<MyCxFixedPt> uv;
};

#endif		// src_vert_class_hpp
