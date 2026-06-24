#ifndef src_pipelinec_misc_includes_h
#define src_pipelinec_misc_includes_h

#ifdef __PIPELINEC__
#include "uintN_t.h"
#include "intN_t.h"
#include "float_e_m_t.h"
#else
#include <stdint.h>
#endif // __PIPELINEC__

//#ifdef __PIPELINEC__
//#define MyFloat float_8_23_t
//#else
//typedef float MyFloat;
//#endif // __PIPELINEC__

#ifndef __PIPELINEC__
#endif

#ifndef __PIPELINEC__
//#define IN(x) const x
//#define __in(x) (x)
#define IN const &
#define __out(x) return (x)
#define pipeline1(x) x
#define pipeline2(x) x
#else // ifdef __PIPELINEC__
#define IN
#endif

#ifdef __PIPELINEC__
#include "bool.h"
#else
#include <stdbool.h>
#endif

//#include "OperatorCxx.hpp"
#pragma PART "xc7a100tcsg324-1" // The FPGA of the Arty A7 100T

#endif		// src_pipelinec_misc_includes_h
