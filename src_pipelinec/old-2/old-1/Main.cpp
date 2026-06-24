#include "FixedPt.hpp"
#include "Vec3.hpp"
#include "Mat3x3.hpp"
#include "Vec4.hpp"
#include "Mat4x4.hpp"

//#pragma MAIN my_main
#define MyFixed FixedPt(i64, 32)
#define i64 int64_t
DO_TYPEDEF_FIXEDPT(i64, 32)
MK_FIXEDPT_PROTOS(i64, 32)
MK_FIXEDPT_FUNCS(i64, 32)

DO_TYPEDEF_VEC3(FixedPt_int64_t_32)
MK_VEC3_PROTOS(FixedPt_int64_t_32)
MK_VEC3_FUNCS(FixedPt_int64_t_32)

DO_TYPEDEF_MAT3X3(FixedPt_int64_t_32)
MK_MAT3X3_PROTOS(FixedPt_int64_t_32)
MK_MAT3X3_FUNCS(FixedPt_int64_t_32)

DO_TYPEDEF_VEC4(FixedPt_int64_t_32)
MK_VEC4_PROTOS(FixedPt_int64_t_32)
MK_VEC4_FUNCS(FixedPt_int64_t_32)

DO_TYPEDEF_MAT4X4(FixedPt_int64_t_32)
MK_MAT4X4_PROTOS(FixedPt_int64_t_32)
MK_MAT4X4_FUNCS(FixedPt_int64_t_32)

#define MyMat3x3Fixed Mat3x3(FixedPt_int64_t_32)
#pragma MAIN_MHZ my_main 100.0
MyMat3x3Fixed my_main(
	MyMat3x3Fixed IN left,
	MyMat3x3Fixed IN right
) {
	MyMat3x3Fixed ret;
	ret = left * right;
	return ret;
}
