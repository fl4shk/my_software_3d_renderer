#ifndef src_rast_class_hpp
#define src_rast_class_hpp

#include "texture_class.hpp"
#include "tri_class.hpp"
#include "transform_class.hpp"
#include "line_drawing_funcs.hpp"

class MyDisplay;

class Rast final {
public:		// types
	//using TriCRef = const Tri&;
	//using TriAtFunc = TriCRef (*)(size_t idx);
private:		// variables
	//std::vector<Tri*> _tri_vec;
	//TriAtFunc _tri_at_func=nullptr;
	//MyDisplay* _disp=nullptr;
public:		// functions
	Rast();
	//Rast(
	//	//TriAtFunc s_tri_at_func=nullptr,
	//	MyDisplay* s_disp=nullptr
	//);
	Rast(const Rast&) = default;
	~Rast();
	Rast& operator = (const Rast&) = default;
	//GEN_GETTER_BY_VAL(tri_at_func);
	//std::vector<std::vector<bool>> 
	std::vector<u8> calc_visib(
		//size_t tri_idx
		const Tri& tri
		//const TriDraw& tri_draw
	) const;
private:		// functions
	std::vector<u8> _calc_flat_top_visib(
		const Tri& tri
	) const;
	std::vector<u8> _calc_flat_bot_visib(
		const Tri& tri
	) const;

};


#endif		// src_rast_class_hpp
