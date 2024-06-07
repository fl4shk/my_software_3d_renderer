#include "BaryLerp.hpp"

BaryLerp::BaryLerp(
	const Tri& tri,
	const Vec2<MyCxFixedPt>& v1
) {
	const Vert& svt0 = tri.screen_v.at(0);
	const Vert& svt1 = tri.screen_v.at(1);
	const Vert& svt2 = tri.screen_v.at(2);

	const MyRwCxFixedPt
		rwa = tri.rw_arr.at(0),
		rwb = tri.rw_arr.at(1),
		rwc = tri.rw_arr.at(2);
	const MyCxFixedPt
		x = v1.x,
		y = v1.y,
		//rwa = tri.rw_arr.at(0), //MyCxFixedPt(1) / vt0.v.w,
		//rwb = tri.rw_arr.at(1), //MyCxFixedPt(1) / vt1.v.w,
		//rwc = tri.rw_arr.at(2), //MyCxFixedPt(1) / vt2.v.w,
		//wa = svt0.v.w,
		//wb = svt1.v.w,
		//wc = svt2.v.w,
		xa = svt0.v.x, // * rw0,
		ya = svt0.v.y, // * rw0,
		za = svt0.v.z, // * rw0,
		xb = svt1.v.x, // * rw1,
		yb = svt1.v.y, // * rw1,
		zb = svt1.v.z, // * rw1,
		xc = svt2.v.x, // * rw2,
		yc = svt2.v.y, // * rw2,
		zc = svt2.v.z, // * rw2,
		ua = svt0.uv.x, // * rwa,
		ub = svt1.uv.x, // * rwa,
		uc = svt2.uv.x, // * rwb,
		va = svt0.uv.y, // * rwb,
		vb = svt1.uv.y, // * rwc,
		vc = svt2.uv.y; // * rwc;
	std::array<std::array<MyCxFixedPt, 2>, 2>
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
		const std::array<std::array<MyCxFixedPt, 2>, 2>& mat2x2
	) -> MyCxFixedPt {
		return (
			mat2x2[0][0] * mat2x2[1][1]
			- mat2x2[0][1] * mat2x2[1][0]
		);
	};
	const MyCxFixedPt
		b_numer_det = det(_b_numer),
		c_numer_det = det(_c_numer),
		denom_det = det(_denom);
		//one_over_denom_det = MyCxFixedPt(1) / denom_det,
		//B = b_numer_det * one_over_denom_det,
		//C = c_numer_det * one_over_denom_det,
		//A = MyCxFixedPt(1) - B - C;
	MyRwCxFixedPt one_over_denom_det;
	//one_over_denom_det.data = (
	//	i64(
	//		denom_det.recip_ldbl()
	//		* (1 << MyRwCxFixedPt::FRAC_WIDTH)
	//	)
	//);
	one_over_denom_det = my_recip(denom_det);
	B = mult_cx_rw(b_numer_det, one_over_denom_det),
	C = mult_cx_rw(c_numer_det, one_over_denom_det),
	A = MyCxFixedPt(1) - B - C;
	if (
		!(
			A < MyCxFixedPt(0) || A > MyCxFixedPt(1)
			|| B < MyCxFixedPt(0) || B > MyCxFixedPt(1)
			|| C < MyCxFixedPt(0) || C > MyCxFixedPt(1)
		)
	) {
		_inside_tri = true;
	}
	const MyCxFixedPt
		interp_rw = (
			mult_cx_rw(A, rwa)
			+ mult_cx_rw(B, rwb)
			+ mult_cx_rw(C, rwc)
		);
	//_one_over_interp_rw.data = (
	//	i64(
	//		interp_rw.recip_ldbl()
	//		* (1 << MyRwCxFixedPt::FRAC_WIDTH)
	//	)
	//);
	_one_over_interp_rw = my_recip(interp_rw);

	_v = {
		.x=x,
		.y=y,
		.z=mult_cx_rw(
			(A * za + B * zb + C * zc),
			_one_over_interp_rw
		)
	};

	_uv = {
		//.x=(A * ua + B * ub + C * uc) / interp_rw,
		//.y=(A * va + B * vb + C * vc) / interp_rw,
		.x=mult_cx_rw(
			(A * ua + B * ub + C * uc),
			_one_over_interp_rw
		),
		.y=mult_cx_rw(
			(A * va + B * vb + C * vc),
			_one_over_interp_rw
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
}
//std::optional<MyCxFixedPt> BaryLerp::lerp(
//	MyCxFixedPt v
//) const {
//	if (!inside_tri()) {
//		return std::nullopt;
//	}
//	return mult_cx_rw(
//		
//	);
//
//}
