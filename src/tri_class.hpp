#ifndef src_tri_class_hpp
#define src_tri_class_hpp

#include "misc_includes.hpp"
//#include "rgb444_class.hpp"
#include "texture_class.hpp"
#include "transform_class.hpp"
#include "vert_class.hpp"

static constexpr size_t TRI_VERT_SIZE = 3;
using TriVert = std::array<Vert, TRI_VERT_SIZE>;

class Tri final {
//private:		// variables
//	//sdl::Surface* _img=nullptr;
public:		// variables
	Texture* img=nullptr;
	//TransformMvp* mvp=nullptr;
	Transform model;
	TriVert
		v,
		project_v;
public:		// functions
	void do_project(
		const Transform& view,
		const Transform& perspective
	);
};

//using TriDrawVert = std::array<Vec2<i32>, TRI_VERT_SIZE>;

//class TriDraw final {
//public:		// variables
//	Tri* tri=nullptr;
//	TriDrawVert v;
//};

#endif		// src_tri_class_hpp
