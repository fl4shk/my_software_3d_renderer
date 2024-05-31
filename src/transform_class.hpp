#ifndef src_transform_class_hpp
#define src_transform_class_hpp

#include "mat4x4_class.hpp"
#include "mat3x3_class.hpp"

//class TransformRet final {
//public:		// variables
//	Vec4<CxFixedI20p12> p_h_prime;
//	Vec3<CxFixedI20p12> p_c_prime;
//};
//enum class TransformKind: uint32_t {
//	
//};

class Transform final {
public:		// constants
	static constexpr Vec3<CxFixedI20p12> DEFAULT_SCALE{
		.x=CxFixedI20p12(1),
		.y=CxFixedI20p12(1),
		.z=CxFixedI20p12(1),
	};
	static constexpr CxFixedI20p12 DEFAULT_FOV{0.25};
public:		// variables
	Mat4x4<CxFixedI20p12>
		//model,
		//view,
		mat;
public:		// functions
	Transform();
	Transform(
		// any
		const Mat4x4<CxFixedI20p12>& s_mat
		//CxFixedI20p12 s_near=0.0,
		//CxFixedI20p12 s_far=1.0,
	);
	Transform(
		// affine
		const Mat3x3<CxFixedI20p12>& rot_scale,
		const Vec3<CxFixedI20p12>& translate
		//CxFixedI20p12 s_near=0.0,
		//CxFixedI20p12 s_far=1.0,
		//bool is_project=true
	);
	Transform(
		// affine
		const Vec3<CxFixedI20p12>& rotate,
		const Vec3<CxFixedI20p12>& translate,
		const Vec3<CxFixedI20p12>& scale=DEFAULT_SCALE
	);
	Transform(
		// perspective projection
		CxFixedI20p12 near,
		CxFixedI20p12 far,
		CxFixedI20p12 fov=DEFAULT_FOV
	);
	Transform(const Transform&) = default;
	~Transform();
	Transform& operator = (const Transform&) = default;
	Vec3<CxFixedI20p12> do_project(
		const Transform& model,
		const Transform& view,
		const Vec3<CxFixedI20p12>& v
	) const;
	//Vec4<CxFixedI20p12> mult(const Vec4<CxFixedI20p12>& v) const;
	void set_rot_scale(const Mat3x3<CxFixedI20p12>& rot_scale);
	void set_rot_scale(
		const Vec3<CxFixedI20p12>& rotate,
		const Vec3<CxFixedI20p12>& scale=DEFAULT_SCALE
	);
	void set_translate(const Vec3<CxFixedI20p12>& translate);
	void set_perspective(
		CxFixedI20p12 near,
		CxFixedI20p12 far,
		CxFixedI20p12 fov=DEFAULT_FOV
	);

private:		// functions
	void _set_to_perspective_finish();
	void _set_to_affine_finish();

	//TransformRet affine(const Vec3<CxFixedI20p12>& v) const;
	//TransformRet project(const Vec3<CxFixedI20p12>& v) const;
};
class TransformMvp final {
public:		// variables
	Transform* model=nullptr;
	Transform* view=nullptr;
	Transform perspective;
};
//Vec3<CxFixedI20p12> project_maybe_divide(
//	const Vec3<CxFixedI20p12>& v,
//	const Transform& t
//);
//
#endif		// src_transform_class_hpp
