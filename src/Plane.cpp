#include "Plane.hpp"
#include "BaryLerp.hpp"

// https://cs418.cs.illinois.edu/website/text/clipping.html
Plane::Plane(
	Kind s_kind
	//const Vec4<MyFixedPt>& s_n
)
	: _kind(s_kind)
{
	//switch (kind()) {
	//	case Kind::W_ZERO: {
	//		_n = {0.0, 0.0, 0.0, 0.0};
	//		//_p = {0.0, 0.0, 0.0, 0.0};
	//	}
	//		break;
	//	case Kind::LEFT: {
	//		//return v.x + v.w;
	//		_n = {1.0, 0.0, 0.0, 1.0};
	//		//_p = {-1.0, 0.0, 0.0, 1.0};
	//	}
	//		break;
	//	case Kind::RIGHT: {
	//		//return -v.x + v.w;
	//		_n = {-1.0, 0.0, 0.0, 1.0};
	//		//_p = {1.0, 0.0, 0.0, 1.0};
	//	}
	//		break;
	//	case Kind::TOP: {
	//		//return v.y + v.w;
	//		_n = {0.0, 1.0, 0.0, 1.0};
	//		//_p = {0.0, -1.0, 0.0, 1.0};
	//	}
	//		break;
	//	case Kind::BOTTOM: {
	//		//return -v.y + v.w;
	//		_n = {0.0, -1.0, 0.0, 1.0};
	//		//_p = {0.0, 1.0, 0.0, 1.0};
	//	}
	//		break;
	//	case Kind::NEAR: {
	//		//return v.z + v.w;
	//		_n = {0.0, 0.0, 1.0, 1.0};
	//		//_p = {0.0, 0.0, -1.0, 1.0};
	//	}
	//		break;
	//	case Kind::FAR: {
	//		//return -v.z;
	//		//_n = {0.0, 0.0, -1.0, 0.0};
	//		_n = {0.0, 0.0, 1.0, 0.0};
	//		//_p = {0.0, 0.0, -1.0, 0.0};
	//	}
	//		break;
	//	case Kind::LIM: {
	//		//return MyFixedPt(-1.0);
	//	}
	//		break;
	//}
}

//bool Plane::inside(const Vec4<MyFixedPt>& v) const {
//	//switch (kind()) {
//	//	case Kind::LEFT: {
//	//		//return v.x + v.w;
//	//	}
//	//		break;
//	//	case Kind::RIGHT: {
//	//		//return -v.x + v.w;
//	//	}
//	//		break;
//	//	case Kind::TOP: {
//	//		//return v.y + v.w;
//	//	}
//	//		break;
//	//	case Kind::BOTTOM: {
//	//		//return -v.y + v.w;
//	//	}
//	//		break;
//	//	case Kind::NEAR: {
//	//		//return v.z + v.w;
//	//	}
//	//		break;
//	//	case Kind::FAR: {
//	//		//return -v.z;
//	//	}
//	//		break;
//	//	case Kind::LIM: {
//	//		//return MyFixedPt(-1.0);
//	//	}
//	//		break;
//	//}
//	//const MyFixedPt& my_dist = dist(v);
//	//switch (kind()) {
//	//	case Kind::LEFT: {
//	//		return my_dist <= 0;
//	//	}
//	//		break;
//	//	case Kind::RIGHT: {
//	//		return my_dist >= 0;
//	//	}
//	//		break;
//	//	case Kind::TOP: {
//	//		return my_dist <= 0;
//	//	}
//	//		break;
//	//	case Kind::BOTTOM: {
//	//		return my_dist >= 0;
//	//	}
//	//		break;
//	//	case Kind::NEAR: {
//	//		return my_dist <= 0;
//	//	}
//	//		break;
//	//	case Kind::FAR: {
//	//		return my_dist >= 0;
//	//	}
//	//		break;
//	//	case Kind::LIM: {
//	//	}
//	//		break;
//	//}
//}

