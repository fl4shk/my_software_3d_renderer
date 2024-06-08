#ifndef src_bary_lerp_class_hpp
#define src_bary_lerp_class_hpp

#include "MiscIncludes.hpp"
#include "Tri.hpp"

class BaryLerp final {
private:		// variables
	MyFixedPt
		A,
		B,
		C;
	bool _inside_tri = false;
	MyRwFixedPt
		_rw,
		_one_over_rw;
	Vec4<MyFixedPt>
		_v;
	Vec2<MyFixedPt>
		_uv;
public:		// functions
	//BaryLerp(
	//	const Tri& tri,
	//	const Vec2<MyFixedPt>& v1//,
	//	//bool just_coords=false
	//);
	BaryLerp(
		const TriRast& tri,
		const Vec2<MyFixedPt>& v1,
		bool do_rast_interp=true
	);
	BaryLerp(
		const Vert& vt0,
		const Vert& vt1,
		const Vert& vt2,
		const std::array<MyRwFixedPt, TRI_VERT_SIZE>& rw_arr,
		const Vec2<MyFixedPt>& v1,
		bool do_rast_interp=true
	);
	BaryLerp(
		const std::array<Vert, TRI_VERT_SIZE>& v,
		const std::array<MyRwFixedPt, TRI_VERT_SIZE>& rw_arr,
		const Vec2<MyFixedPt>& v1,
		bool do_rast_interp=true
	);
	BaryLerp(const BaryLerp&) = default;
	~BaryLerp() = default;
	BaryLerp& operator = (const BaryLerp&) = default;

	//std::optional<MyFixedPt> lerp(
	//	MyFixedPt v
	//) const;
	constexpr inline MyRwFixedPt rw() const {
		return _rw;
	}
	constexpr inline const Vec4<MyFixedPt>& v() const {
		return _v;
	}
	constexpr inline const decltype(_uv)& uv() const {
		return _uv;
	}

	constexpr inline bool inside_tri() const {
		return _inside_tri;
	}
};

#endif		// src_bary_lerp_class_hpp
