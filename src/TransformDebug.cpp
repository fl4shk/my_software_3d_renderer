#include "Transform.hpp"
//
//Transform::Transform(
//  // perspective projection
//  MyFixedPt near,
//  MyFixedPt far,
//  MyFixedPt fov
//) {
//  set_perspective(
//      near,
//      far,
//      fov
//  );
//}
Transform::Transform() {
}
Transform::Transform(
    const Mat4x4<MyFixedPt>& s_mat
)
    : mat(s_mat) 
{
}
Transform::Transform(
    // affine
    const Mat3x3<MyFixedPt>& rot_scale,
    const Vec3<MyFixedPt>& translate
) {
    set_rot_scale(rot_scale);
    set_translate(translate);
    //if (is_project) {
    //  set_to_project();
    //} else {
        set_to_affine_finish();
    //}
}
Transform::Transform(
    // affine
    const Vec3<MyFixedPt>& rotate,
    const Vec3<MyFixedPt>& translate,
    const Vec3<MyFixedPt>& scale
) {
    set_rot_scale(
        rotate,
        scale
    );
    set_translate(translate);
    set_to_affine_finish();
}
