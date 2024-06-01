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
	using DrawT = CxFixedI16p16;
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
	void calc_visib(
		const Tri& tri,
		std::vector<Vec2<DrawT>>& ret
	) const;
private:		// functions
	void _calc_flat_top_visib(
		//const Tri& tri,
		const Vec2<DrawT>& v1,
		const Vec2<DrawT>& v2,
		const Vec2<DrawT>& v3,
		std::vector<Vec2<DrawT>>& ret
	) const;
	void _calc_flat_bot_visib(
		//const Tri& tri,
		const Vec2<DrawT>& v1,
		const Vec2<DrawT>& v2,
		const Vec2<DrawT>& v3,
		std::vector<Vec2<DrawT>>& ret
	) const;
};


#endif		// src_rast_class_hpp
