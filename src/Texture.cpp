#include "Texture.hpp"

Texture::Texture(const std::string& fname) {
	load(fname);
}
Texture::~Texture() {
    //#ifdef __SNOWHOUSECPU__
    //if (_img_handle != nullptr) {
    //    tiny_fs_fclose(_img_handle);
    //}
    //#endif
}

#ifdef __SNOWHOUSECPU__
void Texture::load(const std::string& fname) {
    void* handle = tiny_fs_fopen(fname.c_str(), "r");

    tiny_fs_fread(handle, &_img_size_2d.x, sizeof(_img_size_2d.x));
    tiny_fs_fread(handle, &_img_size_2d.y, sizeof(_img_size_2d.y));
    const u32 temp_img_size = _img_size_2d.y * _img_size_2d.x;
    _img_pixels.reset(new u16[temp_img_size]);
    //memset(_img_pixels.get(), 0, sizeof(u16) * temp_img_size);
    tiny_fs_fread(handle, _img_pixels.get(), sizeof(u16) * temp_img_size);

    tiny_fs_fclose(handle);
}
Vec2<size_t> Texture::size_2d() {
    return Vec2<size_t>{
        .x=size_t(_img_size_2d.x),
        .y=size_t(_img_size_2d.y),
    };
}
Color Texture::at(const Vec2<size_t>& uv) {
    return Color{.data=_img_pixels.get()[uv.y * _img_size_2d.x + uv.x]};
}
#else       // if !defined(__SNOWHOUSECPU__)
void Texture::load(const std::string& fname) {
	_img = IMG_Load(strdup(fname.c_str()));
}
Vec2<size_t> Texture::size_2d() {
    SDL_LockSurface(_img);
    Vec2<size_t> ret = {
        .x=size_t(_img->w),
        .y=size_t(_img->h),
    };
    SDL_UnlockSurface(_img);
    return ret;
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
#endif      // defined(__SNOWHOUSECPU__)
