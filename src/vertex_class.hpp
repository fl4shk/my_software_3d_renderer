#ifndef src_vertex_class_hpp
#define src_vertex_class_hpp

#include "misc_includes.hpp"
#include "rgb444_class.hpp"

constexpr inline CxFixedI20p12 bary_lerp(
	const Vec2<CxFixedI20p12>& a,
	const Vec2<CxFixedI20p12>& b, 
	const Vec2<CxFixedI20p12>& t
) {
	return (t.x - a.x) * (b.y - a.y) - (t.y - a.y) * (b.x - a.x);
}
//class Vec4d final {
//public:		// varaibles
//	Vec3<CxFixedI20p12>
//		xyz{
//			.x=0.0,
//			.y=0.0,
//			.z=0.0,
//		};
//	CxFixedI20p12
//		w=0.0;
//};
class Vertex/*: public Vec3<CxFixedI20p12>*/ {
public:		// variables
	//Vec2<CxFixedI20p12>
	//	uv{
	//		.x=0.0,
	//		.y=0.0,
	//	};
	Vec3<CxFixedI20p12>
		pos{
			.x=0.0,
			.y=0.0,
			.z=0.0,
		};
public:		// functions
};

#endif		// src_vertex_class_hpp
