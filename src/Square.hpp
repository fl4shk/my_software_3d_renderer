#ifndef src_square_class_hpp
#define src_square_class_hpp

#include "Tri.hpp"

class Square {
public:		// variables
	Vec2<MyFixedPt>
		size_2d={1.0, 1.0};
	Vec3<MyFixedPt>
		pos{0.0, 0.0, 0.0};
	Versor<MyFixedPt>
		rot=Versor<MyFixedPt>::identity();
	//Vec3<MyFixedPt>
	//	rot{0.0, 0.0, 0.0};

	//Transform model;
	Texture* img=nullptr;
	std::array<Tri, 2> tri_arr;
	Transform model;
public:		// functions
	std::array<Tri, 2>& update_tri_arr();
};

#endif		// src_square_class_hpp
