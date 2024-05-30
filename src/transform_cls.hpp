#ifndef src_transform_cls_hpp
#define src_transform_cls_hpp

#include "mat4x4_cls.hpp"
#include "mat3x3_cls.hpp"

class TransformRet final {
public:		// variables
	Vec4<double> p_h_prime;
	Vec3<double> p_c_prime;
};
class Transform final {
public:		// variables
	Mat4x4<double> mat;
public:		// functions
	Transform();
	Transform(
		const Mat4x4<double>& s_mat
	);
	Transform(
		const Mat3x3<double>& rot_scale,
		const Vec3<double>& translate
	);
	Transform(const Transform&) = default;
	~Transform();
	Transform& operator = (const Transform&) = default;
	//Vec4<double> mult(const Vec4<double>& v) const;
	void set_rot_scale(const Mat3x3<double>& rot_scale);
	void set_translate(const Vec3<double>& translate);
	//TransformRet affine(const Vec3<double>& v) const;
	//TransformRet project(const Vec3<double>& v) const;
};
Vec3<double> operator * (const Vec3<double>& v, const Transform& t);

#endif		// src_transform_cls_hpp
