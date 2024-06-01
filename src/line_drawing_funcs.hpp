#ifndef src_line_drawing_funcs_hpp
#define src_line_drawing_funcs_hpp
//--------
#include "misc_includes.hpp"
#include <cmath>

//template<typename T>
void calc_line_coords(
	const Vec2<CxFixedI16p16>& v0, const Vec2<CxFixedI16p16>& v1,
	const Vec2<size_t>& screen_size_2d,
	std::vector<Vec2<CxFixedI16p16>>& ret
);

//template<typename T>
//void calc_line_coords(
//	const Vec2<T>& v0, const Vec2<T>& v1,
//	const Vec2<size_t>& screen_size_2d,
//	std::vector<Vec2<int>>& ret
//) {
//	//std::vector<Vec2<T>> ret;
//
//	Vec2<T> delta, pixel_coord, offset;
//
//	delta = Vec2<T>{
//		.x=v1.x - v0.x,
//		.y=v1.y - v0.y
//	};
//
//	if (delta.x < T(0)) {
//		delta.x = -delta.x;
//	}
//	if (delta.y < T(0)) {
//		delta.y = -delta.y;
//	}
//
//	pixel_coord = v0;
//
//	if (v0.x > v1.x) {
//		offset.x = T(-1);
//	} else {
//		offset.x = T(1);
//	}
//
//	if (v0.y > v1.y) {
//		offset.y = T(-1);
//	} else {
//		offset.y = T(1);
//	}
//
//	//m4_plot(pixel_coord.x, pixel_coord.y, color_id, page);
//	auto draw_one = [&]() -> bool {
//		if (
//			(pixel_coord.x < T(0))
//			|| (pixel_coord.x >= T(screen_size_2d.x))
//			|| (pixel_coord.y < T(0))
//			|| (pixel_coord.y >= T(screen_size_2d.y))
//		) {
//			return false;
//		}
//
//		ret.push_back(
//			pixel_coord
//		);
//		return true;
//	};
//
//	if (!draw_one()) {
//		//return ret;
//		return;
//	}
//
//	auto draw 
//		= [&](
//			const T& delta_0, const T& delta_1,
//			T& pixel_coord_0, T& pixel_coord_1,
//			const T& v1_0,
//			T& offset_0, T& offset_1
//		) -> decltype(ret) {
//		T error = delta_0 / T(2);
//
//		while (pixel_coord_0 != v1_0) {
//			error -= delta_1;
//
//			if (error < T(0)) {
//				pixel_coord_1 += offset_1;
//				error += delta_0;
//			}
//			
//			pixel_coord_0 += offset_0;
//
//			//m4_plot(pixel_coord_0, pixel_coord_1, color_id, page);
//			if (!draw_one()) {
//				break;
//			}
//		}
//		return ret;
//	};
//	if (delta.x > delta.y) {
//		draw(
//			delta.x, delta.y,
//			pixel_coord.x, pixel_coord.y,
//			v1.x, 
//			offset.x, offset.y
//		);
//	} else { // if (delta.x <= delta.y)
//		draw(
//			delta.y, delta.x,
//			pixel_coord.y, pixel_coord.x,
//			v1.y, 
//			offset.y, offset.x
//		);
//	}
//}
//template<typename T>
//void calc_line_coords_horiz(
//	const Vec2<T>& v0, const Vec2<T>& v1,
//	const Vec2<size_t>& screen_size_2d,
//	std::vector<Vec2<T>>& ret
//) {
//}
#endif		// src_line_drawing_funcs_hpp
