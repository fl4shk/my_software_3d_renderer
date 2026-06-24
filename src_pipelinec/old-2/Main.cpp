#include "MiscIncludes.hpp"
#pragma MAIN_MHZ my_main 200.0

int32_t my_main(
	int32_t left,
	int32_t right
) {
	int32_t ret;
	ret = left * right;
	if (ret < 3) {
		goto PLUS_1;
	}
	goto RETURN;

PLUS_1:
	ret += 1;

RETURN:
	return ret;
}
