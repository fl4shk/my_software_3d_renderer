#include "BoundingSphere.hpp"


BoundingSphere::BoundingSphere(
	const Vec3<MyFixedPt>& p1,
	const Vec3<MyFixedPt>& p2,
	const Vec3<MyFixedPt>& p3
) {
	// Calculate relative distances
	MyFixedPt A = (p1 - p2).magnitude();
	MyFixedPt B = (p2 - p3).magnitude();
	MyFixedPt C = (p3 - p1).magnitude();

	// Re-orient triangle (make A longest side)
	const Vec3<MyFixedPt>
		* a = &p3,
		* b = &p1,
		* c = &p2;
	if (B < C) {
		std::swap(B, C), std::swap(b, c);
	}
	if (A < B) {
		std::swap(A, B), std::swap(a, b); 
	}

	// If obtuse, just use longest diameter, otherwise circumscribe
	if ((B*B) + (C*C) <= (A*A)) {
		_r = A / 2.0;
		_pos = (*b + *c) / 2.f;
	 } else {
		// http://en.wikipedia.org/wiki/Circumscribed_circle
		MyFixedPt cos_a = (B*B + C*C - A*A) / (B*C*2);
		_r = MyFixedPt(A / (std::sqrt(1 - double(cos_a*cos_a))*2.0));
		Vec3<MyFixedPt> alpha = *a - *c, beta = *b - *c;
		_pos = (
			(
				(
					(beta * alpha.dot(alpha) - alpha * beta.dot(beta))
					.cross(alpha.cross(beta)) 
				) / (
					alpha.cross(beta).dot(alpha.cross(beta)) * 2.0
				)
			) + (
				*c
			)
		);
	 }
}
BoundingSphere::BoundingSphere(
	const Vec4<MyFixedPt>& p1,
	const Vec4<MyFixedPt>& p2,
	const Vec4<MyFixedPt>& p3
):
	BoundingSphere(
		Vec3<MyFixedPt>{p1.x, p1.y, p1.z},
		Vec3<MyFixedPt>{p2.x, p2.y, p2.z},
		Vec3<MyFixedPt>{p3.x, p3.y, p3.z}
	)
{
}
BoundingSphere bounding_sphere_of_tri_clip_v(
	const Tri& tri
) {
	return BoundingSphere(
		tri.proj_v.at(0).v,
		tri.proj_v.at(1).v,
		tri.proj_v.at(2).v
	);
}
