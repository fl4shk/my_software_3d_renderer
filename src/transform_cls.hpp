#ifndef src_transform_cls_hpp
#define src_transform_cls_hpp

#include "mat4x4_cls.hpp"
#include "mat3x3_cls.hpp"

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
};

#endif		// src_transform_cls_hpp
