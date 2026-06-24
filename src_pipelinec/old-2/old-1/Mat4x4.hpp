#ifndef src_pipelinec_mat4x4_hpp
#define src_pipelinec_mat4x4_hpp

#include "MiscIncludes.hpp"
#include "Vec4.hpp"

#define MAT4X4_SIZE_2D_X 4
#define MAT4X4_SIZE_2D_Y 4

#define Mat4x4(T) Mat4x4_ ## T
#define DO_TYPEDEF_MAT4X4(T) \
	typedef struct Mat4x4(T) { \
		T m[MAT4X4_SIZE_2D_Y][MAT4X4_SIZE_2D_X]; \
	} Mat4x4(T); \

#define BINOP_PLUS_MAT4X4_MAT4X4(T) \
	BINOP_PLUS(Mat4x4_ ## T, Mat4x4_ ## T)
#define BINOP_MINUS_MAT4X4_MAT4X4(T) \
	BINOP_MINUS(Mat4x4(T), Mat4x4(T))
#define BINOP_INFERRED_MULT_MAT4X4_MAT4X4(T) \
	BINOP_INFERRED_MULT(Mat4x4(T), Mat4x4(T))
#define BINOP_INFERRED_MULT_MAT4X4_VEC4(T) \
	BINOP_INFERRED_MULT(Mat4x4(T), Vec4(T))
#define BINOP_INFERRED_MULT_MAT4X4_T(T) \
	BINOP_INFERRED_MULT(Mat4x4(T), T)
#define MAT4X4_MULT_HOMOGENEOUS(T) \
	CAT3(mat4x4_, T, _mult_homogeneous)
#define MAT4X4_TRANSPOSE(T) \
	CAT3(mat4x4_, T, _transpose)
#define MAT4X4_IDENTITY(T) \
	CAT3(mat4x4_, T, _identity)


#ifndef __PIPELINEC__
#define BINOP_MULT_MAT4X4_MAT4X4(T) \
	operator *
#else
#define BINOP_MULT_MAT4X4_MAT4X4(T) \
	BIN_OP_MULT_ ## Mat4x4_ ## T ## _ ## T
#endif


#ifndef __PIPELINEC__
#define MK_MAT4X4_PROTOS(T) \
	Mat4x4(T) BINOP_PLUS_MAT4X4_MAT4X4(T)( \
		Mat4x4(T) IN left, \
		Mat4x4(T) IN right \
	); \
	Mat4x4(T) BINOP_MINUS_MAT4X4_MAT4X4(T)( \
		Mat4x4(T) IN left, \
		Mat4x4(T) IN right \
	); \
	Mat4x4(T) BINOP_INFERRED_MULT_MAT4X4_MAT4X4(T)( \
		Mat4x4(T) IN left, \
		Mat4x4(T) IN right \
	); \
	Vec4(T) BINOP_INFERRED_MULT_MAT4X4_VEC4(T)( \
		Mat4x4(T) IN left, \
		Vec4(T) IN right\
	); \
	Mat4x4(T) BINOP_INFERRED_MULT_MAT4X4_T(T)( \
		Mat4x4(T) IN left, \
		T IN right \
	); \
	Mat4x4(T) MAT4X4_TRANSPOSE(T)( \
		Mat4x4(T) self \
	); \
	Mat4x4(T) MAT4X4_IDENTITY(T)( \
		void \
	);
#else
#define MK_MAT4X4_PROTOS(T)
#endif		// !__PIPELINEC__

#define MK_MAT4X4_FUNCS(T) \
	Mat4x4(T) BINOP_PLUS_MAT4X4_MAT4X4(T)( \
		Mat4x4(T) IN left, \
		Mat4x4(T) IN right \
	) { \
		Mat4x4(T) ret; \
		uint32_t j; \
		uint32_t i; \
		for (j=0; j<MAT4X4_SIZE_2D_Y; j+=1) { \
			for (i=0; i<MAT4X4_SIZE_2D_X; i+=1) { \
				ret.m[j][i] = ( \
					left.m[j][i] + right.m[j][i] \
				); \
			} \
		} \
		return ret; \
	} \
	Mat4x4(T) BINOP_MINUS_MAT4X4_MAT4X4(T)( \
		Mat4x4(T) IN left, \
		Mat4x4(T) IN right \
	) { \
		Mat4x4_ ## T ret; \
		uint32_t j; \
		uint32_t i; \
		for (j=0; j<MAT4X4_SIZE_2D_Y; j+=1) { \
			for (i=0; i<MAT4X4_SIZE_2D_X; i+=1) { \
				ret.m[j][i] = ( \
					left.m[j][i] - right.m[j][i] \
				); \
			} \
		} \
		return ret; \
	} \
	Mat4x4(T) BINOP_INFERRED_MULT_MAT4X4_MAT4X4(T)( \
		Mat4x4(T) IN left, \
		Mat4x4(T) IN right \
	) { \
		Mat4x4(T) ret; \
		uint32_t j; \
		uint32_t i; \
		uint32_t k; \
		for (j=1; j<MAT4X4_SIZE_2D_Y; j+=1) { \
			for (i=0; i<MAT4X4_SIZE_2D_X; i+=1) { \
				T sum = {0}; \
				for (k=0; k<MAT4X4_SIZE_2D_X; k+=1) { \
					const T temp_sum = left.m[j][k] * right.m[k][i]; \
					sum = sum + temp_sum; \
				} \
				ret.m[j][i] = sum; \
			} \
		} \
		return ret; \
	} \
	Vec4(T) BINOP_INFERRED_MULT_MAT4X4_VEC4(T)( \
		Mat4x4(T) IN left, \
		Vec4(T) IN right\
	) { \
		Vec4(T) ret; \
		\
		T v_x = right.v[VEC4_IND_X]; \
		T v_y = right.v[VEC4_IND_Y]; \
		T v_z = right.v[VEC4_IND_Z]; \
		T v_w = right.v[VEC4_IND_W]; \
		\
		T a = ( \
			v_x * left.m[0][0] \
			+ v_y * left.m[0][1] \
			+ v_z * left.m[0][2] \
			+ left.m[0][3] \
		); \
		T b = ( \
			v_x * left.m[1][0] \
			+ v_y * left.m[1][1] \
			+ v_z * left.m[1][2] \
			+ left.m[1][3] \
		); \
		T c = ( \
			v_x * left.m[2][0] \
			+ v_y * left.m[2][1] \
			+ v_z * left.m[2][2] \
			+ left.m[2][3] \
		); \
		T w = ( \
			v_x * left.m[3][0] \
			+ v_y * left.m[3][1] \
			+ v_z * left.m[3][2] \
			+ left.m[3][3] \
		); \
		ret.v[VEC4_IND_X] = a; \
		ret.v[VEC4_IND_Y] = b; \
		ret.v[VEC4_IND_Z] = c; \
		ret.v[VEC4_IND_W] = w; \
		\
		return ret; \
	} \
	Mat4x4(T) BINOP_INFERRED_MULT_MAT4X4_T(T)( \
		Mat4x4(T) IN left, \
		T IN scale \
	) { \
		Mat4x4(T) ret; \
		uint32_t j; \
		uint32_t i; \
		for (j=0; j<MAT4X4_SIZE_2D_Y; j+=1) { \
			for (i=0; i<MAT4X4_SIZE_2D_X; i+=1) { \
				ret.m[j][i] = left.m[j][i] * scale; \
			} \
		} \
		return ret; \
	} \
	Vec4(T) MAT4X4_MULT_HOMOGENEOUS(T)( \
		Mat4x4(T) IN left, \
		Vec4(T) IN right \
	) { \
		Vec4(T) ret; \
		\
		T v_x = right.v[VEC4_IND_X]; \
		T v_y = right.v[VEC4_IND_Y]; \
		T v_z = right.v[VEC4_IND_Z]; \
		T v_w = right.v[VEC4_IND_W]; \
		T a = ( \
			v_x * left.m[0][0] \
			+ v_y * left.m[0][1] \
			+ v_z * left.m[0][2] \
			+ left.m[0][3] \
		); \
		T b = ( \
			v_x * left.m[1][0] \
			+ v_y * left.m[1][1] \
			+ v_z * left.m[1][2] \
			+ left.m[1][3] \
		); \
		T c = ( \
			v_x * left.m[2][0] \
			+ v_y * left.m[2][1] \
			+ v_z * left.m[2][2] \
			+ left.m[2][3] \
		); \
		T w = ( \
			v_x * left.m[3][0] \
			+ v_y * left.m[3][1] \
			+ v_z * left.m[3][2] \
			+ left.m[3][3] \
		); \
		ret.v[VEC4_IND_X] = a / w; \
		ret.v[VEC4_IND_Y] = b / w; \
		ret.v[VEC4_IND_Z] = c / w; \
		ret.v[VEC4_IND_W] = w; \
		\
		return ret; \
	} \
	Mat4x4(T) MAT4X4_TRANSPOSE(T)( \
		Mat4x4(T) IN self \
	) { \
		Mat4x4(T) ret; \
		uint32_t j; \
		uint32_t i; \
		for (j=0; j<MAT4X4_SIZE_2D_Y; j+=1) { \
			for (i=0; i<MAT4X4_SIZE_2D_X; i+=1) { \
				ret.m[j][i] = self.m[i][j]; \
			} \
		} \
		return ret; \
	} \
	Mat4x4(T) mat4x4_ ## T ## _identity( \
		void \
	) { \
		return (Mat4x4(T)){ \
			.m={ \
				{(T){.data=1}, (T){.data=0}, (T){.data=0}, (T){.data=0}}, \
				{(T){.data=0}, (T){.data=1}, (T){.data=0}, (T){.data=0}}, \
				{(T){.data=0}, (T){.data=0}, (T){.data=1}, (T){.data=0}}, \
				{(T){.data=0}, (T){.data=0}, (T){.data=0}, (T){.data=1}}, \
			} \
		}; \
	} \

#endif		// src_pipelinec_mat4x4_hpp
