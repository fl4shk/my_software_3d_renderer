// Based on
//	https://github.com/mhdadk/sutherland-hodgman
// which is licensed as follows:
// MIT License
// 
// Copyright (c) 2022 Mahmoud Abdelkhalek
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "clip_class.hpp"

bool Clip::_is_inside(
	const Vec2<MyCxFixedPt>& p1,
	const Vec2<MyCxFixedPt>& p2,
	const Vec2<MyCxFixedPt>& q
) {
	const MyCxFixedPt R(
		(p2.at(0) - p1.at(0)) * (q.at(1) - p1.at(1))
		- (p2.at(1) - p1.at(1)) * (q.at(0) - p1.at(0))
	);
	if (R <= MyCxFixedPt(0)) {
		return true;
	} else {
		return false;
	}
}
Vec2<MyCxFixedPt> Clip::_compute_intersection(
	const Vec2<MyCxFixedPt>& p1,
	const Vec2<MyCxFixedPt>& p2,
	const Vec2<MyCxFixedPt>& p3,
	const Vec2<MyCxFixedPt>& p4
) {
	MyCxFixedPt
		x,
		y;
	if (p2.at(0) - p1.at(0) == MyCxFixedPt(0)) {
		// if first line is vertical
		x = p1.at(0);
		
		// slope and intercept of second line
		MyCxFixedPt m2 = (p4.at(1) - p3.at(1)) / (p4.at(0) - p3.at(0));
		MyCxFixedPt b2 = p3.at(1) - m2 * p3.at(0);
		
		// y-coordinate of intersection
		y = m2 * x + b2;

	} else if (p4.at(0) - p3.at(0) == MyCxFixedPt(0)) {
		// if second line is vertical
		x = p3.at(0);
		
		// slope and intercept of first line
		MyCxFixedPt m1 = (p2.at(1) - p1.at(1)) / (p2.at(0) - p1.at(0));
		MyCxFixedPt b1 = p1.at(1) - m1 * p1.at(0);
		
		// y-coordinate of intersection
		y = m1 * x + b1;
	} else {
		// if neither line is vertical
		MyCxFixedPt m1 = (p2.at(1) - p1.at(1)) / (p2.at(0) - p1.at(0));
		MyCxFixedPt b1 = p1.at(1) - m1 * p1.at(0);
		
		// slope and intercept of second line
		MyCxFixedPt m2 = (p4.at(1) - p3.at(1)) / (p4.at(0) - p3.at(0));
		MyCxFixedPt b2 = p3.at(1) - m2 * p3.at(0);

		// x-coordinate of intersection
		x = (b2 - b1) / (m1 - m2);

		// y-coordinate of intersection
		y = m1 * x + b1;
	}
	return Vec2<MyCxFixedPt>{
		.x=x,
		.y=y,
	};
}
void Clip::clip(Tri& tri) {
	// this function is adapted from the Wikipedia article
	//tri.clip_vec.clear();
	std::vector<Vec2<MyCxFixedPt>> inp_vec;
	for (size_t i=0; i<tri.project_v.size(); ++i) {
		inp_vec.push_back(
			Vec2<MyCxFixedPt>{
				.x=tri.project_v.at(i).v.x,
				.y=tri.project_v.at(i).v.y,
			}
		);
	}
	for (size_t clip_idx=0; clip_idx<SCREEN_POLYGON.size(); ++clip_idx) {
		//tri.clip_vec.push_back(std::vector<Vec2<MyCxFixedPt>>());
		tri.clip_vec.clear();

		const auto& curr_clip_pt = SCREEN_POLYGON.at(clip_idx);
		const auto& prev_clip_pt = (
			SCREEN_POLYGON.at((clip_idx - 1) % SCREEN_POLYGON.size())
		);

		for (size_t i=0; i<inp_vec.size(); ++i) {
			const auto& curr_pt = inp_vec.at(i);
			const auto& prev_pt = inp_vec.at((i - 1) % inp_vec.size());
			const auto& intersecting_pt = _compute_intersection(
				prev_pt, curr_pt, prev_clip_pt, curr_clip_pt
			);
			if (_is_inside(prev_clip_pt, curr_clip_pt, curr_pt)) {
				if (!_is_inside(prev_clip_pt, curr_clip_pt, prev_pt)) {
					tri.clip_vec.push_back(intersecting_pt);
				}
				tri.clip_vec.push_back(curr_pt);
			} else if (
				_is_inside(prev_clip_pt, curr_clip_pt, prev_pt)
			) {
				tri.clip_vec.push_back(prev_pt);
			}
		}
	}
	printout("Clip::clip(): inputs:\n");
	for (size_t k=0; k<inp_vec.size(); ++k) {
		printout(
			k, ": ",
			Vec2<double>{
				.x=double(inp_vec.at(k).x),
				.y=double(inp_vec.at(k).y),
			},
			"\n"
		);
	}

	printout("Clip::clip(): results:\n");
	for (size_t k=0; k<tri.clip_vec.size(); ++k) {
		printout(
			k, ": ",
			Vec2<double>{
				.x=double(tri.clip_vec.at(k).x),
				.y=double(tri.clip_vec.at(k).y),
			},
			"\n"
		);
	}
	printout("\n");
}
