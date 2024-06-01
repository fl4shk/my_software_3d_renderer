#include "tri_class.hpp"


void Tri::do_project(
	const Transform& view,
	const Transform& perspective
) {
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		project_v.at(i).v = perspective.do_project(
			model,
			view,
			v.at(i).v
		);
	}
	//printout("Tri::do_project():\n");
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		Vec3<double> temp_v;
		for (size_t j=0; j<temp_v.SIZE; ++j) {
			temp_v.at(j) = double(project_v.at(i).v.at(j));
		}
		//printout(
		//	//project_v.at(i).v, "\n"
		//	temp_v, "\n"
		//);
	}
	//printout("\n");
}
