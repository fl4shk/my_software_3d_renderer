#include "texture_cls.hpp"

Texture::Texture(const std::string& fname) {
	load(fname);
}
Texture::~Texture() {
}
void Texture::load(const std::string& fname) {
	_img = IMG_Load(strdup(fname.c_str()));
}
SDL_Color Texture::at(const Vec2<size_t>& uv) {
	SDL_LockSurface(_img);

	SDL_PixelFormat* fmt = nullptr;
	SDL_Color col;
	Uint8 idx = 0;
	idx = ((Uint8*)_img->pixels)[
		uv.y * _img->w + uv.x
	];
	col = fmt->palette->colors[idx];

	SDL_UnlockSurface(_img);
	return col;
}
