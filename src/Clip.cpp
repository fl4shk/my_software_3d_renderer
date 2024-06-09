#include "Clip.hpp"

Clip::Clip(
	//const Tri& tri
	//MyFixedPt s_near,
	//MyFixedPt s_far
)
	: _plane_arr{
		//Plane(Plane::Kind::W_ZERO),
		Plane(Plane::Kind::LEFT),
		Plane(Plane::Kind::RIGHT),
		Plane(Plane::Kind::TOP),
		Plane(Plane::Kind::BOTTOM),
		Plane(Plane::Kind::NEAR),
		Plane(Plane::Kind::FAR),
	}
{
}
Clip::~Clip() {
}
std::vector<Tri> Clip::do_clip(
	const Tri& tri
) const {
	std::vector<Tri> ret{
		//Tri{
		//	//.img=tri.img,
		//	.img=tri.img,
		//	.model=tri.model,
		//	.proj_v=tri.proj_v,
		//	//.screen_v=tri.proj_v,
		//	//.rw_arr=tri.rw_arr,
		//}
		//tri
	};
	//std::vector<Tri> ret;
	//std::vector<Vec4<MyFixedPt>> temp;
	std::vector<Vert> temp;
	for (size_t i=0; i<tri.proj_v.size(); ++i) {
		temp.push_back(tri.proj_v.at(i));
	}
	for (
		size_t i=0; i<size_t(Plane::Kind::LIM); ++i
		//size_t i=0; i<1; ++i
		//size_t i=0; i<size_t(Plane::Kind::NEAR); ++i
	) {
		auto& plane = _plane_arr.at(i);
		printout(
			"Clip::do_clip(): ",
			i, " ",
			size_t(plane.kind()),
			"\n"
		);
		//if (i == 0) {
		//} 
		//else {
		//	//plane.update_clip_vec(_plane_arr.at(i - 1).clip_vec);
		//}
		//temp = plane.do_clip(temp);
		printout("temp:\n");
		for (const auto& item: temp) {
			printout(
				"{", item.v, " ", item.uv, "}\n"
			);
		}
		printout("\n");
		temp = plane.do_clip(temp);
		//ret = plane::do_clip(ret);
		if (temp.size() == 0) {
			printout("temp.size() == 0!\n");
			break;
		}
	}
	printout("temp:\n");
	for (const auto& item: temp) {
		printout(
			"{", item.v, " ", item.uv, "}\n"
		);
	}
	printout("\n");
	//printout("testificate\n");
	//return _plane_arr;
	//void draw_ngon(vertex *v, int n) {
	//	vertex *last = v + (n - 1);
	//	vertex *first = v++;
	//	while(v != last) {
	//		draw_triangle(first, v, v + 1);
	//		v++;
	//	}
	//}
	if (temp.size() > 0) {
		printout("temp.size() > 0: ", temp.size(), "\n");
		const Vert
			* temp_data = temp.data(),
			* v = temp_data,
			* last = v + (temp.size() - 1),
			* first = v++;
		while (v != last) {
			ret.push_back(Tri{
				.img=tri.img,
				.model=tri.model,
				.proj_v{
					*first,
					*v,
					*(v + 1),
				}
			});
			++v;
		}
	}
	return ret;
}
//Clip::Clip(
//	const Tri& tri,
//	MyFixedPt s_near,
//	MyFixedPt s_far
//):
//	_near(s_near),
//	_far(s_far)
//{
//	_do_clip(tri);
//}
//
//Clip::~Clip() {
//}
//
//void Clip::_do_clip(
//	const Tri& tri
//) {
//	auto inner_clip = [&](MyFixedPt P) -> void {
//		auto&& to_push = _clip_tri_against_plane(
//			tri,
//			Plane::from_z(P)
//		);
//		if (to_push.size() > 0) {
//			for (auto& item: to_push) {
//				//_tri_vec.push_back(std::move(*to_push));
//				_tri_vec.push_back(std::move(item));
//			}
//		}
//	};
//	inner_clip(near());
//	inner_clip(far());
//}
////std::vector<Tri> Clip::_clip_instance_against_plane(
////	const Tri& tri,
////	MyFixedPt P
////) {
////	const auto& sphere = bounding_sphere_of_tri_screen_v(tri);
////    MyFixedPt d = _signed_distance(P, sphere.pos());
////    if (d > sphere.r()) {
////        return std::vector<Tri>{tri};
////    } else if (d < -sphere.r()) {
////        return std::vector<Tri>();
////    } else {
////        //clipped_instance = Copy(instance)
////        std::vector<Tri> ret;
////        //clipped_instance.triangles =
////        //    ClipTrianglesAgainstPlane(instance.triangles, plane)
////
////        //return clipped_instance
////        return ret;
////    }
////}
//std::vector<Tri> Clip::_clip_tri_against_plane(
//	const Tri& tri,
//	//MyFixedPt P
//	const Plane& plane
//) const {
//}
//MyFixedPt Clip::_signed_distance(
//	//MyFixedPt P, 
//	const Plane& plane,
//	const Vec3<MyFixedPt>& vt
//) const {
//	//normal = plane.normal
//	//return (vertex.x * normal.x)
//	//	+ (vertex.y * normal.y)
//	//	+ (vertex.z * normal.z)
//	//	+ plane.D
//}
