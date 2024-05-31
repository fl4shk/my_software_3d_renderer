#include "transform_class.hpp"
#include <cmath>

Transform::Transform() {
}
Transform::Transform(
	const Mat4x4<double>& s_mat
)
	: mat(s_mat) 
{
}
Transform::Transform(
	// affine
	const Mat3x3<double>& rot_scale,
	const Vec3<double>& translate
) {
	set_rot_scale(rot_scale);
	set_translate(translate);
	//if (is_project) {
	//	set_to_project();
	//} else {
		set_to_affine_finish();
	//}
}
Transform::Transform(
	// affine
	const Vec3<double>& rotate,
	const Vec3<double>& translate,
	const Vec3<double>& scale
) {
	set_rot_scale(
		rotate,
		scale
	);
	set_translate(translate);
	set_to_affine_finish();
}
Transform::Transform(
	// perspective projection
	double near,
	double far,
	double fov
) {
	set_perspective(
		near,
		far,
		fov
	);
}
Transform::~Transform() {
}
void Transform::set_rot_scale(const Mat3x3<double>& rot_scale) {
	for (size_t j=0; j<3u; ++j) {
		for (size_t i=0; i<3u; ++i) {
			mat.m.at(j).at(i) = rot_scale.m.at(j).at(i);
		}
	}
	//printout("Transform::set_rot_scale()\n");
	//printout(mat);
}
void Transform::set_rot_scale(
	const Vec3<double>& rotate,
	const Vec3<double>& scale
) {
	//--------
	Vec3<Mat3x3<double>> rot_m_v;
	//--------
	const Vec3<double> rotate_dbl{
		.x=double(rotate.x),
		.y=double(rotate.y),
		.z=double(rotate.z),
	};
	//--------
	rot_m_v.x.m.at(0).at(0) = double(1);
	rot_m_v.x.m.at(0).at(1) = double(0);
	rot_m_v.x.m.at(0).at(2) = double(0);

	rot_m_v.x.m.at(1).at(0) = double(0);
	rot_m_v.x.m.at(1).at(1) = double(std::cos(rotate_dbl.x));
	rot_m_v.x.m.at(1).at(2) = double(-std::sin(rotate_dbl.x));

	rot_m_v.x.m.at(2).at(0) = double(0);
	rot_m_v.x.m.at(2).at(1) = double(std::sin(rotate_dbl.x));
	rot_m_v.x.m.at(2).at(2) = double(std::cos(rotate_dbl.x));
	//--------
	rot_m_v.y.m.at(0).at(0) = double(std::cos(rotate_dbl.y));
	rot_m_v.y.m.at(0).at(1) = double(0);
	rot_m_v.y.m.at(0).at(2) = double(std::sin(rotate_dbl.y));

	rot_m_v.y.m.at(1).at(0) = double(0);
	rot_m_v.y.m.at(1).at(1) = double(1);
	rot_m_v.y.m.at(1).at(2) = double(0);

	rot_m_v.y.m.at(2).at(0) = double(-std::sin(rotate_dbl.y));
	rot_m_v.y.m.at(2).at(1) = double(0);
	rot_m_v.y.m.at(2).at(2) = double(std::cos(rotate_dbl.y));
	//--------
	rot_m_v.z.m.at(0).at(0) = double(std::cos(rotate_dbl.z));
	rot_m_v.z.m.at(0).at(1) = double(-std::sin(rotate_dbl.z));
	rot_m_v.z.m.at(0).at(2) = double(0);

	rot_m_v.z.m.at(1).at(0) = double(std::sin(rotate_dbl.z));
	rot_m_v.z.m.at(1).at(1) = double(std::cos(rotate_dbl.z));
	rot_m_v.z.m.at(1).at(2) = double(0);

	rot_m_v.z.m.at(2).at(0) = double(0);
	rot_m_v.z.m.at(2).at(1) = double(0);
	rot_m_v.z.m.at(2).at(2) = double(1);
	//printout("set_rot_scale() 2-args:\n");
	//printout("3x3 rotation matrices:\n");
	//printout("x:\n", rot_m_v.x, "\n");
	//printout("y:\n", rot_m_v.y, "\n");
	//printout("z:\n", rot_m_v.z, "\n");
	//--------
	Vec3<Mat3x3<double>> rot_scale_m_v;
	for (size_t k=0; k<rot_scale_m_v.SIZE; ++k) {
		rot_scale_m_v.at(k) = rot_m_v.at(k) * scale.at(k);
	}
	//printout("scaled 3x3 rotation matrices:\n");
	//printout("x:\n", rot_m_v.x, "\n");
	//printout("y:\n", rot_m_v.y, "\n");
	//printout("z:\n", rot_m_v.z, "\n");
	//--------
	const Mat3x3<double> rot_scale_m_xy = (
		(rot_scale_m_v.x * rot_scale_m_v.y) //* rot_scale_m_v.z
	);
	const Mat3x3<double> rot_scale_m = (
		rot_scale_m_xy * rot_scale_m_v.z
	);
	//printout("multiplied rotation/scaling matrices:\n");
	//printout(rot_scale_m_xy);
	//printout(rot_scale_m);
	set_rot_scale(rot_scale_m);
}
void Transform::set_translate(const Vec3<double>& translate) {
	for (size_t j=0; j<3u; ++j) {
		mat.m.at(j).at(3) = translate.at(j);
	}
	//printout("set_translate():\n");
	//printout(mat);
}
void Transform::set_perspective(
	double near,
	double far,
	double fov
) {
	for (size_t j=0; j<mat.SIZE_2D.y; ++j) {
		for (size_t i=0; i<mat.SIZE_2D.x; ++i) {
			mat.m.at(j).at(i) = double(0);
		}
	}
	const double my_dbl = (double(fov) / 2.0) * (MATH_PI / 180.0);
	const double temp(std::tan(my_dbl));
	//printout("Transform::set_perspective(): 0\n");
	//printout(
	//	std::hex,
	//	//fov.whole_part<i64>(), " ",
	//	//fov.frac_part(), " ",
	//	//fov.data, " ",
	//	double(fov), " ",
	//	my_dbl, " ",
	//	//temp.data, "\n",
	//	temp, "\n",
	//	std::dec
	//);
	const double s(double(1) / temp);
	mat.m.at(0).at(0) = s;
	mat.m.at(1).at(1) = s;
	mat.m.at(2).at(2) = -(far / (far - near));
	mat.m.at(2).at(3) = -((far * near) / (far - near));
	_set_to_perspective_finish();
	//printout("Transform::set_perspective(): 1\n");
	//printout(mat);
}
Vec3<double> Transform::do_project(
	const Transform& model,
	const Transform& view,
	const Vec3<double>& v
) const {
	//--------
	Vec3<double> ret;
	//--------
	double a, b, c, w; 
	//const Transform mvp(mat * (view.mat * model.mat));
	//const Transform mvp((model.mat * view.mat) * mat);
	const Mat4x4<double> mvp((model.mat * view.mat) * mat);
	//printout("Transform::do_project():\n");
	//printout(mvp);
	const auto& m = mvp.m;
 
    // Assuming src.w is always 1 for simplicity
    a = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
    b = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
    c = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
    w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];
    //const Vec4<double> final_mult = (
	//	m * Vec4<double>::build_homogeneous(v)
	//);
    //a = final_mult.x;
    //b = final_mult.y;
    //c = final_mult.z;
    //w = final_mult.w;
    //printout(
	//	std::hex,
	//	a/*.data*/, " ",
	//	b/*.data*/, " ",
	//	c/*.data*/, " ",
	//	w/*.data*/, "\n",
	//	std::dec
    //);
 
    if (w != double(1)) {
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
void Transform::set_to_affine_finish() {
	for (size_t i=0; i<3u; ++i) {
		mat.m.at(3).at(i) = double(0);
	}
	mat.m.at(3).at(3) = double(1);
}
void Transform::_set_to_perspective_finish() {
	mat.m.at(3).at(0) = double(0);
	mat.m.at(3).at(1) = double(0);
	mat.m.at(3).at(2) = double(-1);
	mat.m.at(3).at(3) = double(0);
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
