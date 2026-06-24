#ifndef src_pipelinec_vec3_hpp
#define src_pipelinec_vec3_hpp

#include "MiscIncludes.hpp"


#define VEC3_IND_X 0
#define VEC3_IND_Y 1
#define VEC3_IND_Z 2
#define VEC3_SIZE 3

//typedef struct Vec3 {
//	MyFloat v[VEC3_SIZE];
//} Vec3;
//
//#ifndef __PIPELINEC__
//MyFloat vec3_get_x(Vec3 self); 
//Vec3 vec3_set_x(Vec3 self, MyFloat val);
//MyFloat vec3_get_y(Vec3 self); 
//Vec3 vec3_set_y(Vec3 self, MyFloat val);
//MyFloat vec3_get_z(Vec3 self); 
//Vec3 vec3_set_z(Vec3 self, MyFloat val);
//Vec3 BIN_OP_PLUS_Vec3_Vec3(Vec3 left, Vec3 right);
//Vec3 BIN_OP_MINUS_Vec3_Vec3(Vec3 left, Vec3 right);
//Vec3 UNARY_OP_NOT_Vec3(Vec3 expr);
//Vec3 BIN_OP_INFERRED_MULT_Vec3_MyFloat(Vec3 left, MyFloat right);
//Vec3 BIN_OP_MULT_Vec3_MyFloat(Vec3 left, MyFloat right);
//#endif		// __PIPELINEC__
#define Vec3(T) \
	CAT(Vec3_, T)
#define DO_TYPEDEF_VEC3(T) \
	typedef struct Vec3(T) { \
		T v[VEC3_SIZE]; \
	} Vec3(T);

#define BINOP_PLUS_VEC3_VEC3(T) \
	BINOP_PLUS(Vec3(T), Vec3(T))
#define BINOP_MINUS_VEC3_VEC3(T) \
	BINOP_MINUS(Vec3(T), Vec3(T))
#define BINOP_INFERRED_MULT_VEC3_T(T) \
	BINOP_INFERRED_MULT(Vec3(T), T)
#define BINOP_DIV_VEC3_T(T) \
	BINOP_DIV(Vec3(T), T)
#define BINOP_EQ_VEC3_VEC3(T) \
	BINOP_EQ(Vec3(T), Vec3(T))
#define BINOP_NEQ_VEC3_VEC3(T) \
	BINOP_NEQ(Vec3(T), Vec3(T))

#ifndef __PIPELINEC__
#define MK_VEC3_PROTOS(T) \
	Vec3(T) BINOP_PLUS_VEC3_VEC3(T)( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	); \
	Vec3(T) BINOP_MINUS_VEC3_VEC3(T)( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	); \
	Vec3(T) BINOP_INFERRED_MULT_VEC3_T(T)( \
		Vec3(T) IN left, \
		T IN right \
	); \
	Vec3(T) BINOP_DIV_VEC3_T(T)( \
		Vec3(T) IN left, \
		T IN right \
	); \
	bool BINOP_EQ_VEC3_VEC3(T)( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	); \
	bool BINOP_NEQ_VEC3_VEC3(T) ( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	); \
	T vec3_dot( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	); \
	Vec3(T) vec3_cross( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	);
#else
#define MK_VEC3_PROTOS(T)
#endif

#define MK_VEC3_FUNCS(T) \
	Vec3(T) BINOP_PLUS_VEC3_VEC3(T)( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	) { \
		Vec3(T) ret; \
		return ret; \
	} \
	Vec3(T) BINOP_MINUS_VEC3_VEC3(T)( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	) { \
		Vec3(T) ret; \
		return ret; \
	} \
	Vec3(T) BINOP_INFERRED_MULT_VEC3_T(T)( \
		Vec3(T) IN left, \
		T IN right \
	) { \
		Vec3(T) ret; \
		return ret; \
	} \
	Vec3(T) BINOP_DIV_VEC3_T(T)( \
		Vec3(T) IN left, \
		T IN right \
	) { \
		Vec3(T) ret; \
		return ret; \
	} \
	bool BINOP_EQ_VEC3_VEC3(T)( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	) { \
		bool ret = true; \
		uint32_t i; \
		for (i=0; i<VEC3_SIZE; i+=1) { \
			ret = ret && (left.v[i] == right.v[i]); \
		} \
		return ret; \
	} \
	bool BINOP_NEQ_VEC3_VEC3(T) ( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	) { \
		return !(left == right); \
	} \
	T vec3_dot( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	) { \
		T ret{.data=0}; \
		uint32_t i; \
		for (i=0; i<VEC3_SIZE; i+=1) { \
			ret = ret + left.v[i] * right.v[i]; \
		} \
		return ret; \
	} \
	Vec3(T) vec3_cross( \
		Vec3(T) IN left, \
		Vec3(T) IN right \
	) { \
		const T left_x = left.v[VEC3_IND_X]; \
		const T left_y = left.v[VEC3_IND_Y]; \
		const T left_z = left.v[VEC3_IND_Z]; \
		\
		const T right_x = right.v[VEC3_IND_X]; \
		const T right_y = right.v[VEC3_IND_Y]; \
		const T right_z = right.v[VEC3_IND_Z]; \
		\
		return Vec3(T){ \
			(left_y * right_z) - (left_z * right_y), \
			(left_z * right_x) - (left_x * right_z), \
			(left_x * right_y) - (left_y * right_x) \
		}; \
	} \

#endif		// src_pipelinec_vec3_h
