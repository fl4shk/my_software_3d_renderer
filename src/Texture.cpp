#include "Texture.hpp"

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

	SDL_PixelFormat* fmt = _img->format;
	SDL_Color col;
	Uint8 idx = 0;
	idx = ((Uint8*)_img->pixels)[
		uv.y * _img->w + uv.x
	];
	col = fmt->palette->colors[idx];

	SDL_UnlockSurface(_img);
	return col;
}
Uint32 Texture::at_u32(const Vec2<size_t>& uv) {
	const auto& col = at(uv);
	return Uint32(
		(
			Uint32(col.a) << 24ul
		) | (
			Uint32(col.r) << 16ul
		) | (
			Uint32(col.g) << 8ul
		) | (
			Uint32(col.b) << 0ul
		)
	);
}
