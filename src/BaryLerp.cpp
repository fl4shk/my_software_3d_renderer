#include "BaryLerp.hpp"
#include "Mat2x2.hpp"

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

//static constexpr Vec2<size_t> MY_SIZE_2D = {2u, 2u};
//[[gnu::noinline]]
//void do_print_mat2x2(
//    const char* name,
//    const std::array<
//        std::array<MyFixedPt, MY_SIZE_2D.y>,
//        MY_SIZE_2D.x
//    >& val
//) {
//}
//extern "C" {
//
//MyRwFixedPt
//    rwa, //= rw_arr.at(0),
//    rwb, //= rw_arr.at(1),
//    rwc; //= rw_arr.at(2);
//MyFixedPt
//    x, //= v1.x,
//    y, //= v1.y,
//
//    xa, //= vt0.v.x,
//    ya, //= vt0.v.y,
//    za, //= vt0.v.z,
//    wa, //= vt0.v.w,
//
//    xb, //= vt1.v.x,
//    yb, //= vt1.v.y,
//    zb, //= vt1.v.z,
//    wb, //= vt1.v.w,
//
//    xc, //= vt2.v.x,
//    yc, //= vt2.v.y,
//    zc, //= vt2.v.z,
//    wc, //= vt2.v.w,
//
//    ua, //= vt0.uv.x,
//    ub, //= vt1.uv.x,
//    uc, //= vt2.uv.x,
//
//    va, //= vt0.uv.y,
//    vb, //= vt1.uv.y,
//    vc; //= vt2.uv.y;
//}
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
    //Mat2x2<MyFixedPt>
    //    b_numer,
    //    c_numer,
    //    denom;
    //static constexpr size_t BUF_SIZE = 256u;
    //char buf[BUF_SIZE];

    std::array<std::array<MyFixedPt, MY_SIZE_2D.y>, MY_SIZE_2D.x>
        b_numer,
        c_numer,
        denom;
    //auto do_print_mat2x2 = [](
    //    const char* name,
    //    const std::array<
    //        std::array<MyFixedPt, MY_SIZE_2D.y>,
    //        MY_SIZE_2D.x
    //    >& val
    //) -> void {
    //    static constexpr size_t BUF_SIZE = 256u;
    //    char buf[BUF_SIZE];
    //    if constexpr (std::same_as<MyFixedPt, float>) {
    //        buf[snprintf(
    //            buf, BUF_SIZE,
    //            "%s=[[%f %f] [%f %f]]",
    //            name, 
    //            val[0][0], val[0][1],
    //            val[1][0], val[1][1]
    //        )] = '\0';
    //    } else {
    //        buf[snprintf(
    //            buf, BUF_SIZE,
    //            "%s=[[%lf %lf] [%lf %lf]]",
    //            name, 
    //            val[0][0], val[0][1],
    //            val[1][0], val[1][1]
    //        )] = '\0';
    //    }
    //    my_printout(buf);

    //    //my_printout(name, "=[");
    //    ////for (size_t j=0; j<MY_SIZE_2D.y; ++j) {
    //    ////    my_printout("[");
    //    ////    for (size_t i=0; i<MY_SIZE_2D.x; ++i) {
    //    ////        my_printout(val[j][i]);
    //    ////        if (i + 1u < MY_SIZE_2D.x) {
    //    ////            my_printout(" ");
    //    ////        }
    //    ////    }
    //    ////    if (j + 1u < MY_SIZE_2D.y) {
    //    ////        my_printout(" ");
    //    ////    }
    //    ////    my_printout("]");
    //    ////}
    //    //my_printout(
    //    //    "[", val[0][0], " ", val[0][1], "] ",
    //    //    "[", val[1][0], " ", val[1][1], "]"
    //    //);
    //    //my_printout("]");
    //};
    b_numer = {
        {
            {xa - xc, x - xc},
            {ya - yc, y - yc},
        }
    };
    c_numer = {
        {
            {xb - xa, x - xa},
            {yb - ya, y - ya},
        }
    };
    denom = {
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
        b_numer_det = det(b_numer),
        c_numer_det = det(c_numer),
        denom_det = det(denom);
    MyRwFixedPt one_over_denom_det;
    one_over_denom_det = my_recip(denom_det);
    B = mult_cx_rw(b_numer_det, one_over_denom_det),
    C = mult_cx_rw(c_numer_det, one_over_denom_det),
    A = MyFixedPt(1) - B - C;

    //my_printout(
    //    "BaryLerp: ",
    //    "A=", A, " ",
    //    "B=", B, " ",
    //    "C=", C, "\n"
    //);
    //buf[snprintf(
    //    buf, BUF_SIZE,
    //    "BaryLerp: A=%f B=%f C=%f\n",
    //    A, B, C
    //)] = '\0';
    //my_printout(buf);
    if (!(
        A < MyFixedPt(0) || A > MyFixedPt(1)
        || B < MyFixedPt(0) || B > MyFixedPt(1)
        || C < MyFixedPt(0) || C > MyFixedPt(1)
    )) {
        //my_printout("BaryLerp: _inside_tri = true;\n");
        _inside_tri = true;
    } else { // if (do_rast_interp)
        //do_print_mat2x2("b_numer", b_numer);
        //my_printout(" ");
        //do_print_mat2x2("c_numer", c_numer);
        //my_printout(" ");
        //do_print_mat2x2("denom", denom);
        //my_printout("\n");
        ////my_printout(
        ////    "rwa=", rwa, " ",
        ////    "rwb=", rwb, " ",
        ////    "rwc=", rwc, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE, 
        //    "rwa=%f rwb=%f rwc=%f\n",
        //    rwa, rwb, rwc
        //)] = '\0';
        //my_printout(buf);

        ////my_printout(
        ////    "x=", x, " ",
        ////    "xa=", xa, " ",
        ////    "xb=", xb, " ",
        ////    "xc=", xc, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE,
        //    "x=%f xa=%f xb=%f xc=%f\n",
        //    x, xa, xb, xc
        //)] = '\0';
        //my_printout(buf);

        ////my_printout(
        ////    "y=", y, " ",
        ////    "ya=", ya, " ",
        ////    "yb=", yb, " ",
        ////    "yc=", yc, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE,
        //    "y=%f ya=%f yb=%f yc=%f\n",
        //    y, ya, yb, yc
        //)] = '\0';
        //my_printout(buf);

        ////my_printout(
        ////    //"z=", z, " ",
        ////    "za=", za, " ",
        ////    "zb=", zb, " ",
        ////    "zc=", zc, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE,
        //    "za=%f zb=%f zc=%f\n",
        //    za, zb, zc
        //)] = '\0';
        //my_printout(buf);

        ////my_printout(
        ////    //"w=", w, " ",
        ////    "wa=", wa, " ",
        ////    "wb=", wb, " ",
        ////    "wc=", wc, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE,
        //    "wa=%f wb=%f wc=%f\n",
        //    wa, wb, wc
        //)] = '\0';
        //my_printout(buf);

        ////my_printout(
        ////    //"u=", u, " ",
        ////    "ua=", ua, " ",
        ////    "ub=", ub, " ",
        ////    "uc=", uc, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE,
        //    "ua=%f ub=%f uc=%f\n",
        //    ua, ub, uc
        //)] = '\0';
        //my_printout(buf);

        ////my_printout(
        ////    //"v=", v, " ",
        ////    "va=", va, " ",
        ////    "vb=", vb, " ",
        ////    "vc=", vc, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE,
        //    "va=%f vb=%f vc=%f\n",
        //    va, vb, vc
        //)] = '\0';
        //my_printout(buf);
        ////my_printout(
        ////    "BaryLerp: ",
        ////    "b_numer_det=", b_numer_det, " ",
        ////    "c_numer_det=", c_numer_det, " ",
        ////    "denom_det=", denom_det, " ",
        ////    "one_over_denom_det=", one_over_denom_det, "\n"
        ////);
        //buf[snprintf(
        //    buf, BUF_SIZE,
        //    "BaryLerp: "
        //    "b_numer_det=%f "
        //    "c_numer_det=%f "
        //    "denom_det=%f "
        //    "one_over_denom_det=%f\n",
        //    b_numer_det, c_numer_det, denom_det, one_over_denom_det
        //)] = '\0';
        //my_printout(buf);

        //my_printout("BaryLerp: returning!\n");
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
    //my_printout(
    //    "BaryLerp: ",
    //    "_rw=", _rw, " ",
    //    "_one_over_rw=", _one_over_rw, " ",
    //    "_v=", _v, " ",
    //    "_uv=", _uv, "\n"
    //);
}
