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
	//	Vec3<MyCxFixedPt>{ // rotate
	//		.x=MyCxFixedPt(0),
	//		.y=MyCxFixedPt(0),
	//		.z=MyCxFixedPt(0),
	//	},
	//	Vec3<MyCxFixedPt>{ // translate
	//		.x=MyCxFixedPt(30),
	//		.y=MyCxFixedPt(30),
	//		.z=MyCxFixedPt(30),
	//	}
	//);
	Transform view(
		// affine
		//Vec3<MyCxFixedPt>{ // rotate
		//	.x=MyCxFixedPt(0),
		//	.y=MyCxFixedPt(0),
		//	.z=MyCxFixedPt(0),
		//},
		////Vec3<MyCxFixedPt>{ // translate
		////	.x=MyCxFixedPt(0),
		////	.y=MyCxFixedPt(0),
		////	.z=MyCxFixedPt(0),
		////}
		////Mat3x3<MyCxFixedPt>{
		////	.m={
		////		{
		////			{1.0, 0.0, 0.0},
		////			{0.0, 1.0, 0.0},
		////			{0.0, 0.0, 1.0},
		////		},
		////	}
		////},
		////MAT3X3_IDENTITY<MyCxFixedPt>,
		//Vec3<MyCxFixedPt>{ // translate
		//	.x=MyCxFixedPt(15.0),
		//	.y=MyCxFixedPt(15.0),
		//	.z=MyCxFixedPt(-100.0),
		//}
		MAT4X4_IDENTITY<MyCxFixedPt>
		//Mat4x4<MyCxFixedPt>{
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
	const MyCxFixedPt
		near(0.1),
		far(100.0);
	Transform perspective(
		near, // near
		far // far
	);
	//Transform perspective(
	//	MAT4X4_IDENTITY<MyCxFixedPt>
	//);
	//TransformMvp mvp{
	//	.model=&model,
	//	.view=&view,
	//	.perspective=&perspective,
	//};
	//Mat4x4<MyCxFixedPt> my_tri_model = MAT4X4_IDENTITY<MyCxFixedPt>;
	Transform my_tri_model;
	my_tri_model.mat.m.at(0).at(3) = MyCxFixedPt(-20.0);
	my_tri_model.mat.m.at(1).at(3) = MyCxFixedPt(-30.0);
	my_tri_model.mat.m.at(2).at(3) = MyCxFixedPt(30.0);
	//my_tri_model.mat.m.at(3).at(3) = MyCxFixedPt(1.0);
	my_tri_model.set_rot_scale(
		Vec3<MyCxFixedPt>{ // rotate
			.x=MyCxFixedPt(0/*MATH_PI * 1.3*/),
			.y=MyCxFixedPt(0/*MATH_PI * 1.3*/),
			.z=MyCxFixedPt(0),
		}
	);
	//my_tri_model.set_rot_scale(
	//	MAT3X3_IDENTITY<MyCxFixedPt>
	//);
	my_tri_model.set_to_affine_finish();
	Texture texture("gfx/obj/wood_block.bmp");
	Tri tri{
		.img=&texture,
		.model=Transform(
			//// affine
			//Vec3<MyCxFixedPt>{ // rotate
			//	.x=MyCxFixedPt(0),
			//	.y=MyCxFixedPt(0),
			//	.z=MyCxFixedPt(0),
			//},
			////Mat3x3<MyCxFixedPt>{
			////	.m={
			////	}
			////},
			//Vec3<MyCxFixedPt>{ // translate
			//	.x=MyCxFixedPt(10.0),
			//	.y=MyCxFixedPt(10.0),
			//	.z=MyCxFixedPt(200.0),
			//},
			//Vec3<MyCxFixedPt>{ // scale
			//	.x=MyCxFixedPt(2.0),
			//	.y=MyCxFixedPt(2.0),
			//	.z=MyCxFixedPt(2.0),
			//}
			//MAT4X4_IDENTITY<MyCxFixedPt>
			my_tri_model
			//Mat4x4<MyCxFixedPt>{
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
					.x=MyCxFixedPt(1.1),
					.y=MyCxFixedPt(1.1),
					.z=MyCxFixedPt(1.1),
				},
				.uv={
					.x=MyCxFixedPt(0),
					.y=MyCxFixedPt(0),
				},
			},
			Vert{
				.v={
					.x=MyCxFixedPt(35/*15.1*/),
					.y=MyCxFixedPt(35/*15.1*/),
					.z=MyCxFixedPt(1.1),
				},
				.uv={
					.x=MyCxFixedPt(15),
					.y=MyCxFixedPt(0),
				},
			},
			Vert{
				.v={
					.x=MyCxFixedPt(15.1),
					.y=MyCxFixedPt(5.1),
					.z=MyCxFixedPt(1.1),
				},
				.uv={
					.x=MyCxFixedPt(15),
					.y=MyCxFixedPt(15),
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
	tri.do_clip();
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
			temp.x >= /*MyCxFixedPt*/(0)
			&& temp.x <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.x - 1)
			&& temp.y >= /*MyCxFixedPt*/(0)
			&& temp.y <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.y - 1)
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
