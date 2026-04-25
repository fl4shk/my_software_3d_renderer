#include "Clip.hpp"

Clip::Clip()
    : _plane_arr{
        Plane(Plane::Kind::LEFT),
        Plane(Plane::Kind::RIGHT),
        Plane(Plane::Kind::TOP),
        Plane(Plane::Kind::BOTTOM),
        Plane(Plane::Kind::NEAR),
        Plane(Plane::Kind::FAR),
    }
{
}
Clip::~Clip() {
}
std::vector<Tri> Clip::do_clip(
    const Tri& tri
) const {
    std::vector<Tri> ret;
    std::vector<Vert> temp;
    for (size_t i=0; i<tri.proj_v.size(); ++i) {
        temp.push_back(tri.proj_v.at(i));
    }
    for (size_t i=0; i<size_t(Plane::Kind::LIM); ++i) {
        auto& plane = _plane_arr.at(i);
        temp = plane.do_clip(temp);
        if (temp.size() == 0) {
            my_printout("temp.size() == 0!\n");
            break;
        }
    }
    if (temp.size() > 0) {
        //my_printout("temp.size() > 0: ", temp.size(), "\n");
        my_printout("temp:\n");
        for (const auto& item: temp) {
          my_printout(
            "{",
                item.v, " ",
                item.uv, ";    ",
                to_bits(item.v), " ",
                to_bits(item.uv),
            "}\n"
          );
        }
        my_printout("\n");
        const Vert* temp_data = temp.data();
        const Vert* v = temp_data;
        const Vert* last = v + (temp.size() - 1);
        const Vert* first = v++;
        while (v != last) {
            ret.push_back(Tri{
                .img=tri.img,
                .model=tri.model,
                .proj_v{
                    *first,
                    *v,
                    *(v + 1),
                }
            });
            ++v;
        }
    }
    return ret;
}