//MyFixedPt Plane::dist(const Vec4<MyFixedPt>& v) const {
//	return v.dot(n());
//}
std::vector<Tri> Plane::do_clip(
	const std::vector<Tri>& prev_vec
) const {
	std::vector<Tri> ret;
	//std::vector<Vec4<MyFixedPt>> ret;

	auto calc_alpha = [this](
		const Vec4<MyFixedPt>& v1,
		const Vec4<MyFixedPt>& v2
	) -> MyFixedPt {
		const MyFixedPt
			//--------
			x1 = v1.x,
			y1 = v1.y,
			z1 = v1.z,
			w1 = v1.w,
			//--------
			x2 = v2.x,
			y2 = v2.y,
			z2 = v2.z,
			w2 = v2.w;
			//--------
		switch (kind()) {
			//case Kind::W_ZERO: {
			//	return (w1 / (w1 - w2));
			//}
			//	break;
			case Kind::LEFT: {
				return ((w1 + x1) / ((w1 + x1) - (w2 + x2)));
			}
				break;
			case Kind::RIGHT: {
				return ((w1 - x1) / ((w1 - x1) - (w2 - x2)));
			}
				break;
			case Kind::TOP: {
				return ((w1 - y1) / ((w1 - y1) - (w2 - y2)));
			}
				break;
			case Kind::BOTTOM: {
				return ((w1 + y1) / ((w1 + y1) - (w2 + y2)));
			}
				break;
			case Kind::NEAR: {
				return ((w1 + z1) / ((w1 + z1) - (w2 + z2)));
			}
				break;
			case Kind::FAR: {
				return ((w1 - z1) / ((w1 - z1) - (w2 - z2)));
			}
				break;
			//case Kind::LIM: 
			default: {
				return MyFixedPt(1.0);
			}
				break;
		}
	};

	//MyFixedPt
	//	pdot(0.0),
	//	idot(n().dot(prev_vec.front()));

	//for (size_t i=0; i<prev_vec.size(); ++i) {
	//	const Vec4<MyFixedPt>& Q = prev_vec.at(i);
	//	MyFixedPt
	//		dot = n().dot(Q);
	//		if (dot * pdot < MyFixedPt(0.0)) {
	//		}
	//		if (dot > MyFixedPt(0.0)) {
	//			ret.push_back(Q);
	//		}
	//		pdot = dot;
	//}
	//if (pdot * idot < MyFixedPt(0.0)) {
	//}

	for (const auto& tri: prev_vec) {
		const Vert
			& v0 = tri.proj_v.at(0),
			& v1 = tri.proj_v.at(1),
			& v2 = tri.proj_v.at(2);
		const MyFixedPt
			d0 = dist(v0.v),
			d1 = dist(v1.v),
			d2 = dist(v2.v);

		if (
			d0 > MyFixedPt(0.0)
			&& d1 > MyFixedPt(0.0)
			&& d2 > MyFixedPt(0.0)
		) {
			printout(
				"Plane::update_clip_vec(): all visib: ",
				Vec3<double>{double(d0), double(d1), double(d2)}, " ",
				size_t(kind()),
				"\n"
			);
			ret.push_back(tri);
		} else if (
			d0 <= MyFixedPt(0.0)
			&& d1 <= MyFixedPt(0.0)
			&& d2 <= MyFixedPt(0.0)
		) {
			printout(
				"Plane::update_clip_vec(): off screen: ",
				Vec3<double>{double(d0), double(d1), double(d2)}, " ",
				size_t(kind()),
				"\n"
			);
		} else if (
			(
				d0 > MyFixedPt(0.0)
				&& d1 <= MyFixedPt(0.0)
				&& d2 <= MyFixedPt(0.0)
			) || (
				d1 > MyFixedPt(0.0)
				&& d0 <= MyFixedPt(0.0)
				&& d2 <= MyFixedPt(0.0)
			) || (
				d2 > MyFixedPt(0.0)
				&& d0 <= MyFixedPt(0.0)
				&& d1 <= MyFixedPt(0.0)
			)
		) {
			printout(
				"Plane::update_clip_vec(): clip one positive: ",
				Vec3<double>{double(d0), double(d1), double(d2)}, " ",
				size_t(kind()),
				"\n"
			);
			const Vert
				* A = nullptr,
				* B = nullptr,
				* C = nullptr;
			Vec4<MyFixedPt>
				B_prime_v,
				C_prime_v;
			if (d0 > MyFixedPt(0.0)) {
				A = &v0;
				B = &v1;
				C = &v2;
			} else if (d1 > MyFixedPt(0.0)) {
				A = &v1;
				B = &v0;
				C = &v2;
			} else { // if (d2 > MyFixedPt(0.0)
				A = &v2;
				B = &v0;
				C = &v1;
			}
			B_prime_v = intersect(
				A->v, B->v, calc_alpha(A->v, B->v)
			);
			C_prime_v = intersect(
				A->v, C->v, calc_alpha(A->v, C->v)
			);
			const BaryLerp
				B_prime(
					tri.proj_v,
					tri.rw_arr,
					Vec2<MyFixedPt>{
						B_prime_v.x,
						B_prime_v.y,
					}
				),
				C_prime(
					tri.proj_v,
					tri.rw_arr,
					Vec2<MyFixedPt>{
						C_prime_v.x,
						C_prime_v.y,
					}
				);

			ret.push_back(Tri{
				.img=tri.img,
				.model=tri.model,
				.proj_v={
					*A,
					Vert{
						.v=B_prime.v(),
						.uv=B_prime.uv(),
					},
					Vert{
						.v=C_prime.v(), // C_prime.v()
						.uv=C_prime.uv(), // C_prime.uv()
					},
				},
			});

			//Vec4<MyFixedPt>
			//	B_prime = (
			//		lerp(
			//			A
			//			calc_alpha
			//		)
			//	);
		} else { // only one of (d0, d1, d2) is negative
			printout(
				"Plane::update_clip_vec(): clip one negative: ",
				Vec3<double>{double(d0), double(d1), double(d2)}, " ",
				size_t(kind()),
				"\n"
			);
			const Vert
				* A = nullptr,
				* B = nullptr,
				* C = nullptr;
			Vec4<MyFixedPt>
				A_prime_v,
				B_prime_v;
			if (d0 < MyFixedPt(0.0)) {
				//C_rw = &tri.rw_arr.at(0);
				C = &v0;
				B = &v1;
				A = &v2;
			} else if (d1 < MyFixedPt(0.0)) {
				//C_rw = &tri.rw_arr.at(1);
				C = &v1;
				B = &v0;
				A = &v2;
			} else { // if (d2 < MyFixedPt(0.0)
				//C_rw = &tri.rw_arr.at(2);
				C = &v2;
				B = &v0;
				A = &v1;
			}
			A_prime_v = intersect(
				A->v, C->v, calc_alpha(A->v, C->v)
			);
			B_prime_v = intersect(
				B->v, C->v, calc_alpha(B->v, C->v)
			);

			const BaryLerp
				A_prime(
					tri.proj_v,
					tri.rw_arr,
					Vec2<MyFixedPt>{
						A_prime_v.x,
						A_prime_v.y,
					}
				),
				B_prime(
					tri.proj_v,
					tri.rw_arr,
					Vec2<MyFixedPt>{
						B_prime_v.x,
						B_prime_v.y,
					}
				);
			//// Triangle(A, B, A')
			ret.push_back(Tri{
				.img=tri.img,
				.model=tri.model,
				.proj_v={
					*A,
					*B,
					Vert{
						.v=A_prime.v(),
						.uv=A_prime.uv(),
					},
				},
			});
			//ret.push_back(Tri{
			//	//.img=tri.img,
			//	.clip_v={
			//		*A,
			//		*B,
			//		A_prime,
			//	},
			//});
			//// Triangle(A', B, B')
			ret.push_back(Tri{
				.img=tri.img,
				.model=tri.model,
				.proj_v={
					Vert{
						.v=A_prime.v(),
						.uv=A_prime.uv(),
					},
					*B,
					Vert{
						.v=B_prime.v(),
						.uv=B_prime.uv(),
					},
				},
			});
			//ret.push_back(Tri{
			//	//.img=tri.img,
			//	.clip_v={
			//		A_prime,
			//		*B,
			//		B_prime,
			//	},
			//});
		}
	}
	return ret;
}
//std::vector<Tri> Plane::do_clip(
//	const std::vector<Tri>& prev_clip_vec
//) {
//	//clip_vec.clear();
//	//for (const auto& tri: prev_clip_vec) {
//	//	const Vert
//	//		& v0 = tri.v.at(0),
//	//		& v1 = tri.v.at(1),
//	//		& v2 = tri.v.at(2);
//	//	const MyFixedPt
//	//		d0 = dist(v0.v),
//	//		d1 = dist(v1.v),
//	//		d2 = dist(v2.v);
//
//	//	if (
//	//		d0 > MyFixedPt(0.0)
//	//		&& d1 > MyFixedPt(0.0)
//	//		&& d2 > MyFixedPt(0.0)
//	//	) {
//	//		printout(
//	//			"Plane::update_clip_vec(): all visib: ",
//	//			Vec3<double>{double(d0), double(d1), double(d2)}, " ",
//	//			size_t(kind()),
//	//			"\n"
//	//		);
//	//		clip_vec.push_back(Tri{
//	//			.img=tri.img,
//	//			.v=tri.v,
//	//			.rw_arr=tri.rw_arr,
//	//		});
//	//	} else if (
//	//		d0 <= MyFixedPt(0.0)
//	//		&& d1 <= MyFixedPt(0.0)
//	//		&& d2 <= MyFixedPt(0.0)
//	//	) {
//	//		printout(
//	//			"Plane::update_clip_vec(): off screen: ",
//	//			Vec3<double>{double(d0), double(d1), double(d2)}, " ",
//	//			size_t(kind()),
//	//			"\n"
//	//		);
//	//	} else if (
//	//		(
//	//			d0 > MyFixedPt(0.0)
//	//			&& d1 <= MyFixedPt(0.0)
//	//			&& d2 <= MyFixedPt(0.0)
//	//		) || (
//	//			d1 > MyFixedPt(0.0)
//	//			&& d0 <= MyFixedPt(0.0)
//	//			&& d2 <= MyFixedPt(0.0)
//	//		) || (
//	//			d2 > MyFixedPt(0.0)
//	//			&& d0 <= MyFixedPt(0.0)
//	//			&& d1 <= MyFixedPt(0.0)
//	//		)
//	//	) {
//	//		printout(
//	//			"Plane::update_clip_vec(): clip one positive: ",
//	//			Vec3<double>{double(d0), double(d1), double(d2)}, " ",
//	//			size_t(kind()),
//	//			"\n"
//	//		);
//	//		const MyFixedPt* A_rw = nullptr;
//	//		const Vert
//	//			* A = nullptr,
//	//			* B = nullptr,
//	//			* C = nullptr;
//	//		Vec4<MyFixedPt>
//	//			B_prime,
//	//			C_prime;
//	//		if (d0 > MyFixedPt(0.0)) {
//	//			A_rw = &tri.rw_arr.at(0);
//	//			A = &v0;
//	//			B = &v1;
//	//			C = &v2;
//	//		} else if (d1 > MyFixedPt(0.0)) {
//	//			A_rw = &tri.rw_arr.at(1);
//	//			A = &v1;
//	//			B = &v0;
//	//			C = &v2;
//	//		} else { // if (d2 > MyFixedPt(0.0)
//	//			A_rw = &tri.rw_arr.at(2);
//	//			A = &v2;
//	//			B = &v0;
//	//			C = &v1;
//	//		}
//	//		B_prime = intersect(A->v, B->v);
//	//		C_prime = intersect(A->v, C->v);
//	//		const BaryLerp
//	//			B_prime_lerp(
//	//				tri.v,
//	//				tri.rw_arr,
//	//				Vec2<MyFixedPt>{
//	//					B_prime.x,
//	//					B_prime.y,
//	//				},
//	//				false
//	//			),
//	//			C_prime_lerp(
//	//				tri.v,
//	//				tri.rw_arr,
//	//				Vec2<MyFixedPt>{
//	//					C_prime.x,
//	//					C_prime.y,
//	//				},
//	//				false
//	//			);
//	//		clip_vec.push_back({
//	//			.img=tri.img,
//	//			.v{{
//	//				*A,
//	//				{
//	//					.v=B_prime_lerp.v(),
//	//					.uv=B_prime_lerp.uv(),
//	//				},
//	//				{
//	//					.v=C_prime_lerp.v(),
//	//					.uv=C_prime_lerp.uv(),
//	//				},
//	//			}},
//	//			.rw_arr{{
//	//				//my_recip(A->v.w),
//	//				*A_rw,
//	//				B_prime_lerp.rw(),
//	//				C_prime_lerp.rw(),
//	//			}}
//	//		});
//	//		//to_push.screen_v.at(i)
//	//		//_clip_vec.push_back(Tri::from_subdiv_tri(
//	//		//	tri,
//	//		//	A,
//	//		//	B_prime,
//	//		//	C_prime
//	//		//));
//	//	} else { // only one of (d0, d1, d2) is negative
//	//		printout(
//	//			"Plane::update_clip_vec(): clip one negative: ",
//	//			Vec3<double>{double(d0), double(d1), double(d2)}, " ",
//	//			size_t(kind()),
//	//			"\n"
//	//		);
//	//		// let C be the vertex with a negative distance
//	//		const MyFixedPt
//	//			* A_rw = nullptr,
//	//			* B_rw = nullptr;
//	//			//* C_rw = nullptr;
//	//		const Vert
//	//			* A = nullptr,
//	//			* B = nullptr,
//	//			* C = nullptr;
//	//		Vec4<MyFixedPt>
//	//			A_prime,
//	//			B_prime;
//	//		if (d0 < MyFixedPt(0.0)) {
//	//			//C_rw = &tri.rw_arr.at(0);
//	//			C = &v0;
//	//			B = &v1;
//	//			B_rw = &tri.rw_arr.at(1);
//	//			A = &v2;
//	//			A_rw = &tri.rw_arr.at(2);
//	//		} else if (d1 < MyFixedPt(0.0)) {
//	//			//C_rw = &tri.rw_arr.at(1);
//	//			C = &v1;
//	//			B = &v0;
//	//			B_rw = &tri.rw_arr.at(0);
//	//			A = &v2;
//	//			A_rw = &tri.rw_arr.at(2);
//	//		} else { // if (d2 < MyFixedPt(0.0)
//	//			//C_rw = &tri.rw_arr.at(2);
//	//			C = &v2;
//	//			B = &v0;
//	//			B_rw = &tri.rw_arr.at(0);
//	//			A = &v1;
//	//			A_rw = &tri.rw_arr.at(1);
//	//		}
//	//		A_prime = intersect(A->v, C->v);
//	//		B_prime = intersect(B->v, C->v);
//	//		const BaryLerp
//	//			A_prime_lerp(
//	//				tri.v,
//	//				tri.rw_arr,
//	//				Vec2<MyFixedPt>{
//	//					A_prime.x,
//	//					A_prime.y,
//	//				},
//	//				false
//	//			),
//	//			B_prime_lerp(
//	//				tri.v,
//	//				tri.rw_arr,
//	//				Vec2<MyFixedPt>{
//	//					B_prime.x,
//	//					B_prime.y,
//	//				},
//	//				false
//	//			);
//	//		clip_vec.push_back({
//	//			.img=tri.img,
//	//			.v{{
//	//				*A,
//	//				*B,
//	//				{
//	//					.v=A_prime_lerp.v(),
//	//					.uv=A_prime_lerp.uv(),
//	//				},
//	//			}},
//	//			.rw_arr{{
//	//				//my_recip(A->v.w),
//	//				//*C_rw,
//	//				*A_rw,
//	//				*B_rw,
//	//				A_prime_lerp.rw(),
//	//			}}
//	//		});
//	//		clip_vec.push_back({
//	//			.img=tri.img,
//	//			.v{{
//	//				{
//	//					.v=A_prime_lerp.v(),
//	//					.uv=A_prime_lerp.uv(),
//	//				},
//	//				*B,
//	//				{
//	//					.v=B_prime_lerp.v(),
//	//					.uv=B_prime_lerp.uv(),
//	//				},
//	//			}},
//	//			.rw_arr{{
//	//				//my_recip(A->v.w),
//	//				//*C_rw,
//	//				A_prime_lerp.rw(),
//	//				*B_rw,
//	//				B_prime_lerp.rw(),
//	//			}}
//	//		});
//	//		//to_push.screen_v.at(i)
//	//		//_clip_vec.push_back(Tri::from_subdiv_tri(
//	//		//	tri,
//	//		//	A,
//	//		//	B_prime,
//	//		//	C_prime
//	//		//));
//	//	}
//	//}
//	//for (auto& clip: clip_vec) {
//	//	clip.update_screen_v();
//	//}
//	return clip_vec;
//}
//MyFixedPt Plane::dot(
//	Kind kind,
//	const Vec4<MyFixedPt>& v
//) {
//}
//
//u32 Plane::out_code(const Vec4<MyFixedPt>& v) const {
//	u32 ret = 0;
//	//for (size_t i=0; i<size_t(Kind::LIM); ++i) {
//	//	if (dot(Kind(i), v) < 0) {
//	//		out_code |= (1 << i);
//	//	}
//	//}
//	if (v.x < -v.w) {
//		ret |= 1;
//	}
//	if (v.x > v.w) {
//		ret |= 2;
//	}
//	if (v.y < -v.w) {
//		ret |= 4;
//	}
//	if (v.y > v.w) {
//		ret |= 8;
//	}
//	if (v.z < -v.w) {
//		ret |= 16;
//	}
//	if (v.z > MyFixedPt(0.0)) {
//		ret |= 32;
//	}
//	return ret;
//}

