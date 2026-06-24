#ifndef src_pipelinec_vec4_hpp
#define src_pipelinec_vec4_hpp

#include "MiscIncludes.hpp"

#define VEC4_IND_X 0
#define VEC4_IND_Y 1
#define VEC4_IND_Z 2
#define VEC4_IND_W 3
#define VEC4_SIZE 4

#define Vec4(T) \
	CAT(Vec4_, T)

#define DO_TYPEDEF_VEC4(T) \
	typedef struct Vec4(T) { \
		T v[VEC4_SIZE]; \
	} Vec4(T);
#define BINOP_PLUS_VEC4_VEC4(T) \
	BINOP_PLUS(Vec4(T), Vec4(T))
#define BINOP_MINUS_VEC4_VEC4(T) \
	BINOP_MINUS(Vec4(T), Vec4(T))
#define BINOP_INFERRED_MULT_VEC4_T(T) \
	BINOP_INFERRED_MULT(Vec4(T), T)
#define BINOP_DIV_VEC4_T(T) \
	BINOP_DIV(Vec4(T), T)
#define BINOP_EQ_VEC4_VEC4(T) \
	BINOP_EQ(Vec4(T), Vec4(T))
#define BINOP_NEQ_VEC4_VEC4(T) \
	BINOP_NEQ(Vec4(T), Vec4(T))

#ifndef __PIPELINEC__
#define MK_VEC4_PROTOS(T) \
	Vec4(T) BINOP_PLUS_VEC4_VEC4(T)( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	); \
	Vec4(T) BINOP_MINUS_VEC4_VEC4(T)( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	); \
	Vec4(T) BINOP_INFERRED_MULT_VEC4_T(T)( \
		Vec4(T) IN left, \
		T IN right \
	); \
	Vec4(T) BINOP_DIV_VEC4_T(T)( \
		Vec4(T) IN left, \
		T IN right \
	); \
	bool BINOP_EQ_VEC4_VEC4(T)( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	); \
	bool BINOP_NEQ_VEC4_VEC4(T) ( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	); \
	T vec4_dot( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	);
#else
#define MK_VEC4_PROTOS(T)
#endif

#define MK_VEC4_FUNCS(T) \
	Vec4(T) BINOP_PLUS_VEC4_VEC4(T)( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	) { \
		Vec4(T) ret; \
		return ret; \
	} \
	Vec4(T) BINOP_MINUS_VEC4_VEC4(T)( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	) { \
		Vec4(T) ret; \
		return ret; \
	} \
	Vec4(T) BINOP_INFERRED_MULT_VEC4_T(T)( \
		Vec4(T) IN left, \
		T IN right \
	) { \
		Vec4(T) ret; \
		return ret; \
	} \
	Vec4(T) BINOP_DIV_VEC4_T(T)( \
		Vec4(T) IN left, \
		T IN right \
	) { \
		Vec4(T) ret; \
		return ret; \
	} \
	bool BINOP_EQ_VEC4_VEC4(T)( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	) { \
		bool ret = true; \
		uint32_t i; \
		for (i=0; i<VEC4_SIZE; i+=1) { \
			ret = ret && (left.v[i] == right.v[i]); \
		} \
		return ret; \
	} \
	bool BINOP_NEQ_VEC4_VEC4(T) ( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	) { \
		return !(left == right); \
	} \
	T vec4_dot( \
		Vec4(T) IN left, \
		Vec4(T) IN right \
	) { \
		T ret{.data=0}; \
		uint32_t i; \
		for (i=0; i<VEC4_SIZE; i+=1) { \
			ret = ret + left.v[i] * right.v[i]; \
		} \
		return ret; \
	} \

#endif		// src_pipelinec_vec4_hpp
