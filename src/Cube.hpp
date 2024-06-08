#ifndef src_cube_class_hpp
#define src_cube_class_hpp

#include "Tri.hpp"
#include "Square.hpp"

class Cube final {
public:		// types
	enum class FaceIdx: u32 {
		TOP,
		BOT,
		LEFT,
		RIGHT,
		FRONT,
		BACK,
		LIM,
	};
public:		// variables
	//std::array<Tri, 2>
	//	top,
	//	bot,
	//	mid0,
	//	mid1,
	//	mid2,
	//	mid3;
	//std::array<Vert, 4>
	//	top,
	//	bot;
	MyFixedPt
		dim=1.0;
	Vec3<MyFixedPt>
		//size_3d{1.0, 1.0, 1.0},
		pos{0.0, 0.0, 0.0};
	Versor<MyFixedPt>
		rot=Versor<MyFixedPt>::identity();

	std::array<Square, size_t(FaceIdx::LIM)> face_arr;
	Texture* img=nullptr;
	Transform model;
public:		// functions
	//std::array<std::array<Tri, 2>, size_t(TriIdx::LIM)> to_tri_arr() const;
	std::array<Square, size_t(FaceIdx::LIM)>& update_face_arr();
};

#endif		// src_cube_class_hpp
