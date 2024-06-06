//// Based on
////	https://github.com/mhdadk/sutherland-hodgman
//// which is licensed as follows:
//// MIT License
//// 
//// Copyright (c) 2022 Mahmoud Abdelkhalek
//// 
//// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//// 
//// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//// 
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//#include "Clip.hpp"
//
//bool Clip::_is_inside(
//	const Vec2<MyCxFixedPt>& p1,
//	const Vec2<MyCxFixedPt>& p2,
//	const Vec2<MyCxFixedPt>& q
//) {
//	const MyCxFixedPt R(
//		(p2.at(0) - p1.at(0)) * (q.at(1) - p1.at(1))
//		- (p2.at(1) - p1.at(1)) * (q.at(0) - p1.at(0))
//	);
//	if (R <= MyCxFixedPt(0)) {
//		return true;
//	} else {
//		return false;
//	}
//}
//Vec2<MyCxFixedPt> Clip::_compute_intersection(
//	const Vec2<MyCxFixedPt>& p1,
//	const Vec2<MyCxFixedPt>& p2,
//	const Vec2<MyCxFixedPt>& p3,
//	const Vec2<MyCxFixedPt>& p4
//) {
//	MyCxFixedPt
//		x,
//		y;
//	if (p2.at(0) - p1.at(0) == MyCxFixedPt(0)) {
//		// if first line is vertical
//		x = p1.at(0);
//		
//		// slope and intercept of second line
//		MyCxFixedPt m2 = (p4.at(1) - p3.at(1)) / (p4.at(0) - p3.at(0));
//		MyCxFixedPt b2 = p3.at(1) - m2 * p3.at(0);
//		// y-coordinate of intersection
//		y = m2 * x + b2;
//		
//
//	} else if (p4.at(0) - p3.at(0) == MyCxFixedPt(0)) {
//		// if second line is vertical
//		x = p3.at(0);
//		
//		// slope and intercept of first line
//		MyCxFixedPt m1 = (p2.at(1) - p1.at(1)) / (p2.at(0) - p1.at(0));
//		MyCxFixedPt b1 = p1.at(1) - m1 * p1.at(0);
//		
//		// y-coordinate of intersection
//		y = m1 * x + b1;
//	} else {
//		// if neither line is vertical
//		MyCxFixedPt m1 = (p2.at(1) - p1.at(1)) / (p2.at(0) - p1.at(0));
//		MyCxFixedPt b1 = p1.at(1) - m1 * p1.at(0);
//		
//		// slope and intercept of second line
//		MyCxFixedPt m2 = (p4.at(1) - p3.at(1)) / (p4.at(0) - p3.at(0));
//		MyCxFixedPt b2 = p3.at(1) - m2 * p3.at(0);
//
//		// x-coordinate of intersection
//		x = (b2 - b1) / (m1 - m2);
//
//		// y-coordinate of intersection
//		y = m1 * x + b1;
//	}
//	return Vec2<MyCxFixedPt>{
//		.x=x,
//		.y=y,
//	};
//}
//void Clip::clip(Tri& tri) {
//	// this function is adapted from the Wikipedia article
//	//tri.clip_vec.clear();
//	std::vector<Vec2<MyCxFixedPt>> inp_vec;
//	tri.clip_vec.clear();
//	for (size_t i=0; i<tri.project_v.size(); ++i) {
//		tri.clip_vec.push_back(
//			Vec2<MyCxFixedPt>{
//				.x=tri.project_v.at(i).v.x,
//				.y=tri.project_v.at(i).v.y,
//			}
//		);
//		printout(
//			Vec2<double>{
//				.x=double(tri.clip_vec.back().x),
//				.y=double(tri.clip_vec.back().y),
//			},
//			" "
//		);
//	}
//	printout("\n");
//	for (size_t clip_idx=0; clip_idx<SCREEN_POLYGON.size(); ++clip_idx) {
//		//tri.clip_vec.push_back(std::vector<Vec2<MyCxFixedPt>>());
//		inp_vec.clear();
//		//inp_vec = std::move(tri.clip_vec);
//		//printout(inp_vec.size(), " ");
//		//printout("Clip::clip(): inputs:\n");
//		for (size_t k=0; k<tri.clip_vec.size(); ++k) {
//			inp_vec.push_back(tri.clip_vec.at(k));
//			printout(
//				k, ": ",
//				Vec2<double>{
//					.x=double(inp_vec.at(k).x),
//					.y=double(inp_vec.at(k).y),
//				},
//				"\n"
//			);
//		}
//		printout("\n");
//		tri.clip_vec.clear();
//		const auto& curr_clip_pt = SCREEN_POLYGON.at(clip_idx);
//		const auto& prev_clip_pt = (
//			SCREEN_POLYGON.at((clip_idx - 1) % SCREEN_POLYGON.size())
//		);
//
//		//const auto& curr_clip_pt_3 = tri.project_v.at(clip_idx).v;
//		//const auto& prev_clip_pt_3 = (
//		//	tri.project_v.at((clip_idx - 1) % tri.project_v.size()).v
//		////);
//		//const Vec2<MyCxFixedPt>
//		//	curr_clip_pt{
//		//		.x=curr_clip_pt_3.x,
//		//		.y=curr_clip_pt_3.y,
//		//	},
//		//	prev_clip_pt{
//		//		.x=prev_clip_pt_3.x,
//		//		.y=prev_clip_pt_3.y,
//		//	};
//
//		printout(
//			"curr_clip_pt:",
//			Vec2<double>(double(curr_clip_pt.x), double(curr_clip_pt.y)),
//			"\n",
//			"prev_clip_pt:",
//			Vec2<double>(double(prev_clip_pt.x), double(prev_clip_pt.y)),
//			"\n",
//			"\n"
//		);
//
//		for (size_t i=0; i<inp_vec.size(); ++i) {
//			const auto& curr_pt = inp_vec.at(i);
//			const auto& prev_pt = inp_vec.at((i - 1) % inp_vec.size());
//			auto do_compute_intersection = [&]() -> Vec2<MyCxFixedPt> {
//				return _compute_intersection(
//					prev_pt, curr_pt, prev_clip_pt, curr_clip_pt
//				);
//			};
//			auto clip_innards = [&]() -> void {
//				if (_is_inside(prev_clip_pt, curr_clip_pt, curr_pt)) {
//					if (!_is_inside(prev_clip_pt, curr_clip_pt, prev_pt)) {
//						const auto& intersecting_pt = (
//							do_compute_intersection()
//						);
//						tri.clip_vec.push_back(intersecting_pt);
//					}
//					tri.clip_vec.push_back(curr_pt);
//				} else if (
//					_is_inside(prev_clip_pt, curr_clip_pt, prev_pt)
//				) {
//					const auto& intersecting_pt = _compute_intersection(
//						prev_pt, curr_pt, prev_clip_pt, curr_clip_pt
//					);
//					tri.clip_vec.push_back(intersecting_pt);
//				}
//			};
//			clip_innards();
//			//switch (clip_idx) {
//			//	case 0: {
//			//		// left side of screen
//			//		// prev: (0, SCREEN_SIZE_2D.y - 1)
//			//		// curr: (0, 0)
//			//		if (
//			//			(
//			//				curr_pt.x < MyCxFixedPt(0)
//			//				&& prev_pt.x >= MyCxFixedPt(0)
//			//			) || (
//			//				prev_pt.x < MyCxFixedPt(0)
//			//				&& curr_pt.x >= MyCxFixedPt(0)
//			//			)
//			//		) {
//			//			printout(
//			//				"left: ",
//			//				Vec2<double>{
//			//					double(curr_pt.x),
//			//					double(curr_pt.y),
//			//				},
//			//				" ",
//			//				Vec2<double>{
//			//					double(prev_pt.x),
//			//					double(prev_pt.y),
//			//				},
//			//				"\n"
//			//			);
//			//			clip_innards();
//			//		}
//			//	}
//			//		break;
//			//	case 1: {
//			//		// top side of screen
//			//		// prev: (0, 0)
//			//		// curr: (SCREEN_SIZE_2D.x - 1, 0)
//			//		if (
//			//			(
//			//				curr_pt.y < MyCxFixedPt(0)
//			//				&& prev_pt.y >= MyCxFixedPt(0)
//			//			) || (
//			//				prev_pt.y < MyCxFixedPt(0)
//			//				&& curr_pt.y >= MyCxFixedPt(0)
//			//			)
//			//		) {
//			//			printout(
//			//				"top: ",
//			//				Vec2<double>{
//			//					double(curr_pt.x),
//			//					double(curr_pt.y),
//			//				},
//			//				" ",
//			//				Vec2<double>{
//			//					double(prev_pt.x),
//			//					double(prev_pt.y),
//			//				},
//			//				//" ",
//			//				"\n"
//			//			);
//			//			clip_innards();
//			//		}
//			//	}
//			//		break;
//			//	case 2: {
//			//		// right side of screen
//			//		// prev: (SCREEN_SIZE_2D.x - 1, 0)
//			//		// curr: (SCREEN_SIZE_2D.x - 1, SCREEN_SIZE_2D.y - 1)
//			//		if (
//			//			(
//			//				curr_pt.x < MyCxFixedPt(SCREEN_SIZE_2D.x)
//			//				&& prev_pt.x >= MyCxFixedPt(SCREEN_SIZE_2D.x)
//			//			) || (
//			//				prev_pt.x < MyCxFixedPt(SCREEN_SIZE_2D.x)
//			//				&& curr_pt.x >= MyCxFixedPt(SCREEN_SIZE_2D.x)
//			//			)
//			//		) {
//			//			printout(
//			//				"right: ",
//			//				Vec2<double>{
//			//					double(curr_pt.x),
//			//					double(curr_pt.y),
//			//				},
//			//				" ",
//			//				Vec2<double>{
//			//					double(prev_pt.x),
//			//					double(prev_pt.y),
//			//				},
//			//				"\n"
//			//			);
//			//			clip_innards();
//			//		}
//			//	}
//			//		break;
//			//	case 3: {
//			//		// bottom side of screen
//			//		// prev: (SCREEN_SIZE_2D.x - 1, SCREEN_SIZE_2D.y - 1)
//			//		// curr: (0, SCREEN_SIZE_2D.y - 1)
//			//		if (
//			//			(
//			//				curr_pt.y < MyCxFixedPt(SCREEN_SIZE_2D.y)
//			//				&& prev_pt.y >= MyCxFixedPt(SCREEN_SIZE_2D.y)
//			//			) || (
//			//				prev_pt.y < MyCxFixedPt(SCREEN_SIZE_2D.y)
//			//				&& curr_pt.y >= MyCxFixedPt(SCREEN_SIZE_2D.y)
//			//			)
//			//		) {
//			//			printout(
//			//				"bottom: ",
//			//				Vec2<double>{
//			//					double(curr_pt.x),
//			//					double(curr_pt.y),
//			//				},
//			//				" ",
//			//				Vec2<double>{
//			//					double(prev_pt.x),
//			//					double(prev_pt.y),
//			//				},
//			//				"\n"
//			//			);
//			//			clip_innards();
//			//		}
//			//	}
//			//		break;
//			//}
//
//		}
//	}
//	printout("Clip::clip(): inputs:\n");
//	for (size_t k=0; k<inp_vec.size(); ++k) {
//		printout(
//			k, ": ",
//			Vec2<double>{
//				.x=double(inp_vec.at(k).x),
//				.y=double(inp_vec.at(k).y),
//			},
//			"\n"
//		);
//	}
//
//	printout("Clip::clip(): results:\n");
//	for (size_t k=0; k<tri.clip_vec.size(); ++k) {
//		printout(
//			k, ": ",
//			Vec2<double>{
//				.x=double(tri.clip_vec.at(k).x),
//				.y=double(tri.clip_vec.at(k).y),
//			},
//			"\n"
//		);
//	}
//	printout("\n");
//}
