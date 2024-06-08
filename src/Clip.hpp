// https://www.gabrielgambetta.com/computer-graphics-from-scratch/11-clipping.html#clipping-triangles

#ifndef src_clip_class_hpp
#define src_clip_class_hpp

#include "Tri.hpp"
//#include "BoundingSphere.hpp"
#include "Plane.hpp"

//class Clip {
//private:		// variables
//	MyFixedPt
//		_near,
//		_far;
////public:		// variables
//	std::vector<Tri> _tri_vec;
//public:		// functions
//	Clip(
//		const Tri& tri,
//		MyFixedPt s_near,
//		MyFixedPt s_far
//	);
//	Clip(const Clip&) = default;
//	Clip(Clip&&) = default;
//	virtual ~Clip();
//	Clip& operator = (const Clip&) = default;
//	Clip& operator = (Clip&&) = default;
//
//	inline Tri& at(size_t idx) {
//		return _tri_vec.at(idx);
//	}
//	inline const Tri& at(size_t idx) const {
//		return _tri_vec.at(idx);
//	}
//	inline size_t size() const {
//		return _tri_vec.size();
//	}
//	inline auto begin() {
//		return _tri_vec.begin();
//	}
//	inline auto end() {
//		return _tri_vec.end();
//	}
//	inline auto cbegin() const {
//		return _tri_vec.cbegin();
//	}
//	inline auto cend() const {
//		return _tri_vec.cend();
//	}
//	inline MyFixedPt near() const {
//		return _near;
//	}
//	inline MyFixedPt far() const {
//		return _far;
//	}
//	inline const decltype(_tri_vec)& tri_vec() const {
//		return _tri_vec;
//	}
//private:	// functions
//	void _do_clip(
//		const Tri& tri
//	);
//	std::vector<Tri> _clip_tri_against_plane(
//		const Tri& tri,
//		//MyFixedPt P
//		const Plane& plane
//	) const;
//	MyFixedPt _signed_distance(
//		//MyFixedPt P, 
//		const Plane& plane,
//		const Vec3<MyFixedPt>& vt
//	) const;
//
//};

#endif		// src_clip_class_hpp
