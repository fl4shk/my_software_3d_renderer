#ifndef src_cube_class_hpp
#define src_cube_class_hpp

#include "tri_class.hpp"

class Cube final {
public:		// types
	enum class TriIdx: u32 {
		TOP,
		BOT,
		MID0,
		MID1,
		MID2,
		MID3,
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
	Texture* img=nullptr;
	Transform model;
	//std::array<Vert, 4>
	//	top,
	//	bot;
	Vec3<MyCxFixedPt>
		//pos,
		size_3d;
public:		// functions
	std::array<std::array<Tri, 2>, size_t(TriIdx::LIM)> to_tri_arr() const;
};

#endif		// src_cube_class_hpp
