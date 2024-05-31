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
				for (size_t k=0; k<SIZE_2D.x; ++k) {
					const T temp_sum = m.at(j).at(k) * other.m.at(k).at(i);
					sum += temp_sum;
					//printout(
					//	"inner loop: ", k, ": ", temp_sum, " ", sum, "\n"
					//);
				}
				//printout(i, " ", j, ": ", sum, "\n");
				ret.m.at(j).at(i) = sum;
			}
		}
		//printout("\n");
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
template<typename T>
static constexpr Mat3x3<T> MAT3X3_IDENTITY{
	.m={
		{
			{T(1), T(0), T(0)},
			{T(0), T(1), T(0)},
			{T(0), T(0), T(1)},
		}
	}
};

template<typename T>
std::ostream& operator << (std::ostream& os, const Mat3x3<T>& mat) {
	for (size_t j=0; j<mat.m.size(); ++j) {
		for (size_t i=0; i<mat.m.at(j).size(); ++i) {
			osprintout(os, mat.m.at(j).at(i), " ");
		}
		osprintout(os, "\n");
	}
	return os;
}
//template<typename T>
//constexpr inline Mat3x3<T> operator * (
//	const Mat3x3<T> self, const Mat3x3<T>& other
//) {
//	Mat3x3<T> ret;
//	printout("Mat3x3 multiply: \n");
//	printout(self);
//	printout("\n");
//	printout(other);
//	printout("\n");
//	for (size_t j=0; j<ret.SIZE_2D.y; ++j) {
//		for (size_t i=0; i<ret.SIZE_2D.x; ++i) {
//			T sum = T();
//			for (size_t k=0; k<ret.SIZE_2D.x; ++k) {
//				const T temp_sum = self.m.at(j).at(k) * other.m.at(k).at(i);
//				sum += temp_sum;
//				printout(
//					"inner loop: ", k, ": ",
//					"{", j, " ", i, "}: ",
//					"{",
//						self.m.at(j).at(k), " ",
//						other.m.at(k).at(i),
//					"} ",
//					temp_sum, " ",
//					sum, "\n"
//				);
//			}
//			//printout(i, " ", j, ": ", sum, "\n");
//			ret.m.at(j).at(i) = sum;
//		}
//	}
//	printout("\n");
//	return ret;
//}

#endif		// src_mat3x3_class_hpp
