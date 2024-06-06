#ifndef src_versor_class_hpp
#define src_versor_class_hpp

#include "MiscIncludes.hpp"
#include "Vec4.hpp"
#include "Mat3x3.hpp"
#include <cmath>

// https://www.anyleaf.org/blog/quaternions:-a-practical-guide

// quaternion
template<typename T>
class Versor {
public:		// functions
	static constexpr Versor identity () {
		return Versor{.v{
			.x=T(0),
			.y=T(0),
			.z=T(0),
			.w=T(1),
		}};
	}
public:		// variables
	Vec4<T> v=identity().v;
public:		// functions
	constexpr Versor operator + (const Versor& other) const {
		return Versor(v + other.v).norm();
	}
	constexpr Versor operator - (const Versor& other) const {
		return Versor(v - other.v).norm();
	}
	constexpr Versor operator - () const {
		return Versor(-v);
	}
	constexpr Versor operator * (const T& scale) const {
		return Versor(v * scale);
	}
	constexpr Versor operator / (const T& scale) const {
		return Versor(v / scale);
	}
	//constexpr Versor operator - () const {
	//	return {
	//		.v{
	//			.x=-v.x,
	//			.y=-v.y,
	//			.z=-v.z,
	//			.w=-v.w
	//		}
	//	};
	//}

	constexpr Versor operator * (const Vec3<T>& other) const {
		return (
			*this
			* Versor{.v{
				.x=other.x,
				.y=other.y,
				.z=other.z,
				.w=T(0),
			}}
		).norm();
	}
	constexpr Versor operator * (const Versor& other) const {
		//return *this;
		const auto
			& L = v,
			& R = other.v;
		return Versor{.v{
			.x{L.w * R.x + L.x * R.w + L.y * R.z - L.z * R.y},
			.y{L.w * R.y - L.x * R.z + L.y * R.w + L.z * R.x},
			.z{L.w * R.z + L.x * R.y - L.y * R.x + L.z * R.w},
			.w{L.w * R.w - L.x * R.x - L.y * R.y - L.z * R.z},
		}}.norm();
	}
	//constexpr Versor pow(const T& x) const {
	//	return (
	//		T(std::pow(double(mag()), double(x)))
	//	);
	//}
	//constexpr operator Vec3<T>() const {
	//	return {
	//		.x=v.x,
	//		.y=v.y,
	//		.z=v.z,
	//	};
	//}
	constexpr Vec3<T> rotate(const Vec3<T>& rot_v) {
		return (*this * rot_v) * inv();
	}

	constexpr Vec3<T> to_euler_angles() const {
		Vec3<T> ret;

		const Versor<double>
			q_versor(Versor<double>{.v{
				.x=double(v.x),
				.y=double(v.y),
				.z=double(v.z),
				.w=double(v.w),
			}}.norm());
		const Vec4<double>
			q{
				.x=q_versor.v.x,
				.y=q_versor.v.y,
				.z=q_versor.v.z,
				.w=q_versor.v.w,
			};

		// roll (x-axis rotation)
		const double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
		const double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
		ret.x = T(std::atan2(sinr_cosp, cosr_cosp));

		// pitch (y-axis rotation)
		const double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
		const double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
		ret.y = T(2 * std::atan2(sinp, cosp) - M_PI / 2);

		// yaw (z-axis rotation)
		const double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
		const double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
		ret.z = T(std::atan2(siny_cosp, cosy_cosp));

		return ret;
	}

