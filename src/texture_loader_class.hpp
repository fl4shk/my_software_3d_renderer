#ifndef src_texture_loader_class_hpp
#define src_texture_loader_class_hpp

#include "texture_class.hpp"
#include "misc_includes.hpp"

class TextureLoader final {
private:	// variables
	std::vector<std::unique_ptr<Texture>> _img_vec;
public:		// functions
	TextureLoader(
		const std::vector<std::string>& s_texture_fname_vec
	);
	TextureLoader( // for when only one texture is to be loaded
		const std::string& s_texture_fname
	);
	~TextureLoader();
	void load(const std::vector<std::string>& n_texture_fname_vec);
	void load(const std::string& n_texture_fname);
};

#endif		// src_texture_loader_class_hpp
