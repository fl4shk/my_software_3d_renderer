#include "BaryLerp.hpp"

//BaryLerp::BaryLerp(
//	const Tri& tri,
//	const Vec2<MyFixedPt>& v1
//) {
//	init(
//		
//	);
//}
BaryLerp::BaryLerp(
	const TriRast& tri,
	const Vec2<MyFixedPt>& v1,
	bool do_rast_interp
):
	BaryLerp(
		//tri.v.at(0),
		//tri.v.at(1),
		//tri.v.at(2),
		tri.v,
		tri.rw_arr,
		v1,
		do_rast_interp
	)
{
}
BaryLerp::BaryLerp(
	const Vert& vt0,
	const Vert& vt1,
	const Vert& vt2,
	const std::array<MyRwFixedPt, TRI_VERT_SIZE>& rw_arr,
	const Vec2<MyFixedPt>& v1,
	bool do_rast_interp
):
	BaryLerp(
		{vt0, vt1, vt2},
		rw_arr,
		v1,
		do_rast_interp
	)
{
}
BaryLerp::BaryLerp(
	//const Vert& vt0,
	//const Vert& vt1,
	//const Vert& vt2,
	const std::array<Vert, TRI_VERT_SIZE>& v,
	const std::array<MyRwFixedPt, TRI_VERT_SIZE>& rw_arr,
	const Vec2<MyFixedPt>& v1,
	bool do_rast_interp
) {
	//const Vert& svt0 = tri.clip_v.at(0);
	//const Vert& svt1 = tri.clip_v.at(1);
	//const Vert& svt2 = tri.clip_v.at(2);
	const Vert
		& vt0 = v.at(0),
		& vt1 = v.at(1),
		& vt2 = v.at(2);

	const MyRwFixedPt
		//rwa = tri.rw_arr.at(0),
		//rwb = tri.rw_arr.at(1),
		//rwc = tri.rw_arr.at(2);
		rwa = rw_arr.at(0),
		rwb = rw_arr.at(1),
		rwc = rw_arr.at(2);
	const MyFixedPt
		x = v1.x,
		y = v1.y,
		//rwa = tri.rw_arr.at(0), //MyFixedPt(1) / vt0.v.w,
		//rwb = tri.rw_arr.at(1), //MyFixedPt(1) / vt1.v.w,
		//rwc = tri.rw_arr.at(2), //MyFixedPt(1) / vt2.v.w,
		//wa = svt0.v.w,
		//wb = svt1.v.w,
		//wc = svt2.v.w,
		xa = vt0.v.x, // * rw0,
		ya = vt0.v.y, // * rw0,
		za = vt0.v.z, // * rw0,
		wa = vt0.v.w, // * rw0,

		xb = vt1.v.x, // * rw1,
		yb = vt1.v.y, // * rw1,
		zb = vt1.v.z, // * rw1,
		wb = vt1.v.w, // * rw1,

		xc = vt2.v.x, // * rw2,
		yc = vt2.v.y, // * rw2,
		zc = vt2.v.z, // * rw2,
		wc = vt2.v.w, // * rw1,

		ua = vt0.uv.x, // * rwa,
		ub = vt1.uv.x, // * rwa,
		uc = vt2.uv.x, // * rwb,

		va = vt0.uv.y, // * rwb,
		vb = vt1.uv.y, // * rwc,
		vc = vt2.uv.y; // * rwc;
	std::array<std::array<MyFixedPt, 2>, 2>
		_b_numer,
		_c_numer,
		_denom;
	_b_numer = {
		{
			{xa - xc, x - xc},
			{ya - yc, y - yc},
		}
	};
	_c_numer = {
		{
			{xb - xa, x - xa},
			{yb - ya, y - ya},
		}
	};
	_denom = {
		{
			{xb - xa, xc - xa},
			{yb - ya, yc - ya},
		}
	};
	auto det = [](
		const std::array<std::array<MyFixedPt, 2>, 2>& mat2x2
	) -> MyFixedPt {
		return (
			mat2x2[0][0] * mat2x2[1][1]
			- mat2x2[0][1] * mat2x2[1][0]
		);
	};
	const MyFixedPt
		b_numer_det = det(_b_numer),
		c_numer_det = det(_c_numer),
		denom_det = det(_denom);
		//one_over_denom_det = MyFixedPt(1) / denom_det,
		//B = b_numer_det * one_over_denom_det,
		//C = c_numer_det * one_over_denom_det,
		//A = MyFixedPt(1) - B - C;
	MyRwFixedPt one_over_denom_det;
	//one_over_denom_det.data = (
	//	i64(
	//		denom_det.recip_ldbl()
	//		* (1 << MyRwFixedPt::FRAC_WIDTH)
	//	)
	//);
	one_over_denom_det = my_recip(denom_det);
	B = mult_cx_rw(b_numer_det, one_over_denom_det),
	C = mult_cx_rw(c_numer_det, one_over_denom_det),
	A = MyFixedPt(1) - B - C;
	if (!(
		A < MyFixedPt(0) || A > MyFixedPt(1)
		|| B < MyFixedPt(0) || B > MyFixedPt(1)
		|| C < MyFixedPt(0) || C > MyFixedPt(1)
	)) {
		_inside_tri = true;
	} else if (do_rast_interp) {
		return;
	}
	_rw = (
		mult_cx_rw(A, rwa)
		+ mult_cx_rw(B, rwb)
		+ mult_cx_rw(C, rwc)
	);
	//_one_over_interp_rw.data = (
	//	i64(
	//		interp_rw.recip_ldbl()
	//		* (1 << MyRwFixedPt::FRAC_WIDTH)
	//	)
	//);
	_one_over_rw = my_recip(_rw);
	if (do_rast_interp) {
		_v = {
			.x=x,
			.y=y,
			.z=mult_cx_rw(
				(A * za + B * zb + C * zc),
				_one_over_rw
			),
			//.w=interp_rw,
		};

		_uv = {
			//.x=(A * ua + B * ub + C * uc) / interp_rw,
			//.y=(A * va + B * vb + C * vc) / interp_rw,
			.x=mult_cx_rw(
				(A * ua + B * ub + C * uc),
				_one_over_rw
			),
			.y=mult_cx_rw(
				(A * va + B * vb + C * vc),
				_one_over_rw
			),
		};
		//if (
		//	double(uv().x) != 0.0
		//	&& double(uv().y) != 0.0
		//) {
		//	//printout(
		//	//	"ABC", Vec3<double>{double(A), double(B), double(C)}, "\n",
		//	//	"xy", Vec2<double>{double(x), double(y)}, "\n",
		//	//	"uv", Vec2<double>{double(_uv.x), double(_uv.y)}, "\n"
		//	//);
		//}
	} else {
		_v = {
			.x=x,
			.y=y,
			.z=(A * za + B * zb + C * zc),
			.w=(A * wa + B * wb + C * wc),
		};
		_uv = {
			.x=(A * ua + B * ub + C * uc),
			.y=(A * va + B * vb + C * vc),
		};
	}
}
//std::optional<MyFixedPt> BaryLerp::lerp(
//	MyFixedPt v
//) const {
//	if (!inside_tri()) {
//		return std::nullopt;
//	}
//	return mult_cx_rw(
//		
//	);
//
//}
