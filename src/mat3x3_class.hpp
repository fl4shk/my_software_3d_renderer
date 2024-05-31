#ifndef src_mat3x3_class_hpp
#define src_mat3x3_class_hpp

#include <cmath>
#include "misc_includes.hpp"

template<typename T>
class Mat3x3 final {
public:		// constants
	static constexpr Vec2<size_t>
		SIZE_2D{
			.x=3u,
			.y=3u,
		};
public:		// variables
	std::array<
		std::array<T, SIZE_2D.x>,
		SIZE_2D.y
	> m;
public:		// functions
	constexpr inline Mat3x3 operator + (
		const Mat3x3& other
	) const {
		Mat3x3 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = (
					m.at(j).at(i) + other.m.at(j).at(i)
				);
			}
		}
		return ret;
	}
	constexpr inline Mat3x3 operator - (
		const Mat3x3& other
	) const {
		Mat3x3 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = (
					m.at(j).at(i) - other.m.at(j).at(i)
				);
			}
		}
		return ret;
	}
	constexpr inline Mat3x3 operator * (
		const T& scale
	) const {
		Mat3x3 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = m.at(j).at(i) * scale;
			}
		}
		return ret;
	}
	constexpr inline Mat3x3 operator * (
		const Mat3x3& other
	) const {
		Mat3x3 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				T sum = T();
				for (size_t n=0; n<SIZE_2D.x; ++n) {
					sum += m.at(j).at(n) * other.m.at(n).at(i);
				}
				ret.m.at(j).at(i) = sum;
			}
		}
		return ret;
	}
	constexpr inline Vec3<T> operator * (
		const Vec3<T>& other
	) const {
		Vec3<T> ret{
			.x=T(),
			.y=T(),
			.z=T(),
		};
		for (size_t y=0; y<SIZE_2D.y; ++y) {
			T sum = T();
			for (size_t x=0; x<SIZE_2D.x; ++x) {
				sum += m.at(y).at(x) * other.at(x);
			}
			ret.at(y) = sum;
		}
		return ret;
	}
};

#endif		// src_mat3x3_class_hpp
