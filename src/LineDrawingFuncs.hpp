#ifndef src_line_drawing_funcs_hpp
#define src_line_drawing_funcs_hpp
//--------
#include "MiscIncludes.hpp"
#include <cmath>

template<typename T>
void calc_line_coords(
	const Vec2<T>& v0, const Vec2<T>& v1,
	const Vec2<size_t>& screen_size_2d,
	std::vector<Vec2<T>>& ret
) {
	T x;
	T y;
	T x1, y1;
	T x2, y2;

	x1 = v0.x;
	y1 = v0.y;
	x2 = v1.x;
	y2 = v1.y;

	T dx, dy, step;
	T i;

	std::vector<Vec2<T>> temp_ret;

	dx = (x2 - x1);
	dy = (y2 - y1);
	//T dx_abs;
	//dx_abs = std::abs(dx);
	//T dy_abs;
	//dy_abs = std::abs(dy);

	T dx_abs = (
		dx < T(0)
		? -dx
		: dx
	);
	T dy_abs = (
		dx < T(0)
		? -dx
		: dx
	);

	if (dx_abs >= dy_abs) {
		step = dx_abs;
	} else {
		step = dy_abs;
	}

	if (step != T(0)) {
		dx = dx / step;
		dy = dy / step;
		x = x1;
		y = y1;
		i = T(0);

		MyFixedPt last_y = MyFixedPt(y);

		while (i <= step) {
			//putpixel(x, y, 5);
			//printout(Vec2<double>{.x=double(x), .y=double(y)}, " ");
			if (last_y != MyFixedPt(y)) {
				last_y = MyFixedPt(y);
				printout("\n");
			}
			ret.push_back(Vec2<T>{.x=x, .y=y});
			x = x + dx;
			y = y + dy;
			i = i + T(1);
		}
	} else {
		ret.push_back(Vec2<T>{.x=x1, .y=y1});
		//printout(Vec2<double>{.x=double(x1), .y=double(y1)});
	}
	//printout("\n");

	//int x0 = v0.x;
	//int y0 = v0.y;
	//int x1 = v1.x;
	//int y1 = v1.y;
	////if (x0 > x1) {
	////	std::swap(x0, x1);
	////}
	////if (y0 > y1) {
	////	std::swap(y0, y1);
	////}
	//int dx = abs(x1 - x0);
	//int sx = x0 < x1 ? 1 : -1;
	//int dy = -abs(y1 - y0);
	//int sy = y0 < y1 ? 1 : -1;
	//int error = dx + dy;

	//std::vector<Vec2<int>> temp_ret;
	//
	//for (;;) {
	//	  //plot(x0, y0)
	//	const Vec2<int> to_push{.x=x0, .y=y0};
	//	//if (
	//	//	to_push.x < 0 || to_push.x >= int(screen_size_2d.x)
	//	//	|| to_push.y < 0 || to_push.y >= int(screen_size_2d.y)
	//	//) {
	//	//	break;
	//	//}
	//	  ret.push_back(to_push);
	//	  if (x0 == x1 && y0 == y1) {
	//		break;
	//	  }
	//	  int e2 = 2 * error;
	//	  if (e2 >= dy) {
	//		  if (x0 == x1) {
	//			break;
	//		}
	//		  error = error + dy;
	//		  x0 = x0 + sx;
	//	  }
	//	  if (e2 <= dx) {
	//		  if (y0 == y1) {
	//			break;
	//		}
	//		  error = error + dx;
	//		  y0 = y0 + sy;
	//	  }
	//}
	//for (const auto& item: temp_ret) {
	//	printout(item, " ");
	//	ret.push_back(item);
	//}
	//printout("\n");
}

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
