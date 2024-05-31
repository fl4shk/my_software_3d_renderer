#include "tri_class.hpp"


void Tri::do_project(
	const Transform& view,
	const Transform& perspective
) {
	//printout("Tri::do_project():\n");
	for (size_t i=0; i<TRI_VERT_SIZE; ++i) {
		project_v.at(i).v = perspective.do_project(
			model,
			view,
			v.at(i).v
		);
		//printout(
		//	project_v.at(i).v, "\n"
		//);
	}
	//printout("\n");
}
