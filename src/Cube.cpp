#include "Cube.hpp"

auto Cube::update_face_arr() -> std::array<Square, size_t(FaceIdx::LIM)>& {

	auto& top = face_arr.at(size_t(FaceIdx::TOP));
	auto& bot = face_arr.at(size_t(FaceIdx::BOT));
	auto& left = face_arr.at(size_t(FaceIdx::LEFT));
	auto& right = face_arr.at(size_t(FaceIdx::RIGHT));
	auto& front = face_arr.at(size_t(FaceIdx::FRONT));
	auto& back = face_arr.at(size_t(FaceIdx::BACK));

	top.size_2d = bot.size_2d = {dim, dim};
	left.size_2d = right.size_2d = {dim, dim};
	front.size_2d = back.size_2d = {dim, dim};

	for (size_t i=0; i<face_arr.size(); ++i) {
		face_arr.at(i).img = img;
		face_arr.at(i).update_tri_arr();
	}

	return face_arr;
}
//auto Cube::to_tri_arr() const 
//-> std::array<std::array<Tri, 2>, size_t(TriIdx::LIM)> {
//	std::array<std::array<Tri, 2>, size_t(TriIdx::LIM)> ret;
//
//	auto& top = ret.at(size_t(TriIdx::TOP));
//	auto& bot = ret.at(size_t(TriIdx::BOT));
//	auto& mid0 = ret.at(size_t(TriIdx::MID0));
//	auto& mid1 = ret.at(size_t(TriIdx::MID1));
//	auto& mid2 = ret.at(size_t(TriIdx::MID2));
//	auto& mid3 = ret.at(size_t(TriIdx::MID3));
//
//	auto copy_same = [this](auto& arr) -> void {
//		for (size_t i=0; i<arr.size(); ++i) {
//			arr.at(i).img = img;
//			arr.at(i).model = &model;
//
//			arr.at(i).v.at(0).uv = {
//				.x=MyFixedPt(0.1),
//				.y=MyFixedPt(0.1),
//			};
//			arr.at(i).v.at(1).uv = {
//				.x=MyFixedPt(15.0 / 16.0),
//				.y=MyFixedPt(0.1),
//			};
//			arr.at(i).v.at(2).uv = {
//				.x=MyFixedPt(15.0 / 16.0),
//				.y=MyFixedPt(15.0 / 16.0),
//			};
//		}
//	};
//	for (size_t i=0; i<ret.size(); ++i) {
//		copy_same(ret.at(i));
//	}
//
//	const auto
//		hs = size_3d / MyFixedPt(2);
//
//	top.at(0).v.at(0).v.x = hs.x;
//	top.at(0).v.at(0).v.y = hs.y;
//	top.at(0).v.at(0).v.z = hs.z;
//
//	top.at(0).v.at(1).v.x = -hs.x;
//	top.at(0).v.at(1).v.y = hs.y;
//	top.at(0).v.at(1).v.z = hs.z;
//
//	top.at(0).v.at(2).v.x = -hs.x;
//	top.at(0).v.at(2).v.y = hs.y;
//	top.at(0).v.at(2).v.z = -hs.z;
//
//	//top.at(0).v.at(0).uv.x = 
//
//	top.at(1).v.at(0).v.x = hs.x;
//	top.at(1).v.at(0).v.y = hs.y;
//	top.at(1).v.at(0).v.z = hs.z;
//
//	top.at(1).v.at(1).v.x = -hs.x;
//	top.at(1).v.at(1).v.y = hs.y;
//	top.at(1).v.at(1).v.z = hs.z;
//
//	top.at(1).v.at(2).v.x = -hs.x;
//	top.at(1).v.at(2).v.y = hs.y;
//	top.at(1).v.at(2).v.z = -hs.z;
//
//
//	mid0.at(0).v.at(0).v.x = hs.x;
//	mid0.at(0).v.at(0).v.y = hs.y;
//	mid0.at(0).v.at(0).v.z = hs.z;
//
//	mid0.at(0).v.at(1).v.x = hs.x;
//	mid0.at(0).v.at(1).v.y = -hs.y;
//	mid0.at(0).v.at(1).v.z = hs.z;
//
//	mid0.at(0).v.at(2).v.x = -hs.x;
//	mid0.at(0).v.at(2).v.y = -hs.y;
//	mid0.at(0).v.at(2).v.z = hs.z;
//
//	return ret;
//}
