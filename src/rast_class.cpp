#include "rast_class.hpp"
#include "my_display_class.hpp"
#include <stdexcept>


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

std::vector<u8> Rast::calc_visib(
	//size_t tri_idx
	const Tri& tri
	//const TriDraw& tri_draw
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
	//bool ret_arr[SIZE_2D.y * SIZE_2D.x];
	//std::array<bool, SIZE_2D.y * SIZE_2D.x> ret;
	std::vector<u8> ret(SIZE_2D.y * SIZE_2D.x);
	//printout(ret.size(), "\n");
	//ret.fill(false);
	//for (auto& item: ret) {
	//	item = false;
	//}
	for (size_t k=0; k<ret.size(); ++k) {
		ret.at(k) = false;
	}
	//--------
	// 28.4 fixed-point coordinates
    const int Y1 = std::round(16.0f * tri.project_v.at(0).v.y);
    const int Y2 = std::round(16.0f * tri.project_v.at(1).v.y);
    const int Y3 = std::round(16.0f * tri.project_v.at(2).v.y);

    const int X1 = std::round(16.0f * tri.project_v.at(0).v.x);
    const int X2 = std::round(16.0f * tri.project_v.at(1).v.x);
    const int X3 = std::round(16.0f * tri.project_v.at(2).v.x);
    const std::array<Vec2<int>, 3> coords{
		{
			{.x=X1, .y=Y1},
			{.x=X2, .y=Y2},
			{.x=X3, .y=Y3},
		}
    };
    for (size_t i=0; i<coords.size(); ++i) {
		printout(
			tri.project_v.at(i).v, " ",
			std::hex,
			coords.at(i), "\n",
			std::dec
		);
	}

    // Deltas
    const int DX12 = X1 - X2;
    const int DX23 = X2 - X3;
    const int DX31 = X3 - X1;

    const int DY12 = Y1 - Y2;
    const int DY23 = Y2 - Y3;
    const int DY31 = Y3 - Y1;

    // Fixed-point deltas
    const int FDX12 = DX12 << 4;
    const int FDX23 = DX23 << 4;
    const int FDX31 = DX31 << 4;

    const int FDY12 = DY12 << 4;
    const int FDY23 = DY23 << 4;
    const int FDY31 = DY31 << 4;

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

    //(char*&)colorBuffer += miny * STRIDE;
    static constexpr size_t STRIDE = SIZE_2D.x;
    u8* col_buf = ret.data() + miny * STRIDE;
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

    // Loop through blocks
    for (int y = miny; y < maxy; y += q) {
		//ret.push_back(std::vector<bool>());
		printout(
			"y: ", y, "\n"
		);
        for (int x = minx; x < maxx; x += q) {
			printout(
				"x: ", x, "\n"
			);
            // Corners of block
            //int x0 = x << 4;
            //int x1 = (x + q - 1) << 4;
            //int y0 = y << 4;
            //int y1 = (y + q - 1) << 4;

            //// Evaluate half-space functions
            //bool a00 = C1 + DX12 * y0 - DY12 * x0 > 0;
            //bool a10 = C1 + DX12 * y0 - DY12 * x1 > 0;
            //bool a01 = C1 + DX12 * y1 - DY12 * x0 > 0;
            //bool a11 = C1 + DX12 * y1 - DY12 * x1 > 0;
            //int a = (a00 << 0) | (a10 << 1) | (a01 << 2) | (a11 << 3);
    
            //bool b00 = C2 + DX23 * y0 - DY23 * x0 > 0;
            //bool b10 = C2 + DX23 * y0 - DY23 * x1 > 0;
            //bool b01 = C2 + DX23 * y1 - DY23 * x0 > 0;
            //bool b11 = C2 + DX23 * y1 - DY23 * x1 > 0;
            //int b = (b00 << 0) | (b10 << 1) | (b01 << 2) | (b11 << 3);
    
            //bool c00 = C3 + DX31 * y0 - DY31 * x0 > 0;
            //bool c10 = C3 + DX31 * y0 - DY31 * x1 > 0;
            //bool c01 = C3 + DX31 * y1 - DY31 * x0 > 0;
            //bool c11 = C3 + DX31 * y1 - DY31 * x1 > 0;
            //int c = (c00 << 0) | (c10 << 1) | (c01 << 2) | (c11 << 3);

            //// Skip block when outside an edge
            //if (a == 0x0 || b == 0x0 || c == 0x0) {
			//	printout(
			//		"skip block: ", Vec2<int>{.x=x, .y=y}, "\n"
			//	);
			//	continue;
			//}

            ////unsigned int *buffer = colorBuffer;
            ////u8* buf = col_buf;

            //// Accept whole block when totally covered
            //if (a == 0xF && b == 0xF && c == 0xF) {
			//	printout(
			//		"whole block: ", Vec2<int>{.x=x, .y=y}, "\n"
			//	);
            //    for (int iy = 0; iy < q; ++iy) {
            //        for (int ix = x; ix < x + q; ++ix) {
            //            //buffer[ix] = 0x00007F00;   // Green
            //            //to_push_idx = ix;
            //            //ret.at(y).at(x) = true;
            //            //++to_push_idx;
            //            //buf[ix] = true;
            //            col_buf[y * SIZE_2D.x + ix] = true;
            //            //printout(
			//			//	buf[ix], "\n"
            //            //);
            //        }

            //        //(char*&)buffer += STRIDE;
            //        //buf += STRIDE;
            //        //to_push_idx += 8;
            //        //++to_push_idx;
            //    }
            //} else { // Partially covered block
			//	printout(
			//		"partial  block: ", Vec2<int>{.x=x, .y=y}, "\n"
			//	);
            //    int CY1 = C1 + DX12 * y0 - DY12 * x0;
            //    int CY2 = C2 + DX23 * y0 - DY23 * x0;
            //    int CY3 = C3 + DX31 * y0 - DY31 * x0;

            //    for (int iy = y; iy < y + q; ++iy) {
            //        int CX1 = CY1;
            //        int CX2 = CY2;
            //        int CX3 = CY3;
      
            //        for (int ix = x; ix < x + q; ++ix) {
            //            if (CX1 > 0 && CX2 > 0 && CX3 > 0) {
            //                //buffer[ix] = 0x0000007F;   // Blue
			//				//ret_row.push_back(true);
			//				//ret.at
			//				//buf[ix] = true;
			//				col_buf[y * SIZE_2D.x + ix] = true;
            //            }
            //            //else {
			//			//	//ret_row.push_back(false);
            //            //}
            //            //++to_push_idx;

            //            CX1 -= FDY12;
            //            CX2 -= FDY23;
            //            CX3 -= FDY31;
            //        }

            //        CY1 += FDX12;
            //        CY2 += FDX23;
            //        CY3 += FDX31;

            //        //(char*&)buffer += STRIDE;
            //        //buf += STRIDE;
            //    }
            //}
        }
        printout("\n");

        //(char*&)colorBuffer += q * STRIDE;
        //col_buf += q * STRIDE;
    }
	return ret;
}
