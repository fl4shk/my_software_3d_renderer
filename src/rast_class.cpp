#include "rast_class.hpp"
#include "my_display_class.hpp"
#include <stdexcept>
#include <algorithm>
#include <functional>


Rast::Rast() {
}
//Rast::Rast(
//	//TriAtFunc s_tri_at_func,
//	MyDisplay* s_disp
//)
//	: _disp(s_disp)
//{
//}
Rast::~Rast() {
}

void Rast::calc_visib(
	const Tri& tri,
	std::vector<Vec2<DrawT>>& ret
) const {
	// at first sort the three vertices by y-coordinate ascending so v1 is 
	// the topmost vertex
	//sortVerticesAscendingByY();
	Tri temp_tri;
	//if (
	//	tri.project_v.at(0).v.y < tri.project_v.at(1).v.y
	//) {
	auto my_insertion_sort = [](TriVert& project_v) -> void {
		size_t i, j;
		auto& arr = project_v;
		i = 1;
		while (i < arr.size()) {
			j = i;
			while (
				j > 0
				&& arr.at(j - 1).v.y > arr.at(j).v.y
			) {
				std::swap(arr.at(j), arr.at(j - 1));
				--j;
			}
			++i;
		}
		//for (i=0; i<arr.size(); ++i) {
		//	project_v.at(i) = arr.at(arr.size() - i - 1);
		//}
	};
	//}
	temp_tri.project_v = tri.project_v;
	my_insertion_sort(temp_tri.project_v);
	//const auto& v1 = temp_tri.project_v.at(0).v;
	//const auto& v2 = temp_tri.project_v.at(1).v;
	//const auto& v3 = temp_tri.project_v.at(2).v;
	const Vec2<DrawT>
		v1{
			.x=DrawT(temp_tri.project_v.at(0).v.x),
			.y=DrawT(temp_tri.project_v.at(0).v.y),
		},
		v2{
			.x=DrawT(temp_tri.project_v.at(1).v.x),
			.y=DrawT(temp_tri.project_v.at(1).v.y),
		},
		v3{
			.x=DrawT(temp_tri.project_v.at(2).v.x),
			.y=DrawT(temp_tri.project_v.at(2).v.y),
		};
	//printout(
	//	"Rast::calc_visib(): ",
	//	"{",
	//		tri.project_v.at(0).v, " ", 
	//		tri.project_v.at(1).v, " ", 
	//		tri.project_v.at(2).v, " ", 
	//	"}",
	//	"\n",
	//	"{", v1, " ", v2, " ", v3, "}",
	//	"\n\n"
	//);
	//std::vector<Vec2<DrawT>> line12, line23, line13;
	//calc_line_coords(
	//	v1, v2,
	//	SCREEN_SIZE_2D,
	//	line12
	//);

	// here we know that v1.y <= v2.y <= v3.y
	// check for trivial case of bottom-flat triangle
	if (v2.y == v3.y) {
		//fillBottomFlatTriangle(v1, v2, v3);
		_calc_flat_bot_visib(
			//temp_tri,
			v1,
			v2,
			v3,
			ret
		);
	} else if (v1.y == v2.y) {
		// check for trivial case of top-flat triangle
		//fillTopFlatTriangle(g, v1, v2, v3);
		_calc_flat_top_visib(
			//temp_tri,
			v1,
			v2,
			v3,
			ret
		);
	} else {
		// general case - split the triangle in a topflat and bottom-flat 
		// one
		const Vec2<DrawT> v4{
			//.x=DrawT(int(
			//	/*int*/(v1.x)
			//	+ (
			//		(CxFixedI16p16)((v2.y) - (v1.y))
			//		/ (CxFixedI16p16)((v3.y) - (v1.y))
			//	) * (
			//		(v3.x) - (v1.x)
			//	)
			//)),
			.x=DrawT(int(
				v1.x
				+ (
					CxFixedI16p16(v2.y - v1.y) 
					/ CxFixedI16p16(v3.y - v1.y)
				) * (
					v3.x - v1.x
				)
			)),
			.y=DrawT(v2.y),
			//.z=v2.z,
		};
		//printout("v4: ", v4, "\n");
		//fillBottomFlatTriangle(g, v1, v2, v4);
		//fillTopFlatTriangle(g, v2, v4, v3);

		//Tri flat_bot;
		//Tri flat_top;

		//flat_bot.project_v.at(0).v = v1;
		//flat_bot.project_v.at(1).v = v2;
		//flat_bot.project_v.at(2).v = v4;

		//flat_top.project_v.at(0).v = v2;
		//flat_top.project_v.at(1).v = v4;
		//flat_top.project_v.at(2).v = v3;

		_calc_flat_bot_visib(
			//Tri{
			//	.project_v={
			//		v1,
			//		v2,
			//		v4
			//	}
			//},
			//flat_bot,
			v1,
			v2,
			v4,
			ret
		);

		_calc_flat_top_visib(
			//Tri{
			//	.v={
			//		v2,
			//		v4,
			//		v3
			//	}
			//},
			//flat_top,
			v2,
			v4,
			v3,
			ret
		);
	}
}
void Rast::_calc_flat_top_visib(
	//const Tri& tri,
	const Vec2<DrawT>& v1,
	const Vec2<DrawT>& v2,
	const Vec2<DrawT>& v3,
	std::vector<Vec2<DrawT>>& ret
) const {
	//const auto& v1 = tri.project_v.at(0).v;
	//const auto& v2 = tri.project_v.at(1).v;
	//const auto& v3 = tri.project_v.at(2).v;

	//const Vec2<CxFixedI16p16> v1{
	//	.x=CxFixedI16p16(tri.project_v.at(0).v.x),
	//	.y=CxFixedI16p16(tri.project_v.at(0).v.y),
	//};
	//const Vec2<CxFixedI16p16> v2{
	//	.x=CxFixedI16p16(tri.project_v.at(1).v.x),
	//	.y=CxFixedI16p16(tri.project_v.at(1).v.y),
	//};
	//const Vec2<CxFixedI16p16> v3{
	//	.x=CxFixedI16p16(tri.project_v.at(2).v.x),
	//	.y=CxFixedI16p16(tri.project_v.at(2).v.y),
	//};
	CxFixedI16p16 invslope1 = CxFixedI16p16(v3.x - v1.x) / CxFixedI16p16(v3.y - v1.y);
	CxFixedI16p16 invslope2 = CxFixedI16p16(v3.x - v2.x) / CxFixedI16p16(v3.y - v2.y);

	CxFixedI16p16 curr_x1 = v3.x;
	CxFixedI16p16 curr_x2 = v3.x;

	//printout(
	//	"Rast::_calc_flat_top_visib(): ",
	//	v1.x, " ", v2.x, " ", v3.x, "\n",
	//	v1.y, " ", v2.y, " ", v3.y,
	//	"\n"
	//);

	for (
		CxFixedI16p16 scanline_y = /*std::round*/(v3.y);
		scanline_y>=/*std::round*/(v1.y);
		scanline_y-=CxFixedI16p16(1)
	) {
		//drawLine((DrawT)curx1, scanlineY, (DrawT)curx2, scanlineY);
		calc_line_coords(
			Vec2<CxFixedI16p16>{
				.x=/*int(std::trunc(*//*int*/(curr_x1)/*))*/,
				.y=/*int(std::trunc(*/scanline_y/*))*/,
			},
			Vec2<CxFixedI16p16>{
				.x=/*int(std::trunc(*//*int*/(curr_x2)/*))*/,
				.y=/*int(std::trunc(*/scanline_y/*))*/,
			},
			SCREEN_SIZE_2D,
			ret
		);
		curr_x1 -= invslope1;
		curr_x2 -= invslope2;
	}
}
void Rast::_calc_flat_bot_visib(
	//const Tri& tri,
	const Vec2<DrawT>& v1,
	const Vec2<DrawT>& v2,
	const Vec2<DrawT>& v3,
	std::vector<Vec2<DrawT>>& ret
) const {
	//std::vector<Vec2<size_t>> ret(SIZE_2D.y * SIZE_2D.x);

	//for (auto& item: ret) {
	//	item = false;
	//}
	//const Vec2<CxFixedI16p16> v1{
	//	.x=CxFixedI16p16(tri.project_v.at(0).v.x),
	//	.y=CxFixedI16p16(tri.project_v.at(0).v.y),
	//};
	//const Vec2<CxFixedI16p16> v2{
	//	.x=CxFixedI16p16(tri.project_v.at(1).v.x),
	//	.y=CxFixedI16p16(tri.project_v.at(1).v.y),
	//};
	//const Vec2<CxFixedI16p16> v3{
	//	.x=CxFixedI16p16(tri.project_v.at(2).v.x),
	//	.y=CxFixedI16p16(tri.project_v.at(2).v.y),
	//};

	CxFixedI16p16 invslope1 = CxFixedI16p16(v2.x - v1.x) / CxFixedI16p16(v2.y - v1.y);
	CxFixedI16p16 invslope2 = CxFixedI16p16(v3.x - v1.x) / CxFixedI16p16(v3.y - v1.y);

	CxFixedI16p16 curr_x1 = v1.x;
	CxFixedI16p16 curr_x2 = v1.x;

	//printout(
	//	"Rast::_calc_flat_bot_visib(): ",
	//	//v1.x, " ", v2.x, " ", v3.x, "\n",
	//	//v1.y, " ", v2.y, " ", v3.y,
	//	v1, " ", v2, " ", v3,
	//	"\n"
	//);

	for (
		CxFixedI16p16 scanline_y=/*std::round*/(v1.y);
		scanline_y<=/*std::round*/(v2.y);
		scanline_y+=CxFixedI16p16(1)
	) {
		//printout(
		//	curr_x1, " ",
		//	curr_x2, " ",
		//	scanline_y,
		//	"\n"
		//);
		//drawLine((CxFixedI16p16)curx1, scanlineY, (CxFixedI16p16)curx2, scanlineY);
		//calc_line_coords(
		//	Vec2<int>{
		//		.x=int(std::trunc(curr_x1)),
		//		.y=int(/*std::trunc*/(scanline_y)),
		//	},
		//	Vec2<int>{
		//		.x=int(std::trunc(curr_x2)),
		//		.y=int(/*std::trunc*/(scanline_y)),
		//	},
		//	SCREEN_SIZE_2D,
		//	ret
		//);
		calc_line_coords(
			Vec2<DrawT>{
				.x=/*int(std::trunc(*/DrawT(curr_x1)/*))*/,
				.y=/*int(std::trunc(*/scanline_y/*))*/,
			},
			Vec2<DrawT>{
				.x=/*int(std::trunc(*/DrawT(curr_x2)/*))*/,
				.y=/*int(std::trunc(*/scanline_y/*))*/,
			},
			SCREEN_SIZE_2D,
			ret
		);
		curr_x1 += invslope1;
		curr_x2 += invslope2;
	}
	//for (const auto& item: ret) {
	//	printout(
	//		item
	//	);
	//}
	//printout("\n");
}
//std::vector<u8> Rast::calc_visib(
//	//size_t tri_idx
//	const Tri& tri
//	//const TriDraw& tri_draw
//) const {
//	//--------
//	//if (_tri_at_func == nullptr) {
//	//	throw std::runtime_error(
//	//		"Rast::draw(): `_tri_at_func` is nullptr"
//	//	);
//	//}
//	//if (_disp == nullptr) {
//	//	throw std::runtime_error(
//	//		"Rast::draw(): `_disp` is nullptr"
//	//	);
//	//}
//	//std::vector<Vec2<size_t>> ret;
//	//std::vector<std::vector<bool>> ret;
//	//bool ret_arr[SIZE_2D.y * SIZE_2D.x];
//	//std::array<bool, SIZE_2D.y * SIZE_2D.x> ret;
//	std::vector<u8> ret(SIZE_2D.y * SIZE_2D.x);
//	//printout(ret.size(), "\n");
//	//ret.fill(false);
//	//for (auto& item: ret) {
//	//	item = false;
//	//}
//	for (size_t k=0; k<ret.size(); ++k) {
//		ret.at(k) = false;
//	}
//	//--------
//	// 28.4 fixed-point coordinates
//    const int Y1 = std::round(16.0f * tri.project_v.at(0).v.y);
//    const int Y2 = std::round(16.0f * tri.project_v.at(1).v.y);
//    const int Y3 = std::round(16.0f * tri.project_v.at(2).v.y);
//
//    const int X1 = std::round(16.0f * tri.project_v.at(0).v.x);
//    const int X2 = std::round(16.0f * tri.project_v.at(1).v.x);
//    const int X3 = std::round(16.0f * tri.project_v.at(2).v.x);
//    const std::array<Vec2<int>, 3> coords{
//		{
//			{.x=X1, .y=Y1},
//			{.x=X2, .y=Y2},
//			{.x=X3, .y=Y3},
//		}
//    };
//    for (size_t i=0; i<coords.size(); ++i) {
//		printout(
//			tri.project_v.at(i).v, " ",
//			std::hex,
//			coords.at(i), "\n",
//			std::dec
//		);
//	}
//
//    // Deltas
//    const int DX12 = (X1 - X2) >> 4;
//    const int DX23 = (X2 - X3) >> 4;
//    const int DX31 = (X3 - X1) >> 4;
//
//    const int DY12 = (Y1 - Y2) >> 4;
//    const int DY23 = (Y2 - Y3) >> 4;
//    const int DY31 = (Y3 - Y1) >> 4;
//
//    // Fixed-point deltas
//    const int FDX12 = DX12 << 4;
//    const int FDX23 = DX23 << 4;
//    const int FDX31 = DX31 << 4;
//
//    const int FDY12 = DY12 << 4;
//    const int FDY23 = DY23 << 4;
//    const int FDY31 = DY31 << 4;
//
//    // Bounding rectangle
//    int minx = (std::min(std::min(X1, X2), X3) + 0xF) >> 4;
//    int maxx = (std::max(std::max(X1, X2), X3) + 0xF) >> 4;
//    int miny = (std::min(std::min(Y1, Y2), Y3) + 0xF) >> 4;
//    int maxy = (std::max(std::max(Y1, Y2), Y3) + 0xF) >> 4;
//
//    // Block size, standard 8x8 (must be power of two)
//    const int q = 8;
//
//    // Start in corner of 8x8 block
//    minx &= ~(q - 1);
//    miny &= ~(q - 1);
//
//    //(char*&)colorBuffer += miny * STRIDE;
//    static constexpr size_t STRIDE = SIZE_2D.x;
//    u8* col_buf = ret.data() + miny * STRIDE;
//    //Vec2<size_t> to_push; 
//    //size_t to_push_idx = miny * STRIDE;
//    //auto do_push_back = [&ret, &to_push_idx]() -> void {
//	//	ret.push_back(
//	//		Vec2<size_t>{
//	//			.x=to_push_idx
//	//		}
//	//	);
//    //};
//
//    // Half-edge constants
//    int C1 = DY12 * X1 - DX12 * Y1;
//    int C2 = DY23 * X2 - DX23 * Y2;
//    int C3 = DY31 * X3 - DX31 * Y3;
//
//    // Correct for fill convention
//    if (DY12 < 0 || (DY12 == 0 && DX12 > 0)) {
//		++C1;
//	}
//    if (DY23 < 0 || (DY23 == 0 && DX23 > 0)) {
//		++C2;
//	}
//    if (DY31 < 0 || (DY31 == 0 && DX31 > 0)) {
//		++C3;
//	}
//
//    // Loop through blocks
//    for (int y = miny; y < maxy; y += q) {
//		//ret.push_back(std::vector<bool>());
//		printout(
//			"y: ", y, "\n"
//		);
//        for (int x = minx; x < maxx; x += q) {
//			printout(
//				"x, q: ",
//				x, " ",
//				q, "\n"
//			);
//            // Corners of block
//            int x0 = x << 4;
//            int x1 = (x + q - 1) << 4;
//            int y0 = y << 4;
//            int y1 = (y + q - 1) << 4;
//            printout(
//				"{",
//					"{", x0, " ", x1, "}, ",
//					"{", y0, " ", y1, "}",
//				"}",
//				"\n"
//            );
//
//            // Evaluate half-space functions
//            int a00_i = C1 + DX12 * y0 - DY12 * x0;
//            int a10_i = C1 + DX12 * y0 - DY12 * x1;
//            int a01_i = C1 + DX12 * y1 - DY12 * x0;
//            int a11_i = C1 + DX12 * y1 - DY12 * x1;
//            bool a00 = a00_i > 0;
//            bool a10 = a10_i > 0;
//            bool a01 = a01_i > 0;
//            bool a11 = a11_i > 0;
//            int a = (
//				(int(a00) << 0)
//				| (int(a10) << 1)
//				| (int(a01) << 2)
//				| (int(a11) << 3)
//			);
//    
//            int b00_i = C2 + DX23 * y0 - DY23 * x0;
//            int b10_i = C2 + DX23 * y0 - DY23 * x1;
//            int b01_i = C2 + DX23 * y1 - DY23 * x0;
//            int b11_i = C2 + DX23 * y1 - DY23 * x1;
//            bool b00 = b00_i > 0;
//            bool b10 = b10_i > 0;
//            bool b01 = b01_i > 0;
//            bool b11 = b11_i > 0;
//            int b = (
//				(int(b00) << 0)
//				| (int(b10) << 1)
//				| (int(b01) << 2)
//				| (int(b11) << 3)
//			);
//    
//            int c00_i = C3 + DX31 * y0 - DY31 * x0;
//            int c10_i = C3 + DX31 * y0 - DY31 * x1;
//            int c01_i = C3 + DX31 * y1 - DY31 * x0;
//            int c11_i = C3 + DX31 * y1 - DY31 * x1;
//            int c00 = c00_i > 0;
//            int c10 = c10_i > 0;
//            int c01 = c01_i > 0;
//            int c11 = c11_i > 0;
//            int c = (
//				(int(c00) << 0)
//				| (int(c10) << 1)
//				| (int(c01) << 2)
//				| (int(c11) << 3)
//			);
//
//            // Skip block when outside an edge
//            if (a == 0x0 || b == 0x0 || c == 0x0) {
//				printout(
//					"skip block: ",
//					Vec2<int>{.x=x, .y=y}, " ",
//					"{", a, " ", b, " ", c, "}",
//					"\n",
//					"a_i:{",
//						a00_i, " ",
//						a10_i, " ",
//						a01_i, " ",
//						a11_i,
//					"}\n", 
//					"b_i:{",
//						b00_i, " ",
//						b10_i, " ",
//						b01_i, " ",
//						b11_i,
//					"}\n", 
//					"c_i:{",
//						c00_i, " ",
//						c10_i, " ",
//						c01_i, " ",
//						c11_i,
//					"}\n"
//				);
//				continue;
//			}
//
//            //unsigned int *buffer = colorBuffer;
//            //u8* buf = col_buf;
//
//            // Accept whole block when totally covered
//            if (a == 0xF && b == 0xF && c == 0xF) {
//				printout(
//					"whole block: ", Vec2<int>{.x=x, .y=y}, "\n"
//				);
//                for (int iy = 0; iy < q; ++iy) {
//                    for (int ix = x; ix < x + q; ++ix) {
//                        //buffer[ix] = 0x00007F00;   // Green
//                        //to_push_idx = ix;
//                        //ret.at(y).at(x) = true;
//                        //++to_push_idx;
//                        //buf[ix] = true;
//                        col_buf[y * SIZE_2D.x + ix] = true;
//                        //printout(
//						//	buf[ix], "\n"
//                        //);
//                    }
//
//                    //(char*&)buffer += STRIDE;
//                    //buf += STRIDE;
//                    //to_push_idx += 8;
//                    //++to_push_idx;
//                }
//            } else { // Partially covered block
//				printout(
//					"partial  block: ", Vec2<int>{.x=x, .y=y}, "\n"
//				);
//                int CY1 = C1 + DX12 * y0 - DY12 * x0;
//                int CY2 = C2 + DX23 * y0 - DY23 * x0;
//                int CY3 = C3 + DX31 * y0 - DY31 * x0;
//
//                for (int iy = y; iy < y + q; ++iy) {
//                    int CX1 = CY1;
//                    int CX2 = CY2;
//                    int CX3 = CY3;
//      
//                    for (int ix = x; ix < x + q; ++ix) {
//                        if (CX1 > 0 && CX2 > 0 && CX3 > 0) {
//                            //buffer[ix] = 0x0000007F;   // Blue
//							//ret_row.push_back(true);
//							//ret.at
//							//buf[ix] = true;
//							col_buf[y * SIZE_2D.x + ix] = true;
//                        }
//                        //else {
//						//	//ret_row.push_back(false);
//                        //}
//                        //++to_push_idx;
//
//                        CX1 -= FDY12;
//                        CX2 -= FDY23;
//                        CX3 -= FDY31;
//                    }
//
//                    CY1 += FDX12;
//                    CY2 += FDX23;
//                    CY3 += FDX31;
//
//                    //(char*&)buffer += STRIDE;
//                    //buf += STRIDE;
//                }
//            }
//        }
//        printout("\n");
//
//        //(char*&)colorBuffer += q * STRIDE;
//        //col_buf += q * STRIDE;
//    }
//	return ret;
//}
