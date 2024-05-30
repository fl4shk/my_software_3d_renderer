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
	for (size_t j=0; j<3u; ++j) {
		for (size_t i=0; i<3u; ++i) {
			mat.m.at(j).at(i) = rot_scale.m.at(j).at(i);
		}
	}
	for (size_t i=0; i<3u; ++i) {
		mat.m.at(3).at(i) = translate.at(i);
	}
	for (size_t j=0; j<3u; ++j) {
		mat.m.at(j).at(3) = 0;
	}
	mat.m.at(3).at(3) = 1;
}
Transform::~Transform() {
}
