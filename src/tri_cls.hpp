#ifndef src_tri_cls_hpp
#define src_tri_cls_hpp

#include "misc_includes.hpp"
//#include "rgb444_cls.hpp"
#include "texture_cls.hpp"

static constexpr size_t TRI_VERT_SIZE = 3ull;
using TriVert = std::array<Vec3<double>, TRI_VERT_SIZE>;

class Tri {
//private:		// variables
//	//sdl::Surface* _img=nullptr;
public:		// variables
	Texture* img=nullptr;
	TriVert v;
	//size_t texture_idx=0;
	//Vec2<size_t> texture_size_2d{.x=0, .y=0};
	//std::shared_ptr<Uint32[]> pixels{nullptr};
public:		// functions
	//inline sdl::Surface& img() {
	//	return *_img;
	//}
	//inline const sdl::Surface& image() const {
	//	return *_img;
	//}
};

#endif		// src_tri_cls_hpp
