#ifndef src_transform_class_hpp
#define src_transform_class_hpp

#include "mat4x4_class.hpp"
#include "mat3x3_class.hpp"

//class TransformRet final {
//public:		// variables
//	Vec4<CxFixedI16p16> p_h_prime;
//	Vec3<CxFixedI16p16> p_c_prime;
//};
//enum class TransformKind: uint32_t {
//	
//};

class Transform final {
public:		// constants
	static constexpr Vec3<CxFixedI16p16> DEFAULT_SCALE{
		.x=CxFixedI16p16(1),
		.y=CxFixedI16p16(1),
		.z=CxFixedI16p16(1),
	};
	static constexpr CxFixedI16p16 DEFAULT_FOV{
		0.25 * 360
	};
public:		// variables
	Mat4x4<CxFixedI16p16>
		//model,
		//view,
		mat;
public:		// functions
	Transform();
	Transform(
		// any
		const Mat4x4<CxFixedI16p16>& s_mat
		//CxFixedI16p16 s_near=0.0,
		//CxFixedI16p16 s_far=1.0,
	);
	Transform(
		// affine
		const Mat3x3<CxFixedI16p16>& rot_scale,
		const Vec3<CxFixedI16p16>& translate
		//CxFixedI16p16 s_near=0.0,
		//CxFixedI16p16 s_far=1.0,
		//bool is_project=true
	);
	Transform(
		// affine
		const Vec3<CxFixedI16p16>& rotate,
		const Vec3<CxFixedI16p16>& translate,
		const Vec3<CxFixedI16p16>& scale=DEFAULT_SCALE
	);
	Transform(
		// perspective projection
		CxFixedI16p16 near,
		CxFixedI16p16 far,
		CxFixedI16p16 fov=DEFAULT_FOV
	);
	Transform(const Transform&) = default;
	~Transform();
	Transform& operator = (const Transform&) = default;
	//Vec4<CxFixedI16p16> mult(const Vec4<CxFixedI16p16>& v) const;
	void set_rot_scale(const Mat3x3<CxFixedI16p16>& rot_scale);
	void set_rot_scale(
		const Vec3<CxFixedI16p16>& rotate,
		const Vec3<CxFixedI16p16>& scale=DEFAULT_SCALE
	);
	void set_translate(const Vec3<CxFixedI16p16>& translate);
	void set_perspective(
		CxFixedI16p16 near,
		CxFixedI16p16 far,
		CxFixedI16p16 fov=DEFAULT_FOV
	);
	Vec3<CxFixedI16p16> do_project(
		const Transform& model,
		const Transform& view,
		const Vec3<CxFixedI16p16>& v
	) const;

	void set_to_affine_finish();
private:		// functions
	void _set_to_perspective_finish();

	//TransformRet affine(const Vec3<CxFixedI16p16>& v) const;
	//TransformRet project(const Vec3<CxFixedI16p16>& v) const;
};
//class TransformMvp final {
//public:		// variables
//	Transform* model=nullptr;
//	Transform* view=nullptr;
//	Transform* perspective=nullptr;
//public:		// functions
//	inline Vec3<CxFixedI16p16> do_project(
//		const Vec3<CxFixedI16p16>& v
//	) const {
//		return perspective->do_project(
//			*model,
//			*view,
//			v
//		);
//	}
//};
//Vec3<CxFixedI16p16> project_maybe_divide(
//	const Vec3<CxFixedI16p16>& v,
//	const Transform& t
//);
//
#endif		// src_transform_class_hpp
