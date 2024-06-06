#ifndef src_tri_class_hpp
#define src_tri_class_hpp

#include "MiscIncludes.hpp"
//#include "Rgb444.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Vert.hpp"

static constexpr size_t TRI_VERT_SIZE = 3;
using TriVert = std::array<Vert, TRI_VERT_SIZE>;

//constexpr inline MyCxFixedPt bary_lerp(
//	const Vec2<MyCxFixedPt>& a,
//	const Vec2<MyCxFixedPt>& b,
//	const Vec2<MyCxFixedPt>& t
//) {
//    return (t.x - a.x) * (b.y - a.y) - (t.y - a.y) * (b.x - a.x);
//}
//constexpr inline MyCxFixedPt my_lerp(
//	MyCxFixedPt t0,
//	MyCxFixedPt t1,
//	MyCxFixedPt alpha
//) {
//	return t0 * alpha + t1 * (1 - alpha);
//}
class Tri final {
//private:		// variables
//	//sdl::Surface* _img=nullptr;
public:		// variables
	Texture* img=nullptr;
	//TransformMvp* mvp=nullptr;
	Transform* model=nullptr;
	TriVert
		v,
		proj_v,
		screen_v;
	std::array<MyRwCxFixedPt, TRI_VERT_SIZE> rw_arr;
	//std::array<MyCxFixedPt, TRI_VERT_SIZE> rw_arr;
	//std::array<Vec2<MyCxFixedPt>, TRI_VERT_SIZE> persp_v
	//std::vector<Vec2<MyCxFixedPt>> clip_vec;
public:		// functions
	void do_project_etc(
		const Transform& view,
		const Transform& perspective
	);
	//void do_clip();
};

//using TriDrawVert = std::array<Vec2<i32>, TRI_VERT_SIZE>;

//class TriDraw final {
//public:		// variables
//	Tri* tri=nullptr;
//	TriDrawVert v;
//};

#endif		// src_tri_class_hpp
