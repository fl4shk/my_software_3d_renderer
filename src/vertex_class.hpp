#ifndef src_vertex_class_hpp
#define src_vertex_class_hpp

#include "misc_includes.hpp"
#include "rgb444_class.hpp"

constexpr inline double bary_lerp(
	const Vec2<double>& a,
	const Vec2<double>& b, 
	const Vec2<double>& t
) {
	return (t.x - a.x) * (b.y - a.y) - (t.y - a.y) * (b.x - a.x);
}
//class Vec4d final {
//public:		// varaibles
//	Vec3<double>
//		xyz{
//			.x=0.0,
//			.y=0.0,
//			.z=0.0,
//		};
//	double
//		w=0.0;
//};
class Vertex/*: public Vec3<double>*/ {
public:		// variables
	//Vec2<double>
	//	uv{
	//		.x=0.0,
	//		.y=0.0,
	//	};
	Vec3<double>
		pos{
			.x=0.0,
			.y=0.0,
			.z=0.0,
		};
public:		// functions
};

#endif		// src_vertex_class_hpp
