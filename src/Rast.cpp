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
//    //TriAtFunc s_tri_at_func,
//    MyDisplay* s_disp
//)
//    : _disp(s_disp)
//{
//}
Rast::~Rast() {
}

void Rast::_do_push_back(
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
    if (lerp.inside_tri()) {
        //my_printout("test\n");
        //my_printout(
        //    "Rast::_do_push_back(): "
        //    "lerp.inside_tri() == true\n"
        //);
        ret.push_back(
            VertTextureCoords{
                .img=tri.img,
                .v=v,
                .uv=lerp.uv(),
            }
        );
    } else {
        //my_printout(
        //    "Rast::_do_push_back(): "
        //    "lerp.inside_tri() == false\n"
        //);
    }
}
void Rast::calc_visib(
    //size_t tri_idx
    //const std::pair<Tri, TriRast>& tri,
    const Tri& tri,
    std::vector<VertTextureCoords>& ret//,
    //const TriDraw& tri_draw
    //MyFixedPt near
) const {
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
    minx = clamp(minx, 0, int(SCREEN_SIZE_2D.x - 1));
    maxx = clamp(maxx, 0, int(SCREEN_SIZE_2D.x - 1));
    miny = clamp(miny, 0, int(SCREEN_SIZE_2D.y - 1));
    maxy = clamp(maxy, 0, int(SCREEN_SIZE_2D.y - 1));

    my_printout(
        "minmax_x{", minx, " ", maxx, "}\n",
        "minmax_y{", miny, " ", maxy, "}\n"
    );

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
        for (int x = minx; x < maxx; x += q) {
            
            //my_printout("x:", x, "\n");
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
                        //my_printout(
                        //    "Rast::calc_visib(): _do_push_back(): ",
                        //    "y=", y, " ",
                        //    "x=", x, " ",
                        //    "iy=", iy, " ",
                        //    "ix=", ix, " ",
                        //    "N=", N, "\n"
                        //);
                        _do_push_back(
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
        }
        //my_printout("\n");

        //(char*&)colorBuffer += q * STRIDE;
        //col_buf += q * STRIDE;
    }
    //return ret;
}
