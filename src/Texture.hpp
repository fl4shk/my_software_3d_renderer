#ifndef src_texture_class_hpp
#define src_texture_class_hpp

#include "MiscIncludes.hpp"
#include "ColorsEtc.hpp"

class Texture final {
private:		// variables
	//std::string fname;
	//std::string pal_fname;

    #ifdef __SNOWHOUSECPU__
	std::unique_ptr<u16[]> _img_pixels;
	Vec2<u32> _img_size_2d;
	//void* _img_handle = nullptr;
	#else       // if !defined(__SNOWHOUSECPU__)
	sdl::Surface _img;
	#endif      // defined(__SNOWHOUSECPU__)

	//sdl::Image image;
	//std::unique_ptr<Uint32[]> pixels{nullptr};
	//Vec2<size_t> size_2d{
	//	.x=0,
	//	.y=0,
	//};
public:		// functions
	Texture(const std::string& fname);
	~Texture();
	void load(const std::string& fname);
	Vec2<size_t> size_2d();
	//Uint32& at(const Vec2<size_t>& pos);
	Color at(const Vec2<size_t>& uv);
	#ifndef __SNOWHOUSECPU__
	Uint32 at_u32(const Vec2<size_t>& uv);
	#endif      // !defined(__SNOWHOUSECPU__)
};

#endif		// src_texture_class_hpp
