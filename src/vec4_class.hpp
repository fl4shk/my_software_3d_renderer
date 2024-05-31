#ifndef src_vec4_class_hpp
#define src_vec4_class_hpp

#include "misc_includes.hpp"

template<typename T>
class Vec4 {
public:		// constants
	static constexpr size_t SIZE = 4ul;
public:		// variables
	T
		x=T(),
		y=T(),
		z=T(),
		w=T();
public:		// functions
	static constexpr inline Vec4 build_homogeneous(const Vec3<T>& v) {
		return Vec4{
			.x=v.x,
			.y=v.y,
			.z=v.z,
			.w=T(1),
		};
	}
	constexpr inline Vec4 operator + (const Vec4& other) const {
		Vec4 ret;
		for (size_t i=0; i<SIZE; ++i) {
			ret.at(i) = at(i) + other.at(i);
		}
		return ret;
	}
	constexpr inline Vec4 operator - (const Vec4& other) const {
		Vec4 ret;
		for (size_t i=0; i<SIZE; ++i) {
			ret.at(i) = at(i) - other.at(i);
		}
		return ret;
	}
	constexpr inline Vec4 operator * (const T& scale) const {
		Vec4 ret;
		for (size_t i=0; i<SIZE; ++i) {
			ret.at(i) = at(i) * scale;
		}
		return ret;
	}
	constexpr inline T& at(size_t pos) {
		const std::array<T, SIZE> arr{x, y, z, w};
		return arr.at(pos);
	}
	constexpr inline const T& at(size_t pos) const {
		const std::array<T, SIZE> arr{x, y, z, w};
		return arr.at(pos);
	}
};

#endif		// src_vec4_class_hpp
