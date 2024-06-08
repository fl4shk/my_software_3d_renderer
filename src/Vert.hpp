#ifndef src_vert_class_hpp
#define src_vert_class_hpp

#include "MiscIncludes.hpp"
#include "Vec4.hpp"
#include "Texture.hpp"

class Vert final {
public:		// variables
	Vec4<MyFixedPt> v;
	Vec2<MyFixedPt> uv;
public:		// functions
	constexpr inline Vec2<MyFixedPt> v2() const {
		return Vec2<MyFixedPt>{
			.x=v.x,
			.y=v.y,
		};
	}
};
class VertTextureCoords final {
public:		// variables
	Texture* img=nullptr;
	Vec2<MyFixedPt> v;
	Vec2<MyFixedPt> uv;
};

#endif		// src_vert_class_hpp
