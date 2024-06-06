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
//	MyCxFixedPt near
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
//				Vec2<MyCxFixedPt>
//					v;
//					//{
//					//	.x=x,
//					//	.y=y,
//					//};
//				//v.x.data = (
//				//	x << (MyCxFixedPt::FRAC_WIDTH - 4)
//				//);
//				//v.y.data = (
//				//	y << (MyCxFixedPt::FRAC_WIDTH - 4)
//				//);
//				//v.x.data = MyCxFixedPt(x >> 4);
//				//v.x.data = MyCxFixedPt(x >> 4);
//				v.x = MyCxFixedPt(x); 
//				v.y = MyCxFixedPt(y); 
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
//	MyCxFixedPt near
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
//				//		(MyCxFixedPt)((v2.y) - (v1.y))
//				//		/ (MyCxFixedPt)((v3.y) - (v1.y))
//				//	) * (
//				//		(v3.x) - (v1.x)
//				//	)
//				//)),
//				.x=DrawT(/*int*/(
//					v1.v.x
//					+ mult_cx_rw(
//						MyCxFixedPt(v2.v.y - v1.v.y),
//						MyRwCxFixedPt(
//							MyCxFixedPt(v3.v.y - v1.v.y).recip_ldbl()
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
//			Vec2<MyCxFixedPt>{
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
//	const Vec2<MyCxFixedPt> v1{
//		.x=MyCxFixedPt(tri.screen_v.at(0).v.x),
//		.y=MyCxFixedPt(tri.screen_v.at(0).v.y),
//	};
//	const Vec2<MyCxFixedPt> v2{
//		.x=MyCxFixedPt(tri.screen_v.at(1).v.x),
//		.y=MyCxFixedPt(tri.screen_v.at(1).v.y),
//	};
//	const Vec2<MyCxFixedPt> v3{
//		.x=MyCxFixedPt(tri.screen_v.at(2).v.x),
//		.y=MyCxFixedPt(tri.screen_v.at(2).v.y),
//	};
//	//MyCxFixedPt invslope1 = MyCxFixedPt(v3.x - v1.x) / MyCxFixedPt(v3.y - v1.y);
//	//MyCxFixedPt invslope2 = MyCxFixedPt(v3.x - v2.x) / MyCxFixedPt(v3.y - v2.y);
//
//	const MyCxFixedPt
//		invslope1 = mult_cx_rw(
//			MyCxFixedPt(v3.x - v1.x),
//			MyRwCxFixedPt(MyCxFixedPt(v3.y - v1.y).recip_ldbl())
//		),
//		invslope2 = mult_cx_rw(
//			MyCxFixedPt(v3.x - v2.x),
//			MyRwCxFixedPt(MyCxFixedPt(v3.y - v2.y).recip_ldbl())
//		);
//	MyCxFixedPt
//		curr_x1 = MyCxFixedPt(v3.x),
//		curr_x2 = MyCxFixedPt(v3.x);
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
//	std::vector<Vec2<MyCxFixedPt>> temp_ret;
//
//	for (
//		MyCxFixedPt scanline_y = /*std::round*/MyCxFixedPt(v3.y);
//		scanline_y>=/*std::round*/MyCxFixedPt(v1.y);
//		scanline_y-=MyCxFixedPt(1)
//	) {
//		//drawLine((DrawT)curx1, scanlineY, (DrawT)curx2, scanlineY);
//		calc_line_coords(
//			Vec2<MyCxFixedPt>{
//				.x=MyCxFixedPt(curr_x1),
//				.y=MyCxFixedPt(scanline_y),
//			},
//			Vec2<MyCxFixedPt>{
//				.x=MyCxFixedPt(curr_x2),
//				.y=MyCxFixedPt(scanline_y),
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
//		const Vec2<MyCxFixedPt>
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
//	const Vec2<MyCxFixedPt> v1{
//		.x=MyCxFixedPt(tri.screen_v.at(0).v.x),
//		.y=MyCxFixedPt(tri.screen_v.at(0).v.y),
//	};
//	const Vec2<MyCxFixedPt> v2{
//		.x=MyCxFixedPt(tri.screen_v.at(1).v.x),
//		.y=MyCxFixedPt(tri.screen_v.at(1).v.y),
//	};
//	const Vec2<MyCxFixedPt> v3{
//		.x=MyCxFixedPt(tri.screen_v.at(2).v.x),
//		.y=MyCxFixedPt(tri.screen_v.at(2).v.y),
//	};
//
//	//MyCxFixedPt invslope1 = MyCxFixedPt(v2.x - v1.x) / MyCxFixedPt(v2.y - v1.y);
//	//MyCxFixedPt invslope2 = MyCxFixedPt(v3.x - v1.x) / MyCxFixedPt(v3.y - v1.y);
//	const MyCxFixedPt
//		invslope1 = mult_cx_rw(
//			MyCxFixedPt(v2.x - v1.x),
//			MyRwCxFixedPt(MyCxFixedPt(v2.y - v1.y).recip_ldbl())
//		),
//		invslope2 = mult_cx_rw(
//			MyCxFixedPt(v3.x - v1.x),
//			MyRwCxFixedPt(MyCxFixedPt(v3.y - v1.y).recip_ldbl())
//		);
//
//	MyCxFixedPt
//		curr_x1 = MyCxFixedPt(v1.x),
//		curr_x2 = MyCxFixedPt(v1.x);
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
//	std::vector<Vec2<MyCxFixedPt>> temp_ret;
//	for (
//		MyCxFixedPt scanline_y=MyCxFixedPt(v1.y);
//		scanline_y<=MyCxFixedPt(v2.y);
//		scanline_y+=MyCxFixedPt(1)
//	) {
//		//printout(
//		//	curr_x1, " ",
//		//	curr_x2, " ",
//		//	scanline_y,
//		//	"\n"
//		//);
//		//drawLine((MyCxFixedPt)curx1, scanlineY, (MyCxFixedPt)curx2, scanlineY);
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
//			Vec2<MyCxFixedPt>{
//				.x=MyCxFixedPt(curr_x1),
//				.y=MyCxFixedPt(scanline_y),
//			},
//			Vec2<MyCxFixedPt>{
//				.x=MyCxFixedPt(curr_x2),
//				.y=MyCxFixedPt(scanline_y),
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
//		const Vec2<MyCxFixedPt>
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
	const Tri& tri,
	const Vec2<DrawT>& v,
	std::vector<VertTextureCoords>& ret
) const {
	const BaryLerp
		lerp(
			tri,
			Vec2<MyCxFixedPt>{
				.x=MyCxFixedPt(v.x),
				.y=MyCxFixedPt(v.y),
			}
		);
	if (lerp.inside_tri()) {
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
	//const Vec2<DrawT> temp_v{
	//	.x=DrawT(v.x), /// DrawT(SCREEN_SIZE_2D.x),
	//	.y=DrawT(v.y), /// DrawT(SCREEN_SIZE_2D.y),
	//};
	////const Vert& pvt0 = tri.screen_v.at(0);
	////const Vert& pvt1 = tri.screen_v.at(1);
	////const Vert& pvt2 = tri.screen_v.at(2);
	//const Vert& svt0 = tri.screen_v.at(0);
	//const Vert& svt1 = tri.screen_v.at(1);
	//const Vert& svt2 = tri.screen_v.at(2);

	//const MyRwCxFixedPt
	//	rwa = tri.rw_arr.at(0),
	//	rwb = tri.rw_arr.at(1),
	//	rwc = tri.rw_arr.at(2);
	//const MyCxFixedPt
	//	x = v.x,
	//	y = v.y,
	//	//rwa = tri.rw_arr.at(0), //MyCxFixedPt(1) / vt0.v.w,
	//	//rwb = tri.rw_arr.at(1), //MyCxFixedPt(1) / vt1.v.w,
	//	//rwc = tri.rw_arr.at(2), //MyCxFixedPt(1) / vt2.v.w,
	//	//wa = svt0.v.w,
	//	//wb = svt1.v.w,
	//	//wc = svt2.v.w,
	//	xa = svt0.v.x, // * rw0,
	//	ya = svt0.v.y, // * rw0,
	//	xb = svt1.v.x, // * rw1,
	//	yb = svt1.v.y, // * rw1,
	//	xc = svt2.v.x, // * rw2,
	//	yc = svt2.v.y, // * rw2,
	//	ua = svt0.uv.x, // * rwa,
	//	ub = svt1.uv.x, // * rwa,
	//	uc = svt2.uv.x, // * rwb,
	//	va = svt0.uv.y, // * rwb,
	//	vb = svt1.uv.y, // * rwc,
	//	vc = svt2.uv.y; // * rwc;
	////printout(
	////	"xy: ",
	////	"{", xa, " ", ya, "} ",
	////	"{", xb, " ", yb, "} ",
	////	"{", xc, " ", yc, "} ",
	////	"\n",
	////	"uv: ",
	////	"{", ua, " ", va, "} ",
	////	"{", ub, " ", vb, "} ",
	////	"{", uc, " ", vc, "} ",
	////	"\n"
	////);

	//const std::array<std::array<MyCxFixedPt, 2>, 2>
	//	b_numer{
	//		{
	//			{xa - xc, x - xc},
	//			{ya - yc, y - yc},
	//		}
	//	},
	//	c_numer{
	//		{
	//			{xb - xa, x - xa},
	//			{yb - ya, y - ya},
	//		}
	//	},
	//	denom{
	//		{
	//			{xb - xa, xc - xa},
	//			{yb - ya, yc - ya},
	//		}
	//	};

	//// determinant for a 2x2 matrix
	//auto det = [](
	//	const std::array<std::array<MyCxFixedPt, 2>, 2>& mat2x2
	//) -> MyCxFixedPt {
	//	return (
	//		mat2x2[0][0] * mat2x2[1][1]
	//		- mat2x2[0][1] * mat2x2[1][0]
	//	);
	//};
	//const MyCxFixedPt
	//	b_numer_det = det(b_numer),
	//	c_numer_det = det(c_numer),
	//	denom_det = det(denom);
	//	//one_over_denom_det = MyCxFixedPt(1) / denom_det,
	//	//B = b_numer_det * one_over_denom_det,
	//	//C = c_numer_det * one_over_denom_det,
	//	//A = MyCxFixedPt(1) - B - C;
	//MyRwCxFixedPt one_over_denom_det;
	////one_over_denom_det.data = (
	////	i64(
	////		denom_det.recip_ldbl()
	////		* (1 << MyRwCxFixedPt::FRAC_WIDTH)
	////	)
	////);
	//one_over_denom_det = my_recip(denom_det);
	//const MyCxFixedPt
	//	B = mult_cx_rw(b_numer_det, one_over_denom_det),
	//	C = mult_cx_rw(c_numer_det, one_over_denom_det),
	//	A = MyCxFixedPt(1) - B - C;

	////printout(
	////	"b_numer",
	////	"{"
	////);
	////for (size_t j=0; j<b_numer.size(); ++j) {
	////	printout("{");
	////	for (size_t i=0; i<b_numer.at(j).size(); ++i) {
	////		printout(
	////			double(b_numer.at(j).at(i)), " "
	////		);
	////	}
	////	printout("}");
	////}
	////printout(
	////	"}",
	////	"\n"
	////);
	////printout(
	////	"c_numer",
	////	"{"
	////);
	////for (size_t j=0; j<c_numer.size(); ++j) {
	////	printout("{");
	////	for (size_t i=0; i<c_numer.at(j).size(); ++i) {
	////		printout(
	////			double(c_numer.at(j).at(i)), " "
	////		);
	////	}
	////	printout("}");
	////}
	////printout(
	////	"}",
	////	"\n"
	////);
	////printout(
	////	"denom",
	////	"{"
	////);
	////for (size_t j=0; j<denom.size(); ++j) {
	////	printout("{");
	////	for (size_t i=0; i<denom.at(j).size(); ++i) {
	////		printout(
	////			double(denom.at(j).at(i)), " "
	////		);
	////	}
	////	printout("}");
	////}
	////printout(
	////	"}",
	////	"\n"
	////);
	////printout(
	////	double(b_numer_det), " ",
	////	double(c_numer_det), " ",
	////	double(denom_det), " ",
	////	double(one_over_denom_det),
	////	"\n"
	////);
	//if (
	//	//A < MyCxFixedPt(-0.05) || A > MyCxFixedPt(1.05)
	//	//|| B < MyCxFixedPt(-0.05) || B > MyCxFixedPt(1.05)
	//	//|| C < MyCxFixedPt(-0.05) || C > MyCxFixedPt(1.05)
	//	A < MyCxFixedPt(0.0) || A > MyCxFixedPt(1.0)
	//	|| B < MyCxFixedPt(0.0) || B > MyCxFixedPt(1.0)
	//	|| C < MyCxFixedPt(0.0) || C > MyCxFixedPt(1.0)
	//) {
	//	//printout(
	//	//	"outside triangle:",
	//	//	"{", double(A), " ", double(B), " ", double(C), "}",
	//	//	"\n"
	//	//);
	//	return;
	//}
	//const MyCxFixedPt
	//	//interp_rw = A * rwa + B * rwb + C * rwc;
	//	interp_rw = (
	//		mult_cx_rw(A, rwa)
	//		+ mult_cx_rw(B, rwb)
	//		+ mult_cx_rw(C, rwc)
	//	);
	//	//interp_rw = A / wa + B / wb + C / wc;
	//MyRwCxFixedPt one_over_interp_rw;
	////one_over_interp_rw.data = (
	////	i64(
	////		interp_rw.recip_ldbl()
	////		* (1 << MyRwCxFixedPt::FRAC_WIDTH)
	////	)
	////);
	//one_over_interp_rw = my_recip(interp_rw);
	//
	//const Vec2<MyCxFixedPt>
	//	uv{
	//		//.x=(A * ua + B * ub + C * uc) / interp_rw,
	//		//.y=(A * va + B * vb + C * vc) / interp_rw,
	//		.x=mult_cx_rw(
	//			(A * ua + B * ub + C * uc),
	//			one_over_interp_rw
	//		),
	//		.y=mult_cx_rw(
	//			(A * va + B * vb + C * vc),
	//			one_over_interp_rw
	//		),
	//	};
	////printout(
	////	"uv:",
	////	Vec2<double>{
	////		.x=double(uv.x),
	////		.y=double(uv.y),
	////	},
	////	"\n"
	////);

	////printout(
	////	"{", xa, " ", ya, "} ",
	////	"{", xb, " ", yb, "} ",
	////	"{", xc, " ", yc, "}\n"
	////);
	////printout(
	////	"{",
	////		double(A), " ",
	////		double(B), " ",
	////		double(C),
	////	"}",
	////	"\n"
	////);
	//////const double rw0 = (
	//////	double(1.0) / vt0.v.w
	//////);
	//////const double rw1 = (
	//////	double(1.0) / vt1.v.w
	//////);
	//////const double rw2 = (
	//////	double(1.0) / vt2.v.w
	//////);
	////const double
	////	lerp0 = double(bary_lerp(vt0.v2(), vt1.v2(), temp_v)),
	////	lerp1 = double(bary_lerp(vt1.v2(), vt2.v2(), temp_v)),
	////	lerp2 = double(bary_lerp(vt2.v2(), vt0.v2(), temp_v));
	//////printout(
	//////	lerp0, " ",
	//////	lerp1, " ",
	//////	lerp2,
	//////	"\n"
	//////);
	////const double rz = (
	////	double(/*MyCxFixedPt*/(1.) )
	////	/ (
	////		lerp0 * -double(vt0.v.w)
	////		+ lerp1 * -double(vt1.v.w)
	////		+ lerp2 * -double(vt2.v.w)
	////	)
	////);
	////const double my_u = (
	////	rz * (
	////		lerp0 * double(vt0.uv.x)
	////		+ lerp1 * double(vt1.uv.x)
	////		+ lerp2 * double(vt2.uv.x)
	////	)
	////);
	////const double my_v = (
	////	rz
	////	* (
	////		lerp0 * double(vt0.uv.y)
	////		+ lerp1 * double(vt1.uv.y)
	////		+ lerp2 * double(vt2.uv.y)
	////	)
	////);
	////printout(
	////	"do_push_back(): ",
	////	"{",
	////		double(vt0.v.w), " ",
	////		double(vt1.v.w), " ",
	////		double(vt2.v.w),
	////	"}", " ",
	////	rz, " ",
	////	"{", lerp0, " ", lerp1, " ", lerp2, "}", " ",
	////	Vec2<double>{
	////		.x=double(temp_v.x),
	////		.y=double(temp_v.y),
	////	},
	////	" ",
	////	Vec2<double>{
	////		.x=double(v.x),
	////		.y=double(v.y),
	////	},
	////	" ",
	////	double(my_u), " ",
	////	double(my_v),
	////	"\n"
	////);
	//ret.push_back(
	//	//to_push
	//	VertTextureCoords{
	//		.img=tri.img,
	//		.v=v,
	//		.uv=uv,
	//		//.uv={
	//		//	.x=uv.x, //A * xa + B * xb + C * xc,
	//		//	.y=uv.y, //A * ya + B * yb + C * yc,
	//		//}
	//	}
	//	//Vec4<DrawT>{
	//	//	.x=v.x,
	//	//	.y=v.y,
	//	//	//.z=
	//	//}
	//);
	////printout("\n");
}
//void Rast::calc_visib(
//	//size_t tri_idx
//	const Tri& tri,
//	std::vector<VertTextureCoords>& ret,
//	//const TriDraw& tri_draw
//	MyCxFixedPt near
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
//	MyCxFixedPt near
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
	const Tri& tri,
	std::vector<VertTextureCoords>& ret,
	//const TriDraw& tri_draw
	MyCxFixedPt near
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
	const int Y1 = std::round(16.0 * double((tri.screen_v.at(0).v.y)));
	const int Y2 = std::round(16.0 * double((tri.screen_v.at(1).v.y)));
	const int Y3 = std::round(16.0 * double((tri.screen_v.at(2).v.y)));

	const int X1 = std::round(16.0 * double((tri.screen_v.at(0).v.x)));
	const int X2 = std::round(16.0 * double((tri.screen_v.at(1).v.x)));
	const int X3 = std::round(16.0 * double((tri.screen_v.at(2).v.x)));
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

	if (minx < (0)) {
		minx = (0);
	}
	if (maxx > int(SCREEN_SIZE_2D.x - 1)) {
		maxx = (SCREEN_SIZE_2D.x - 1);
	}
	if (miny < (0)) {
		miny = (0);
	}
	if (maxy > int(SCREEN_SIZE_2D.y - 1)) {
		maxy = (SCREEN_SIZE_2D.y - 1);
	}

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
	//	const Vec2<MyCxFixedPt>& p0,
	//	const Vec2<MyCxFixedPt>& p1,
	//	const Vec2<MyCxFixedPt>& p2
	//) {
	//	return (p1 - p0).zcross((p2 - p0));
	//};
	//auto interpolate = [](
	//	const auto a[3], auto p, const Vec3<MyCxFixedPt>& coord
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
			//const Vec2<DrawT> to_push{
			//	.x=DrawT(x),
			//	.y=DrawT(y),
			//};
			//printout(
			//	"x, q: ",
			//	x, " ",
			//	q, "\n"
			//);
			// Corners of block
			int x0 = x << 4;
			int x1 = (x + q - 1) << 4;
			int y0 = y << 4;
			int y1 = (y + q - 1) << 4;
			//printout(
			//	"{",
			//		"x01{",
			//			double(x0) / 16.0, " ", double(x1) / 16.0,
			//		"} ",
			//		"y01{",
			//			double(y0) / 16.0, " ", double(y1) / 16.0,
			//		"}",
			//	"}",
			//	"\n"
			//);

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
					_do_push_back(
						tri,
						Vec2<DrawT>{
							.x=DrawT(ix),
							.y=DrawT(y + iy),
						},
						ret
					);
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
