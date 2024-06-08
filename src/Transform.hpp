#ifndef src_transform_class_hpp
#define src_transform_class_hpp

#include "Mat4x4.hpp"
#include "Mat3x3.hpp"
#include "Versor.hpp"

//class TransformRet final {
//public:		// variables
//	Vec4<MyFixedPt> p_h_prime;
//	Vec3<MyFixedPt> p_c_prime;
//};
//enum class TransformKind: uint32_t {
//	
//};

class Transform final {
public:		// constants
	static constexpr Vec3<MyFixedPt> DEFAULT_SCALE{
		.x=MyFixedPt(1),
		.y=MyFixedPt(1),
		.z=MyFixedPt(1),
	};
	static constexpr MyFixedPt DEFAULT_FOV{
		//0.25 * 360
		70.0
		//0.125 * 360
		//1
	};
public:		// variables
	Mat4x4<MyFixedPt>
		//model,
		//view,
		mat;
public:		// functions
	Transform();
	Transform(
		// any
		const Mat4x4<MyFixedPt>& s_mat
		//MyFixedPt s_near=0.0,
		//MyFixedPt s_far=1.0,
	);
	Transform(
		// affine
		const Mat3x3<MyFixedPt>& rot_scale,
		const Vec3<MyFixedPt>& translate
		//MyFixedPt s_near=0.0,
		//MyFixedPt s_far=1.0,
		//bool is_project=true
	);
	Transform(
		// affine
		const Vec3<MyFixedPt>& rotate,
		const Vec3<MyFixedPt>& translate,
		const Vec3<MyFixedPt>& scale=DEFAULT_SCALE
	);
	Transform(
		// affine
		const Versor<MyFixedPt>& rotate,
		const Vec3<MyFixedPt>& translate,
		const Vec3<MyFixedPt>& scale=DEFAULT_SCALE
	);
	Transform(
		// perspective projection
		MyFixedPt near,
		MyFixedPt far,
		MyFixedPt fov=DEFAULT_FOV
	);
	Transform(const Transform&) = default;
	~Transform();
	Transform& operator = (const Transform&) = default;
	//Vec4<MyFixedPt> mult(const Vec4<MyFixedPt>& v) const;
	void set_rot_scale(const Mat3x3<MyFixedPt>& rot_scale);
	void set_rot_scale(
		const Vec3<MyFixedPt>& rotate,
		const Vec3<MyFixedPt>& scale=DEFAULT_SCALE
	);
	void set_rot_scale(
		const Versor<MyFixedPt>& rotate,
		const Vec3<MyFixedPt>& scale=DEFAULT_SCALE
	);
	void set_translate(const Vec3<MyFixedPt>& translate);
	Vec3<MyFixedPt> translate() const;
	void set_perspective(
		MyFixedPt near,
		MyFixedPt far,
		MyFixedPt fov=DEFAULT_FOV
	);
	Vec4<MyFixedPt> do_project(
		const Transform& model,
		const Transform& view,
		const Vec4<MyFixedPt>& v
	) const;

	// from `view`'s perspective
	Transform look_at(
		const Vec3<MyFixedPt>& model_pos,
		//const Transform& view,
		const Vec3<MyFixedPt>& up={
			.x=MyFixedPt(0.0),
			.y=MyFixedPt(1.0),
			.z=MyFixedPt(0.0),
		}
	) const;
	Transform look_at(
		const Transform& model,
		const Vec3<MyFixedPt>& up={
			.x=MyFixedPt(0.0),
			.y=MyFixedPt(1.0),
			.z=MyFixedPt(0.0),
		}
	) const;
	void set_look_at(
		const Transform& model,
		const Vec3<MyFixedPt>& up={
			.x=MyFixedPt(0.0),
			.y=MyFixedPt(1.0),
			.z=MyFixedPt(0.0),
		}
	);

	void set_to_affine_finish();
	
	//inline void set_translate(
	//	const Vec3<MyFixedPt>& v
	//) {
	//	for (size_t k=0; k<v.SIZE; ++k) {
	//		mat.m.at(k).at(3) = v.at(k);
	//	}
	//}
private:		// functions
	static constexpr inline Mat3x3<MyFixedPt> _calc_scale_mat(
		const Vec3<MyFixedPt>& scale
	) {
		return Mat3x3<MyFixedPt>{.m{
			{
				{scale.x, 0.0, 0.0},
				{0.0, scale.y, 0.0},
				{0.0, 0.0, scale.z},
			}
		}};
	}
	void _set_to_perspective_finish();

	//TransformRet affine(const Vec3<MyFixedPt>& v) const;
	//TransformRet project(const Vec3<MyFixedPt>& v) const;
};
//class TransformMvp final {
//public:		// variables
//	Transform* model=nullptr;
//	Transform* view=nullptr;
//	Transform* perspective=nullptr;
//public:		// functions
//	inline Vec3<MyFixedPt> do_project(
//		const Vec3<MyFixedPt>& v
//	) const {
//		return perspective->do_project(
//			*model,
//			*view,
//			v
//		);
//	}
//};
//Vec3<MyFixedPt> project_maybe_divide(
//	const Vec3<MyFixedPt>& v,
//	const Transform& t
//);
//
#endif		// src_transform_class_hpp
