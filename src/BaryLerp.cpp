#include "BaryLerp.hpp"

//BaryLerp::BaryLerp(
//    const Tri& tri,
//    const Vec2<MyFixedPt>& v1
//) {
//    init(
//        
//    );
//}
//BaryLerp::BaryLerp(
//    //const Tri& tri,
//    const std::pair<Tri, TriRast>& tri,
//    const Vec2<MyFixedPt>& v1,
//    bool do_rast_interp
//):
//    BaryLerp(
//        //tri.v.at(0),
//        //tri.v.at(1),
//        //tri.v.at(2),
//        tri.first,
//        tri.second.screen_v,
//        tri.first.rw_arr,
//        v1,
//        do_rast_interp
//    )
//{
//}
BaryLerp::BaryLerp(
    const Tri& tri,
    //const Vert& vt0,
    //const Vert& vt1,
    //const Vert& vt2,
    //const std::array<MyRwFixedPt, TRI_VERT_SIZE>& rw_arr,
    const Vec2<MyFixedPt>& v1//,
    //bool do_rast_interp
):
    BaryLerp(
        tri.screen_v,
        tri.rw_arr,
        v1
        //do_rast_interp
    )
{
}
BaryLerp::BaryLerp(
    const std::array<Vert, TRI_VERT_SIZE>& v,
    const std::array<MyRwFixedPt, TRI_VERT_SIZE>& rw_arr,
    const Vec2<MyFixedPt>& v1
) {
    const Vert
        & vt0 = v.at(0),
        & vt1 = v.at(1),
        & vt2 = v.at(2);

    const MyRwFixedPt
        rwa = rw_arr.at(0),
        rwb = rw_arr.at(1),
        rwc = rw_arr.at(2);
    const MyFixedPt
        x = v1.x,
        y = v1.y,

        xa = vt0.v.x,
        ya = vt0.v.y,
        za = vt0.v.z,
        wa = vt0.v.w,

        xb = vt1.v.x,
        yb = vt1.v.y,
        zb = vt1.v.z,
        wb = vt1.v.w,

        xc = vt2.v.x,
        yc = vt2.v.y,
        zc = vt2.v.z,
        wc = vt2.v.w,

        ua = vt0.uv.x,
        ub = vt1.uv.x,
        uc = vt2.uv.x,

        va = vt0.uv.y,
        vb = vt1.uv.y,
        vc = vt2.uv.y;
    static constexpr Vec2<size_t> MY_SIZE_2D = {2u, 2u};
    std::array<std::array<MyFixedPt, MY_SIZE_2D.y>, MY_SIZE_2D.x>
        _b_numer,
        _c_numer,
        _denom;
    auto do_print_mat2x2 = [](
        const char* name,
        const std::array<
            std::array<MyFixedPt, MY_SIZE_2D.y>,
            MY_SIZE_2D.x
        >& val
    ) -> void {
        my_printout(name, "=[");
        for (size_t j=0; j<MY_SIZE_2D.y; ++j) {
            my_printout("[");
            for (size_t i=0; i<MY_SIZE_2D.x; ++i) {
                my_printout(val[j][i]);
                if (i + 1u < MY_SIZE_2D.x) {
                    my_printout(" ");
                }
            }
            if (j + 1u < MY_SIZE_2D.y) {
                my_printout(" ");
            }
            my_printout("]");
        }
        my_printout("]");
    };
    _b_numer = {
        {
            {xa - xc, x - xc},
            {ya - yc, y - yc},
        }
    };
    _c_numer = {
        {
            {xb - xa, x - xa},
            {yb - ya, y - ya},
        }
    };
    _denom = {
        {
            {xb - xa, xc - xa},
            {yb - ya, yc - ya},
        }
    };

    auto det = [](
        const std::array<std::array<MyFixedPt, 2>, 2>& mat2x2
    ) -> MyFixedPt {
        return (
            mat2x2[0][0] * mat2x2[1][1]
            - mat2x2[0][1] * mat2x2[1][0]
        );
    };
    const MyFixedPt
        b_numer_det = det(_b_numer),
        c_numer_det = det(_c_numer),
        denom_det = det(_denom);
    MyRwFixedPt one_over_denom_det;
    one_over_denom_det = my_recip(denom_det);
    B = mult_cx_rw(b_numer_det, one_over_denom_det),
    C = mult_cx_rw(c_numer_det, one_over_denom_det),
    A = MyFixedPt(1) - B - C;

    my_printout(
        "BaryLerp: ",
        "A=", A, " ",
        "B=", B, " ",
        "C=", C, "\n"
    );
    do_print_mat2x2("_b_numer", _b_numer);
    my_printout(" ");
    do_print_mat2x2("_c_numer", _c_numer);
    my_printout(" ");
    do_print_mat2x2("_denom", _denom);
    my_printout("\n");
    if (!(
        A < MyFixedPt(0) || A > MyFixedPt(1)
        || B < MyFixedPt(0) || B > MyFixedPt(1)
        || C < MyFixedPt(0) || C > MyFixedPt(1)
    )) {
        my_printout(
            "rwa=", rwa, " ",
            "rwb=", rwb, " ",
            "rwc=", rwc, "\n"
        );
        my_printout(
            "x=", x, " ",
            "xa=", xa, " ",
            "xb=", xb, " ",
            "xc=", xc, "\n"
        );
        my_printout(
            "y=", y, " ",
            "ya=", ya, " ",
            "yb=", yb, " ",
            "yc=", yc, "\n"
        );
        my_printout(
            //"z=", z, " ",
            "za=", za, " ",
            "zb=", zb, " ",
            "zc=", zc, "\n"
        );
        my_printout(
            //"w=", w, " ",
            "wa=", wa, " ",
            "wb=", wb, " ",
            "wc=", wc, "\n"
        );
        my_printout(
            //"u=", u, " ",
            "ua=", ua, " ",
            "ub=", ub, " ",
            "uc=", uc, "\n"
        );
        my_printout(
            //"v=", v, " ",
            "va=", va, " ",
            "vb=", vb, " ",
            "vc=", vc, "\n"
        );
        my_printout(
            "BaryLerp: ",
            "b_numer_det=", b_numer_det, " ",
            "c_numer_det=", c_numer_det, " ",
            "denom_det=", denom_det, " ",
            "one_over_denom_det=", one_over_denom_det, "\n"
        );
        my_printout("BaryLerp: _inside_tri = true;\n");
        _inside_tri = true;
    } else { // if (do_rast_interp)
        my_printout("BaryLerp: returning!\n");
        return;
    }
    _rw = (
        mult_cx_rw(A, rwa)
        + mult_cx_rw(B, rwb)
        + mult_cx_rw(C, rwc)
    );
    _one_over_rw = my_recip(_rw);
    _v = {
        .x=x,
        .y=y,
        .z=mult_cx_rw(
            (A * za + B * zb + C * zc),
            _one_over_rw
        ),
        //.w=interp_rw,
    };

    _uv = {
        .x=mult_cx_rw(
            (A * ua + B * ub + C * uc),
            _one_over_rw
        ),
        .y=mult_cx_rw(
            (A * va + B * vb + C * vc),
            _one_over_rw
        ),
    };
    my_printout(
        "BaryLerp: ",
        "_rw=", _rw, " ",
        "_one_over_rw=", _one_over_rw, " ",
        "_v=", _v, " ",
        "_uv=", _uv, "\n"
    );
}
