#ifndef src_vertex_class_hpp
#define src_vertex_class_hpp

#include "MiscIncludes.hpp"
#include "Rgb444.hpp"

constexpr inline MyCxFixedPt bary_lerp(
	const Vec2<MyCxFixedPt>& a,
	const Vec2<MyCxFixedPt>& b, 
	const Vec2<MyCxFixedPt>& t
) {
	return (t.x - a.x) * (b.y - a.y) - (t.y - a.y) * (b.x - a.x);
}
//class Vec4d final {
//public:		// varaibles
//	Vec3<MyCxFixedPt>
//		xyz{
//			.x=0.0,
//			.y=0.0,
//			.z=0.0,
//		};
//	MyCxFixedPt
//		w=0.0;
//};
class Vertex/*: public Vec3<MyCxFixedPt>*/ {
public:		// variables
	//Vec2<MyCxFixedPt>
	//	uv{
	//		.x=0.0,
	//		.y=0.0,
	//	};
	Vec3<MyCxFixedPt>
		pos{
			.x=0.0,
			.y=0.0,
			.z=0.0,
		};
public:		// functions
};

#endif		// src_vertex_class_hpp