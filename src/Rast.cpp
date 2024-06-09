#include "Rast.hpp"
#include "MyDisplay.hpp"
#include <stdexcept>
//#include <algorithm>
//#include <functional>
#include "BaryLerp.hpp"
#include <cmath>


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

//void Rast::calc_visib(
//	const Tri& tri,
//	std::vector<VertTextureCoords>& ret,
//	MyFixedPt near
//) const {
//	const Vert
//		& v1 = tri.screen_v.at(0),
//		& v2 = tri.screen_v.at(1),
//		& v3 = tri.screen_v.at(2);
//	//// 28.4 fixed-point coordinates
//	// 24.8 fixed-point coordinates
//    const i64 Y1 = std::round(256.0 * int(v1.v.y));
//    const i64 Y2 = std::round(256.0 * int(v2.v.y));
//    const i64 Y3 = std::round(256.0 * int(v3.v.y));
//
//    const i64 X1 = std::round(256.0 * int(v1.v.x));
//    const i64 X2 = std::round(256.0 * int(v2.v.x));
//    const i64 X3 = std::round(256.0 * int(v3.v.x));
//    //printout(
//	//	"Rast::calc_visib():\n",
//	//	"X123{",
//	//		double(X1) / 16.0, " ",
//	//		double(X2) / 16.0, " ",
//	//		double(X3) / 16.0,
//	//	"}\n",
//	//	"Y123{",
//	//		double(Y1) / 16.0, " ",
//	//		double(Y2) / 16.0, " ",
//	//		double(Y3) / 16.0,
//	//	"}\n"
//    //);
//
//    // Deltas
//    const i64 DX12 = X1 - X2;
//    const i64 DX23 = X2 - X3;
//    const i64 DX31 = X3 - X1;
//
//    const i64 DY12 = Y1 - Y2;
//    const i64 DY23 = Y2 - Y3;
//    const i64 DY31 = Y3 - Y1;
//
//    // Fixed-point deltas
//    const i64 FDX12 = DX12 << 8;
//    const i64 FDX23 = DX23 << 8;
//    const i64 FDX31 = DX31 << 8;
//
//    const i64 FDY12 = DY12 << 8;
//    const i64 FDY23 = DY23 << 8;
//    const i64 FDY31 = DY31 << 8;
//
//    // Bounding rectangle
//    i64 minx = (std::min(std::min(X1, X2), X3) + 0xFF) >> 8;
//    i64 maxx = (std::max(std::max(X1, X2), X3) + 0xFF) >> 8;
//    i64 miny = (std::min(std::min(Y1, Y2), Y3) + 0xFF) >> 8;
//    i64 maxy = (std::max(std::max(Y1, Y2), Y3) + 0xFF) >> 8;
//    //minx = liborangepower::math::clamp(minx, 0, SCREEN_SIZE_2D.x - 1);
//    if (minx < 0) {
//		minx = 0;
//    }
//    if (maxx > SCREEN_SIZE_2D.x - 1) {
//		maxx = SCREEN_SIZE_2D.x;
//    }
//    if (miny < 0) {
//		miny = 0;
//    }
//    if (maxy > SCREEN_SIZE_2D.y - 1) {
//		maxy = SCREEN_SIZE_2D.y;
//    }
//
//    //(char*&)colorBuffer += miny * stride;
//
//    // Half-edge constants
//    i64 C1 = DY12 * X1 - DX12 * Y1;
//    i64 C2 = DY23 * X2 - DX23 * Y2;
//    i64 C3 = DY31 * X3 - DX31 * Y3;
//
//    // Correct for fill convention
//    if(DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
//    if(DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
//    if(DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;
//
//    i64 CY1 = C1 + DX12 * (miny << 8) - DY12 * (minx << 8);
//    i64 CY2 = C2 + DX23 * (miny << 8) - DY23 * (minx << 8);
//    i64 CY3 = C3 + DX31 * (miny << 8) - DY31 * (minx << 8);
//
//    for (i64 y = miny; y < maxy; y++)
//    {
//        i64 CX1 = CY1;
//        i64 CX2 = CY2;
//        i64 CX3 = CY3;
//   
//        for (i64 x = minx; x < maxx; x++)
//        {
//			//printout(
//			//	"CX{",
//			//		double(CX1) / 256.0, " ",
//			//		double(CX2) / 256.0, " ",
//			//		double(CX3) / 256.0, //" ",
//			//	"}\n"
//			//);
//            if (CX1 > 0 && CX2 > 0 && CX3 > 0)
//            {
//				printout(
//					"CX{",
//						double(CX1) / 256.0, " ",
//						double(CX2) / 256.0, " ",
//						double(CX3) / 256.0, //" ",
//					"}\n"
//				);
//                //colorBuffer[x] = 0x00FFFFFF;
//				Vec2<MyFixedPt>
//					v;
//					//{
//					//	.x=x,
//					//	.y=y,
//					//};
//				//v.x.data = (
//				//	x << (MyFixedPt::FRAC_WIDTH - 4)
//				//);
//				//v.y.data = (
//				//	y << (MyFixedPt::FRAC_WIDTH - 4)
//				//);
//				//v.x.data = MyFixedPt(x >> 4);
//				//v.x.data = MyFixedPt(x >> 4);
//				v.x = MyFixedPt(x); 
//				v.y = MyFixedPt(y); 
//				ret.push_back(VertTextureCoords{
//					.v=v,
//					.uv=BaryLerp(tri, v).uv(),
//				});
//            }
//
//            CX1 -= FDY12;
//            CX2 -= FDY23;
//            CX3 -= FDY31;
//        }
//
//        CY1 += FDX12;
//        CY2 += FDX23;
//        CY3 += FDX31;
//
//        //(char*&)colorBuffer += stride;
//    }
//}
//void Rast::calc_visib(
//	const Tri& tri,
//	std::vector<VertTextureCoords>& ret,
//	MyFixedPt near
//) const {
//	// at first sort the three vertices by y-coordinate ascending so v1 is 
//	// the topmost vertex
//	//sortVerticesAscendingByY();
//	Tri temp_tri;
//	//if (
//	//	tri.screen_v.at(0).v.y < tri.screen_v.at(1).v.y
//	//) {
//	auto my_insertion_sort = [](TriVert& screen_v) -> void {
//		size_t i, j;
//		auto& arr = screen_v;
//		i = 1;
//		while (i < arr.size()) {
//			j = i;
//			while (
//				j > 0
//				&& arr.at(j - 1).v.y > arr.at(j).v.y
//			) {
//				std::swap(arr.at(j), arr.at(j - 1));
//				--j;
//			}
//			++i;
//		}
//		//for (i=0; i<arr.size(); ++i) {
//		//	screen_v.at(i) = arr.at(arr.size() - i - 1);
//		//}
//	};
//	//}
//	temp_tri.screen_v = tri.screen_v;
//	my_insertion_sort(temp_tri.screen_v);
//	//const auto& v1 = temp_tri.screen_v.at(0).v;
//	//const auto& v2 = temp_tri.screen_v.at(1).v;
//	//const auto& v3 = temp_tri.screen_v.at(2).v;
//	const Vert
//		v1(
//			//.x=DrawT(temp_tri.screen_v.at(0).v.x),
//			//.y=DrawT(temp_tri.screen_v.at(0).v.y),
//			//.z=DrawT(temp_tri.screen_v.at(0))
//			temp_tri.screen_v.at(0)
//		),
//		v2(
//			//.x=DrawT(temp_tri.screen_v.at(1).v.x),
//			//.y=DrawT(temp_tri.screen_v.at(1).v.y),
//			temp_tri.screen_v.at(1)
//		),
//		v3(
//			//.x=DrawT(temp_tri.screen_v.at(2).v.x),
//			//.y=DrawT(temp_tri.screen_v.at(2).v.y),
//			temp_tri.screen_v.at(2)
//		);
//	//printout(
//	//	"Rast::calc_visib(): ",
//	//	"{",
//	//		tri.screen_v.at(0).v, " ", 
//	//		tri.screen_v.at(1).v, " ", 
//	//		tri.screen_v.at(2).v, " ", 
//	//	"}",
//	//	"\n",
//	//	"{", v1, " ", v2, " ", v3, "}",
//	//	"\n\n"
//	//);
//	//std::vector<Vec2<DrawT>> line12, line23, line13;
//	//calc_line_coords(
//	//	v1, v2,
//	//	SCREEN_SIZE_2D,
//	//	line12
//	//);
//
//	// here we know that v1.y <= v2.y <= v3.y
//	// check for trivial case of bottom-flat triangle
//	if (v2.v.y == v3.v.y) {
//		//fillBottomFlatTriangle(v1, v2, v3);
//		_calc_flat_bot_visib(
//			temp_tri,
//			//v1,
//			//v2,
//			//v3,
//			ret
//		);
//	} else if (v1.v.y == v2.v.y) {
//		// check for trivial case of top-flat triangle
//		//fillTopFlatTriangle(g, v1, v2, v3);
//		_calc_flat_top_visib(
//			temp_tri,
//			//v1,
//			//v2,
//			//v3,
//			ret
//		);
//	} else {
//		// general case - split the triangle in a topflat and bottom-flat 
//		// one
//		Vert v4{
//			.v{
//				//.x=DrawT(int(
//				//	/*int*/(v1.x)
//				//	+ (
//				//		(MyFixedPt)((v2.y) - (v1.y))
//				//		/ (MyFixedPt)((v3.y) - (v1.y))
//				//	) * (
//				//		(v3.x) - (v1.x)
//				//	)
//				//)),
//				.x=DrawT(/*int*/(
//					v1.v.x
//					+ mult_cx_rw(
//						MyFixedPt(v2.v.y - v1.v.y),
//						MyRwFixedPt(
//							MyFixedPt(v3.v.y - v1.v.y).recip_ldbl()
//						)
//					) * (
//						v3.v.x - v1.v.x
//					)
//				)),
//				.y=DrawT(v2.v.y),
//				.z=v2.v.z,
//				.w=v2.v.w,
//			},
//			//.uv{
//			//	.x=
//			//}
//		};
//		v4.uv = BaryLerp(
//			temp_tri,
//			Vec2<MyFixedPt>{
//				.x=v4.v.x,
//				.y=v4.v.y,
//			}
//		).uv();
//		printout(
//			"v1.uv",
//				Vec2<double>{double(v1.uv.x), double(v1.uv.y)},
//			"\n"
//			"v2.uv",
//				Vec2<double>{double(v2.uv.x), double(v2.uv.y)},
//			"\n"
//			"v3.uv",
//				Vec2<double>{double(v3.uv.x), double(v3.uv.y)},
//			"\n"
//			"v4.uv",
//				Vec2<double>{double(v4.uv.x), double(v4.uv.y)},
//			"\n"
//		);
//
//		//printout("v4: ", v4, "\n");
//		//fillBottomFlatTriangle(g, v1, v2, v4);
//		//fillTopFlatTriangle(g, v2, v4, v3);
//
//		Tri flat_bot;
//		Tri flat_top;
//
//		flat_bot = temp_tri;
//		flat_top = temp_tri;
//		flat_bot.screen_v.at(0) = v1;
//		flat_bot.screen_v.at(1) = v2;
//		flat_bot.screen_v.at(2) = v4;
//
//		flat_top.screen_v.at(0) = v2;
//		flat_top.screen_v.at(1) = v4;
//		flat_top.screen_v.at(2) = v3;
//
//		_calc_flat_bot_visib(
//			flat_bot,
//			ret
//		);
//
//		_calc_flat_top_visib(
//			flat_top,
//			ret
//		);
//	}
//}
//void Rast::_calc_flat_top_visib(
//	const Tri& tri,
//	//const Vert& v1,
//	//const Vert& v2,
//	//const Vert& v3,
//	//std::vector<Vec2<DrawT>>& ret
//	std::vector<VertTextureCoords>& ret
//) const {
//	//const auto& v1 = tri.screen_v.at(0).v;
//	//const auto& v2 = tri.screen_v.at(1).v;
//	//const auto& v3 = tri.screen_v.at(2).v;
//
//	const Vec2<MyFixedPt> v1{
//		.x=MyFixedPt(tri.screen_v.at(0).v.x),
//		.y=MyFixedPt(tri.screen_v.at(0).v.y),
//	};
//	const Vec2<MyFixedPt> v2{
//		.x=MyFixedPt(tri.screen_v.at(1).v.x),
//		.y=MyFixedPt(tri.screen_v.at(1).v.y),
//	};
//	const Vec2<MyFixedPt> v3{
//		.x=MyFixedPt(tri.screen_v.at(2).v.x),
//		.y=MyFixedPt(tri.screen_v.at(2).v.y),
//	};
//	//MyFixedPt invslope1 = MyFixedPt(v3.x - v1.x) / MyFixedPt(v3.y - v1.y);
//	//MyFixedPt invslope2 = MyFixedPt(v3.x - v2.x) / MyFixedPt(v3.y - v2.y);
//
//	const MyFixedPt
//		invslope1 = mult_cx_rw(
//			MyFixedPt(v3.x - v1.x),
//			MyRwFixedPt(MyFixedPt(v3.y - v1.y).recip_ldbl())
//		),
//		invslope2 = mult_cx_rw(
//			MyFixedPt(v3.x - v2.x),
//			MyRwFixedPt(MyFixedPt(v3.y - v2.y).recip_ldbl())
//		);
//	MyFixedPt
//		curr_x1 = MyFixedPt(v3.x),
//		curr_x2 = MyFixedPt(v3.x);
//
//	//printout(
//	//	"Rast::_calc_flat_top_visib(): ",
//	//	v1.x, " ", v2.x, " ", v3.x, "\n",
//	//	v1.y, " ", v2.y, " ", v3.y,
//	//	"\n"
//	//);
//	printout(
//		"Rast::_calc_flat_bot_visib(): ",
//		//v1.x, " ", v2.x, " ", v3.x, "\n",
//		//v1.y, " ", v2.y, " ", v3.y,
//		Vec2<double>{.x=double(v1.x), .y=double(v1.y)}, " ", 
//		Vec2<double>{.x=double(v2.x), .y=double(v2.y)}, " ", 
//		Vec2<double>{.x=double(v3.x), .y=double(v3.y)}, 
//		"\n"
//	);
//	std::vector<Vec2<MyFixedPt>> temp_ret;
//
//	for (
//		MyFixedPt scanline_y = /*std::round*/MyFixedPt(v3.y);
//		scanline_y>=/*std::round*/MyFixedPt(v1.y);
//		scanline_y-=MyFixedPt(1)
//	) {
//		//drawLine((DrawT)curx1, scanlineY, (DrawT)curx2, scanlineY);
//		calc_line_coords(
//			Vec2<MyFixedPt>{
//				.x=MyFixedPt(curr_x1),
//				.y=MyFixedPt(scanline_y),
//			},
//			Vec2<MyFixedPt>{
//				.x=MyFixedPt(curr_x2),
//				.y=MyFixedPt(scanline_y),
//			},
//			SCREEN_SIZE_2D,
//			//ret
//			temp_ret
//		);
//		curr_x1 -= invslope1;
//		curr_x2 -= invslope2;
//	}
//	for (const auto& temp_item: temp_ret) {
//		//ret.push_back(Vec2<DrawT>{
//		//	.x=DrawT(temp_item.x),
//		//	.y=DrawT(temp_item.y),
//		//});
//		const Vec2<MyFixedPt>
//			v{
//				.x=temp_item.x,
//				.y=temp_item.y,
//			};
//		ret.push_back(VertTextureCoords{
//			.v=v,
//			.uv=BaryLerp(tri, v).uv(),
//		});
//	}
//}
//void Rast::_calc_flat_bot_visib(
//	const Tri& tri,
//	//const Vec2<DrawT>& v1,
//	//const Vec2<DrawT>& v2,
//	//const Vec2<DrawT>& v3,
//	//std::vector<Vec2<DrawT>>& ret
//	std::vector<VertTextureCoords>& ret
//) const {
//	//std::vector<Vec2<size_t>> ret(SIZE_2D.y * SIZE_2D.x);
//
//	//for (auto& item: ret) {
//	//	item = false;
//	//}
//	const Vec2<MyFixedPt> v1{
//		.x=MyFixedPt(tri.screen_v.at(0).v.x),
//		.y=MyFixedPt(tri.screen_v.at(0).v.y),
//	};
//	const Vec2<MyFixedPt> v2{
//		.x=MyFixedPt(tri.screen_v.at(1).v.x),
//		.y=MyFixedPt(tri.screen_v.at(1).v.y),
//	};
//	const Vec2<MyFixedPt> v3{
//		.x=MyFixedPt(tri.screen_v.at(2).v.x),
//		.y=MyFixedPt(tri.screen_v.at(2).v.y),
//	};
//
//	//MyFixedPt invslope1 = MyFixedPt(v2.x - v1.x) / MyFixedPt(v2.y - v1.y);
//	//MyFixedPt invslope2 = MyFixedPt(v3.x - v1.x) / MyFixedPt(v3.y - v1.y);
//	const MyFixedPt
//		invslope1 = mult_cx_rw(
//			MyFixedPt(v2.x - v1.x),
//			MyRwFixedPt(MyFixedPt(v2.y - v1.y).recip_ldbl())
//		),
//		invslope2 = mult_cx_rw(
//			MyFixedPt(v3.x - v1.x),
//			MyRwFixedPt(MyFixedPt(v3.y - v1.y).recip_ldbl())
//		);
//
//	MyFixedPt
//		curr_x1 = MyFixedPt(v1.x),
//		curr_x2 = MyFixedPt(v1.x);
//
//	printout(
//		"Rast::_calc_flat_bot_visib(): ",
//		//v1.x, " ", v2.x, " ", v3.x, "\n",
//		//v1.y, " ", v2.y, " ", v3.y,
//		Vec2<double>{.x=double(v1.x), .y=double(v1.y)}, " ", 
//		Vec2<double>{.x=double(v2.x), .y=double(v2.y)}, " ", 
//		Vec2<double>{.x=double(v3.x), .y=double(v3.y)}, 
//		"\n"
//	);
//
//	std::vector<Vec2<MyFixedPt>> temp_ret;
//	for (
//		MyFixedPt scanline_y=MyFixedPt(v1.y);
//		scanline_y<=MyFixedPt(v2.y);
//		scanline_y+=MyFixedPt(1)
//	) {
//		//printout(
//		//	curr_x1, " ",
//		//	curr_x2, " ",
//		//	scanline_y,
//		//	"\n"
//		//);
//		//drawLine((MyFixedPt)curx1, scanlineY, (MyFixedPt)curx2, scanlineY);
//		//calc_line_coords(
//		//	Vec2<int>{
//		//		.x=int(std::trunc(curr_x1)),
//		//		.y=int(/*std::trunc*/(scanline_y)),
//		//	},
//		//	Vec2<int>{
//		//		.x=int(std::trunc(curr_x2)),
//		//		.y=int(/*std::trunc*/(scanline_y)),
//		//	},
//		//	SCREEN_SIZE_2D,
//		//	ret
//		//);
//		calc_line_coords(
//			Vec2<MyFixedPt>{
//				.x=MyFixedPt(curr_x1),
//				.y=MyFixedPt(scanline_y),
//			},
//			Vec2<MyFixedPt>{
//				.x=MyFixedPt(curr_x2),
//				.y=MyFixedPt(scanline_y),
//			},
//			SCREEN_SIZE_2D,
//			//ret
//			temp_ret
//		);
//		curr_x1 += invslope1;
//		curr_x2 += invslope2;
//	}
//	for (const auto& temp_item: temp_ret) {
//		//ret.push_back(Vec2<DrawT>{
//		//	.x=DrawT(temp_item.x),
//		//	.y=DrawT(temp_item.y),
//		//});
//		const Vec2<MyFixedPt>
//			v{
//				.x=temp_item.x,
//				.y=temp_item.y,
//			};
//		ret.push_back(VertTextureCoords{
//			.v=v,
//			.uv=BaryLerp(tri, v).uv(),
//		});
//	}
//	//for (const auto& item: ret) {
//	//	printout(
//	//		item
//	//	);
//	//}
//	//printout("\n");
//}
void Rast::_do_push_back(
	//const Vert& v1,
	//const Vert& v2,
	//const Vert& v3,
	//const std::pair<Tri, TriRast>& tri,
	const Tri& tri,
	const Vec2<DrawT>& v,
	std::vector<VertTextureCoords>& ret
) const {
	const BaryLerp
		lerp(
			//tri.first,
			//tri.second.screen_v,
			//tri.first.rw_arr,
			tri,
			Vec2<MyFixedPt>{
				.x=MyFixedPt(v.x),
				.y=MyFixedPt(v.y),
			}
		);
	if (
		lerp.inside_tri()
		//&& (
		//	lerp.v().x >= MyFixedPt(-1.0)
		//	&& lerp.v().x <= MyFixedPt(1.0)
		//) && (
		//	lerp.v().y >= MyFixedPt(-1.0)
		//	&& lerp.v().y <= MyFixedPt(1.0)
		//) 
		//&& (
		//	//lerp.v().z >= MyFixedPt(0.0)
		//	lerp.v().z >= MyFixedPt(-1.0)
		//	&& lerp.v().z <= MyFixedPt(1.0)
		//)
		//true
	) {
		//printout("test\n");
		ret.push_back(
			//to_push
			VertTextureCoords{
				.img=tri.img,
				.v=v,
				.uv=lerp.uv(),
				//.uv={
				//	.x=uv.x, //A * xa + B * xb + C * xc,
				//	.y=uv.y, //A * ya + B * yb + C * yc,
				//}
			}
			//Vec4<DrawT>{
			//	.x=v.x,
			//	.y=v.y,
			//	//.z=
			//}
		);
	}
}
//void Rast::calc_visib(
//	//size_t tri_idx
//	const Tri& tri,
//	std::vector<VertTextureCoords>& ret,
//	//const TriDraw& tri_draw
//	MyFixedPt near
//) const {
//    // 28.4 fixed-point coordinates
//    const int Y1 = std::round(16.0 * double(tri.screen_v.at(0).v.y));
//    const int Y2 = std::round(16.0 * double(tri.screen_v.at(1).v.y));
//    const int Y3 = std::round(16.0 * double(tri.screen_v.at(2).v.y));
//
//    const int X1 = std::round(16.0 * double(tri.screen_v.at(0).v.x));
//    const int X2 = std::round(16.0 * double(tri.screen_v.at(1).v.x));
//    const int X3 = std::round(16.0 * double(tri.screen_v.at(2).v.x));
//
//    // Deltas
//    const int DX12 = X1 - X2;
//    const int DX23 = X2 - X3;
//    const int DX31 = X3 - X1;
//
//    const int DY12 = Y1 - Y2;
//    const int DY23 = Y2 - Y3;
//    const int DY31 = Y3 - Y1;
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
//    //(char*&)colorBuffer += miny * stride;
//
//    // Half-edge constants
//    int C1 = DY12 * X1 - DX12 * Y1;
//    int C2 = DY23 * X2 - DX23 * Y2;
//    int C3 = DY31 * X3 - DX31 * Y3;
//
//    // Correct for fill convention
//    if(DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
//    if(DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
//    if(DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;
//
//    int CY1 = C1 + DX12 * (miny << 4) - DY12 * (minx << 4);
//    int CY2 = C2 + DX23 * (miny << 4) - DY23 * (minx << 4);
//    int CY3 = C3 + DX31 * (miny << 4) - DY31 * (minx << 4);
//
//    for(int y = miny; y < maxy; y++)
//    {
//        int CX1 = CY1;
//        int CX2 = CY2;
//        int CX3 = CY3;
//   
//        for(int x = minx; x < maxx; x++)
//        {
//            if (CX1 > 0 && CX2 > 0 && CX3 > 0)
//            {
//                //colorBuffer[x] = 0x00FFFFFF;
//                printout(
//					"found pixel: ",
//					Vec2<double>{double(x), double(y)},
//					"\n"
//                );
//                _do_push_back(
//					tri,
//					Vec2<DrawT>{DrawT(x), DrawT(y)},
//					ret
//                );
//            }
//
//            CX1 -= FDY12;
//            CX2 -= FDY23;
//            CX3 -= FDY31;
//        }
//
//        CY1 += FDX12;
//        CY2 += FDX23;
//        CY3 += FDX31;
//
//        //(char*&)colorBuffer += stride;
//    }
//}
//void Rast::calc_visib(
//	//size_t tri_idx
//	const Tri& tri,
//	std::vector<VertTextureCoords>& ret,
//	//const TriDraw& tri_draw
//	MyFixedPt near
//) const {
//	const auto
//		& v1 = tri.v.at(0).v,
//		& v2 = tri.v.at(1).v,
//		& v3 = tri.v.at(2).v;
//	const double y1 = double(v1.y);
//	const double y2 = double(v2.y);
//	const double y3 = double(v3.y);
//
//	const double x1 = double(v1.x);
//	const double x2 = double(v2.x);
//	const double x3 = double(v3.x);
//
//	// Bounding rectangle
//	int minx = (int)std::min(std::min(x1, x2), x3);
//	int maxx = (int)std::max(std::max(x1, x2), x3);
//	int miny = (int)std::min(std::min(y1, y2), y3);
//	int maxy = (int)std::max(std::max(y1, y2), y3);
//
//	//(char*&)colorBuffer += miny * stride;
//
//	// Scan through bounding rectangle
//	for (double y = miny; y < maxy; y++)
//	{
//		for (double x = minx; x < maxx; x++)
//		{
//			// When all half-space functions positive, pixel is in triangle
//			if (
//				(x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0.0
//				&& (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0.0
//				&& (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0.0)
//			{
//				//colorBuffer[x] = 0x00FFFFFF;   // White
//				printout(
//					"Rast::calc_visib(): calling `_do_push_back()`\n"
//				);
//				_do_push_back(
//					tri,
//					Vec2<DrawT>(DrawT(x), DrawT(y)),
//					ret
//				);
//			}
//		}
//
//		//(char*&)colorBuffer += stride;
//	}
//}
void Rast::calc_visib(
	//size_t tri_idx
	//const std::pair<Tri, TriRast>& tri,
	const Tri& tri,
	std::vector<VertTextureCoords>& ret//,
	//const TriDraw& tri_draw
	//MyFixedPt near
) const {
	//--------
	//if (_tri_at_func == nullptr) {
	//	throw std::runtime_error(
	//		"Rast::draw(): `_tri_at_func` is nullptr"
	//	);
	//}
	//if (_disp == nullptr) {
	//	throw std::runtime_error(
	//		"Rast::draw(): `_disp` is nullptr"
	//	);
	//}
	//std::vector<Vec2<size_t>> ret;
	//std::vector<std::vector<bool>> ret;
	//bool ret_arr[SCREEN_SIZE_2D.y * SCREEN_SIZE_2D.x];
	//std::array<bool, SCREEN_SIZE_2D.y * SCREEN_SIZE_2D.x> ret;
	//std::vector<u8> ret(SCREEN_SIZE_2D.y * SCREEN_SIZE_2D.x);
	//printout(ret.size(), "\n");
	//ret.fill(false);
	//for (auto& item: ret) {
	//	item = false;
	//}
	//for (size_t k=0; k<ret.size(); ++k) {
	//	ret.at(k) = false;
	//}
	//--------
	//auto temp_v = tri.screen_v;
	// 28.4 fixed-point coordinates
	const int Y1 = std::round(
		16.0 * double((tri.screen_v.at(0).v.y))
	);
	const int Y2 = std::round(
		16.0 * double((tri.screen_v.at(1).v.y))
	);
	const int Y3 = std::round(
		16.0 * double((tri.screen_v.at(2).v.y))
	);

	const int X1 = std::round(
		16.0 * double((tri.screen_v.at(0).v.x))
	);
	const int X2 = std::round(
		16.0 * double((tri.screen_v.at(1).v.x))
	);
	const int X3 = std::round(
		16.0 * double((tri.screen_v.at(2).v.x))
	);
	//const std::array<Vec2<int>, 3> coords{
	//	{
	//		{.x=X1, .y=Y1},
	//		{.x=X2, .y=Y2},
	//		{.x=X3, .y=Y3},
	//	}
	//};
	//for (size_t i=0; i<coords.size(); ++i) {
	//	printout(
	//		tri.screen_v.at(i).v, " ",
	//		std::hex,
	//		coords.at(i), "\n",
	//		std::dec
	//	);
	//}

	// Deltas
	const int DX12 = (X1 - X2);
	const int DX23 = (X2 - X3);
	const int DX31 = (X3 - X1);

	const int DY12 = (Y1 - Y2);
	const int DY23 = (Y2 - Y3);
	const int DY31 = (Y3 - Y1);

	// Fixed-point deltas
	const int FDX12 = DX12 << 4;
	const int FDX23 = DX23 << 4;
	const int FDX31 = DX31 << 4;

	const int FDY12 = DY12 << 4;
	const int FDY23 = DY23 << 4;
	const int FDY31 = DY31 << 4;

	//const int FDX12 = (X1 - X2) >> 4;
	//const int FDX23 = (X2 - X3) >> 4;
	//const int FDX31 = (X3 - X1) >> 4;

	//const int FDY12 = (Y1 - Y2) >> 4;
	//const int FDY23 = (Y2 - Y3) >> 4;
	//const int FDY31 = (Y3 - Y1) >> 4;

	//const int DX12 = FDX12 >> 8;
	//const int DX23 = FDX23 >> 8;
	//const int DX31 = FDX31 >> 8;

	//const int DY12 = FDY12 >> 8;
	//const int DY23 = FDY23 >> 8;
	//const int DY31 = FDY31 >> 8;

	// Bounding rectangle
	int minx = (std::min(std::min(X1, X2), X3) + 0xF) >> 4;
	int maxx = (std::max(std::max(X1, X2), X3) + 0xF) >> 4;
	int miny = (std::min(std::min(Y1, Y2), Y3) + 0xF) >> 4;
	int maxy = (std::max(std::max(Y1, Y2), Y3) + 0xF) >> 4;

	
	// Block size, standard 8x8 (must be power of two)
	const int q = 8;

	// Start in corner of 8x8 block
	minx &= ~(q - 1);
	miny &= ~(q - 1);

	using liborangepower::math::clamp;
	//if (minx < (0)) {
	//	minx = (0);
	//}
	//if (maxx > int(SCREEN_SIZE_2D.x - 1)) {
	//	maxx = (SCREEN_SIZE_2D.x - 1);
	//}
	//minx = clamp(minx, 0, int(SCREEN_SIZE_2D.x - 1));
	//maxx = clamp(maxx, 0, int(SCREEN_SIZE_2D.x - 1));
	//miny = clamp(miny, 0, int(SCREEN_SIZE_2D.y - 1));
	//maxy = clamp(maxy, 0, int(SCREEN_SIZE_2D.y - 1));
	//if (maxy > int(SCREEN_SIZE_2D.y - 1)) {
	//	maxy = (SCREEN_SIZE_2D.y - 1);
	//}

	printout(
		"minmax_x{", minx, " ", maxx, "}\n",
		"minmax_y{", miny, " ", maxy, "}\n"
	);

	//(char*&)colorBuffer += miny * STRIDE;
	//static constexpr size_t STRIDE = SCREEN_SIZE_2D.x;
	//u8* col_buf = ret.data() + miny * STRIDE;

	//Vec2<size_t> to_push; 
	//size_t to_push_idx = miny * STRIDE;
	//auto do_push_back = [&ret, &to_push_idx]() -> void {
	//	ret.push_back(
	//		Vec2<size_t>{
	//			.x=to_push_idx
	//		}
	//	);
	//};

	// Half-edge constants
	int C1 = DY12 * X1 - DX12 * Y1;
	int C2 = DY23 * X2 - DX23 * Y2;
	int C3 = DY31 * X3 - DX31 * Y3;

	// Correct for fill convention
	if (DY12 < 0 || (DY12 == 0 && DX12 > 0)) {
		++C1;
	}
	if (DY23 < 0 || (DY23 == 0 && DX23 > 0)) {
		++C2;
	}
	if (DY31 < 0 || (DY31 == 0 && DX31 > 0)) {
		++C3;
	}
	//auto area = [](
	//	const Vec2<MyFixedPt>& p0,
	//	const Vec2<MyFixedPt>& p1,
	//	const Vec2<MyFixedPt>& p2
	//) {
	//	return (p1 - p0).zcross((p2 - p0));
	//};
	//auto interpolate = [](
	//	const auto a[3], auto p, const Vec3<MyFixedPt>& coord
	//) {
	//	return coord.x*a[0].*p + coord.y*a[1].*p + coord.z*a[2].*p;
	//};


	// Loop through blocks
	for (int y = miny; y < maxy; y += q) {
		//ret.push_back(std::vector<bool>());
		//printout(
		//	"y: ", y, "\n"
		//);
		for (int x = minx; x < maxx; x += q) {
			////const Vec2<DrawT> to_push{
			////	.x=DrawT(x),
			////	.y=DrawT(y),
			////};
			////printout(
			////	"x, q: ",
			////	x, " ",
			////	q, "\n"
			////);
			//// Corners of block
			//int x0 = x << 4;
			//int x1 = (x + q - 1) << 4;
			//int y0 = y << 4;
			//int y1 = (y + q - 1) << 4;
			////printout(
			////	"{",
			////		"x01{",
			////			double(x0) / 16.0, " ", double(x1) / 16.0,
			////		"} ",
			////		"y01{",
			////			double(y0) / 16.0, " ", double(y1) / 16.0,
			////		"}",
			////	"}",
			////	"\n"
			////);

			//// Evaluate half-space functions
			//bool a00_i = C1 + DX12 * y0 - DY12 * x0 > 0;
			//bool a10_i = C1 + DX12 * y0 - DY12 * x1 > 0;
			//bool a01_i = C1 + DX12 * y1 - DY12 * x0 > 0;
			//bool a11_i = C1 + DX12 * y1 - DY12 * x1 > 0;
			////int a00 = a00_i >= 0;
			////int a10 = a10_i >= 0;
			////int a01 = a01_i >= 0;
			////int a11 = a11_i >= 0;
			//int a = (
			//	(int(a00_i) << 0)
			//	| (int(a10_i) << 1)
			//	| (int(a01_i) << 2)
			//	| (int(a11_i) << 3)
			//);
	
			//bool b00_i = C2 + DX23 * y0 - DY23 * x0 > 0;
			//bool b10_i = C2 + DX23 * y0 - DY23 * x1 > 0;
			//bool b01_i = C2 + DX23 * y1 - DY23 * x0 > 0;
			//bool b11_i = C2 + DX23 * y1 - DY23 * x1 > 0;
			////int b00 = b00_i >= 0;
			////int b10 = b10_i >= 0;
			////int b01 = b01_i >= 0;
			////int b11 = b11_i >= 0;
			//int b = (
			//	(int(b00_i) << 0)
			//	| (int(b10_i) << 1)
			//	| (int(b01_i) << 2)
			//	| (int(b11_i) << 3)
			//);
	
			//bool c00_i = C3 + DX31 * y0 - DY31 * x0 > 0;
			//bool c10_i = C3 + DX31 * y0 - DY31 * x1 > 0;
			//bool c01_i = C3 + DX31 * y1 - DY31 * x0 > 0;
			//bool c11_i = C3 + DX31 * y1 - DY31 * x1 > 0;
			////int c00 = c00_i >= 0;
			////int c10 = c10_i >= 0;
			////int c01 = c01_i >= 0;
			////int c11 = c11_i >= 0;
			//int c = (
			//	(int(c00_i) << 0)
			//	| (int(c10_i) << 1)
			//	| (int(c01_i) << 2)
			//	| (int(c11_i) << 3)
			//);

			//// Skip block when outside an edge
			//if (a == 0x0 || b == 0x0 || c == 0x0) {
			//	//printout(
			//	//	"skip block: ",
			//	//	Vec2<int>{.x=x, .y=y}, " ",
			//	//	"{", a, " ", b, " ", c, "}",
			//	//	//"\n"
			//	//	//" ",
			//	//	//"a_i{",
			//	//	//	a00_i, " ",
			//	//	//	a10_i, " ",
			//	//	//	a01_i, " ",
			//	//	//	a11_i,
			//	//	//"}", 
			//	//	//" ",
			//	//	//"b_i{",
			//	//	//	b00_i, " ",
			//	//	//	b10_i, " ",
			//	//	//	b01_i, " ",
			//	//	//	b11_i,
			//	//	//"}", 
			//	//	//" ",
			//	//	//"c_i{",
			//	//	//	c00_i, " ",
			//	//	//	c10_i, " ",
			//	//	//	c01_i, " ",
			//	//	//	c11_i,
			//	//	//"}",
			//	//	"\n"
			//	//);
			//	continue;
			//}

			//unsigned int *buffer = colorBuffer;
			//u8* buf = col_buf;
			for (int iy=0; iy<q; ++iy) {
				for (int ix=x; ix<x + q; ++ix) {
					//--------
					// implement back-face culling
					const auto
						//& v4a = tri.second.screen_v.at(0),
						//& v4b = tri.second.screen_v.at(1),
						//& v4c = tri.second.screen_v.at(2);
						& v4a = tri.screen_v.at(0).v,
						& v4b = tri.screen_v.at(1).v,
						& v4c = tri.screen_v.at(2).v;
					const Vec3<MyFixedPt>
						v0(v4a.x, v4a.y, v4a.z),
						v1(v4b.x, v4b.y, v4b.z),
						v2(v4c.x, v4c.y, v4c.z);
					// Surface normal to the triangle, per the Wikipedia
					// article on backface culling
					const auto& N = (-(v2 - v0)).cross(v1 - v0);
					//--------
					if (v0.dot(N) >= 0) {
						_do_push_back(
							//tri.first,
							tri,
							Vec2<DrawT>{
								.x=DrawT(ix),
								.y=DrawT(y + iy),
							},
							ret
						);
					}
					//--------
				}
			}

			// Accept whole block when totally covered
			//if (a == 0xF && b == 0xF && c == 0xF) {
			//	printout(
			//		"whole block: ", Vec2<int>{.x=x, .y=y}, "\n"
			//	);
			//	for (int iy = 0; iy < q; ++iy) {
			//		for (int ix = x; ix < x + q; ++ix) {
			//			printout("testificate 1\n");
			//			//buffer[ix] = 0x00007F00;	 // Green
			//			//to_push_idx = ix;
			//			//ret.at(y).at(x) = true;
			//			//++to_push_idx;
			//			//buf[ix] = true;
			//			//col_buf[y * SCREEN_SIZE_2D.x + ix] = true;
			//			_do_push_back(
			//				//to_push
			//				tri,
			//				Vec2<DrawT>{
			//					.x=DrawT(ix),
			//					.y=DrawT(y + iy),
			//				},
			//				ret
			//			);
			//			//printout(
			//			//	Vec2<double>(
			//			//		double(ret.back().x),
			//			//		double(ret.back().y)
			//			//	),
			//			//	"\n"
			//			//);
			//			//printout(
			//			//	buf[ix], "\n"
			//			//);
			//		}

			//		//(char*&)buffer += STRIDE;
			//		//buf += STRIDE;
			//		//to_push_idx += 8;
			//		//++to_push_idx;
			//	}
			//} else { // Partially covered block
			//	printout(
			//		"partial block: ", Vec2<int>{.x=x, .y=y}, "\n"
			//	);
			//	int CY1 = C1 + DX12 * y0 - DY12 * x0;
			//	int CY2 = C2 + DX23 * y0 - DY23 * x0;
			//	int CY3 = C3 + DX31 * y0 - DY31 * x0;

			//	for (int iy = y; iy < y + q; ++iy) {
			//		int CX1 = CY1;
			//		int CX2 = CY2;
			//		int CX3 = CY3;
	  
			//		for (int ix = x; ix < x + q; ++ix) {
			//			if (CX1 > 0 && CX2 > 0 && CX3 > 0) {
			//				printout("testificate 2\n");
			//				//buffer[ix] = 0x0000007F;	 // Blue
			//				//ret_row.push_back(true);
			//				//ret.at
			//				//buf[ix] = true;
			//				//col_buf[y * SCREEN_SIZE_2D.x + ix] = true;
			//				//ret.push_back(to_push);
			//				_do_push_back(
			//					//to_push
			//					tri,
			//					Vec2<DrawT>{
			//						.x=DrawT(ix),
			//						.y=DrawT(iy),
			//					},
			//					ret
			//				);
			//			}
			//			//else {
			//			//	//ret_row.push_back(false);
			//			//}
			//			//++to_push_idx;

			//			CX1 -= FDY12;
			//			CX2 -= FDY23;
			//			CX3 -= FDY31;
			//		}

			//		CY1 += FDX12;
			//		CY2 += FDX23;
			//		CY3 += FDX31;

			//		//(char*&)buffer += STRIDE;
			//		//buf += STRIDE;
			//	}
			//}
		}
		//printout("\n");

		//(char*&)colorBuffer += q * STRIDE;
		//col_buf += q * STRIDE;
	}
	//return ret;
}
