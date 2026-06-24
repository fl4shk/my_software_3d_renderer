#ifndef src_pipelinec_cx_fixed_pt_hpp
#define src_pipelinec_cx_fixed_pt_hpp

#include "MiscIncludes.hpp"

#define FixedPt(IntT, FW) \
	CAT(CAT(FixedPt_, IntT), CAT(_, FW))
#define DO_TYPEDEF_FIXEDPT(IntT, FW) \
	typedef struct FixedPt(IntT, FW) { \
		IntT data; \
	} FixedPt(IntT, FW);

#define BINOP_PLUS_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_PLUS(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_MINUS_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_MINUS(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_INFERRED_MULT_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_INFERRED_MULT(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_DIV_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_DIV(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_EQ_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_EQ(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_NEQ_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_NEQ(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_GT_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_GT(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_GTE_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_GTE(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_LT_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_LT(FixedPt(IntT, FW), FixedPt(IntT, FW))
#define BINOP_LTE_FIXEDPT_FIXEDPT(IntT, FW) \
	BINOP_LTE(FixedPt(IntT, FW), FixedPt(IntT, FW))

#ifndef __PIPELINEC__
#define MK_FIXEDPT_PROTOS(IntT, FW) \
	FixedPt(IntT, FW) BINOP_PLUS_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	FixedPt(IntT, FW) BINOP_MINUS_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	FixedPt(IntT, FW) BINOP_INFERRED_MULT_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	FixedPt(IntT, FW) BINOP_DIV_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	/* FixedPt(IntT, FW) CAT(fixedpt_inv_sqrt_, CAT3(IntT, _, FW))( */ \
	/* 	FixedPt(IntT, FW) IN self */ \
	/* ); */ \
	bool BINOP_EQ_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	bool BINOP_NEQ_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	bool BINOP_GT_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	bool BINOP_GTE_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	bool BINOP_LT_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	); \
	bool BINOP_LTE_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	);
#else
#define MK_FIXEDPT_PROTOS(IntT, FW)
#endif		// __PIPELINEC__

#define MK_FIXEDPT_FUNCS(IntT, FW) \
	FixedPt(IntT, FW) BINOP_PLUS_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		FixedPt(IntT, FW) ret; \
		ret.data = left.data + right.data; \
		return ret; \
	} \
	FixedPt(IntT, FW) BINOP_MINUS_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		FixedPt(IntT, FW) ret; \
		ret.data = left.data - right.data; \
		return ret; \
	} \
	FixedPt(IntT, FW) BINOP_INFERRED_MULT_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		FixedPt(IntT, FW) ret; \
		ret.data = ( \
			(((int64_t)left.data) * ((int64_t)right.data)) >> FW \
		); \
		return ret; \
	} \
	FixedPt(IntT, FW) BINOP_DIV_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		FixedPt(IntT, FW) ret; \
		ret.data = (((int64_t)left.data) << FW) / ((int64_t)right.data); \
		return ret; \
	} \
	/* FixedPt(IntT, FW) CAT(fixedpt_inv_sqrt_, CAT3(IntT, _, FW))( */ \
	/*	FixedPt(IntT, FW) IN self */ \
	/* ) { */ \
	/*	const float self_flt = ( */ \
	/*		((float)self.data) */ \
	/*		/ ((float)(((int64_t)1) << ((int64_t)FW))) */ \
	/*	); */ \
	/* } */ \
	bool BINOP_EQ_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		return (left.data == right.data); \
	} \
	bool BINOP_NEQ_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		return (left.data != right.data); \
	} \
	bool BINOP_GT_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		return (left.data > right.data); \
	} \
	bool BINOP_GTE_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		return (left.data >= right.data); \
	} \
	bool BINOP_LT_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		return (left.data < right.data); \
	} \
	bool BINOP_LTE_FIXEDPT_FIXEDPT(IntT, FW)( \
		FixedPt(IntT, FW) IN left, \
		FixedPt(IntT, FW) IN right \
	) { \
		return (left.data <= right.data); \
	}

#endif		// src_pipelinec_cx_fixed_pt_hpp
