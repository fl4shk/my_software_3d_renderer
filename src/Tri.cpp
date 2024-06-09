#include "Tri.hpp"
#include "Clip.hpp"
#include "BaryLerp.hpp"

void Tri::do_project_etc(
	const Transform& view,
	const Transform& perspective
) {
	TriVert temp_v;
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		proj_v.at(i).v = perspective.do_project(
			*model,
			view,
			v.at(i).v
		);
		proj_v.at(i).uv = v.at(i).uv;
		//rw_arr.at(i).data = (
		//	i64(
		//		proj_v.at(i).v.w.recip_ldbl()
		//		* (1 << MyRwFixedPt::FRAC_WIDTH)
		//		//i64(MyRwFixedPt(1).data)
		//		/// (
		//		//	i64(proj_v.at(i).v.w.data)
		//		//	<< i64(abs(
		//		//		i64(MyRwFixedPt::FRAC_WIDTH)
		//		//		- i64(MyFixedPt::FRAC_WIDTH)
		//		//	))
		//		//)
		//	)
		//);
		rw_arr.at(i) = my_recip(proj_v.at(i).v.w);
		//temp_v.at(i).v.x = (
		//	mult_cx_rw(proj_v.at(i).v.x, rw_arr.at(i))
		//);
		//temp_v.at(i).v.y = (
		//	mult_cx_rw(proj_v.at(i).v.y, rw_arr.at(i))
		//);
		//temp_v.at(i).v.z = (
		//	mult_cx_rw(proj_v.at(i).v.z, rw_arr.at(i))
		//	//v.at(i).v.z
		//);
		//temp_v.at(i).v.w = (
		//	//mult_cx_rw(proj_v.at(i).v.w, rw_arr.at(i))
		//	v.at(i).v.w
		//);
		//temp_v.at(i).uv = v.at(i).uv;
		//screen_v.at(i).v.x = (
		//	(
		//		//(
		//		//	(
		//		//		i64(temp_v.at(i).v.x.data)
		//		//		* i64(rw_arr.at(i).data)
		//		//	) >> MY_RW_FRAC_SHIFT
		//		//)
		//		///// (temp_v.at(i).v.w)
		//		//	//+ (HALF_SCREEN_SIZE_2D.x)
		//		//mult_cx_rw(temp_v.at(i).v.x, rw_arr.at(i))
		//		(
		//			(temp_v.at(i).v.x + 1) * HALF_SCREEN_SIZE_2D.x
		//		)
		//		//+ HALF_SCREEN_SIZE_2D.x
		//	)
		//);
		//screen_v.at(i).v.y = (
		//	//(
		//	//	temp_v.at(i).v.y 
		//	//	//* HALF_SCREEN_SIZE_2D.y
		//	//	//+ HALF_SCREEN_SIZE_2D.y
		//	//)
		//	/// (temp_v.at(i).v.w)
		//	//mult_cx_rw(temp_v.at(i).v.y, rw_arr.at(i))
		//	//temp_v.at(i).v.y

		//	(
		//		(temp_v.at(i).v.y + 1) * HALF_SCREEN_SIZE_2D.y
		//	)
		//	//+ HALF_SCREEN_SIZE_2D.y
		//		////* MyFixedPt(SCREEN_SIZE_2D.y)
		//);
		//screen_v.at(i).v.z = temp_v.at(i).v.z;
		//screen_v.at(i).v.w = temp_v.at(i).v.w;
		//screen_v.at(i).uv.x = (
		//	//temp_v.at(i).uv.x //* rw_arr.at(i)
		//	/// (temp_v.at(i).v.w)
		//	mult_cx_rw(temp_v.at(i).uv.x, rw_arr.at(i))
		//);
		//screen_v.at(i).uv.y = (
		//	//temp_v.at(i).uv.y //* rw_arr.at(i)
		//	/// (temp_v.at(i).v.w)
		//	mult_cx_rw(temp_v.at(i).uv.y, rw_arr.at(i))
		//);
	}
	printout("Tri::do_project():\n");
	printout("v:\n");
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		Vec3<double> temp_v;
		for (size_t j=0; j<temp_v.SIZE; ++j) {
			temp_v.at(j) = double(v.at(i).v.at(j));
		}
		//printout(
		//	//project_v.at(i).v, "\n"
		//	"{", temp_v, " ", double(v.at(i).v.w), "}",
		//	"\n"
		//);
		const Vec2<double>
			my_uv{
				.x=double(v.at(i).uv.x),
				.y=double(v.at(i).uv.y),
			};
		printout(
			//project_v.at(i).v, "\n"
			"{",
				temp_v, " ",
				double(v.at(i).v.w), " ",
				my_uv,
			"}",
			"\n"
		);
	}
	printout("proj_v:\n");
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		Vec3<double> temp_v;
		for (size_t j=0; j<temp_v.SIZE; ++j) {
			temp_v.at(j) = double(proj_v.at(i).v.at(j));
		}
		printout(
			//project_v.at(i).v, "\n"
			"{", temp_v, " ", double(proj_v.at(i).v.w), "}",
			"\n"
		);
	}
	//printout("clip_v:\n");
	//for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
	//	Vec3<double> temp_v;
	//	for (size_t j=0; j<temp_v.SIZE; ++j) {
	//		temp_v.at(j) = double(clip_v.at(i).v.at(j));
	//	}
	//	const Vec2<double>
	//		my_clip_uv{
	//			.x=double(clip_v.at(i).uv.x),
	//			.y=double(clip_v.at(i).uv.y),
	//		};
	//	printout(
	//		//project_v.at(i).v, "\n"
	//		"{",
	//			temp_v, " ",
	//			double(clip_v.at(i).v.w), " ",
	//			my_clip_uv,
	//		"}",
	//		"\n"
	//	);
	//}
	//printout("screen_v:\n");
	//for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
	//	Vec3<double> temp_v;
	//	for (size_t j=0; j<temp_v.SIZE; ++j) {
	//		temp_v.at(j) = double(screen_v.at(i).v.at(j));
	//	}
	//	const Vec2<double>
	//		my_screen_uv{
	//			.x=double(screen_v.at(i).uv.x),
	//			.y=double(screen_v.at(i).uv.y),
	//		};
	//	printout(
	//		//project_v.at(i).v, "\n"
	//		"{",
	//			temp_v, " ",
	//			double(screen_v.at(i).v.w), " ",
	//			my_screen_uv,
	//		"}",
	//		"\n"
	//	);
	//}
	printout("\n");
}
void Tri::persp_div() {
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		screen_v.at(i).v.x = (
			(
				//(
				//	(
				//		i64(proj_v.at(i).v.x.data)
				//		* i64(rw_arr.at(i).data)
				//	) >> MY_RW_FRAC_SHIFT
				//)
				///// (proj_v.at(i).v.w)
				//	//+ (HALF_SCREEN_SIZE_2D.x)
				//mult_cx_rw(proj_v.at(i).v.x, rw_arr.at(i))
				mult_cx_rw(
					(proj_v.at(i).v.x + 1) * HALF_SCREEN_SIZE_2D.x,
					rw_arr.at(i)
				)
				//+ HALF_SCREEN_SIZE_2D.x
			)
		);
		screen_v.at(i).v.y = (
			//(
			//	proj_v.at(i).v.y 
			//	//* HALF_SCREEN_SIZE_2D.y
			//	//+ HALF_SCREEN_SIZE_2D.y
			//)
			/// (proj_v.at(i).v.w)
			//mult_cx_rw(proj_v.at(i).v.y, rw_arr.at(i))
			//proj_v.at(i).v.y

			mult_cx_rw(
				(proj_v.at(i).v.y + 1) * HALF_SCREEN_SIZE_2D.y,
				//clip_lerp.rw()
				rw_arr.at(i)
			)
			//+ HALF_SCREEN_SIZE_2D.y
				////* MyFixedPt(SCREEN_SIZE_2D.y)
		);
		screen_v.at(i).v.z = (
			mult_cx_rw(
				proj_v.at(i).v.z,
				//clip_lerp.rw()
				rw_arr.at(i)
			)
		);
		screen_v.at(i).v.w = proj_v.at(i).v.w;
		screen_v.at(i).uv.x = (
			//temp_v.at(i).uv.x //* rw_arr.at(i)
			/// (temp_v.at(i).v.w)
			mult_cx_rw(proj_v.at(i).uv.x, rw_arr.at(i))
		);
		screen_v.at(i).uv.y = (
			//temp_v.at(i).uv.y //* rw_arr.at(i)
			/// (temp_v.at(i).v.w)
			mult_cx_rw(proj_v.at(i).uv.y, rw_arr.at(i))
		);
	}
	printout("screen_v:\n");
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		Vec3<double> temp_v;
		for (size_t j=0; j<temp_v.SIZE; ++j) {
			temp_v.at(j) = double(screen_v.at(i).v.at(j));
		}
		const Vec2<double>
			my_screen_uv{
				.x=double(screen_v.at(i).uv.x),
				.y=double(screen_v.at(i).uv.y),
			};
		printout(
			//project_v.at(i).v, "\n"
			"{",
				temp_v, " ",
				double(screen_v.at(i).v.w), " ",
				my_screen_uv,
			"}",
			"\n"
		);
	}
	printout("\n");
}
//void TriRast::update_screen_v(const Tri& tri) {
//	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
//		//const BaryLerp clip_lerp(
//		//	tri.proj_v,
//		//	tri.rw_arr,
//		//	Vec2<MyFixedPt>{clip_v.at(i).x, clip_v.at(i).y}
//		//);
//		//rw_arr.at(i) = clip_lerp.rw();
//		//clip_v.at(i).v.x = (
//		//	mult_cx_rw(v.at(i).v.x, rw_arr.at(i))
//		//);
//		//clip_v.at(i).v.y = (
//		//	mult_cx_rw(v.at(i).v.y, rw_arr.at(i))
//		//);
//		//clip_v.at(i).v.z = (
//		//	//mult_cx_rw(v.at(i).v.z, rw_arr.at(i))
//		//	v.at(i).v.z
//		//);
//		//clip_v.at(i).v.w = (
//		//	//mult_cx_rw(v.at(i).v.w, rw_arr.at(i))
//		//	v.at(i).v.w
//		//);
//		//clip_v.at(i).uv = v.at(i).uv;
//		screen_v.at(i).x = (
//			(
//				//(
//				//	(
//				//		i64(clip_v.at(i).v.x.data)
//				//		* i64(rw_arr.at(i).data)
//				//	) >> MY_RW_FRAC_SHIFT
//				//)
//				///// (clip_v.at(i).v.w)
//				//	//+ (HALF_SCREEN_SIZE_2D.x)
//				//mult_cx_rw(clip_v.at(i).v.x, rw_arr.at(i))
//				mult_cx_rw(
//					(clip_v.at(i).x + 1) * HALF_SCREEN_SIZE_2D.x,
//					rw_arr.at(i)
//				)
//				//+ HALF_SCREEN_SIZE_2D.x
//			)
//		);
//		screen_v.at(i).y = (
//			//(
//			//	clip_v.at(i).v.y 
//			//	//* HALF_SCREEN_SIZE_2D.y
//			//	//+ HALF_SCREEN_SIZE_2D.y
//			//)
//			/// (clip_v.at(i).v.w)
//			//mult_cx_rw(clip_v.at(i).v.y, rw_arr.at(i))
//			//clip_v.at(i).v.y
//
//			mult_cx_rw(
//				(clip_v.at(i).y + 1) * HALF_SCREEN_SIZE_2D.y,
//				//clip_lerp.rw()
//				rw_arr.at(i)
//			)
//			//+ HALF_SCREEN_SIZE_2D.y
//				////* MyFixedPt(SCREEN_SIZE_2D.y)
//		);
//		screen_v.at(i).z = (
//			mult_cx_rw(
//				clip_v.at(i).z,
//				//clip_lerp.rw()
//				rw_arr.at(i)
//			)
//		);
//		screen_v.at(i).w = clip_v.at(i).w;
//		screen_v.at(i).uv.x = (
//			//temp_v.at(i).uv.x //* rw_arr.at(i)
//			/// (temp_v.at(i).v.w)
//			mult_cx_rw(clip_v.at(i).uv.x, rw_arr.at(i))
//		);
//		screen_v.at(i).uv.y = (
//			//temp_v.at(i).uv.y //* rw_arr.at(i)
//			/// (temp_v.at(i).v.w)
//			mult_cx_rw(clip_v.at(i).uv.y, rw_arr.at(i))
//		);
//		//screen_v.at(i).uv.x = (
//		//	//clip_v.at(i).uv.x //* rw_arr.at(i)
//		//	/// (clip_v.at(i).v.w)
//		//	mult_cx_rw(clip_v.at(i).uv.x, rw_arr.at(i))
//		//);
//		//screen_v.at(i).uv.y = (
//		//	//clip_v.at(i).uv.y //* rw_arr.at(i)
//		//	/// (clip_v.at(i).v.w)
//		//	mult_cx_rw(clip_v.at(i).uv.y, rw_arr.at(i))
//		//);
//	}
//	printout("clip_v:\n");
//	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
//		Vec3<double> temp_v;
//		for (size_t j=0; j<temp_v.SIZE; ++j) {
//			temp_v.at(j) = double(clip_v.at(i).at(j));
//		}
//		//const Vec2<double>
//		//	my_clip_uv{
//		//		.x=double(clip_v.at(i).uv.x),
//		//		.y=double(clip_v.at(i).uv.y),
//		//	};
//		printout(
//			//project_v.at(i).v, "\n"
//			"{",
//				temp_v, " ",
//				double(clip_v.at(i).w), //" ",
//				//my_clip_uv,
//			"}",
//			"\n"
//		);
//	}
//	printout("screen_v:\n");
//	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
//		Vec3<double> temp_v;
//		for (size_t j=0; j<temp_v.SIZE; ++j) {
//			temp_v.at(j) = double(screen_v.at(i).at(j));
//		}
//		//const Vec2<double>
//		//	my_screen_uv{
//		//		.x=double(screen_v.at(i).uv.x),
//		//		.y=double(screen_v.at(i).uv.y),
//		//	};
//		printout(
//			//project_v.at(i).v, "\n"
//			"{",
//				temp_v, " ",
//				double(screen_v.at(i).w), //" ",
//				//my_screen_uv,
//			"}",
//			"\n"
//		);
//	}
//	printout("rw_arr:\n");
//	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
//		printout(
//			rw_arr.at(i)
//		);
//		if (i + 1 < TRI_VERT_SIZE) {
//			printout(" ");
//		}
//	}
//	printout("\n");
//}
//std::vector<Tri> Tri::do_clip() const {
//	std::vector<Tri> ret;
//	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
//		//auto& my_proj = proj_v.at(i);
//		//auto& my_clip = clip_v.at(i);
//		//screen_v.at(i).v.x = (
//		//	(
//		//		//(
//		//		//	(
//		//		//		i64(clip_v.at(i).v.x.data)
//		//		//		* i64(rw_arr.at(i).data)
//		//		//	) >> MY_RW_FRAC_SHIFT
//		//		//)
//		//		///// (clip_v.at(i).v.w)
//		//		//	//+ (HALF_SCREEN_SIZE_2D.x)
//		//		//mult_cx_rw(clip_v.at(i).v.x, rw_arr.at(i))
//		//		(
//		//			(clip_v.at(i).v.x + 1) * HALF_SCREEN_SIZE_2D.x
//		//		)
//		//		//+ HALF_SCREEN_SIZE_2D.x
//		//	)
//		//);
//		//screen_v.at(i).v.y = (
//		//	//(
//		//	//	clip_v.at(i).v.y 
//		//	//	//* HALF_SCREEN_SIZE_2D.y
//		//	//	//+ HALF_SCREEN_SIZE_2D.y
//		//	//)
//		//	/// (clip_v.at(i).v.w)
//		//	//mult_cx_rw(clip_v.at(i).v.y, rw_arr.at(i))
//		//	//clip_v.at(i).v.y
//
//		//	(
//		//		(clip_v.at(i).v.y + 1) * HALF_SCREEN_SIZE_2D.y
//		//	)
//		//	//+ HALF_SCREEN_SIZE_2D.y
//		//		////* MyFixedPt(SCREEN_SIZE_2D.y)
//		//);
//		//screen_v.at(i).v.z = clip_v.at(i).v.z;
//		//screen_v.at(i).v.w = clip_v.at(i).v.w;
//		//screen_v.at(i).uv.x = (
//		//	//clip_v.at(i).uv.x //* rw_arr.at(i)
//		//	/// (clip_v.at(i).v.w)
//		//	mult_cx_rw(clip_v.at(i).uv.x, rw_arr.at(i))
//		//);
//		//screen_v.at(i).uv.y = (
//		//	//clip_v.at(i).uv.y //* rw_arr.at(i)
//		//	/// (clip_v.at(i).v.w)
//		//	mult_cx_rw(clip_v.at(i).uv.y, rw_arr.at(i))
//		//);
//	}
//	return ret;
//}
//void Tri::do_clip() {
//	Clip::clip(*this);
//}
//TriRast TriRast::from_subdiv_tri(
//	const Tri& tri,
//	const Vec4<MyFixedPt>& v0,
//	const Vec4<MyFixedPt>& v1,
//	const Vec4<MyFixedPt>& v2
//) {
//	TriRast ret;
//	return ret;
//}
