#include "line_drawing_funcs.hpp"

void calc_line_coords(
	const Vec2<int>& v0, const Vec2<int>& v1,
	const Vec2<size_t>& screen_size_2d,
	std::vector<Vec2<int>>& ret
) {
	int x0 = v0.x;
	int y0 = v0.y;
	int x1 = v1.x;
	int y1 = v1.y;
	//if (x0 > x1) {
	//	std::swap(x0, x1);
	//}
	//if (y0 > y1) {
	//	std::swap(y0, y1);
	//}
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    std::vector<Vec2<int>> temp_ret;
    
    for (;;) {
        //plot(x0, y0)
		const Vec2<int> to_push{.x=x0, .y=y0};
		//if (
		//	to_push.x < 0 || to_push.x >= int(screen_size_2d.x)
		//	|| to_push.y < 0 || to_push.y >= int(screen_size_2d.y)
		//) {
		//	break;
		//}
        ret.push_back(to_push);
        if (x0 == x1 && y0 == y1) {
			break;
        }
        int e2 = 2 * error;
        if (e2 >= dy) {
            if (x0 == x1) {
				break;
			}
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx) {
            if (y0 == y1) {
				break;
			}
            error = error + dx;
            y0 = y0 + sy;
        }
    }
    //for (const auto& item: temp_ret) {
	//	printout(item, " ");
	//	ret.push_back(item);
    //}
    //printout("\n");
}
