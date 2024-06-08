#ifndef src_rast_class_hpp
#define src_rast_class_hpp

#include "Texture.hpp"
#include "Tri.hpp"
#include "Transform.hpp"
#include "LineDrawingFuncs.hpp"
#include "Vert.hpp"

class MyDisplay;

class Rast final {
public:		// types
	//using TriCRef = const Tri&;
	//using TriAtFunc = TriCRef (*)(size_t idx);
	using DrawT = MyFixedPt;
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
		const TriRast& tri,
		std::vector<VertTextureCoords>& ret,
		MyFixedPt near
	) const;
private:		// functions
	void _calc_flat_top_visib(
		const TriRast& tri,
		//const Vert& v1,
		//const Vert& v2,
		//const Vert& v3,
		//std::vector<Vec2<DrawT>>& ret
		std::vector<VertTextureCoords>& ret
	) const;
	void _calc_flat_bot_visib(
		const TriRast& tri,
		//const Vert& v1,
		//const Vert& v2,
		//const Vert& v3,
		//std::vector<Vec2<DrawT>>& ret
		std::vector<VertTextureCoords>& ret
	) const;
	void _do_push_back(
		//const Vert& v1,
		//const Vert& v2,
		//const Vert& v3,
		const TriRast& tri,
		const Vec2<DrawT>& v,
		std::vector<VertTextureCoords>& ret
	) const;
};


#endif		// src_rast_class_hpp
