#ifndef src_mat4x4_cls_hpp
#define src_mat4x4_cls_hpp

#include <cmath>
#include "vec4_cls.hpp"
#include "misc_includes.hpp"

template<typename T>
class Mat4x4 final {
public:		// constants
	static constexpr Vec2<size_t>
		SIZE_2D{
			.x=4u,
			.y=4u,
		};
public:		// variables
	std::array<
		std::array<T, SIZE_2D.x>,
		SIZE_2D.y
	> m;
public:		// functions
	constexpr inline Mat4x4 operator + (
		const Mat4x4& other
	) const {
		Mat4x4 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = (
					m.at(j).at(i) + other.m.at(j).at(i)
				);
			}
		}
		return ret;
	}
	constexpr inline Mat4x4 operator - (
		const Mat4x4& other
	) const {
		Mat4x4 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = (
					m.at(j).at(i) - other.m.at(j).at(i)
				);
			}
		}
		return ret;
	}
	constexpr inline Mat4x4 operator * (
		const Mat4x4& other
	) const {
		Mat4x4 ret;
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
	constexpr inline Vec4<T> operator * (
		const Vec4<T>& other
	) const {
		Vec4<T> ret{
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

#endif		// src_mat4x4_cls_hpp
