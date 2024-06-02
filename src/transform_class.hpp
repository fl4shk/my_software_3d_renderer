#ifndef src_transform_class_hpp
#define src_transform_class_hpp

#include "mat4x4_class.hpp"
#include "mat3x3_class.hpp"

//class TransformRet final {
//public:		// variables
//	Vec4<MyCxFixedPt> p_h_prime;
//	Vec3<MyCxFixedPt> p_c_prime;
//};
//enum class TransformKind: uint32_t {
//	
//};

class Transform final {
public:		// constants
	static constexpr Vec3<MyCxFixedPt> DEFAULT_SCALE{
		.x=MyCxFixedPt(1),
		.y=MyCxFixedPt(1),
		.z=MyCxFixedPt(1),
	};
	static constexpr MyCxFixedPt DEFAULT_FOV{
		0.25 * 360
	};
public:		// variables
	Mat4x4<MyCxFixedPt>
		//model,
		//view,
		mat;
public:		// functions
	Transform();
	Transform(
		// any
		const Mat4x4<MyCxFixedPt>& s_mat
		//MyCxFixedPt s_near=0.0,
		//MyCxFixedPt s_far=1.0,
	);
	Transform(
		// affine
		const Mat3x3<MyCxFixedPt>& rot_scale,
		const Vec3<MyCxFixedPt>& translate
		//MyCxFixedPt s_near=0.0,
		//MyCxFixedPt s_far=1.0,
		//bool is_project=true
	);
	Transform(
		// affine
		const Vec3<MyCxFixedPt>& rotate,
		const Vec3<MyCxFixedPt>& translate,
		const Vec3<MyCxFixedPt>& scale=DEFAULT_SCALE
	);
	Transform(
		// perspective projection
		MyCxFixedPt near,
		MyCxFixedPt far,
		MyCxFixedPt fov=DEFAULT_FOV
	);
	Transform(const Transform&) = default;
	~Transform();
	Transform& operator = (const Transform&) = default;
	//Vec4<MyCxFixedPt> mult(const Vec4<MyCxFixedPt>& v) const;
	void set_rot_scale(const Mat3x3<MyCxFixedPt>& rot_scale);
	void set_rot_scale(
		const Vec3<MyCxFixedPt>& rotate,
		const Vec3<MyCxFixedPt>& scale=DEFAULT_SCALE
	);
	void set_translate(const Vec3<MyCxFixedPt>& translate);
	void set_perspective(
		MyCxFixedPt near,
		MyCxFixedPt far,
		MyCxFixedPt fov=DEFAULT_FOV
	);
	Vec4<MyCxFixedPt> do_project(
		const Transform& model,
		const Transform& view,
		const Vec4<MyCxFixedPt>& v
	) const;

	void set_to_affine_finish();
private:		// functions
	void _set_to_perspective_finish();

	//TransformRet affine(const Vec3<MyCxFixedPt>& v) const;
	//TransformRet project(const Vec3<MyCxFixedPt>& v) const;
};
//class TransformMvp final {
//public:		// variables
//	Transform* model=nullptr;
//	Transform* view=nullptr;
//	Transform* perspective=nullptr;
//public:		// functions
//	inline Vec3<MyCxFixedPt> do_project(
//		const Vec3<MyCxFixedPt>& v
//	) const {
//		return perspective->do_project(
//			*model,
//			*view,
//			v
//		);
//	}
//};
//Vec3<MyCxFixedPt> project_maybe_divide(
//	const Vec3<MyCxFixedPt>& v,
//	const Transform& t
//);
//
#endif		// src_transform_class_hpp
