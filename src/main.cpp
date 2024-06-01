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
	//	Vec3<CxFixedI16p16>{ // rotate
	//		.x=CxFixedI16p16(0),
	//		.y=CxFixedI16p16(0),
	//		.z=CxFixedI16p16(0),
	//	},
	//	Vec3<CxFixedI16p16>{ // translate
	//		.x=CxFixedI16p16(30),
	//		.y=CxFixedI16p16(30),
	//		.z=CxFixedI16p16(30),
	//	}
	//);
	Transform view(
		// affine
		//Vec3<CxFixedI16p16>{ // rotate
		//	.x=CxFixedI16p16(0),
		//	.y=CxFixedI16p16(0),
		//	.z=CxFixedI16p16(0),
		//},
		////Vec3<CxFixedI16p16>{ // translate
		////	.x=CxFixedI16p16(0),
		////	.y=CxFixedI16p16(0),
		////	.z=CxFixedI16p16(0),
		////}
		////Mat3x3<CxFixedI16p16>{
		////	.m={
		////		{
		////			{1.0, 0.0, 0.0},
		////			{0.0, 1.0, 0.0},
		////			{0.0, 0.0, 1.0},
		////		},
		////	}
		////},
		////MAT3X3_IDENTITY<CxFixedI16p16>,
		//Vec3<CxFixedI16p16>{ // translate
		//	.x=CxFixedI16p16(15.0),
		//	.y=CxFixedI16p16(15.0),
		//	.z=CxFixedI16p16(-100.0),
		//}
		MAT4X4_IDENTITY<CxFixedI16p16>
		//Mat4x4<CxFixedI16p16>{
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
	const CxFixedI16p16
		near(0.1),
		far(100.0);
	Transform perspective(
		near, // near
		far // far
	);
	//Transform perspective(
	//	MAT4X4_IDENTITY<CxFixedI16p16>
	//);
	//TransformMvp mvp{
	//	.model=&model,
	//	.view=&view,
	//	.perspective=&perspective,
	//};
	//Mat4x4<CxFixedI16p16> my_tri_model = MAT4X4_IDENTITY<CxFixedI16p16>;
	Transform my_tri_model;
	my_tri_model.mat.m.at(0).at(3) = CxFixedI16p16(-20.0);
	my_tri_model.mat.m.at(1).at(3) = CxFixedI16p16(-30.0);
	my_tri_model.mat.m.at(2).at(3) = CxFixedI16p16(30.0);
	//my_tri_model.mat.m.at(3).at(3) = CxFixedI16p16(1.0);
	my_tri_model.set_rot_scale(
		Vec3<CxFixedI16p16>{ // rotate
			.x=CxFixedI16p16(0/*MATH_PI * 1.3*/),
			.y=CxFixedI16p16(0/*MATH_PI * 1.3*/),
			.z=CxFixedI16p16(0),
		}
	);
	//my_tri_model.set_rot_scale(
	//	MAT3X3_IDENTITY<CxFixedI16p16>
	//);
	my_tri_model.set_to_affine_finish();
	Texture texture("gfx/obj/wood_block.bmp");
	Tri tri{
		.img=&texture,
		.model=Transform(
			//// affine
			//Vec3<CxFixedI16p16>{ // rotate
			//	.x=CxFixedI16p16(0),
			//	.y=CxFixedI16p16(0),
			//	.z=CxFixedI16p16(0),
			//},
			////Mat3x3<CxFixedI16p16>{
			////	.m={
			////	}
			////},
			//Vec3<CxFixedI16p16>{ // translate
			//	.x=CxFixedI16p16(10.0),
			//	.y=CxFixedI16p16(10.0),
			//	.z=CxFixedI16p16(200.0),
			//},
			//Vec3<CxFixedI16p16>{ // scale
			//	.x=CxFixedI16p16(2.0),
			//	.y=CxFixedI16p16(2.0),
			//	.z=CxFixedI16p16(2.0),
			//}
			//MAT4X4_IDENTITY<CxFixedI16p16>
			my_tri_model
			//Mat4x4<CxFixedI16p16>{
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
					.x=CxFixedI16p16(1.1),
					.y=CxFixedI16p16(1.1),
					.z=CxFixedI16p16(1.1),
				},
				.uv={
					.x=CxFixedI16p16(0),
					.y=CxFixedI16p16(0),
				},
			},
			Vert{
				.v={
					.x=CxFixedI16p16(15.1),
					.y=CxFixedI16p16(15.1),
					.z=CxFixedI16p16(1.1),
				},
				.uv={
					.x=CxFixedI16p16(15),
					.y=CxFixedI16p16(0),
				},
			},
			Vert{
				.v={
					.x=CxFixedI16p16(15.1),
					.y=CxFixedI16p16(5.1),
					.z=CxFixedI16p16(1.1),
				},
				.uv={
					.x=CxFixedI16p16(15),
					.y=CxFixedI16p16(15),
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
	std::vector<Vec2<Rast::DrawT>> visib;
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
		const Vec2<int> temp{
			.x=int(item.x),
			.y=int(item.y),
		};
		if (
			temp.x >= /*CxFixedI16p16*/(0)
			&& temp.x <= /*CxFixedI16p16*/int(SCREEN_SIZE_2D.x - 1)
			&& temp.y >= /*CxFixedI16p16*/(0)
			&& temp.y <= /*CxFixedI16p16*/int(SCREEN_SIZE_2D.y - 1)
		) {
			//printout(temp);
			visib_buf.at(int(temp.y) * SCREEN_SIZE_2D.x + int(temp.x)) = 1;
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
