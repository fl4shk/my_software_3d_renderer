#ifndef src_pipelinec_mat3x3_hpp
#define src_pipelinec_mat3x3_hpp

#include "MiscIncludes.hpp"

#define MAT3X3_SIZE_2D_X 3
#define MAT3X3_SIZE_2D_Y 3

#define Mat3x3(T) Mat3x3_ ## T
#define DO_TYPEDEF_MAT3X3(T) \
	typedef struct Mat3x3(T) { \
		T m[MAT3X3_SIZE_2D_Y][MAT3X3_SIZE_2D_X]; \
	} Mat3x3(T); \

#define BINOP_PLUS_MAT3X3_MAT3X3(T) \
	BINOP_PLUS(Mat3x3_ ## T, Mat3x3_ ## T)
#define BINOP_MINUS_MAT3X3_MAT3X3(T) \
	BINOP_MINUS(Mat3x3(T), Mat3x3(T))
#define BINOP_INFERRED_MULT_MAT3X3_T(T) \
	BINOP_INFERRED_MULT(Mat3x3(T), T)
#define BINOP_INFERRED_MULT_MAT3X3_MAT3X3(T) \
	BINOP_INFERRED_MULT(Mat3x3(T), Mat3x3(T))
#define MAT3X3_TRANSPOSE(T) \
	CAT3(mat3x3_, T, _transpose)
#define MAT3X3_IDENTITY(T) \
	CAT3(mat3x3_, T, _identity)


//#ifndef __PIPELINEC__
//#define BINOP_MULT_MAT3X3_MAT3X3(T)
//	operator *
//#else
//#define BINOP_MULT_MAT3X3_MAT3X3(T)
//	BIN_OP_MULT_ ## Mat3x3_ ## T ## _ ## T
//#endif


#ifndef __PIPELINEC__
#define MK_MAT3X3_PROTOS(T) \
	Mat3x3(T) BINOP_PLUS_MAT3X3_MAT3X3(T)( \
		Mat3x3(T) IN left, \
		Mat3x3(T) IN right \
	); \
	Mat3x3(T) BINOP_MINUS_MAT3X3_MAT3X3(T)( \
		Mat3x3(T) IN left, \
		Mat3x3(T) IN right \
	); \
	Mat3x3(T) BINOP_INFERRED_MULT_MAT3X3_T(T)( \
		Mat3x3(T) IN left, \
		T IN right \
	); \
	Mat3x3(T) BINOP_INFERRED_MULT_MAT3X3_MAT3X3(T)( \
		Mat3x3(T) IN left, \
		Mat3x3(T) IN right \
	); \
	Mat3x3(T) MAT3X3_TRANSPOSE(T)( \
		Mat3x3(T) self \
	); \
	Mat3x3(T) MAT3X3_IDENTITY(T)( \
		void \
	);
#else
#define MK_MAT3X3_PROTOS(T)
#endif		// !__PIPELINEC__

#define MK_MAT3X3_FUNCS(T) \
Mat3x3(T) BINOP_PLUS_MAT3X3_MAT3X3(T)( \
	Mat3x3(T) IN left, \
	Mat3x3(T) IN right \
) { \
	Mat3x3(T) ret; \
	uint32_t j; \
	uint32_t i; \
	for (j=0; j<MAT3X3_SIZE_2D_Y; j+=1) { \
		for (i=0; i<MAT3X3_SIZE_2D_X; i+=1) { \
			ret.m[j][i] = ( \
				left.m[j][i] + right.m[j][i] \
			); \
		} \
	} \
	return ret; \
} \
Mat3x3(T) BINOP_MINUS_MAT3X3_MAT3X3(T)( \
	Mat3x3(T) IN left, \
	Mat3x3(T) IN right \
) { \
	Mat3x3_ ## T ret; \
	uint32_t j; \
	uint32_t i; \
	for (j=0; j<MAT3X3_SIZE_2D_Y; j+=1) { \
		for (i=0; i<MAT3X3_SIZE_2D_X; i+=1) { \
			ret.m[j][i] = ( \
				left.m[j][i] - right.m[j][i] \
			); \
		} \
	} \
	return ret; \
} \
Mat3x3(T) BINOP_INFERRED_MULT_MAT3X3_T(T)( \
	Mat3x3(T) IN left, \
	T IN scale \
) { \
	Mat3x3(T) ret; \
	uint32_t j; \
	uint32_t i; \
	for (j=0; j<MAT3X3_SIZE_2D_Y; j+=1) { \
		for (i=0; i<MAT3X3_SIZE_2D_X; i+=1) { \
			ret.m[j][i] = left.m[j][i] * scale; \
		} \
	} \
	return ret; \
} \
Mat3x3(T) BINOP_INFERRED_MULT_MAT3X3_MAT3X3(T)( \
	Mat3x3(T) IN left, \
	Mat3x3(T) IN right \
) { \
	Mat3x3(T) ret; \
	uint32_t j; \
	uint32_t i; \
	uint32_t k; \
	for (j=1; j<MAT3X3_SIZE_2D_Y; j+=1) { \
		for (i=0; i<MAT3X3_SIZE_2D_X; i+=1) { \
			T sum = {0}; \
			for (k=0; k<MAT3X3_SIZE_2D_X; k+=1) { \
				const T temp_sum = left.m[j][k] * right.m[k][i]; \
				sum = sum + temp_sum; \
			} \
			ret.m[j][i] = sum; \
		} \
	} \
	return ret; \
} \
Mat3x3(T) BIN_OP_MULT_ ## Mat3x3_ ## T ## _ ## T( \
	Mat3x3(T) IN left, \
	T IN scale \
) { \
	Mat3x3(T) ret; \
	uint32_t j; \
	uint32_t i; \
	for (j=0; j<MAT3X3_SIZE_2D_Y; j+=1) { \
		for (i=0; i<MAT3X3_SIZE_2D_X; i+=1) { \
			ret.m[j][i] = left.m[j][i] * scale; \
		} \
	} \
	return ret; \
} \
Mat3x3(T) BIN_OP_MULT_ ## Mat3x3_ ## T ## _ ## Mat3x3_ ## T( \
	Mat3x3(T) IN left, \
	Mat3x3(T) IN right \
) { \
	Mat3x3(T) ret; \
	uint32_t j; \
	uint32_t i; \
	uint32_t k; \
	for (j=0; j<MAT3X3_SIZE_2D_Y; j+=1) { \
		for (i=0; i<MAT3X3_SIZE_2D_X; i+=1) { \
			T sum = {0}; \
			for (k=0; k<MAT3X3_SIZE_2D_X; k+=1) { \
				const T temp_sum = left.m[j][k] * right.m[k][i]; \
				sum = sum + temp_sum; \
			} \
			ret.m[j][i] = sum; \
		} \
	} \
	return ret; \
} \
Mat3x3(T) MAT3X3_TRANSPOSE(T)( \
	Mat3x3(T) IN self \
) { \
	Mat3x3(T) ret; \
	uint32_t j; \
	uint32_t i; \
	for (j=0; j<MAT3X3_SIZE_2D_Y; j+=1) { \
		for (i=0; i<MAT3X3_SIZE_2D_X; i+=1) { \
			ret.m[j][i] = self.m[i][j]; \
		} \
	} \
	return ret; \
} \
Mat3x3(T) MAT3X3_IDENTITY(T)( \
	void \
) { \
	return (Mat3x3(T)){ \
		.m={ \
			{(T){.data=1}, (T){.data=0}, (T){.data=0}}, \
			{(T){.data=0}, (T){.data=1}, (T){.data=0}}, \
			{(T){.data=0}, (T){.data=0}, (T){.data=1}}, \
		} \
	}; \
}


#endif		// src_pipelinec_mat3x3_hpp
