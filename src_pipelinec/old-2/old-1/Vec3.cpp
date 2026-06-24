#include "Vec3.hpp"

//MyFloat vec3_get_x(Vec3 self) {
//	return self.v[VEC3_IND_X];
//}
//Vec3 vec3_set_x(Vec3 self, MyFloat val) {
//	Vec3 ret = self;
//	ret.v[VEC3_IND_X] = val;
//	return ret;
//}
//MyFloat vec3_get_y(Vec3 self) {
//	return self.v[VEC3_IND_Y];
//}
//Vec3 vec3_set_y(Vec3 self, MyFloat val) {
//	Vec3 ret = self;
//	ret.v[VEC3_IND_Y] = val;
//	return ret;
//}
//MyFloat vec3_get_z(Vec3 self) {
//	return self.v[VEC3_IND_Z];
//}
//Vec3 vec3_set_z(Vec3 self, MyFloat val) {
//	Vec3 ret = self;
//	ret.v[VEC3_IND_Z] = val;
//	return ret;
//}
//
//Vec3 BIN_OP_PLUS_Vec3_Vec3(Vec3 left, Vec3 right) {
//	Vec3 ret;
//	uint32_t i;
//	for (i=0; i<VEC3_SIZE; i+=1) {
//		ret.v[i] = left.v[i] + right.v[i];
//	}
//	return ret;
//}
//Vec3 BIN_OP_MINUS_Vec3_Vec3(Vec3 left, Vec3 right) {
//	Vec3 ret;
//	uint32_t i;
//	for (i=0; i<VEC3_SIZE; i+=1) {
//		ret.v[i] = left.v[i] - right.v[i];
//	}
//	return ret;
//}
//Vec3 UNARY_OP_NOT_Vec3(Vec3 expr) {
//	Vec3 ret;
//	uint32_t i;
//	for (i=0; i<VEC3_SIZE; i+=1) {
//		ret.v[i] = -expr.v[i];
//	}
//	return ret;
//}
//Vec3 BIN_OP_INFERRED_MULT_Vec3_MyFloat(Vec3 left, MyFloat right) {
//	Vec3 ret;
//	uint32_t i;
//	for (i=0; i<VEC3_SIZE; i+=1) {
//		ret.v[i] = left.v[i] * right;
//	}
//	return ret;
//}
//Vec3 BIN_OP_MULT_Vec3_MyFloat(Vec3 left, MyFloat right) {
//	Vec3 ret;
//	uint32_t i;
//	for (i=0; i<VEC3_SIZE; i+=1) {
//		ret.v[i] = left.v[i] * right;
//	}
//	return ret;
//}
