#include "my_display_class.hpp"
#include "vec4_class.hpp"
#include "rast_class.hpp"
#include "mat4x4_class.hpp"

int main(int argc, char** argv) {
	//liborangepower::time::Prng a;
	//pcg_random
	//pcg64 a;
	//pcg_extras::seed_seq_from<std::random_device> seed_source;
	//pcg64 rng(seed_source);
	MyDisplay disp;
	Rast rast;
	//Transform model(
	//	// affine
	//	Vec3<double>{ // rotate
	//		.x=double(0),
	//		.y=double(0),
	//		.z=double(0),
	//	},
	//	Vec3<double>{ // translate
	//		.x=double(30),
	//		.y=double(30),
	//		.z=double(30),
	//	}
	//);
	Transform view(
		// affine
		Vec3<double>{ // rotate
			.x=double(0),
			.y=double(0),
			.z=double(0),
		},
		//Vec3<double>{ // translate
		//	.x=double(0),
		//	.y=double(0),
		//	.z=double(0),
		//}
		//Mat3x3<double>{
		//	.m={
		//		{
		//			{1.0, 0.0, 0.0},
		//			{0.0, 1.0, 0.0},
		//			{0.0, 0.0, 1.0},
		//		},
		//	}
		//},
		//MAT3X3_IDENTITY<double>,
		Vec3<double>{ // translate
			.x=double(15.0),
			.y=double(15.0),
			.z=double(0.0),
		}
		//MAT4X4_IDENTITY<double>
		//Mat4x4<double>{
		//	.m={
		//		{
		//			{1.0, 0.0, 0.0, 0.0},
		//			{0.0, 1.0, 0.0, 0.0},
		//			{0.0, 0.0, 1.0, 0.0},
		//			{0.0, 0.0, 0.0, 1.0},
		//		},
		//	}
		//}
	);
	Transform perspective(
		double(0),
		double(10)
	);
	//TransformMvp mvp{
	//	.model=&model,
	//	.view=&view,
	//	.perspective=&perspective,
	//};
	Texture texture("gfx/obj/wood_block.bmp");
	Tri tri{
		.img=&texture,
		.model=Transform(
			// affine
			Vec3<double>{ // rotate
				.x=double(0),
				.y=double(0),
				.z=double(0),
			},
			//Mat3x3<double>{
			//	.m={
			//	}
			//},
			Vec3<double>{ // translate
				.x=double(1.0),
				.y=double(1.0),
				.z=double(-1.0),
			},
			Vec3<double>{
				.x=1.0,
				.y=1.0,
				.z=1.0,
			}
			//MAT4X4_IDENTITY<double>
			//Mat4x4<double>{
			//	.m={
			//		{
			//			{1.0, 0.0, 0.0, 0.0},
			//			{0.0, 1.0, 0.0, 0.0},
			//			{0.0, 0.0, 1.0, 0.0},
			//			{0.0, 0.0, 0.0, 1.0},
			//		},
			//	}
			//}
		),
		.v={
			Vert{
				.v={
					.x=double(1.1),
					.y=double(1.1),
					.z=double(1.1)
				},
				.uv={
					.x=double(0),
					.y=double(0),
				},
			},
			Vert{
				.v={
					.x=double(15.1),
					.y=double(1.1),
					.z=double(1.1)
				},
				.uv={
					.x=double(15),
					.y=double(0),
				},
			},
			Vert{
				.v={
					.x=double(16.1),
					.y=double(16.1),
					.z=double(1.1)
				},
				.uv={
					.x=double(15),
					.y=double(15),
				},
			},
		},
		.project_v={
			Vert(),
			Vert(),
			Vert(),
		},
	};
	tri.do_project(
		view,
		perspective
	);
	const auto& visib = rast.calc_visib(tri);
	for (size_t j=0; j<SIZE_2D.y; ++j) {
		for (size_t i=0; i<SIZE_2D.x; ++i) {
			if (visib.at(j * SIZE_2D.x + i)) {
				printout(
					//uint32_t(visib.at(j * SIZE_2D.x + i)),
					Vec2<size_t>{.x=i, .y=j},
					"\n"
				);
			}
		}
		//printout("\n");
	}
	printout("\n");
	for (;;) {
		if (disp.do_exit()) {
			break;
		}
		disp.handle_sdl_events();
		disp.refresh();
	}
	
	return 0;
}
