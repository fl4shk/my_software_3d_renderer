#include "../../src_pipelinec/FixedPt.hpp"
DO_TYPEDEF_FIXEDPT(int64_t, 32)
static FixedPt(int64_t, 32) inv_sqrt_lut[8] = {
	(FixedPt(int64_t, 32)){.data=0},
	(FixedPt(int64_t, 32)){.data=0x100000000},
	(FixedPt(int64_t, 32)){.data=0xb504f333},
	(FixedPt(int64_t, 32)){.data=0x93cd3a2c},
	(FixedPt(int64_t, 32)){.data=0x80000000},
	(FixedPt(int64_t, 32)){.data=0x727c9716},
	(FixedPt(int64_t, 32)){.data=0x6882f5c0},
	(FixedPt(int64_t, 32)){.data=0x60c2479a},
};