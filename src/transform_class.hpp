#ifndef src_transform_class_hpp
#define src_transform_class_hpp

#include "mat4x4_class.hpp"
#include "mat3x3_class.hpp"

//class TransformRet final {
//public:		// variables
//	Vec4<double> p_h_prime;
//	Vec3<double> p_c_prime;
//};
//enum class TransformKind: uint32_t {
//	
//};

class Transform final {
public:		// constants
	static constexpr Vec3<double> DEFAULT_SCALE{
		.x=double(1),
		.y=double(1),
		.z=double(1),
	};
	static constexpr double DEFAULT_FOV{
		0.25 * 360
	};
public:		// variables
	Mat4x4<double>
		//model,
		//view,
		mat;
public:		// functions
	Transform();
	Transform(
		// any
		const Mat4x4<double>& s_mat
		//double s_near=0.0,
		//double s_far=1.0,
	);
	Transform(
		// affine
		const Mat3x3<double>& rot_scale,
		const Vec3<double>& translate
		//double s_near=0.0,
		//double s_far=1.0,
		//bool is_project=true
	);
	Transform(
		// affine
		const Vec3<double>& rotate,
		const Vec3<double>& translate,
		const Vec3<double>& scale=DEFAULT_SCALE
	);
	Transform(
		// perspective projection
		double near,
		double far,
		double fov=DEFAULT_FOV
	);
	Transform(const Transform&) = default;
	~Transform();
	Transform& operator = (const Transform&) = default;
	//Vec4<double> mult(const Vec4<double>& v) const;
	void set_rot_scale(const Mat3x3<double>& rot_scale);
	void set_rot_scale(
		const Vec3<double>& rotate,
		const Vec3<double>& scale=DEFAULT_SCALE
	);
	void set_translate(const Vec3<double>& translate);
	void set_perspective(
		double near,
		double far,
		double fov=DEFAULT_FOV
	);
	Vec3<double> do_project(
		const Transform& model,
		const Transform& view,
		const Vec3<double>& v
	) const;

	void set_to_affine_finish();
private:		// functions
	void _set_to_perspective_finish();

	//TransformRet affine(const Vec3<double>& v) const;
	//TransformRet project(const Vec3<double>& v) const;
};
//class TransformMvp final {
//public:		// variables
//	Transform* model=nullptr;
//	Transform* view=nullptr;
//	Transform* perspective=nullptr;
//public:		// functions
//	inline Vec3<double> do_project(
//		const Vec3<double>& v
//	) const {
//		return perspective->do_project(
//			*model,
//			*view,
//			v
//		);
//	}
//};
//Vec3<double> project_maybe_divide(
//	const Vec3<double>& v,
//	const Transform& t
//);
//
#endif		// src_transform_class_hpp
