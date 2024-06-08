#ifndef src_vec4_class_hpp
#define src_vec4_class_hpp

#include "MiscIncludes.hpp"

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
	constexpr inline Vec4 operator - () const {
		Vec4 ret;
		for (size_t i=0; i<SIZE; ++i) {
			ret.at(i) = -at(i);
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
	constexpr inline Vec4 operator / (const T& scale) const {
		Vec4 ret;
		for (size_t i=0; i<SIZE; ++i) {
			ret.at(i) = at(i) / scale;
		}
		return ret;
	}
	constexpr inline T dot(const Vec4& other) const {
		T ret = 0;
		for (size_t i=0; i<SIZE; ++i) {
			ret += at(i) * other.at(i);
		}
		return ret;
	}
	constexpr inline Vec4 norm() const {
		return *this / mag();
	}
	constexpr inline T mag() const {
		return liborangepower::math::cstm_sqrt(
			(x * x) + (y * y) + (z * z) + (w * w)
		);
	}
	constexpr inline T& at(size_t idx) {
		std::array<T*, SIZE> arr{&x, &y, &z, &w};
		return *arr.at(idx);
	}
	constexpr inline const T& at(size_t idx) const {
		std::array<const T*, SIZE> arr{&x, &y, &z, &w};
		return *arr.at(idx);
	}
};

template<typename T>
std::ostream& operator << (std::ostream& os, const Vec4<T>& v) {
	os << "{";
	for (size_t i=0; i<v.SIZE; ++i) {
		os << v.at(i);
		if (i + 1 < v.SIZE) {
			printout(" ");
		}
	}
	os << "}";
	return os;
}

#endif		// src_vec4_class_hpp
