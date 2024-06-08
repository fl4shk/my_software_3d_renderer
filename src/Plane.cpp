#include "Plane.hpp"
#include "BaryLerp.hpp"

// https://cs418.cs.illinois.edu/website/text/clipping.html
Plane::Plane(
	Kind s_kind
	//const Vec4<MyFixedPt>& s_n
):
	_kind(s_kind)
{
	switch (kind()) {
		case Kind::LEFT: {
			//return v.x + v.w;
			_n = {1.0, 0.0, 0.0, 1.0};
		}
			break;
		case Kind::RIGHT: {
			//return -v.x + v.w;
			_n = {-1.0, 0.0, 0.0, 1.0};
		}
			break;
		case Kind::TOP: {
			//return v.y + v.w;
			_n = {0.0, 1.0, 0.0, 1.0};
		}
			break;
		case Kind::BOTTOM: {
			//return -v.y + v.w;
			_n = {0.0, -1.0, 0.0, 1.0};
		}
			break;
		case Kind::NEAR: {
			//return v.z + v.w;
			_n = {0.0, 0.0, 1.0, 1.0};
		}
			break;
		case Kind::FAR: {
			//return -v.z;
			_n = {0.0, 0.0, -1.0, 0.0};
		}
			break;
		case Kind::LIM: {
			//return MyFixedPt(-1.0);
		}
			break;
	}
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

MyFixedPt Plane::dist(const Vec4<MyFixedPt>& v) const {
	return v.dot(n());
}
std::vector<TriRast>& Plane::update_clip_vec(const Tri& tri) {
	_clip_vec.clear();

	const Vert
		& v0 = tri.clip_v.at(0),
		& v1 = tri.clip_v.at(1),
		& v2 = tri.clip_v.at(2);
	const MyFixedPt
		d0 = dist(v0.v),
		d1 = dist(v1.v),
		d2 = dist(v2.v);

	if (
		d0 > MyFixedPt(0.0)
		&& d1 > MyFixedPt(0.0)
		&& d2 > MyFixedPt(0.0)
	) {
		_clip_vec.push_back(TriRast{
			.img=tri.img,
			.v=tri.clip_v,
			.rw_arr=tri.rw_arr,
		});
	} else if (
		d0 <= MyFixedPt(0.0)
		&& d1 <= MyFixedPt(0.0)
		&& d2 <= MyFixedPt(0.0)
	) {
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
		const MyFixedPt* A_rw = nullptr;
		const Vert
			* A = nullptr,
			* B = nullptr,
			* C = nullptr;
		Vec4<MyFixedPt>
			B_prime,
			C_prime;
		if (d0 > MyFixedPt(0.0)) {
			A_rw = &tri.rw_arr.at(0);
			A = &v0;
			B = &v1;
			C = &v2;
		} else if (d1 > MyFixedPt(0.0)) {
			A_rw = &tri.rw_arr.at(1);
			A = &v1;
			B = &v0;
			C = &v2;
		} else { // if (d2 > MyFixedPt(0.0)
			A_rw = &tri.rw_arr.at(2);
			A = &v2;
			B = &v0;
			C = &v1;
		}
		B_prime = intersect(A->v, B->v);
		C_prime = intersect(A->v, C->v);
		const BaryLerp
			B_prime_lerp(
				tri.clip_v,
				tri.rw_arr,
				Vec2<MyFixedPt>{
					B_prime.x,
					B_prime.y,
				},
				false
			),
			C_prime_lerp(
				tri.clip_v,
				tri.rw_arr,
				Vec2<MyFixedPt>{
					C_prime.x,
					C_prime.y,
				},
				false
			);
		_clip_vec.push_back({
			.img=tri.img,
			.v{{
				*A,
				{
					.v=B_prime_lerp.v(),
					.uv=B_prime_lerp.uv(),
				},
				{
					.v=C_prime_lerp.v(),
					.uv=C_prime_lerp.uv(),
				},
			}},
			.rw_arr{{
				//my_recip(A->v.w),
				*A_rw,
				B_prime_lerp.rw(),
				C_prime_lerp.rw(),
			}}
		});
		//to_push.screen_v.at(i)
		//_clip_vec.push_back(TriRast::from_subdiv_tri(
		//	tri,
		//	A,
		//	B_prime,
		//	C_prime
		//));
	} else { // only one of (d0, d1, d2) is negative
		// let C be the vertex with a negative distance
		const MyFixedPt
			* A_rw = nullptr,
			* B_rw = nullptr;
			//* C_rw = nullptr;
		const Vert
			* A = nullptr,
			* B = nullptr,
			* C = nullptr;
		Vec4<MyFixedPt>
			A_prime,
			B_prime;
		if (d0 < MyFixedPt(0.0)) {
			//C_rw = &tri.rw_arr.at(0);
			C = &v0;
			B = &v1;
			B_rw = &tri.rw_arr.at(1);
			A = &v2;
			A_rw = &tri.rw_arr.at(2);
		} else if (d1 < MyFixedPt(0.0)) {
			//C_rw = &tri.rw_arr.at(1);
			C = &v1;
			B = &v0;
			B_rw = &tri.rw_arr.at(0);
			A = &v2;
			A_rw = &tri.rw_arr.at(2);
		} else { // if (d2 < MyFixedPt(0.0)
			//C_rw = &tri.rw_arr.at(2);
			C = &v2;
			B = &v0;
			B_rw = &tri.rw_arr.at(0);
			A = &v1;
			A_rw = &tri.rw_arr.at(1);
		}
		A_prime = intersect(A->v, C->v);
		B_prime = intersect(B->v, C->v);
		const BaryLerp
			A_prime_lerp(
				tri.clip_v,
				tri.rw_arr,
				Vec2<MyFixedPt>{
					A_prime.x,
					A_prime.y,
				},
				false
			),
			B_prime_lerp(
				tri.clip_v,
				tri.rw_arr,
				Vec2<MyFixedPt>{
					B_prime.x,
					B_prime.y,
				},
				false
			);
		_clip_vec.push_back({
			.img=tri.img,
			.v{{
				*A,
				*B,
				{
					.v=A_prime_lerp.v(),
					.uv=A_prime_lerp.uv(),
				},
			}},
			.rw_arr{{
				//my_recip(A->v.w),
				//*C_rw,
				*A_rw,
				*B_rw,
				A_prime_lerp.rw(),
			}}
		});
		_clip_vec.push_back({
			.img=tri.img,
			.v{{
				{
					.v=A_prime_lerp.v(),
					.uv=A_prime_lerp.uv(),
				},
				*B,
				{
					.v=B_prime_lerp.v(),
					.uv=B_prime_lerp.uv(),
				},
			}},
			.rw_arr{{
				//my_recip(A->v.w),
				//*C_rw,
				A_prime_lerp.rw(),
				*B_rw,
				B_prime_lerp.rw(),
			}}
		});
		//to_push.screen_v.at(i)
		//_clip_vec.push_back(TriRast::from_subdiv_tri(
		//	tri,
		//	A,
		//	B_prime,
		//	C_prime
		//));
	}

	return _clip_vec;
}
//MyFixedPt Plane::dot(
//	Kind kind,
//	const Vec4<MyFixedPt>& v
//) {
//}
//
//u8 Plane::out_code(const Vec4<MyFixedPt>& v) {
//	u8 out_code = 0;
//	for (size_t i=0; i<size_t(Kind::LIM); ++i) {
//		if (dot(Kind(i), v) < 0) {
//			out_code |= (1 << i);
//		}
//	}
//	return out_code;
//}
Vec4<MyFixedPt> Plane::intersect(
	const Vec4<MyFixedPt>& q,
	const Vec4<MyFixedPt>& p
) const {
	// https://math.stackexchange.com/questions/2481917/how-to-get-intersection-points-between-a-plane-and-a-triangle-3d
	// we know we have an intersection when we use this function
	const MyFixedPt
		my_q_dot_n(q.dot(n())),
		my_p_dot_n(p.dot(n()));
	//if (
	//	(
	//		my_q_dot_n < MyFixedPt(0.0)
	//		&& my_p_dot_n >= MyFixedPt(0.0)
	//	) || (
	//		my_p_dot_n < MyFixedPt(0.0)
	//		&& my_q_dot_n >= MyFixedPt(0.0)
	//	)
	//) {
		const Vec4<MyFixedPt>
			a(p * my_q_dot_n),
			b(q * my_p_dot_n);
		return (a - b);
	//} else {
	//	return std::nullopt;
	//}
}
MyFixedPt Plane::lerp(
	MyFixedPt a,
	MyFixedPt b,
	MyFixedPt alpha
) {
	const MyFixedPt a1 = MyFixedPt(1.0) - alpha;
	return MyFixedPt(a1 * a + alpha * b);
}
Vec4<MyFixedPt> Plane::lerp(
	const Vec4<MyFixedPt>& a,
	const Vec4<MyFixedPt>& b,
	MyFixedPt alpha
) {
	Vec4<MyFixedPt> ret;
	const MyFixedPt a1 = MyFixedPt(1.0) - alpha;

	ret.x = a1 * a.x + alpha * b.x;
	ret.y = a1 * a.y + alpha * b.y;
	ret.z = a1 * a.z + alpha * b.z;
	ret.w = a1 * a.w + alpha * b.w;

	return ret;
}
