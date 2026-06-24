#ifndef src_pipelinec_operator_cxx_hpp
#define src_pipelinec_operator_cxx_hpp

#define PPCAT(a, b) a ## b
#define CAT(a, b) PPCAT(a, b)
#define PPCAT3(a, b, c) a ## b ## c
#define CAT3(a, b, c) PPCAT3(a, b, c)
#define PPCAT4(a, b, c, d) a ## b ## c ## d
#define CAT4(a, b, c,d ) PPCAT4(a, b, c, d)

#ifndef __PIPELINEC__
#define BINOP_PLUS(LeftT, RightT) \
	operator +
#else
#define BINOP_PLUS(LeftT, RightT) \
	CAT(CAT(BIN_OP_PLUS_, LeftT), CAT(_, RightT))
#endif

#ifndef __PIPELINEC__
#define BINOP_MINUS(LeftT, RightT) \
	operator -
#else
#define BINOP_MINUS(LeftT, RightT) \
	CAT(CAT(BIN_OP_MINUS_, LeftT), CAT(_, RightT))
#endif

#ifndef __PIPELINEC__
#define BINOP_INFERRED_MULT(LeftT, RightT) \
	operator *
#else
#define BINOP_INFERRED_MULT(LeftT, RightT) \
	CAT(CAT(BIN_OP_INFERRED_MULT_, LeftT), CAT(_, RightT))
#endif

//#ifndef __PIPELINEC__
//#define BINOP_MULT_MAT3X3_MAT3X3(T)
//	operator *
//#else
//#define BINOP_MULT_MAT3X3_MAT3X3(T)
//	BIN_OP_MULT_ ## Mat3x3_ ## T ## _ ## T
//#endif

#ifndef __PIPELINEC__
#define BINOP_DIV(LeftT, RightT) \
	operator /
#else
#define BINOP_DIV(LeftT, RightT) \
	CAT(CAT(BIN_OP_DIV_, LeftT), CAT(_, RightT))
#endif

#ifndef __PIPELINEC__
#define BINOP_MOD(LeftT, RightT) \
	operator %
#else
#define BINOP_MOD(LeftT, RightT) \
	CAT(CAT(BIN_OP_MOD_, LeftT), CAT(_, RightT))
#endif

#ifndef __PIPELINEC__
#define BINOP_EQ(LeftT, RightT) \
	operator ==
#else
#define BINOP_EQ(LeftT, RightT) \
	CAT(CAT(BIN_OP_EQ_, LeftT), CAT(_, RightT))
#endif

#ifndef __PIPELINEC__
#define BINOP_NEQ(LeftT, RightT) \
	operator !=
#else
#define BINOP_NEQ(LeftT, RightT) \
	CAT(CAT(BIN_OP_NEQ_, LeftT), CAT(_, RightT))
#endif

#ifndef __PIPELINEC__
#define BINOP_GT(LeftT, RightT) \
	operator >
#else
#define BINOP_GT(LeftT, RightT) \
	CAT(CAT(BIN_OP_GT_, LeftT), CAT(_, RightT))
#endif
#ifndef __PIPELINEC__
#define BINOP_GTE(LeftT, RightT) \
	operator >=
#else
#define BINOP_GTE(LeftT, RightT) \
	CAT(CAT(BIN_OP_GTE_, LeftT), CAT(_, RightT))
#endif

#ifndef __PIPELINEC__
#define BINOP_LT(LeftT, RightT) \
	operator <
#else
#define BINOP_LT(LeftT, RightT) \
	CAT(CAT(BIN_OP_LT_, LeftT), CAT(_, RightT))
#endif
#ifndef __PIPELINEC__
#define BINOP_LTE(LeftT, RightT) \
	operator <=
#else
#define BINOP_LTE(LeftT, RightT) \
	CAT(CAT(BIN_OP_LTE_, LeftT), CAT(_, RightT))
#endif


#endif		// src_pipelinec_operator_cxx_hpp
