#include "MathFuncs.hpp"

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

