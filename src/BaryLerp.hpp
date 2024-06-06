#ifndef src_bary_lerp_class_hpp
#define src_bary_lerp_class_hpp

#include "MiscIncludes.hpp"
#include "Tri.hpp"

class BaryLerp final {
private:		// variables
	MyCxFixedPt
		A,
		B,
		C;
	bool _inside_tri = false;
	MyRwCxFixedPt
		//_interp_rw,
		_one_over_interp_rw;
	Vec3<MyCxFixedPt>
		_v;
	Vec2<MyCxFixedPt>
		_uv;
public:		// functions
	BaryLerp(
		const Tri& tri,
		const Vec2<MyCxFixedPt>& v//,
		//bool just_coords=false
	);
	BaryLerp(const BaryLerp&) = default;
	~BaryLerp() = default;
	BaryLerp& operator = (const BaryLerp&) = default;

	//std::optional<MyCxFixedPt> lerp(
	//	MyCxFixedPt v
	//) const;
	constexpr inline const decltype(_uv)& uv() const {
		return _uv;
	}

	constexpr inline bool inside_tri() const {
		return _inside_tri;
	}
};

#endif		// src_bary_lerp_class_hpp
