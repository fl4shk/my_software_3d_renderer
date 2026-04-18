#include "BaryLerp.hpp"
#include "liborangepower_src/misc/misc_types.hpp"

BaryLerp::BaryLerp(
    const Tri& tri,
    const Vec2<MyFixedPt>& v1//,
):
    BaryLerp(
        tri.screen_v,
        tri.rw_arr,
        v1
    )
{
}
BaryLerp::BaryLerp(
    const std::array<Vert, TRI_VERT_SIZE>& v,
    const std::array<MyRwFixedPt, TRI_VERT_SIZE>& rw_arr,
    const Vec2<MyFixedPt>& v1
) {
    const Vert& vt0 = v.at(0);
    const Vert& vt1 = v.at(1);
    const Vert& vt2 = v.at(2);

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
    std::array<std::array<MyFixedPt, 2>, 2>
        _b_numer,
        _c_numer,
        _denom;
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
    if (!(
        A < MyFixedPt(0) || A > MyFixedPt(1)
        || B < MyFixedPt(0) || B > MyFixedPt(1)
        || C < MyFixedPt(0) || C > MyFixedPt(1)
    )) {
        _inside_tri = true;
        //mm_printout("BaryLerp::BaryLerp(): setting `_inside_tri`!\n");
    } else /*if (do_rast_interp)*/ {
        //printout("returning!\n");
        //mm_printout("BaryLerp::BaryLerp(): returning!\n");
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
        //.x=(A * ua + B * ub + C * uc) / interp_rw,
        //.y=(A * va + B * vb + C * vc) / interp_rw,
        .x=mult_cx_rw(
            (A * ua + B * ub + C * uc),
            _one_over_rw
        ),
        .y=mult_cx_rw(
            (A * va + B * vb + C * vc),
            _one_over_rw
        ),
    };
}
