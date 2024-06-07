#include "Transform.hpp"
#include <cmath>

Transform::Transform() {
}
Transform::Transform(
	const Mat4x4<MyCxFixedPt>& s_mat
)
	: mat(s_mat) 
{
}
Transform::Transform(
	// affine
	const Mat3x3<MyCxFixedPt>& rot_scale,
	const Vec3<MyCxFixedPt>& translate
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
	const Vec3<MyCxFixedPt>& rotate,
	const Vec3<MyCxFixedPt>& translate,
	const Vec3<MyCxFixedPt>& scale
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
	MyCxFixedPt near,
	MyCxFixedPt far,
	MyCxFixedPt fov
) {
	set_perspective(
		near,
		far,
		fov
	);
}
Transform::~Transform() {
}
void Transform::set_rot_scale(const Mat3x3<MyCxFixedPt>& rot_scale) {
	for (size_t j=0; j<3u; ++j) {
		for (size_t i=0; i<3u; ++i) {
			mat.m.at(j).at(i) = rot_scale.m.at(j).at(i);
		}
	}
	//printout("Transform::set_rot_scale()\n");
	//printout(mat);
}
void Transform::set_rot_scale(
	const Vec3<MyCxFixedPt>& rotate,
	const Vec3<MyCxFixedPt>& scale
) {
	//--------
	Vec3<Mat3x3<MyCxFixedPt>> rot_m_v;
	//--------
	const Vec3<double> rotate_dbl{
		.x=double(rotate.x),
		.y=double(rotate.y),
		.z=double(rotate.z),
	};
	//--------
	rot_m_v.x.m.at(0).at(0) = 1.0;
	rot_m_v.x.m.at(0).at(1) = 0.0;
	rot_m_v.x.m.at(0).at(2) = 0.0;

	rot_m_v.x.m.at(1).at(0) = 0.0;
	rot_m_v.x.m.at(1).at(1) = std::cos(rotate_dbl.x);
	rot_m_v.x.m.at(1).at(2) = -std::sin(rotate_dbl.x);

	rot_m_v.x.m.at(2).at(0) = 0.0;
	rot_m_v.x.m.at(2).at(1) = std::sin(rotate_dbl.x);
	rot_m_v.x.m.at(2).at(2) = std::cos(rotate_dbl.x);
	//rot_m_v.x = MAT3X3_IDENTITY<MyCxFixedPt>;
	//--------
	rot_m_v.y.m.at(0).at(0) = std::cos(rotate_dbl.y);
	rot_m_v.y.m.at(0).at(1) = 0.0;
	rot_m_v.y.m.at(0).at(2) = std::sin(rotate_dbl.y);

	rot_m_v.y.m.at(1).at(0) = 0.0;
	rot_m_v.y.m.at(1).at(1) = 1.0;
	rot_m_v.y.m.at(1).at(2) = 0.0;

	rot_m_v.y.m.at(2).at(0) = -std::sin(rotate_dbl.y);
	rot_m_v.y.m.at(2).at(1) = 0.0;
	rot_m_v.y.m.at(2).at(2) = std::cos(rotate_dbl.y);
	//--------
	rot_m_v.z.m.at(0).at(0) = std::cos(rotate_dbl.z);
	rot_m_v.z.m.at(0).at(1) = -std::sin(rotate_dbl.z);
	rot_m_v.z.m.at(0).at(2) = 0.0;

	rot_m_v.z.m.at(1).at(0) = std::sin(rotate_dbl.z);
	rot_m_v.z.m.at(1).at(1) = std::cos(rotate_dbl.z);
	rot_m_v.z.m.at(1).at(2) = 0.0;

	rot_m_v.z.m.at(2).at(0) = 0.0;
	rot_m_v.z.m.at(2).at(1) = 0.0;
	rot_m_v.z.m.at(2).at(2) = 1.0;
	//rot_m_v.z = MAT3X3_IDENTITY<MyCxFixedPt>;
	//printout("set_rot_scale() 2-args:\n");
	//printout("3x3 rotation matrices:\n");
	//printout("x:\n", Mat3x3<double>::cast_from(rot_m_v.x), "\n");
	//printout("y:\n", Mat3x3<double>::cast_from(rot_m_v.y), "\n");
	//printout("z:\n", Mat3x3<double>::cast_from(rot_m_v.z), "\n");
	//--------
	//Vec3<Mat3x3<MyCxFixedPt>> rot_scale_m_v;
	//for (size_t k=0; k<rot_scale_m_v.SIZE; ++k) {
	//	rot_scale_m_v.at(k) = rot_m_v.at(k) * scale.at(k);
	//	rot_scale_m_v.at(k) = rot_m_v.at(k);
	//}
	const auto scale_m = _calc_scale_mat(scale);

	//printout("scale 3x3 matrix:\n");
	//printout(Mat3x3<double>::cast_from(scale_m), "\n");
	////printout("x:\n", Mat3x3<double>::cast_from(rot_scale_m_v.x), "\n");
	////printout("y:\n", Mat3x3<double>::cast_from(rot_scale_m_v.y), "\n");
	////printout("z:\n", Mat3x3<double>::cast_from(rot_scale_m_v.z), "\n");
	//--------
	const Mat3x3<MyCxFixedPt> rot_scale_m = (
		// scale should be applied first, otherwise you're scaling your
		// rotation
		((scale_m * rot_m_v.z) * rot_m_v.y) * rot_m_v.x
	);
	//const Mat3x3<MyCxFixedPt> rot_scale_m = (
	//	rot_scale_m_zy * rot_scale_m_v.x
	//);
	//printout("multiplied rotation/scaling matrices:\n");
	////printout(Mat3x3<double>::cast_from(rot_scale_m_zy), "\n");
	//printout(Mat3x3<double>::cast_from(rot_scale_m), "\n");
	set_rot_scale(rot_scale_m);
}
void Transform::set_rot_scale(
	const Versor<MyCxFixedPt>& rotate,
	const Vec3<MyCxFixedPt>& scale
) {
	set_rot_scale(
		_calc_scale_mat(scale) * rotate.to_rot_mat()
	);
}
void Transform::set_translate(const Vec3<MyCxFixedPt>& translate) {
	for (size_t j=0; j<3u; ++j) {
		mat.m.at(j).at(3) = translate.at(j);
	}
	//printout("set_translate():\n");
	//printout(mat);
}
Vec3<MyCxFixedPt> Transform::translate() const {
	Vec3<MyCxFixedPt> ret;
	for (size_t j=0; j<ret.SIZE; ++j) {
		ret.at(j) = mat.m.at(j).at(3);
	}
	return ret;
}
void Transform::set_perspective(
	MyCxFixedPt near,
	MyCxFixedPt far,
	MyCxFixedPt fov
) {
	for (size_t j=0; j<mat.SIZE_2D.y; ++j) {
		for (size_t i=0; i<mat.SIZE_2D.x; ++i) {
			mat.m.at(j).at(i) = MyCxFixedPt(0);
		}
	}
	const double my_dbl = double(
		double(fov) / (2.0) * (double(MATH_PI) / (180.0))
	);
	const MyCxFixedPt temp(std::tan(my_dbl));
	//printout("Transform::set_perspective(): 0\n");
	//printout(
	//	std::hex,
	//	//fov.whole_part<i64>(), " ",
	//	//fov.frac_part(), " ",
	//	//fov.data, " ",
	//	MyCxFixedPt(fov), " ",
	//	my_dbl, " ",
	//	//temp.data, "\n",
	//	temp, "\n",
	//	std::dec
	//);
	const MyCxFixedPt e(MyCxFixedPt(1) / temp);
	mat.m.at(0).at(0) = (
		e / (
			MyCxFixedPt(SCREEN_SIZE_2D.x) / MyCxFixedPt(SCREEN_SIZE_2D.y)
		)
	);
	mat.m.at(1).at(1) = e;
	const double near_dbl = double(near);
	const double far_dbl = double(far);
	// https://jsantell.com/3d-projection/
	const MyCxFixedPt temp_0 = MyCxFixedPt(
		//-(far / (far - near))
		//-(far_dbl / (far_dbl - near_dbl))
		(far_dbl + near_dbl) / (near_dbl - far_dbl)
	);
	const MyCxFixedPt temp_1 = MyCxFixedPt(
		//-((far * near) / (far - near))
		//-((far_dbl * near_dbl) / (far_dbl - near_dbl))
		(2.0 * far_dbl * near_dbl) / (near_dbl - far_dbl)
	);
	//printout(
	//	"Transform::set_perspective():\n",
	//	double(temp_0), " ",
	//	double(temp_1),
	//	"\n"
	//);
	mat.m.at(2).at(2) = temp_0;
	mat.m.at(2).at(3) = temp_1;
	_set_to_perspective_finish();
	//printout("Transform::set_perspective(): 1\n");
	//printout(mat);
}
Vec4<MyCxFixedPt> Transform::do_project(
	const Transform& model,
	const Transform& view,
	const Vec4<MyCxFixedPt>& v
) const {
	//--------
	//Vec3<MyCxFixedPt> ret;
	//--------
	//MyCxFixedPt a, b, c, w; 
	//const Transform mvp(mat * (view.mat * model.mat));
	//const Transform mvp((model.mat * view.mat) * mat);
	//const Mat4x4<MyCxFixedPt>
	//	mv(model.mat.mult_homogeneous(view.mat)),
	//	mvp(
	//	 mv.mult_homogeneous(mat)
	//		//(mat * view.mat) * model.mat
	//	);
	//printout("Transform::do_project():\n");

	//Mat4x4<double>
	//	model_dbl,
	//	view_dbl,
	//	perspective_dbl,
	//	//mv_dbl,
	//	//mvp_dbl;
	//for (size_t j=0; j<mvp_dbl.SIZE_2D.y; ++j) {
	//	for (size_t i=0; i<mvp_dbl.SIZE_2D.x; ++i) {
	//		model_dbl.m.at(j).at(i) = double(model.mat.m.at(j).at(i));
	//		view_dbl.m.at(j).at(i) = double(view.mat.m.at(j).at(i));
	//		perspective_dbl.m.at(j).at(i) = double(mat.m.at(j).at(i));
	//		mv_dbl.m.at(j).at(i) = double(mv.m.at(j).at(i));
	//		mvp_dbl.m.at(j).at(i) = double(mvp.m.at(j).at(i));
	//	}
	//}
	//printout(
	//	"model:\n", model_dbl, "\n",
	//	"view:\n", view_dbl, "\n",
	//	"perspective:\n", perspective_dbl, "\n",
	//	"mv:\n", mv_dbl, "\n",
	//	"mvp:\n", mvp_dbl, "\n"
	//);
	//const auto& m = mvp.m;

	const Vec4<MyCxFixedPt>
		model_v = model.mat.mult_homogeneous(
			//Vec4<MyCxFixedPt>::build_homogeneous(v)
			v
		),
		view_v = view.mat.mult_homogeneous(model_v),
		persp_v = mat.mult_homogeneous(view_v),
		//persp_v = mat.mult_homogeneous(model_v),
		//persp_v = mat * view_v,
		//persp_v = mat.mult_homogeneous(v),
		//view_v = view.mat.mult_homogeneous(persp_v),
		//model_v = model.mat.mult_homogeneous(
		//	//Vec4<MyCxFixedPt>::build_homogeneous(v)
		//	view_v
		//),
		//almost_ret = mat * view_v,
		ret(
			//.x=(almost_ret.x /* * MyCxFixedPt(SCREEN_SIZE_2D.x) */),
			//.y=(almost_ret.y /* * MyCxFixedPt(SCREEN_SIZE_2D.y) */),
			//(persp_v.x /*+ HALF_SCREEN_SIZE_2D.x*/),
			//(persp_v.y /*+ HALF_SCREEN_SIZE_2D.y*/),
			//persp_v.z,
			//persp_v.w
			persp_v
		);
	//Mat4x4<MyCxFixedPt>
	//	temp_model(model.mat),
	//	temp_view(view.mat);
	printout(
		"Transform::do_project():\n",
		"persp_mat:\n", mat, "\n",
		"view_mat:\n", view.mat, "\n",
		"model_mat:\n", model.mat, "\n",
		"v", v, "\n",
		"persp_v", persp_v, "\n",
		"view_v", view_v, "\n",
		"model_v", model_v, "\n",
		"\n"
	);

	////temp_model.m.at(0).at(3) -= HALF_SCREEN_SIZE_2D.x;
	////temp_model.m.at(1).at(3) -= HALF_SCREEN_SIZE_2D.y;
	////temp_view.m.at(0).at(3) -= HALF_SCREEN_SIZE_2D.x;
	////temp_view.m.at(1).at(3) -= HALF_SCREEN_SIZE_2D.y;
	//printout(
	//	"model{",
	//		double(model.mat.m.at(0).at(3)), " ", 
	//		double(model.mat.m.at(1).at(3)),
	//	"}\n",
	//	"view{",
	//		double(view.mat.m.at(0).at(3)), " ", 
	//		double(view.mat.m.at(1).at(3)),
	//	"}\n"
	//	"temp_model{",
	//		double(temp_model.m.at(0).at(3)), " ", 
	//		double(temp_model.m.at(1).at(3)),
	//	"}\n",
	//	"temp_view{",
	//		double(temp_view.m.at(0).at(3)), " ", 
	//		double(temp_view.m.at(1).at(3)),
	//	"}\n"
	//);
	//const auto
	//	//model_view = temp_view * temp_model,
	//	//mvp = mat * model_view;
	//	pv_mat = mat * temp_view,
	//	mvp = pv_mat * temp_model;
	//const Vec4<MyCxFixedPt>
	//	almost_ret = mvp * v,
	//	ret(
	//		//.x=(almost_ret.x + HALF_SCREEN_SIZE_2D.x) / MyCxFixedPt(2),
	//		//.y=(almost_ret.y + HALF_SCREEN_SIZE_2D.y) / MyCxFixedPt(2),
	//		//.z=almost_ret.z,
	//		//.w=almost_ret.w,
	//		almost_ret
	//	); //mvp.mult_homogeneous(v);
		

	//const Vec3<double>
	//	model_v_dbl{
	//		.x=double(model_v.x),
	//		.y=double(model_v.y),
	//		.z=double(model_v.z),
	//	},
	//	view_v_dbl{
	//		.x=double(view_v.x),
	//		.y=double(view_v.y),
	//		.z=double(view_v.z),
	//	},
	//	almost_ret_dbl{
	//		.x=double(almost_ret.x),
	//		.y=double(almost_ret.y),
	//		.z=double(almost_ret.z),
	//	},
	//	ret_dbl{
	//		.x=double(ret.x),
	//		.y=double(ret.y),
	//		.z=double(ret.z),
	//	};
	//printout(
	//	"model_v: ", model_v_dbl, "\n",
	//	"view_v: ", view_v_dbl, "\n",
	//	"almost_ret: ", almost_ret_dbl, "\n",
	//	"ret: ", ret_dbl, "\n",
	//	"\n"
	//);
 
    // Assuming src.w is always 1 for simplicity
    //a = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
    //b = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
    //c = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
    //w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];
    //const Vec4<MyCxFixedPt> final_mult = (
	//	m * Vec4<MyCxFixedPt>::build_homogeneous(v)
	//);
    //a = final_mult.x;
    //b = final_mult.y;
    //c = final_mult.z;
    //w = final_mult.w;
    //printout(
	//	std::hex,
	//	"{",
	//		"a:", double(a)/*.data*/, " ",
	//		"b:", double(b)/*.data*/, " ",
	//		"c:", double(c)/*.data*/, " ",
	//		"w:", double(w)/*.data*/,
	//	"}",
	//	"\n",
	//	std::dec
    //);
 
    //if (w != MyCxFixedPt(1)) {
	//	// do the perspective divide
	//	printout(
	//		"do the perspective divide\n"
	//	);
    //    ret.x = a / w; 
    //    ret.y = b / w; 
    //    ret.z = c / w; 
    //} else {
	//	printout(
	//		"DON'T do the perspective divide\n"
	//	);
    //    ret.x = a; 
    //    ret.y = b; 
    //    ret.z = c; 
    //}
    //printout(
	//	//"{",
	//	//	"a:", double(a)/*.data*/, " ",
	//	//	"b:", double(b)/*.data*/, " ",
	//	//	"c:", double(c)/*.data*/, " ",
	//	//	"w:", double(w)/*.data*/,
	//	//"}",
	//	//"\n",
	//	"{",
	//		//double(a), " ", double(b), " ", double(c), " ", double(w),
	//		"vx:", double(v.x), " ",
	//		"vy:", double(v.y), " ",
	//		"vz:", double(v.z),
	//	"}",
	//	"\n",
	//	"{",
	//		"rx:", double(ret.x), " ",
	//		"ry:", double(ret.y), " ",
	//		"rz:", double(ret.z),
	//	"}", 
	//	"\n\n"
	//);
    //--------
	return ret;
	//--------
}
Transform Transform::look_at(
	const Vec3<MyCxFixedPt>& model_pos,
	//const Transform& view,
	const Vec3<MyCxFixedPt>& up
) const {
	Transform ret;
	//const Vec3<MyCxFixedPt>
	//	n_forward((model_pos - translate()).norm()),
	//	n_up(translate().cross(up).norm()),
	//	n_right(n_forward.cross(n_up).norm());
	//for (size_t j=0; j<3; ++j) {
	//	for (size_t i=0; i<3; ++i) {
	//		if (j == 0) {
	//			ret.mat.m.at(j).at(i) = n_right.at(i);
	//		} else if (j == 1) {
	//			ret.mat.m.at(j).at(i) = n_up.at(i);
	//		} else {
	//			ret.mat.m.at(j).at(i) = n_forward.at(i);
	//		}
	//	}
	//}
	//--------
	const Vec3<MyCxFixedPt>
		eye(translate()),
		center(model_pos),
		n((eye - center).norm()),
		u(up.cross(n).norm()),
		v(n.cross(u));
	const MyCxFixedPt
		neg_u_dot_eye((-u).dot(eye)),
		neg_v_dot_eye((-v).dot(eye)),
		neg_n_dot_eye((-n).dot(eye));

	ret.mat = Mat4x4<MyCxFixedPt>{{
		{
			//{u.at(0), v.at(0), n.at(0), MyCxFixedPt(0.0)},
			//{u.at(1), v.at(1), n.at(1), MyCxFixedPt(0.0)},
			//{u.at(2), v.at(2), n.at(2), MyCxFixedPt(0.0)},
			//{neg_u_dot_eye, neg_v_dot_eye, neg_n_dot_eye, MyCxFixedPt(1.0)},
			{u.at(0), u.at(1), u.at(2), neg_u_dot_eye},
			{v.at(0), v.at(1), v.at(2), neg_v_dot_eye},
			{n.at(0), n.at(1), n.at(2), neg_n_dot_eye},
			{
				MyCxFixedPt(0.0),
				MyCxFixedPt(0.0),
				MyCxFixedPt(0.0), 
				MyCxFixedPt(1.0), 
			},
		}
	}};
	//const Vec3<MyCxFixedPt>
	//	my_translate(translate()),
	//	f((model_pos - my_translate).norm()),
	//	up_prime(up.norm()),
	//	s(f.cross(up_prime)),
	//	u(s.norm().cross(f));
	//ret.mat.m = {
	//	{
	//		{s.x, s.y, s.z, -my_translate.x},
	//		{u.x, u.y, u.z, -my_translate.y},
	//		{-f.x, -f.y, -f.z, -my_translate.z},
	//		{
	//			MyCxFixedPt(0), MyCxFixedPt(0), MyCxFixedPt(0),
	//			MyCxFixedPt(1),
	//		},
	//	},
	//};
	return ret;
}
Transform Transform::look_at(
	const Transform& model,
	const Vec3<MyCxFixedPt>& up
) const {
	return look_at(
		model.translate(),
		up
	);
}
void Transform::set_look_at(
	const Transform& model,
	const Vec3<MyCxFixedPt>& up
) {
	*this = look_at(model, up);
}
void Transform::set_to_affine_finish() {
	for (size_t i=0; i<3u; ++i) {
		mat.m.at(3).at(i) = MyCxFixedPt(0);
	}
	mat.m.at(3).at(3) = MyCxFixedPt(1);
}
void Transform::_set_to_perspective_finish() {
	mat.m.at(3).at(0) = MyCxFixedPt(0);
	mat.m.at(3).at(1) = MyCxFixedPt(0);
	mat.m.at(3).at(2) = MyCxFixedPt(-1);
	mat.m.at(3).at(3) = MyCxFixedPt(0);
}
//TransformRet Transform::affine(const Vec3<MyCxFixedPt>& v) const {
//	TransformRet ret;
//	const Vec3<MyCxFixedPt> v_prime = vec_mult_matrix(v, *this);
//	//ret.p_h_prime = Vec4<MyCxFixedPt>::build_homogeneous(v_prime);
//	//ret.p_c_prime = v_prime;
//	return ret;
//}
//TransformRet Transform::project(const Vec3<MyCxFixedPt>& v) const {
//	TransformRet ret;
//	//const MyCxFixedPt w_prime = (
//	//	(v.x * mat.m.at(3).at(0))
//	//	+ (v.y * mat.m.at(3).at(1))
//	//	+ (v.z * mat.m.at(3).at(2))
//	//	+ (mat.m.at(3).at(3))
//	//);
//	//ret.p_h_prime = Vec4<MyCxFixedPt>{
//	//	.x=
//	//};
//	return ret;
//}
//Vec3<MyCxFixedPt> operator * (const Vec4<MyCxFixedPt>& v, const Transform& t) {
//	//--------
//	Vec3<MyCxFixedPt> ret;
//	//--------
//	MyCxFixedPt a, b, c, w; 
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
//Vec3<MyCxFixedPt> mult_affine(const Vec3<MyCxFixedPt>& v, const Transform& t) {
//}
