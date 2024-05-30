#include "transform_cls.hpp"

Transform::Transform() {
}
Transform::Transform(
	const Mat4x4<double>& s_mat
)
	: mat(s_mat) 
{
}
Transform::Transform(
	const Mat3x3<double>& rot_scale,
	const Vec3<double>& translate
) {
	set_rot_scale(rot_scale);
	set_translate(translate);
	for (size_t j=0; j<3u; ++j) {
		mat.m.at(j).at(3) = 0;
	}
	mat.m.at(3).at(3) = 1;
}
Transform::~Transform() {
}
void Transform::set_rot_scale(const Mat3x3<double>& rot_scale) {
	for (size_t j=0; j<3u; ++j) {
		for (size_t i=0; i<3u; ++i) {
			mat.m.at(j).at(i) = rot_scale.m.at(j).at(i);
		}
	}
}
void Transform::set_translate(const Vec3<double>& translate) {
	for (size_t i=0; i<3u; ++i) {
		mat.m.at(3).at(i) = translate.at(i);
	}
}
//TransformRet Transform::affine(const Vec3<double>& v) const {
//	TransformRet ret;
//	const Vec3<double> v_prime = vec_mult_matrix(v, *this);
//	//ret.p_h_prime = Vec4<double>::build_homogeneous(v_prime);
//	//ret.p_c_prime = v_prime;
//	return ret;
//}
//TransformRet Transform::project(const Vec3<double>& v) const {
//	TransformRet ret;
//	//const double w_prime = (
//	//	(v.x * mat.m.at(3).at(0))
//	//	+ (v.y * mat.m.at(3).at(1))
//	//	+ (v.z * mat.m.at(3).at(2))
//	//	+ (mat.m.at(3).at(3))
//	//);
//	//ret.p_h_prime = Vec4<double>{
//	//	.x=
//	//};
//	return ret;
//}
//Vec3<double> operator * (const Vec4<double>& v, const Transform& t) {
//	//--------
//	Vec3<double> ret;
//	//--------
//	double a, b, c, w; 
//
//	const auto& m = t.mat.m;
// 
//    // Note: v.w is assumed to be 1
//    a = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + v.w * m[3][0]; 
//    b = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + v.w * m[3][1]; 
//    c = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + v.w * m[3][2]; 
//    w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + v.w * m[3][3]; 
// 
//    ret.x = a / w; 
//    ret.y = b / w; 
//    ret.z = c / w; 
//
//	return ret;
//	//--------
//}
//Vec3<double> mult_affine(const Vec3<double>& v, const Transform& t) {
//}
Vec3<double> operator * (const Vec3<double>& v, const Transform& t) {
	//--------
	Vec3<double> ret;
	//--------
	double a, b, c, w; 
	const auto& m = t.mat.m;
 
    // Assuming src.w is always 1 for simplicity
    a = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0]; 
    b = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1]; 
    c = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]; 
    w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3]; 
 
    if (w != 1) {
        ret.x = a / w; 
        ret.y = b / w; 
        ret.z = c / w; 
    } else { 
        ret.x = a; 
        ret.y = b; 
        ret.z = c; 
    } 
    //--------
	return ret;
	//--------
}
