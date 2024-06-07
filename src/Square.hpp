#ifndef src_square_class_hpp
#define src_square_class_hpp

#include "Tri.hpp"

class Square {
public:		// variables
	Vec2<MyCxFixedPt>
		size_2d={10.0, 10.0};
	Vec3<MyCxFixedPt>
		pos{0.0, 0.0, 0.0 };
	Versor<MyCxFixedPt>
		rot=Versor<MyCxFixedPt>::identity();
	//Vec3<MyCxFixedPt>
	//	rot{0.0, 0.0, 0.0};

	//Transform model;
	Texture* img=nullptr;
	std::array<Tri, 2> tri_arr;
	Transform model;
public:		//
	std::array<Tri, 2>& update_tri_arr();
};

#endif		// src_square_class_hpp
