#ifndef src_math_funcs_hpp
#define src_math_funcs_hpp

#include "MiscIncludes.hpp"

MyFixedPt mult_cx_rw(
	MyFixedPt a, MyRwFixedPt rw
);
MyRwFixedPt my_recip(
	MyFixedPt a
);
MyFixedPt my_sin(
    MyFixedPt val
);
MyFixedPt my_cos(
    MyFixedPt val
);

MyFixedPt non_mbr_sqrt(
    MyFixedPt val
);

#endif      // src_math_funcs_hpp
