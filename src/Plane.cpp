#include "Plane.hpp"
#include "BaryLerp.hpp"

// https://cs418.cs.illinois.edu/website/text/clipping.html
Plane::Plane(
    Kind s_kind
    //const Vec4<MyFixedPt>& s_n
)
    : _kind(s_kind)
{
}

std::vector<Vert> Plane::do_clip(
    const std::vector<Vert>& prev_vec
) const {
    std::vector<Vert> ret(prev_vec);

    auto intersect_frustum = [this](
        const Vec4<MyFixedPt>& a, const Vec4<MyFixedPt>& b
    ) -> MyFixedPt {
        switch (kind()) {
            case Kind::LEFT: {
                const MyFixedPt ret = (
                    (-a.w - a.x) / (b.x - a.x + b.w - a.w)
                );
                my_printout(
                    "intersect_frustum() LEFT: ", ret, "\n"
                );
                return ret;
            }
            case Kind::RIGHT: {
                const MyFixedPt ret = (
                    (a.w - a.x) / (b.x - a.x - b.w + a.w)
                );
                my_printout(
                    "intersect_frustum() RIGHT: ", ret, "\n"
                );
                return ret;
            }
            case Kind::BOTTOM: {
                const MyFixedPt ret = (
                    (-a.w - a.y) / (b.y - a.y + b.w - a.w)
                );
                my_printout(
                    "intersect_frustum() BOTTOM: ", ret, "\n"
                );
                return ret;
            }
            case Kind::TOP: {
                const MyFixedPt ret = (
                    (a.w - a.y) / (b.y - a.y - b.w + a.w)
                );
                my_printout(
                    "intersect_frustum() TOP: ", ret, "\n"
                );
                return ret;
            }
            case Kind::NEAR: {
                const MyFixedPt ret = (
                    (-a.w - a.z) / (b.z - a.z + b.w - a.w)
                );
                my_printout(
                    "intersect_frustum() NEAR: ", ret, "\n"
                );
                return ret;
            }
            case Kind::FAR: {
                const MyFixedPt ret = (
                    (a.w - a.z) / (b.z - a.z - b.w + a.w)
                );
                my_printout(
                    "intersect_frustum() FAR: ", ret, "\n"
                );
                return ret;
            }
            default: {
                my_printout("intersect_frustum(): oops!\n");
                return MyFixedPt(0.0);
            }
        }
    };

    auto inside_frustum_plane = [this](
        const Vec4<MyFixedPt>& v
    ) -> bool {
        switch(kind()) {
            case Kind::LEFT: {
                const bool ret = (v.x >= -v.w);
                my_printout(
                    "inside_frustum_plane() LEFT: ", ret, "\n"
                );
                return ret;
            }
            case Kind::RIGHT: {
                const bool ret = (v.x <= v.w);
                my_printout(
                    "inside_frustum_plane() RIGHT: ", ret, "\n"
                );
                return ret;
            }
            case Kind::BOTTOM: {
                const bool ret = (v.y >= -v.w);
                my_printout(
                    "inside_frustum_plane() BOTTOM: ", ret, "\n"
                );
                return ret;
            }
            case Kind::TOP: {
                const bool ret = (v.y <= v.w);
                my_printout(
                    "inside_frustum_plane() TOP: ", ret, "\n"
                );
                return ret;
            }
            case Kind::NEAR: {
                const bool ret = (v.z >= -v.w);
                my_printout(
                    "inside_frustum_plane() NEAR: ", ret, "\n"
                );
                return ret;
            }
            case Kind::FAR: {
                const bool ret = (v.z <= v.w);
                my_printout(
                    "inside_frustum_plane() FAR: ", ret, "\n"
                );
                return ret;
            }
            default: {
                my_printout("inside_frustum_plane(): oops!\n");
                return false;
            }
        }
        return false;
    };

    auto clip_edge_frustum = [&](
        int* vnumptr,
        const Vert& v0, const Vert& v1
    ) -> int {
        int vnum = *vnumptr;

        int in0, in1;
        MyFixedPt t;

        in0 = inside_frustum_plane(v0.v);
        in1 = inside_frustum_plane(v1.v);

        if (in0) {
            // start inside
            if (in1) {
                //// all inside
                //ret.push_back(v1);
                //++vnum;
                //*vnumptr = vnum;
                //return 1;
                for (size_t i=ret.size(); i<vnum + 1; ++i) {
                    ret.push_back(Vert());
                }
                ret.at(vnum++) = v1;
                *vnumptr = vnum;
                return 1;
            } else {
                // going out
                //ret.push_back(prev_vec.at(vnum));
                //t = intersect_frustum(v0.v, v1.v);
                //ret.back() = lerp(v0, v1, t);
                //++vnum; // append new vertex on the intersection point
                for (size_t i=ret.size(); i<vnum + 1; ++i) {
                    ret.push_back(Vert());
                }
                auto& vref = ret.at(vnum);
                t = intersect_frustum(v0.v, v1.v);
                vref = lerp(v0, v1, t);
                ++vnum;
            }
        } else {
            // start outside
            if (in1) {
                //ret.push_back(prev_vec.at(vnum));
                //t = intersect_frustum(v0.v, v1.v);
                //ret.back() = lerp(v0, v1, t);
                //++vnum; // apend new vertex on teh intersection point
                //ret.push_back(v1);
                for (size_t i=ret.size(); i<vnum + 1; ++i) {
                    ret.push_back(Vert());
                }
                auto& vref = ret.at(vnum);
                t = intersect_frustum(v0.v, v1.v);
                vref = lerp(v0, v1, t);
                for (size_t i=ret.size(); i<vnum + 1; ++i) {
                    ret.push_back(Vert());
                }
                ++vnum;
                for (size_t i=ret.size(); i<vnum + 1; ++i) {
                    ret.push_back(Vert());
                }
                ret.at(vnum++) = v1;
            } else {
                // all outside
                return -1;
            }
        }
        *vnumptr = vnum;
        return 0;
    };

    const auto vnum = prev_vec.size();
    int voutnum;
    int i, next_idx, res;
    int edges_clipped = 0;

    if (vnum == 1) {
        // special case: point clipping
        if (inside_frustum_plane(prev_vec.front().v)) {
            my_printout("special case: point clipping\n");
            ret.push_back(prev_vec.front());
        }
        return ret;
    }

    voutnum = 0;
    my_printout("vnum: ", vnum, "\n");

    for (i=0; i<vnum; i++) {
        next_idx = i + 1;
        if (next_idx >= vnum) {
            next_idx = 0;
        }
        //res = clip_edge_frustum(vout, voutnum, vin + i, vin + nextidx, fplane);
        clip_edge_frustum(&voutnum, prev_vec.at(i), prev_vec.at(next_idx));
        //if (res == 0) {
        //  ++edges_clipped;
        //}
    }

    if (voutnum <= 0) {
        //assert(edges_clipped == 0);
        //return -1;
        //my_printout("edges_clipped == 0\n");
        my_printout("voutnum:", voutnum, " <= 0\n",);
        return std::vector<Vert>();
    }

    my_printout(
        "return ret;\n"
    );

    return ret;
}


