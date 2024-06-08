#ifndef src_bounding_sphere_class_hpp
#define src_bounding_sphere_class_hpp

#include "Tri.hpp"

class BoundingSphere final {
private:		// variables
	Vec3<MyFixedPt>
		_pos{0.0, 0.0, 0.0};
	MyFixedPt
		_r=1.0;
public:		// functions
	BoundingSphere(
		const Vec3<MyFixedPt>& p1,
		const Vec3<MyFixedPt>& p2,
		const Vec3<MyFixedPt>& p3
	);
	BoundingSphere(
		const Vec4<MyFixedPt>& p1,
		const Vec4<MyFixedPt>& p2,
		const Vec4<MyFixedPt>& p3
	);
	BoundingSphere(const BoundingSphere&) = default;
	~BoundingSphere();
	BoundingSphere& operator = (const BoundingSphere&) = default;

	inline const decltype(_pos)& pos() const {
		return _pos;
	}
	inline const decltype(_r)& r() const {
		return _r;
	}
};
BoundingSphere bounding_sphere_of_tri_clip_v(
	const Tri& tri
);

#endif		// src_bounding_sphere_class_hpp
