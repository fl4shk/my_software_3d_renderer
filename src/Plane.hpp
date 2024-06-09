#ifndef src_plane_class_hpp
#define src_plane_class_hpp

#include "Tri.hpp"

class Plane final {
public:		// types
	enum class Kind: size_t {
		//W_ZERO,		// v dot (0 0 0 0)
		LEFT,		// v dot (1 0 0 1)
		RIGHT,		// v dot (-1 0 0 1)
		TOP,		// v dot (0 1 0 1)
		BOTTOM,		// v dot (0 -1 0 1)
		NEAR,		// v dot (0 0 1 0)
		FAR,		// v dot (0 0 -1 1)
		//BX,		// (w + x)*(w - x)
		//BY,		// (w + y)*(w - y)
		//BZ,		// (w)*(w - z)
		LIM,
	};
private:		// variables
	Kind _kind;
	//Vec4<MyFixedPt>
	//	_n{0.0, 0.0, 0.0, 1.0};
	//	//_p{0.0, 0.0, 0.0, 1.0};
private:		// fvariables
	//std::vector<Tri> clip_vec;
	//Vec4<MyFixedPt> _old_pos{0.0, 0.0, 0.0, 1.0};
	//u32 _old_out_code = 0;
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

	//bool inside(const Vec4<MyFixedPt>& v) const;
	//constexpr inline MyFixedPt dist(
	//	const Vec4<MyFixedPt>& v
	//) const {
	//	return n().dot(v);
	//}
	//u32 inside(
	//	const Vec4<MyFixedPt>& v1,
	//	const Vec4<MyFixedPt>& v2,
	//	const Vec4<MyFixedPt>& v3
	//) const;
	//std::vector<Vec4<MyFixedPt>> do_clip(
	//	const std::vector<Vec4<MyFixedPt>>& prev_vec
	//) const;
	//std::vector<Tri> do_clip(
	//	const std::vector<Tri>& prev_vec
	//) const;
	std::vector<Vert> do_clip(
		const std::vector<Vert>& prev_vec
	) const;

	constexpr inline Kind kind() const {
		return _kind;
	}
	static constexpr Vert lerp(
		const Vert& v0,
		const Vert& v1,
		MyFixedPt t
	) {
		return Vert{
			.v{
				.x=lerp(v0.v.x, v1.v.x, t),
				.y=lerp(v0.v.y, v1.v.y, t),
				.z=lerp(v0.v.z, v1.v.z, t),
				.w=lerp(v0.v.w, v1.v.w, t),
			},
			.uv{
				.x=lerp(v0.uv.x, v1.uv.x, t),
				.y=lerp(v0.uv.y, v1.uv.y, t),
			},
		};
	}
	//constexpr inline Vec4<MyFixedPt> n() const {
	//	//return _n;
	//	switch (kind()) {
	//		//case Kind::W_ZERO: {
	//		//	return {0.0, 0.0, 0.0, 0.0001};
	//		//	//_p = {0.0, 0.0, 0.0, 0.0};
	//		//}
	//		//	break;
	//		case Kind::LEFT: {
	//			//return v.x + v.w;
	//			return {1.0, 0.0, 0.0, 1.0};
	//			//_p = {-1.0, 0.0, 0.0, 1.0};
	//		}
	//			break;
	//		case Kind::RIGHT: {
	//			//return -v.x + v.w;
	//			return {-1.0, 0.0, 0.0, 1.0};
	//			//_p = {1.0, 0.0, 0.0, 1.0};
	//		}
	//			break;
	//		case Kind::TOP: {
	//			//return v.y + v.w;
	//			return {0.0, 1.0, 0.0, 1.0};
	//			//_p = {0.0, -1.0, 0.0, 1.0};
	//		}
	//			break;
	//		case Kind::BOTTOM: {
	//			//return -v.y + v.w;
	//			return {0.0, -1.0, 0.0, 1.0};
	//			//_p = {0.0, 1.0, 0.0, 1.0};
	//		}
	//			break;
	//		//case Kind::NEAR: {
	//		//	//return -v.z;
	//		//	//return {0.0, 0.0, 1.0, 1.0};
	//		//	return {0.0, 0.0, 1.0, 0.0};
	//		//	//_p = {0.0, 0.0, -1.0, 1.0};
	//		//}
	//		//	break;
	//		//	//return -v.z + v.w;
	//		//case Kind::FAR: {
	//		//	//return -v.z + v.w;
	//		//	//_n = {0.0, 0.0, -1.0, 0.0};
	//		//	//return {0.0, 0.0, 1.0, 0.0};
	//		//	return {0.0, 0.0, -1.0, 1.0};
	//		//	//return {0.0, 0.0, -1.0, 1.0};
	//		//	//_p = {0.0, 0.0, -1.0, 0.0};
	//		//}
	//			break;
	//		//case Kind::LIM: 
	//		default: {
	//			//return MyFixedPt(-1.0);
	//			return {0.0, 0.0, 0.0, 0.0};
	//		}
	//			break;
	//	}
	//}
	//inline const Vec4<MyFixedPt>& p() const {
	//	return _p;
	//}


	//static MyFixedPt dot(
	//	Kind kind,
	//	const Vec4<MyFixedPt>& v
	//);
	//u32 out_code(const Vec4<MyFixedPt>& v) const;
	//Vec4<MyFixedPt> intersect(
	//	const Vec4<MyFixedPt>& q1,
	//	const Vec4<MyFixedPt>& q2,
	//	MyFixedPt alpha
	//) const;
	static constexpr MyFixedPt lerp(
		MyFixedPt a,
		MyFixedPt b,
		MyFixedPt t
	) {
		//const MyFixedPt a1 = MyFixedPt(1.0) - t;
		//return MyFixedPt(a1 * a + t * b);
		return a + (b - a) * t;
	}
	//static Vec4<MyFixedPt> lerp(
	//	const Vec4<MyFixedPt>& a,
	//	const Vec4<MyFixedPt>& b,
	//	MyFixedPt alpha
	//);
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
