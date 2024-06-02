#include "tri_class.hpp"
#include "clip_class.hpp"

void Tri::do_project_etc(
	const Transform& view,
	const Transform& perspective
) {
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		proj_v.at(i).v = perspective.do_project(
			model,
			view,
			v.at(i).v
		);
		proj_v.at(i).uv = v.at(i).uv;
		rw_arr.at(i).data = (
			i64(
				proj_v.at(i).v.w.recip_ldbl()
				* (1 << MyRwCxFixedPt::FRAC_WIDTH)
				//i64(MyRwCxFixedPt(1).data)
				/// (
				//	i64(proj_v.at(i).v.w.data)
				//	<< i64(abs(
				//		i64(MyRwCxFixedPt::FRAC_WIDTH)
				//		- i64(MyCxFixedPt::FRAC_WIDTH)
				//	))
				//)
			)
		);
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
				mult_cx_rw(proj_v.at(i).v.x, rw_arr.at(i))
				+ HALF_SCREEN_SIZE_2D.x
			)
		);
		screen_v.at(i).v.y = (
			//(
			//	proj_v.at(i).v.y 
			//	//* HALF_SCREEN_SIZE_2D.y
			//	//+ HALF_SCREEN_SIZE_2D.y
			//)
			/// (proj_v.at(i).v.w)
			mult_cx_rw(proj_v.at(i).v.y, rw_arr.at(i))
				//* rw_arr.at(i)
			+ HALF_SCREEN_SIZE_2D.y
				////* MyCxFixedPt(SCREEN_SIZE_2D.y)
		);
		screen_v.at(i).v.z = proj_v.at(i).v.z;
		screen_v.at(i).v.w = proj_v.at(i).v.w;
		screen_v.at(i).uv.x = (
			//proj_v.at(i).uv.x //* rw_arr.at(i)
			/// (proj_v.at(i).v.w)
			mult_cx_rw(proj_v.at(i).uv.x, rw_arr.at(i))
		);
		screen_v.at(i).uv.y = (
			//proj_v.at(i).uv.y //* rw_arr.at(i)
			/// (proj_v.at(i).v.w)
			mult_cx_rw(proj_v.at(i).uv.y, rw_arr.at(i))
		);
	}
	//printout("Tri::do_project():\n");
	//printout("v:\n");
	//for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
	//	Vec3<double> temp_v;
	//	for (size_t j=0; j<temp_v.SIZE; ++j) {
	//		temp_v.at(j) = double(v.at(i).v.at(j));
	//	}
	//	printout(
	//		//project_v.at(i).v, "\n"
	//		"{", temp_v, " ", double(v.at(i).v.w), "}",
	//		"\n"
	//	);
	//}
	//printout("proj_v:\n");
	//for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
	//	Vec3<double> temp_v;
	//	for (size_t j=0; j<temp_v.SIZE; ++j) {
	//		temp_v.at(j) = double(proj_v.at(i).v.at(j));
	//	}
	//	printout(
	//		//project_v.at(i).v, "\n"
	//		"{", temp_v, " ", double(proj_v.at(i).v.w), "}",
	//		"\n"
	//	);
	//}
	//printout("screen_v:\n");
	//for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
	//	Vec3<double> temp_v;
	//	for (size_t j=0; j<temp_v.SIZE; ++j) {
	//		temp_v.at(j) = double(screen_v.at(i).v.at(j));
	//	}
	//	printout(
	//		//project_v.at(i).v, "\n"
	//		"{", temp_v, " ", double(screen_v.at(i).v.w), "}",
	//		"\n"
	//	);
	//}
	//printout("\n");
}
//void Tri::do_clip() {
//	Clip::clip(*this);
//}
