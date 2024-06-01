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
			.z=double(20.0),
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
		double(-100), // near
		double(100) // far
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
				.x=double(10.0),
				.y=double(10.0),
				.z=double(3.0),
			},
			Vec3<double>{ // scale
				.x=2.0,
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
					.x=double(-1.1),
					.y=double(-1.1),
					.z=double(-1.1)
				},
				.uv={
					.x=double(0),
					.y=double(0),
				},
			},
			Vert{
				.v={
					.x=double(-15.1),
					.y=double(-15.1),
					.z=double(-1.1)
				},
				.uv={
					.x=double(15),
					.y=double(0),
				},
			},
			Vert{
				.v={
					.x=double(-15.1),
					.y=double(-5.1),
					.z=double(-1.1)
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
	std::vector<Vec2<int>> visib;
	rast.calc_visib(
		tri,
		visib
	);
	//calc_line_coords(
	//	Vec2<int>{
	//		.x=int(tri.project_v.at(0).v.x),
	//		.y=int(tri.project_v.at(0).v.y),
	//	},
	//	Vec2<int>{
	//		.x=int(tri.project_v.at(1).v.x),
	//		.y=int(tri.project_v.at(1).v.y),
	//	},
	//	SIZE_2D,
	//	visib
	//);
	std::array<u8, SCREEN_SIZE_2D.y * SCREEN_SIZE_2D.x> visib_buf;
	visib_buf.fill(false);
	//int last_y = 0;
	for (const auto& item: visib) {
		//printout(item, " ");
		//if (last_y != item.y) {
		//	printout("\n");
		//}
		//last_y = item.y;
		if (
			item.x >= 0 && item.x <= int(SCREEN_SIZE_2D.x) - 1
			&& item.y >= 0 && item.y <= int(SCREEN_SIZE_2D.y) - 1
		) {
			visib_buf.at(int(item.y) * SCREEN_SIZE_2D.x + int(item.x)) = 1;
		}
	}
	//for (size_t j=0; j<SCREEN_SIZE_2D.y; ++j) {
	//	for (size_t i=0; i<SCREEN_SIZE_2D.x; ++i) {
	//		if (visib_buf.at(j * SCREEN_SIZE_2D.x + i)) {
	//			//disp.set(
	//			//	Vec2<size_t>{
	//			//		.x=i,
	//			//		.y=j,
	//			//	},
	//			//	0xfffffff
	//			//);
	//			printout(
	//				//uint32_t(visib.at(j * SIZE_2D.x + i)),
	//				//"visib: ",
	//				//Vec2<size_t>{.x=i, .y=j},
	//				//"\n"
	//				1
	//			);
	//		} else {
	//			printout(" ");
	//		}
	//	}
	//	printout("\n");
	//}
	//printout("\n");
	for (;;) {
		if (disp.do_exit()) {
			break;
		}
		disp.handle_sdl_events();
		for (size_t j=0; j<SCREEN_SIZE_2D.y; ++j) {
			for (size_t i=0; i<SCREEN_SIZE_2D.x; ++i) {
				if (visib_buf.at(j * SCREEN_SIZE_2D.x + i)) {
					disp.set(
						Vec2<size_t>{
							.x=i,
							.y=j,
						},
						0xfffffff
					);
					//printout(
					//	//uint32_t(visib.at(j * SIZE_2D.x + i)),
					//	//"visib: ",
					//	//Vec2<size_t>{.x=i, .y=j},
					//	//"\n"
					//	1
					//);
				} else {
					//printout(" ");
				}
			}
			//printout("\n");
		}
		disp.refresh();
	}
	
	return 0;
}