	static constexpr Versor from_axis_angle(
		const Vec3<T>& unit_v1,
		const T& angle
	) {
		return Versor{.v{
			.x=T(std::sin(double(angle) / 2.0) * double(unit_v1.x)),
			.y=T(std::sin(double(angle) / 2.0) * double(unit_v1.y)),
			.z=T(std::sin(double(angle) / 2.0) * double(unit_v1.z)),
			.w=T(std::cos(double(angle) / 2.0)),
		}}.norm();
	}
	static constexpr Versor from_x_angle(
		const T& x_angle
	) {
		return from_axis_angle(
			Vec3<T>{T(1.0), T(0.0), T(0.0)},
			x_angle
		);
	}
	static constexpr Versor from_y_angle(
		const T& y_angle
	) {
		return from_axis_angle(
			Vec3<T>{T(0.0), T(1.0), T(0.0)},
			y_angle
		);
	}
	static constexpr Versor from_z_angle(
		const T& z_angle
	) {
		return from_axis_angle(
			Vec3<T>{T(0.0), T(0.0), T(1.0)},
			z_angle
		);
	}
	//static constexpr Versor from_y_angle(
	//	const T& y_angle
	//) {
	//	return from_axis_angle(
	//		Vec3<T>{T(0.0), T(1.0), T(0.0)},
	//		y_angle
	//	);
	//}
	static constexpr Versor from_angles(
		const Vec3<T>& angles
	) {
		return from_axes_angles(
			Vec3<Vec3<T>>{
				.x{T(1), T(0), T(0)},
				.y{T(0), T(1), T(0)},
				.z{T(0), T(0), T(1)},
			},
			angles
		);
	}
	static constexpr Versor from_axes_angles(
		const Vec3<Vec3<T>>& unit_axes,
		const Vec3<T>& angles
	) {
		const Vec3<Versor>
			O{
				.x=from_axis_angle(unit_axes.x, angles.x),
				.y=from_axis_angle(unit_axes.y, angles.y),
				.z=from_axis_angle(unit_axes.z, angles.z),
			};
		return ((O.x * O.y) * O.z).norm();
	}
	constexpr Mat3x3<T> to_rot_mat() const {
		class MyQ{
		public:		// variables
			T
				i=T(),
				j=T(),
				k=T(),
				r=T();
		};
		const Versor
			q_versor(norm()),
			qsq_versor(
				Versor{.v{
					.x=q_versor.v.x * q_versor.v.x,
					.y=q_versor.v.y * q_versor.v.y,
					.z=q_versor.v.z * q_versor.v.z,
					.w=q_versor.v.w * q_versor.v.w,
				}}//.norm()
			);
		const MyQ
			q{
				.i=q_versor.v.x,
				.j=q_versor.v.y,
				.k=q_versor.v.z,
				.r=q_versor.v.w,
			},
			qsq{
				.i=qsq_versor.v.x,
				.j=qsq_versor.v.y,
				.k=qsq_versor.v.z,
				.r=qsq_versor.v.w,
				//.i=q.i * q.i,
				//.j=q.j * q.j,
				//.k=q.k * q.k,
				//.r=q.r * q.r,
			};
		return Mat3x3<T>{
			.m{
				{
					{
						T(1) - T(2) * (qsq.j + qsq.k),
						T(2) * (q.i * q.j - q.k * q.r),
						T(2) * (q.i * q.k + q.j * q.r),
					},
					{
						T(2) * (q.i * q.j + q.k * q.r),
						T(1) - T(2) * (qsq.i + qsq.k),
						T(2) * (q.j * q.k - q.i * q.r),
					},
					{
						T(2) * (q.i * q.k - q.j * q.r),
						T(2) * (q.j * q.k + q.i * q.r),
						T(1) - T(2) * (qsq.i + qsq.j),
					},
				}
			},
		};
	}


	// rotate unit vectors
	static constexpr Versor from_rotate_unit(
		const Vec3<T>& unit_v1,
		const Vec3<T>& unit_v2
	) {
		Versor temp;
		const T my_dot(unit_v1.dot(unit_v2));
		if (my_dot == T(1)) {
			return identity();
		} else if (my_dot == T(-1)) {
			//return identity().rotate
			const Versor
				temp2(unit_v1);
		} else {
			temp.v.w = 1 + my_dot;
			const Vec3<T> my_cross(unit_v1.cross(unit_v2));
			temp.v.x = my_cross.x;
			temp.v.y = my_cross.y;
			temp.v.z = my_cross.z;
		}
		return temp.norm();
	}

	// inverse, or conjugate
	constexpr Versor inv() const {
		return Versor{
			.v{
				.x=-v.x,
				.y=-v.y,
				.z=-v.z,
				.w=v.w,
			}
		};
	}

	// normalized
	constexpr Versor norm() const {
		return Versor(v.norm());
	}

	// magnitude
	constexpr inline T mag() const {
		return v.mag();
	}

	constexpr T& at(size_t idx) {
		return v.at(idx);
	}
	constexpr const T& at(size_t idx) const {
		return v.at(idx);
	}
	constexpr size_t size() const {
		return v.size();
	}
};
template<typename T>
static constexpr Versor<T> VERSOR_IDENTITY(
	Versor<T>::identity()
);

#endif		// src_versor_class_hpp
