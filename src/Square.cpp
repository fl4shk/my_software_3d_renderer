#include "Square.hpp"

std::array<Tri, 2>& Square::update_tri_arr() {
	auto
		& a = tri_arr.at(0),
		& b = tri_arr.at(1);


	const Vec2<MyCxFixedPt>
		hs(size_2d / MyCxFixedPt(2.0));
	const MyCxFixedPt
		zero(0.0),
		one(1.0),
		uv_min(0.01),
		uv_max(15.0 / 16.0);
	a.v.at(0).v = {
		.x=-hs.x, 
		.y=-hs.y,
		.z=zero,
		.w=one,
	};
	a.v.at(0).uv = {
		.x=uv_min,
		.y=uv_min,
	};
	a.v.at(1).v = b.v.at(0).v = {
		.x=-hs.x,
		.y=hs.y,
		.z=zero,
		.w=one,
	};
	a.v.at(1).uv = b.v.at(0).uv = {
		.x=uv_min,
		.y=uv_max,
	};
	a.v.at(2).v = b.v.at(1).v = {
		.x=hs.x,
		.y=-hs.y,
		.z=zero,
		.w=one,
	};
	a.v.at(2).uv = b.v.at(1).uv = {
		.x=uv_max,
		.y=uv_min,
	};
	b.v.at(2).v = {
		.x=hs.x,
		.y=hs.y,
		.z=zero,
		.w=one,
	};
	b.v.at(2).uv = {
		.x=uv_max,
		.y=uv_max,
	};

	model.set_rot_scale(rot);
	model.set_translate(pos);
	model.set_to_affine_finish();

	for (size_t i=0; i<tri_arr.size(); ++i) {
		auto& tri = tri_arr.at(i);
		tri.img = img;
		tri.model = &model;
	}

	return tri_arr;
}
