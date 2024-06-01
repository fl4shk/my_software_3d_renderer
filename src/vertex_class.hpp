#ifndef src_vertex_class_hpp
#define src_vertex_class_hpp

#include "misc_includes.hpp"
#include "rgb444_class.hpp"

constexpr inline CxFixedI16p16 bary_lerp(
	const Vec2<CxFixedI16p16>& a,
	const Vec2<CxFixedI16p16>& b, 
	const Vec2<CxFixedI16p16>& t
) {
	return (t.x - a.x) * (b.y - a.y) - (t.y - a.y) * (b.x - a.x);
}
//class Vec4d final {
//public:		// varaibles
//	Vec3<CxFixedI16p16>
//		xyz{
//			.x=0.0,
//			.y=0.0,
//			.z=0.0,
//		};
//	CxFixedI16p16
//		w=0.0;
//};
class Vertex/*: public Vec3<CxFixedI16p16>*/ {
public:		// variables
	//Vec2<CxFixedI16p16>
	//	uv{
	//		.x=0.0,
	//		.y=0.0,
	//	};
	Vec3<CxFixedI16p16>
		pos{
			.x=0.0,
			.y=0.0,
			.z=0.0,
		};
public:		// functions
};

#endif		// src_vertex_class_hpp
