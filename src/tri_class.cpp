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
		rw_arr.at(i) = (MyCxFixedPt(1) / proj_v.at(i).v.w);
		screen_v.at(i).v.x = (
			(
				proj_v.at(i).v.x 
				//* HALF_SCREEN_SIZE_2D.x
				//+ HALF_SCREEN_SIZE_2D.x
				////* MyCxFixedPt(SCREEN_SIZE_2D.x)
			) 
			* rw_arr.at(i)
				+ HALF_SCREEN_SIZE_2D.x
		);
		screen_v.at(i).v.y = (
			(
				proj_v.at(i).v.y 
				//* HALF_SCREEN_SIZE_2D.y
				//+ HALF_SCREEN_SIZE_2D.y
			)
				* rw_arr.at(i)
				+ HALF_SCREEN_SIZE_2D.y
				////* MyCxFixedPt(SCREEN_SIZE_2D.y)
		);
		screen_v.at(i).v.z = proj_v.at(i).v.z;
		screen_v.at(i).v.w = proj_v.at(i).v.w;
		screen_v.at(i).uv.x = (
			proj_v.at(i).uv.x * rw_arr.at(i)
		);
		screen_v.at(i).uv.y = (
			proj_v.at(i).uv.y * rw_arr.at(i)
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