Vec4<MyFixedPt> Plane::intersect(
	const Vec4<MyFixedPt>& q1,
	const Vec4<MyFixedPt>& q2,
	MyFixedPt alpha
) const {
	return q1 + ((q2 - q1) * alpha);

	//// https://math.stackexchange.com/questions/2481917/how-to-get-intersection-points-between-a-plane-and-a-triangle-3d
	//// we know we have an intersection when we use this function
	//const MyFixedPt
	//	my_q_dot_n(q.dot(n())),
	//	my_p_dot_n(p.dot(n()));
	////if (
	////	(
	////		my_q_dot_n < MyFixedPt(0.0)
	////		&& my_p_dot_n >= MyFixedPt(0.0)
	////	) || (
	////		my_p_dot_n < MyFixedPt(0.0)
	////		&& my_q_dot_n >= MyFixedPt(0.0)
	////	)
	////) {
	//	const Vec4<MyFixedPt>
	//		a(p * my_q_dot_n),
	//		b(q * my_p_dot_n);
	//	return (a - b);
	////} else {
	////	return std::nullopt;
	////}
}

//MyFixedPt Plane::lerp(
//	MyFixedPt a,
//	MyFixedPt b,
//	MyFixedPt alpha
//) {
//	const MyFixedPt a1 = MyFixedPt(1.0) - alpha;
//	return MyFixedPt(a1 * a + alpha * b);
//}
//Vec4<MyFixedPt> Plane::lerp(
//	const Vec4<MyFixedPt>& a,
//	const Vec4<MyFixedPt>& b,
//	MyFixedPt alpha
//) {
//	Vec4<MyFixedPt> ret;
//	const MyFixedPt a1 = MyFixedPt(1.0) - alpha;
//
//	ret.x = a1 * a.x + alpha * b.x;
//	ret.y = a1 * a.y + alpha * b.y;
//	ret.z = a1 * a.z + alpha * b.z;
//	ret.w = a1 * a.w + alpha * b.w;
//
//	return ret;
//}
