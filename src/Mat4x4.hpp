#ifndef src_mat4x4_class_hpp
#define src_mat4x4_class_hpp

#include <cmath>
#include "Mat3x3.hpp"
#include "Vec4.hpp"
#include "MiscIncludes.hpp"

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
	template<typename OtherT>
	static Mat4x4 cast_from(const Mat4x4<OtherT>& other) {
		Mat4x4 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = T(other.m.at(j).at(i));
			}
		}
		return ret;
	}
	Mat4x4 operator + (
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
	Mat4x4 operator - (
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
	Mat4x4 operator * (
		const T& scale
	) const {
		Mat4x4 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = m.at(j).at(i) * scale;
			}
		}
		return ret;
	}
	Mat4x4 operator * (
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
	
	Vec4<T> mult_homogeneous(
		const Vec4<T>& v
	) const {
		//const Vec4<T> temp = *this * Vec4<T>::build_homogeneous(other);
		Vec4<T> ret;

		T a = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
		T b = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
		T c = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
		T w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];
		ret.x = a / w;
		ret.y = b / w;
		ret.z = c / w;
		ret.w = w;
		//if (w != T(1)) {
		//	ret.x = a / w;
		//	ret.y = b / w;
		//	ret.z = c / w;
		//} else {
		//	ret.x = a;
		//	ret.y = b;
		//	ret.z = c;
		//}

		return ret;
	}
	Vec4<T> operator * (
		const Vec4<T>& v
	) const {
		Vec4<T> ret{
			.x=T(),
			.y=T(),
			.z=T(),
			.w=T(),
		};
		//for (size_t y=0; y<SIZE_2D.y; ++y) {
		//	T sum = T();
		//	for (size_t x=0; x<SIZE_2D.x; ++x) {
		//		sum = sum + m.at(y).at(x) * other.at(x);
		//	}
		//	ret.at(y) = sum;
		//}
		T a = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
		T b = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
		T c = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
		T w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];
		ret.x = a;
		ret.y = b;
		ret.z = c;
		ret.w = w;
		return ret;
	}
	Mat4x4 transpose() const {
		Mat4x4 ret;
		for (size_t j=0; j<SIZE_2D.y; ++j) {
			for (size_t i=0; i<SIZE_2D.x; ++i) {
				ret.m.at(j).at(i) = m.at(i).at(j);
			}
		}
		return ret;
	}
	Mat4x4 inverse() const {
		const T A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		const T A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
		const T A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
		const T A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
		const T A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
		const T A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
		const T A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		const T A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
		const T A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
		const T A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		const T A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
		const T A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		const T A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
		const T A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
		const T A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
		const T A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
		const T A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
		const T A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

		const auto inv_det = my_recip(
			(
				m[0][0]
				* (
					m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223 
				)
			) - (
				m[0][1]
				* (
					m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223 
				) 
			) + (
				m[0][2]
				* (
					m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123
				) 
			) - (
				m[0][3]
				* (
					m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123 
				)
			)
		);
		//det = my_recip(det);

		Mat4x4 ret;
		ret.m[0][0] = (
			inv_det
			* (
				m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223
			)
		);
		ret.m[0][1] = (
			inv_det
			* (
				-(m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223)
			)
		);
		ret.m[0][2] = (
			inv_det
			* (
				(m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213)
			)
		);
		ret.m[0][3] = (
			inv_det
			* (
				(m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212)
			)
		);
		ret.m[1][0] = (
			inv_det
			* (
				(m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223)
			)
		);
		ret.m[1][1] = (
			inv_det
			* (
				(m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223)
			)
		);
		ret.m[1][2] = (
			inv_det
			* (
				(m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213)
			)
		);
		ret.m[1][3] = (
			inv_det
			* (
				(m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212)
			)
		);
		ret.m[2][0] = (
			inv_det
			* (
				(m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123)
			)
		);
		ret.m[2][1] = (
			inv_det
			* (
				(m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123)
			)
		);
		ret.m[2][2] = (
			inv_det
			* (
				(m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113)
			)
		);
		ret.m[2][3] = (
			inv_det
			* (
				(m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112)
			)
		);
		ret.m[3][0] = (
			inv_det
			* (
				(m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123)
			)
		);
		ret.m[3][1] = (
			inv_det
			* (
				(m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123)
			)
		);
		ret.m[3][2] = (
			inv_det
			* (
				(m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113)
			)
		);
		ret.m[3][3] = (
			inv_det
			* (
				(m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112)
			)
		);
		return ret;
	}
	//explicit constexpr inline operator Vec3<T> () const {
	//	return Vec3
	//}
	void set_translate(
		const Vec3<T>& v,
		bool right_vec_mult=true
	) {
		for (size_t k=0; k<v.SIZE; ++k) {
			if (right_vec_mult) {
				m.at(k).at(3) = v.at(k);
			} else {
				m.at(3).at(k) = v.at(k);
			}
		}
	}
	void set_rot_scale(
		const Mat3x3<T>& m3x3,
		bool right_vec_mult=true
	) {
		for (size_t j=0; j<m3x3.SIZE_2D.y; ++j) {
			for (size_t i=0; i<m3x3.SIZE_2D.x; ++i) {
				if (right_vec_mult) {
					m.at(j).at(i) = m3x3.m.at(j).at(i);
				} else {
					// use the transpose
					m.at(j).at(i) = m3x3.m.at(i).at(j);
				}
			}
		}
	}
};
template<typename T>
static constexpr Mat4x4<T> MAT4X4_IDENTITY{
	.m={
		{
			{T(1), T(0), T(0), T(0)},
			{T(0), T(1), T(0), T(0)},
			{T(0), T(0), T(1), T(0)},
			{T(0), T(0), T(0), T(1)},
		}
	},
};
//template<typename T>
//inline Vec4<T> operator * (const Vec4<T>& v, const Mat4x4<T>& mat) {
//	Vec4<T> ret{
//		.x=T(),
//		.y=T(),
//		.z=T(),
//		.w=T(),
//	};
//	for (size_t x=0; x<mat.SIZE_2D.x; ++x) {
//		T sum = T();
//		for (size_t y=0; y<mat.SIZE_2D.y; ++y) {
//			sum += mat.m.at(y).at(x) * v.at(y);
//		}
//		ret.at(x) = sum;
//	}
//	return ret;
//}
//template<typename T>
//constexpr inline Vec4<T> project

template<typename T>
std::ostream& operator << (std::ostream& os, const Mat4x4<T>& mat) {
	for (size_t j=0; j<mat.m.size(); ++j) {
		for (size_t i=0; i<mat.m.at(j).size(); ++i) {
			osprintout(os, mat.m.at(j).at(i), " ");
		}
		osprintout(os, "\n");
	}
	return os;
}

#endif		// src_mat4x4_class_hpp
