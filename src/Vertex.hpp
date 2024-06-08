#ifndef src_vertex_class_hpp
#define src_vertex_class_hpp

#include "MiscIncludes.hpp"
#include "Rgb444.hpp"

constexpr inline MyFixedPt bary_lerp(
	const Vec2<MyFixedPt>& a,
	const Vec2<MyFixedPt>& b, 
	const Vec2<MyFixedPt>& t
) {
	return (t.x - a.x) * (b.y - a.y) - (t.y - a.y) * (b.x - a.x);
}
//class Vec4d final {
//public:		// varaibles
//	Vec3<MyFixedPt>
//		xyz{
//			.x=0.0,
//			.y=0.0,
//			.z=0.0,
//		};
//	MyFixedPt
//		w=0.0;
//};
class Vertex/*: public Vec3<MyFixedPt>*/ {
public:		// variables
	//Vec2<MyFixedPt>
	//	uv{
	//		.x=0.0,
	//		.y=0.0,
	//	};
	Vec3<MyFixedPt>
		pos{
			.x=0.0,
			.y=0.0,
			.z=0.0,
		};
public:		// functions
};

#endif		// src_vertex_class_hpp
