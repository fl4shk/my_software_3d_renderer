#include "TextureLoader.hpp"

TextureLoader::TextureLoader(
	const std::vector<std::string>& s_texture_fname_vec
) {
	load(s_texture_fname_vec);
}
TextureLoader::TextureLoader(
	const std::string& s_texture_fname
) {
	load(s_texture_fname);
}
TextureLoader::~TextureLoader() {
}

void TextureLoader::load(
	const std::vector<std::string>& n_texture_fname_vec
) {
	for (const auto& texture_fname: n_texture_fname_vec) {
		//_load(texture_fname);
		//auto raw_img = sdl::Surface(
		//	IMG_Load(strdup(texture_fname.c_str()))
		//);
		//auto fmt = raw_img->format;
		auto img = (
			//SDL_ConvertSurface(raw_img, fmt, 0u)
			std::unique_ptr<Texture>(
				new Texture(
					//sdl::Surface(
						//IMG_Load(strdup(
						texture_fname//.c_str()
					//))
					//)
				)
			)
		);
		_img_vec.push_back(std::move(img));
	}
}
void TextureLoader::load(const std::string& n_texture_fname) {
	load(std::vector<std::string>{n_texture_fname});
}
