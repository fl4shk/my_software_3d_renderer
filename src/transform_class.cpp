#include "transform_class.hpp"
#include <cmath>

Transform::Transform() {
}
Transform::Transform(
	const Mat4x4<CxFixedI20p12>& s_mat
)
	: mat(s_mat) 
{
}
Transform::Transform(
	// affine
	const Mat3x3<CxFixedI20p12>& rot_scale,
	const Vec3<CxFixedI20p12>& translate
) {
	set_rot_scale(rot_scale);
	set_translate(translate);
	//if (is_project) {
	//	set_to_project();
	//} else {
		_set_to_affine_finish();
	//}
}
Transform::Transform(
	// affine
	const Vec3<CxFixedI20p12>& rotate,
	const Vec3<CxFixedI20p12>& translate,
	const Vec3<CxFixedI20p12>& scale
) {
	set_rot_scale(
		rotate,
		scale
	);
	set_translate(translate);
	_set_to_affine_finish();
}
Transform::~Transform() {
}
Transform::Transform(
	// perspective projection
	CxFixedI20p12 near,
	CxFixedI20p12 far,
	CxFixedI20p12 fov
) {
}
void Transform::set_rot_scale(const Mat3x3<CxFixedI20p12>& rot_scale) {
	for (size_t j=0; j<3u; ++j) {
		for (size_t i=0; i<3u; ++i) {
			mat.m.at(j).at(i) = rot_scale.m.at(j).at(i);
		}
	}
}
void Transform::set_rot_scale(
	const Vec3<CxFixedI20p12>& rotate,
	const Vec3<CxFixedI20p12>& scale
) {
	//--------
	Vec3<Mat3x3<CxFixedI20p12>> rot_m_v;
	//--------
	const Vec3<double> rotate_dbl{
		.x=double(rotate.x),
		.y=double(rotate.y),
		.z=double(rotate.z),
	};
	//--------
	rot_m_v.x.m.at(0).at(0) = CxFixedI20p12(1);
	rot_m_v.x.m.at(0).at(1) = CxFixedI20p12(0);
	rot_m_v.x.m.at(0).at(2) = CxFixedI20p12(0);

	rot_m_v.x.m.at(1).at(0) = CxFixedI20p12(0);
	rot_m_v.x.m.at(1).at(1) = CxFixedI20p12(std::cos(rotate_dbl.x));
	rot_m_v.x.m.at(1).at(2) = CxFixedI20p12(-std::sin(rotate_dbl.x));

	rot_m_v.x.m.at(2).at(0) = CxFixedI20p12(0);
	rot_m_v.x.m.at(2).at(1) = CxFixedI20p12(std::sin(rotate_dbl.x));
	rot_m_v.x.m.at(2).at(2) = CxFixedI20p12(std::cos(rotate_dbl.x));
	//--------
	rot_m_v.y.m.at(0).at(0) = CxFixedI20p12(std::cos(rotate_dbl.y));
	rot_m_v.y.m.at(0).at(1) = CxFixedI20p12(0);
	rot_m_v.y.m.at(0).at(2) = CxFixedI20p12(std::sin(rotate_dbl.y));

	rot_m_v.y.m.at(1).at(0) = CxFixedI20p12(0);
	rot_m_v.y.m.at(1).at(1) = CxFixedI20p12(1);
	rot_m_v.y.m.at(1).at(2) = CxFixedI20p12(0);

	rot_m_v.y.m.at(2).at(0) = CxFixedI20p12(-std::sin(rotate_dbl.y));
	rot_m_v.y.m.at(2).at(1) = CxFixedI20p12(0);
	rot_m_v.y.m.at(2).at(2) = CxFixedI20p12(std::cos(rotate_dbl.y));
	//--------
	rot_m_v.z.m.at(0).at(0) = CxFixedI20p12(std::cos(rotate_dbl.z));
	rot_m_v.z.m.at(0).at(1) = CxFixedI20p12(-std::sin(rotate_dbl.z));
	rot_m_v.z.m.at(0).at(2) = CxFixedI20p12(0);

	rot_m_v.z.m.at(1).at(0) = CxFixedI20p12(std::sin(rotate_dbl.z));
	rot_m_v.z.m.at(1).at(1) = CxFixedI20p12(std::cos(rotate_dbl.z));
	rot_m_v.z.m.at(1).at(2) = CxFixedI20p12(0);

	rot_m_v.z.m.at(2).at(0) = CxFixedI20p12(0);
	rot_m_v.z.m.at(2).at(1) = CxFixedI20p12(0);
	rot_m_v.z.m.at(2).at(2) = CxFixedI20p12(1);
	//--------
	Vec3<Mat3x3<CxFixedI20p12>> rot_scale_m_v;
	for (size_t k=0; k<rot_scale_m_v.SIZE; ++k) {
		rot_scale_m_v.at(k) = rot_scale_m_v.at(k) * scale.at(k);
	}
	//--------
	const Mat3x3<CxFixedI20p12> rot_scale_m(
		(rot_scale_m_v.x * rot_scale_m_v.y) * rot_scale_m_v.z
	);
	set_rot_scale(rot_scale_m);
}
void Transform::set_translate(const Vec3<CxFixedI20p12>& translate) {
	for (size_t j=0; j<3u; ++j) {
		mat.m.at(j).at(3) = translate.at(j);
	}
}
Vec3<CxFixedI20p12> Transform::do_project(
	const Transform& model,
	const Transform& view,
	const Vec3<CxFixedI20p12>& v
) const {
	//--------
	Vec3<CxFixedI20p12> ret;
	//--------
	CxFixedI20p12 a, b, c, w; 
	//const Transform mvp(mat * (view.mat * model.mat));
	const Transform mvp((model.mat * view.mat) * mat);
	const auto& m = mvp.mat.m;
 
    // Assuming src.w is always 1 for simplicity
    a = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
    b = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
    c = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
    w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];
 
    if (w != CxFixedI20p12(1)) {
		// do the perspective divide
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
void Transform::_set_to_affine_finish() {
	for (size_t i=0; i<3u; ++i) {
		mat.m.at(3).at(i) = CxFixedI20p12(0);
	}
	mat.m.at(3).at(3) = CxFixedI20p12(1);
}
void Transform::_set_to_perspective_finish() {
	mat.m.at(0).at(3) = CxFixedI20p12(0);
	mat.m.at(1).at(3) = CxFixedI20p12(0);
	mat.m.at(2).at(3) = CxFixedI20p12(-1);
	mat.m.at(3).at(3) = CxFixedI20p12(0);
}
//TransformRet Transform::affine(const Vec3<CxFixedI20p12>& v) const {
//	TransformRet ret;
//	const Vec3<CxFixedI20p12> v_prime = vec_mult_matrix(v, *this);
//	//ret.p_h_prime = Vec4<CxFixedI20p12>::build_homogeneous(v_prime);
//	//ret.p_c_prime = v_prime;
//	return ret;
//}
//TransformRet Transform::project(const Vec3<CxFixedI20p12>& v) const {
//	TransformRet ret;
//	//const CxFixedI20p12 w_prime = (
//	//	(v.x * mat.m.at(3).at(0))
//	//	+ (v.y * mat.m.at(3).at(1))
//	//	+ (v.z * mat.m.at(3).at(2))
//	//	+ (mat.m.at(3).at(3))
//	//);
//	//ret.p_h_prime = Vec4<CxFixedI20p12>{
//	//	.x=
//	//};
//	return ret;
//}
//Vec3<CxFixedI20p12> operator * (const Vec4<CxFixedI20p12>& v, const Transform& t) {
//	//--------
//	Vec3<CxFixedI20p12> ret;
//	//--------
//	CxFixedI20p12 a, b, c, w; 
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
//Vec3<CxFixedI20p12> mult_affine(const Vec3<CxFixedI20p12>& v, const Transform& t) {
//}