//Vec4<MyFixedPt> Plane::intersect(
//  const Vec4<MyFixedPt>& q1,
//  const Vec4<MyFixedPt>& q2,
//  MyFixedPt alpha
//) const {
//  return q1 + ((q2 - q1) * alpha);
//
//  //// https://math.stackexchange.com/questions/2481917/how-to-get-intersection-points-between-a-plane-and-a-triangle-3d
//  //// we know we have an intersection when we use this function
//  //const MyFixedPt
//  //  my_q_dot_n(q.dot(n())),
//  //  my_p_dot_n(p.dot(n()));
//  ////if (
//  ////    (
//  ////        my_q_dot_n < MyFixedPt(0.0)
//  ////        && my_p_dot_n >= MyFixedPt(0.0)
//  ////    ) || (
//  ////        my_p_dot_n < MyFixedPt(0.0)
//  ////        && my_q_dot_n >= MyFixedPt(0.0)
//  ////    )
//  ////) {
//  //  const Vec4<MyFixedPt>
//  //      a(p * my_q_dot_n),
//  //      b(q * my_p_dot_n);
//  //  return (a - b);
//  ////} else {
//  ////    return std::nullopt;
//  ////}
//}

//MyFixedPt Plane::lerp(
//  MyFixedPt a,
//  MyFixedPt b,
//  MyFixedPt alpha
//) {
//  const MyFixedPt a1 = MyFixedPt(1.0) - alpha;
//  return MyFixedPt(a1 * a + alpha * b);
//}
//Vec4<MyFixedPt> Plane::lerp(
//  const Vec4<MyFixedPt>& a,
//  const Vec4<MyFixedPt>& b,
//  MyFixedPt alpha
//) {
//  Vec4<MyFixedPt> ret;
//  const MyFixedPt a1 = MyFixedPt(1.0) - alpha;
//
//  ret.x = a1 * a.x + alpha * b.x;
//  ret.y = a1 * a.y + alpha * b.y;
//  ret.z = a1 * a.z + alpha * b.z;
//  ret.w = a1 * a.w + alpha * b.w;
//
//  return ret;
//}
