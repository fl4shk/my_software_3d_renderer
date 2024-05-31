#ifndef src_texture_class_hpp
#define src_texture_class_hpp

#include "misc_includes.hpp"

class Texture final {
private:		// variables
	//std::string fname;
	//std::string pal_fname;
	sdl::Surface _img;
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
	//Uint32& at(const Vec2<size_t>& pos);
	SDL_Color at(const Vec2<size_t>& uv);
	Uint32 at_u32(const Vec2<size_t>& uv);
};

#endif		// src_texture_class_hpp
