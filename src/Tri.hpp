#ifndef src_tri_class_hpp
#define src_tri_class_hpp

#include "MiscIncludes.hpp"
//#include "Rgb444.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Vert.hpp"

static constexpr size_t TRI_VERT_SIZE = 3;
using TriVert = std::array<Vert, TRI_VERT_SIZE>;

//constexpr inline MyFixedPt bary_lerp(
//	const Vec2<MyFixedPt>& a,
//	const Vec2<MyFixedPt>& b,
//	const Vec2<MyFixedPt>& t
//) {
//    return (t.x - a.x) * (b.y - a.y) - (t.y - a.y) * (b.x - a.x);
//}
//constexpr inline MyFixedPt my_lerp(
//	MyFixedPt t0,
//	MyFixedPt t1,
//	MyFixedPt alpha
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
		clip_v;
		//screen_v;
	std::array<MyRwFixedPt, TRI_VERT_SIZE> rw_arr;
	//std::array<MyFixedPt, TRI_VERT_SIZE> rw_arr;
	//std::array<Vec2<MyFixedPt>, TRI_VERT_SIZE> persp_v
	//std::vector<Vec2<MyFixedPt>> clip_vec;
public:		// functions
	void do_project(
		const Transform& view,
		const Transform& perspective
	);
	//std::vector<Tri> do_clip() const;
	//void do_clip();
};
class TriRast final {
public:		// variables
	Texture* img=nullptr;
	TriVert v;
	std::array<MyRwFixedPt, TRI_VERT_SIZE> rw_arr;
public:		// functions
	//static TriRast from_subdiv_tri(
	//	const Tri& tri,
	//	const Vec4<MyFixedPt>& v0,
	//	const Vec4<MyFixedPt>& v1,
	//	const Vec4<MyFixedPt>& v2
	//);
};

//using TriDrawVert = std::array<Vec2<i32>, TRI_VERT_SIZE>;

//class TriDraw final {
//public:		// variables
//	Tri* tri=nullptr;
//	TriDrawVert v;
//};

#endif		// src_tri_class_hpp
