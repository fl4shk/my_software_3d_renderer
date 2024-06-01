#include "line_drawing_funcs.hpp"

//void calc_line_coords(
//	const Vec2<MyCxFixedPt>& v0, const Vec2<MyCxFixedPt>& v1,
//	const Vec2<size_t>& screen_size_2d,
//	std::vector<Vec2<MyCxFixedPt>>& ret
//) {
//	MyCxFixedPt x;
//	MyCxFixedPt y;
//	MyCxFixedPt x1, y1;
//	MyCxFixedPt x2, y2;
//
//	x1 = v0.x;
//	y1 = v0.y;
//	x2 = v1.x;
//	y2 = v1.y;
//
//	MyCxFixedPt dx, dy, step;
//	MyCxFixedPt i;
//
//	std::vector<Vec2<MyCxFixedPt>> temp_ret;
//
//	dx = (x2 - x1);
//	dy = (y2 - y1);
//	MyCxFixedPt dx_abs;
//	dx_abs.data = std::abs(dx.data);
//	MyCxFixedPt dy_abs;
//	dy_abs.data = std::abs(dy.data);
//
//	//MyCxFixedPt dx_abs = (
//	//	dx < MyCxFixedPt(0)
//	//	? -dx
//	//	: dx
//	//);
//	//MyCxFixedPt dy_abs = (
//	//	dx < MyCxFixedPt(0)
//	//	? -dx
//	//	: dx
//	//);
//
//	if (dx_abs >= dy_abs) {
//		step = dx_abs;
//	} else {
//		step = dy_abs;
//	}
//
//	if (step != MyCxFixedPt(0)) {
//		dx = dx / step;
//		dy = dy / step;
//		x = x1;
//		y = y1;
//		i = MyCxFixedPt(0);
//
//		double last_y = double(y);
//
//		while (i <= step) {
//			//putpixel(x, y, 5);
//			//printout(Vec2<double>{.x=double(x), .y=double(y)}, " ");
//			if (last_y != double(y)) {
//				last_y = double(y);
//				printout("\n");
//			}
//			ret.push_back(Vec2<MyCxFixedPt>{.x=x, .y=y});
//			x = x + dx;
//			y = y + dy;
//			i = i + MyCxFixedPt(1);
//		}
//	} else {
//		ret.push_back(Vec2<MyCxFixedPt>{.x=x1, .y=y1});
//		//printout(Vec2<double>{.x=double(x1), .y=double(y1)});
//	}
//	//printout("\n");
//
//	//int x0 = v0.x;
//	//int y0 = v0.y;
//	//int x1 = v1.x;
//	//int y1 = v1.y;
//	////if (x0 > x1) {
//	////	std::swap(x0, x1);
//	////}
//	////if (y0 > y1) {
//	////	std::swap(y0, y1);
//	////}
//	//int dx = abs(x1 - x0);
//	//int sx = x0 < x1 ? 1 : -1;
//	//int dy = -abs(y1 - y0);
//	//int sy = y0 < y1 ? 1 : -1;
//	//int error = dx + dy;
//
//	//std::vector<Vec2<int>> temp_ret;
//	//
//	//for (;;) {
//	//	  //plot(x0, y0)
//	//	const Vec2<int> to_push{.x=x0, .y=y0};
//	//	//if (
//	//	//	to_push.x < 0 || to_push.x >= int(screen_size_2d.x)
//	//	//	|| to_push.y < 0 || to_push.y >= int(screen_size_2d.y)
//	//	//) {
//	//	//	break;
//	//	//}
//	//	  ret.push_back(to_push);
//	//	  if (x0 == x1 && y0 == y1) {
//	//		break;
//	//	  }
//	//	  int e2 = 2 * error;
//	//	  if (e2 >= dy) {
//	//		  if (x0 == x1) {
//	//			break;
//	//		}
//	//		  error = error + dy;
//	//		  x0 = x0 + sx;
//	//	  }
//	//	  if (e2 <= dx) {
//	//		  if (y0 == y1) {
//	//			break;
//	//		}
//	//		  error = error + dx;
//	//		  y0 = y0 + sy;
//	//	  }
//	//}
//	//for (const auto& item: temp_ret) {
//	//	printout(item, " ");
//	//	ret.push_back(item);
//	//}
//	//printout("\n");
//}
