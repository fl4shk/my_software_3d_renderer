#include "Clip.hpp"

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
