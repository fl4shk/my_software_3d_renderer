#ifndef src_plane_class_hpp
#define src_plane_class_hpp

#include "Tri.hpp"

class Plane final {
public:		// types
	enum class Kind: size_t {
		LEFT,		// v * (1 0 0 1)
		RIGHT,		// v * (-1 0 0 1)
		TOP,		// v * (0 1 0 1)
		BOTTOM,		// v * (0 -1 0 1)
		NEAR,		// v * (0 0 1 1)
		FAR,		// v * (0 0 -1 0)
		LIM,
	};
private:		// variables
	Kind _kind;
	Vec4<MyFixedPt> _n{0.0, 0.0, 0.0, 1.0};
	std::vector<TriRast> _clip_vec;
	//Vec4<MyFixedPt> _old_pos{0.0, 0.0, 0.0, 1.0};
	//u8 _old_out_code = 0;
public:		// functions
	Plane(
		Kind s_kind
		//const Vec4<MyFixedPt>& s_n
	);
	Plane(const Plane&) = default;
	Plane(Plane&&) = default;
	~Plane() = default;
	Plane& operator = (const Plane&) = default;
	Plane& operator = (Plane&&) = default;

	bool inside(const Vec4<MyFixedPt>& v) const;
	MyFixedPt dist(const Vec4<MyFixedPt>& v) const;
	//u32 inside(
	//	const Vec4<MyFixedPt>& v1,
	//	const Vec4<MyFixedPt>& v2,
	//	const Vec4<MyFixedPt>& v3
	//) const;
	std::vector<TriRast>& update_clip_vec(const Tri& tri);

	inline Kind kind() const {
		return _kind;
	}
	inline const Vec4<MyFixedPt>& n() const {
		return _n;
	}

	//static MyFixedPt dot(
	//	Kind kind,
	//	const Vec4<MyFixedPt>& v
	//);
	//static u8 out_code(const Vec4<MyFixedPt>& v);
	Vec4<MyFixedPt> intersect(
		const Vec4<MyFixedPt>& q,
		const Vec4<MyFixedPt>& p
	) const;
	static MyFixedPt lerp(
		MyFixedPt a,
		MyFixedPt b,
		MyFixedPt alpha
	);
	static Vec4<MyFixedPt> lerp(
		const Vec4<MyFixedPt>& a,
		const Vec4<MyFixedPt>& b,
		MyFixedPt alpha
	);
};


//class Plane final {
//public:		// variables
//	//Vec3<MyFixedPt>
//	//	n{0.0, 0.0, 0.0};
//	//MyFixedPt
//	//	& a = n.x,
//	//	& b = n.y,
//	//	& c = n.z;
//	//MyFixedPt
//	//	d=0.0;
//public:		// functions
//	MyFixedPt dot
//	////constexpr inline Vec3<MyFixedPt> norm() const {
//	////	return n.norm();
//	////}
//	//static constexpr inline Plane from_z(
//	//	MyFixedPt P
//	//) {
//	//	return Plane();
//	//};
//	//static constexpr inline Plane clip_bounds_left(
//	//	const Vec4<MyFixedPt>& v
//	//) {
//	//	const MyFixedPt d(v.w * (v.w - v.x));
//	//	return Plane{
//	//		.n{1.0, 0.0, 0.0},
//	//		.d=d,
//	//	};
//	//}
//	//static constexpr inline Plane clip_bounds_right(
//	//	const Vec4<MyFixedPt>& v
//	//) {
//	//	const MyFixedPt d(v.w * (v.w + v.x));
//	//	return Plane{
//	//		.n{-1.0, 0.0, 0.0},
//	//		.d=d,
//	//	};
//	//}
//	//static constexpr inline Plane clip_bounds_bottom(
//	//	const Vec4<MyFixedPt>& v
//	//) {
//	//	const MyFixedPt d(v.w * (v.w - v.y));
//	//	return Plane{
//	//		.n{0.0, 1.0, 0.0},
//	//		.d=d,
//	//	};
//	//}
//	//static constexpr inline Plane clip_bounds_top(
//	//	const Vec4<MyFixedPt>& v
//	//) {
//	//	const MyFixedPt d(v.w * (v.w + v.y));
//	//	return Plane{
//	//		.n{0.0, -1.0, 0.0},
//	//		.d=d,
//	//	};
//	//}
//	//static constexpr inline Plane clip_bounds_near(
//	//	const Vec4<MyFixedPt>& v
//	//) {
//	//	const MyFixedPt d(v.w * (v.w - v.z));
//	//	return Plane{
//	//		.n{0.0, 0.0, 1.0},
//	//		.d=d,
//	//	};
//	//}
//	//static constexpr inline Plane clip_bounds_far(
//	//	const Vec4<MyFixedPt>& v
//	//) {
//	//	const MyFixedPt d(v.w * (v.w + v.z));
//	//	return Plane{
//	//		.n{0.0, 0.0, -1.0},
//	//		.d=d,
//	//	};
//	//}
//};
//static constexpr Plane
//	CLIP_PLANE_LEFT{ // x/w = -1
//		.n{-1, 0, 0},
//		.d=MyFixedPt(),
//	},
//	CLIP_PLANE_RIGHT{ // x/w = +1
//	},
//	CLIP_PLANE_BOTTOM{ // y/w = -1
//	},
//	CLIP_PLANE_TOP{ // y/w = +1
//	};

#endif		// src_plane_class_hpp
