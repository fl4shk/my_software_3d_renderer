#include "MathFuncs.hpp"
#include <cmath>

//MyFixedPt mult_cx_rw(
//    MyFixedPt a, MyRwFixedPt rw
//) {
//}
MyFixedPt mult_cx_rw(
	MyFixedPt a, MyRwFixedPt rw
) {
	MyFixedPt ret;
	//ret.data = (
	//	(i64(a.data) * i64(rw.data))
	//	>> MyRwFixedPt::FRAC_WIDTH
	//	// the two fractional widths are added to one another
	//);
	ret = a * rw;
	return ret;
}
MyRwFixedPt my_recip(
	MyFixedPt a
) {
	MyRwFixedPt ret;
	//ret.data = (
	//	i64(
	//		a.recip_ldbl()
	//		* (1 << MyRwFixedPt::FRAC_WIDTH)
	//	)
	//);
	//ret = MyRwFixedPt(1.0 / double(a));
	ret = MyRwFixedPt(1) / a;
	return ret;
}

MyFixedPt my_sqrt(
    MyFixedPt val
) {
}

static constexpr size_t TRIG_LUT_SIZE = 1024u;

using MyTrigLut = std::array<MyFixedPt, TRIG_LUT_SIZE>;
static constexpr MyTrigLut mk_trig_lut() {
    MyTrigLut ret;
    static constexpr u64 FRAC_SCALE = (
        u64(1ull) << u64(MyFixedPt::FRAC_WIDTH)
    );
    for (size_t i=0; i<TRIG_LUT_SIZE; ++i) {
        double temp = std::sin(
            MyFixedPt::FRAC_WIDTH * double(TRIG_LUT_SIZE)
        );
    }
    return ret;
}
static constexpr MyTrigLut MY_TRIG_LUT = mk_trig_lut();

MyFixedPt my_sin(
    MyFixedPt val
) {
}
MyFixedPt my_cos(
    MyFixedPt val
) {
}
MyFixedPt non_mbr_sqrt(
    MyFixedPt val
) {
    return MyFixedPt(0);
}
