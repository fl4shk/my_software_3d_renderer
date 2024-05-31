//#ifndef src_rgb444_class_hpp
//#define src_rgb444_class_hpp
//
//// src/rgb444_class.hpp
//
//#include "misc_includes.hpp"
//
//class Rgb444 final {
//public:		// variables
//	Uint8
//		r=0,
//		g=0,
//		b=0;
//public:		// functions
//	constexpr inline Uint32 to_u32() const {
//		return (
//			(
//				0xffu << 24u
//			) | (
//				(Uint32(b) & 0xfu) << 20u
//			) | (
//				(Uint32(g) & 0xfu) << 12u
//			) | (
//				(Uint32(r) & 0xfu) << 4u
//			)
//		);
//	}
//	static constexpr inline Rgb444 create(
//		Uint32 to_conv
//	) {
//		return Rgb444{
//			.r=Uint8((to_conv >> 4u) & 0xfu),
//			.g=Uint8((to_conv >> 12u) & 0xfu),
//			.b=Uint8((to_conv >> 20u) & 0xfu),
//		};
//	}
//};
//
//#endif		// src_rgb444_class_hpp
