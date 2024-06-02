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
	const MyCxFixedPt
		near(0.1),
		far(100.0);
	Transform perspective(
		near, // near
		far // far
	);
	const Vec2<MyCxFixedPt>
		tri_base_height{
			.x=MyCxFixedPt(50.0),
			.y=MyCxFixedPt(50.0),
		},
		tri_half_base_height{
			.x=tri_base_height.x / MyCxFixedPt(2),
			.y=tri_base_height.y / MyCxFixedPt(2),
		};
	Mat4x4<MyCxFixedPt> view_mat(MAT4X4_IDENTITY<MyCxFixedPt>);
	view_mat.m.at(0).at(3) = (
		//HALF_SCREEN_SIZE_2D.x - tri_half_base_height.x
		0.0
	);
	view_mat.m.at(1).at(3) = (
		//HALF_SCREEN_SIZE_2D.y - tri_half_base_height.x
		0.0
	);
	view_mat.m.at(2).at(3) = (
		//MyCxFixedPt(near) + MyCxFixedPt(0.1)
		//MyCxFixedPt(1.00)
		MyCxFixedPt(0.100)
	);
	Transform view(
		view_mat
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
	Vec3<MyCxFixedPt> tri_pos{
		//.x=HALF_SCREEN_SIZE_2D.x,
		//.y=HALF_SCREEN_SIZE_2D.y,
		.x=MyCxFixedPt(0),
		.y=MyCxFixedPt(0),
		.z=MyCxFixedPt(-0.50),
	};
	Transform my_tri_model;
	my_tri_model.mat.set_translate(tri_pos);
	my_tri_model.set_rot_scale(
		//Vec3<MyCxFixedPt>{ // rotate
		//	.x=MyCxFixedPt(MATH_PI * 0.5/*0*//*MATH_PI * 1.3*/),
		//	.y=MyCxFixedPt(0/*MATH_PI * 1.3*/),
		//	.z=MyCxFixedPt(0),
		//}
		//Vec3<MyCxFixedPt>{ // scale
		//	.x=MyCxFixedPt(4.00),
		//	.y=MyCxFixedPt(4.00),
		//	.z=MyCxFixedPt(1.0),
		//}
		MAT3X3_IDENTITY<MyCxFixedPt>
		//* MyCxFixedPt(0.10)
		//* MyCxFixedPt(1 / 3.0)
	);
	//my_tri_model.set_rot_scale(
	//	MAT3X3_IDENTITY<MyCxFixedPt>
	//);
	my_tri_model.set_to_affine_finish();
	const MyCxFixedPt
		my_z = MyCxFixedPt(0.0);
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
					.x=-tri_half_base_height.x,
					.y=-tri_half_base_height.y,
					.z=MyCxFixedPt(0.0),
				},
				.uv={
					.x=MyCxFixedPt(0.1 / 16.0),
					.y=MyCxFixedPt(0.1 / 16.0),
				},
			},
			Vert{
				.v={
					.x=-tri_half_base_height.x,
					.y=+tri_half_base_height.y,
					.z=MyCxFixedPt(0.0),
				},
				.uv={
					.x=MyCxFixedPt(15.0 / 16.0),
					.y=MyCxFixedPt(0.1 / 16.0),
				},
			},
			Vert{
				.v={
					.x=tri_half_base_height.x,
					.y=tri_half_base_height.y,
					.z=MyCxFixedPt(0.0),
				},
				.uv={
					.x=MyCxFixedPt(15.0 / 16.0),
					.y=MyCxFixedPt(15.0 / 16.0),
				},
			},
		},
		.proj_v={
			Vert(),
			Vert(),
			Vert(),
		},
		.screen_v{
			Vert(),
			Vert(),
			Vert(),
		},
	};
	for (;;) {
		if (disp.do_exit()) {
			break;
		}
		disp.handle_sdl_events();
		my_tri_model.set_translate(tri_pos);
		const auto n_view = view.look_at(
			my_tri_model
		);
		tri.do_project_etc(
			n_view,
			perspective
		);
		//tri.do_clip();
		std::vector<VertTextureCoords> visib;
		rast.calc_visib(
			tri,
			visib,
			near
		);
		std::array<
			std::pair<u8, Vec2<MyCxFixedPt>>,
			SCREEN_SIZE_2D.y * SCREEN_SIZE_2D.x
		> visib_buf;
		//visib_buf.fill(false);
		visib_buf.fill(
			std::make_pair<u8, Vec2<MyCxFixedPt>>(
				false,
				{
					.x=MyCxFixedPt(0),
					.y=MyCxFixedPt(0),
				}
			)
		);
		//int last_y = 0;
		for (const auto& item: visib) {
			//printout(item, " ");
			//if (last_y != item.y) {
			//	printout("\n");
			//}
			//last_y = item.y;
			const Vec2<int> temp{
				.x=int(item.v.x),
				.y=int(item.v.y),
			};
			if (
				temp.x >= /*MyCxFixedPt*/(0)
				&& temp.x <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.x - 1)
				&& temp.y >= /*MyCxFixedPt*/(0)
				&& temp.y <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.y - 1)
			) {
				//printout(temp);
				auto& my_visib = visib_buf.at(
					int(temp.y) * SCREEN_SIZE_2D.x + int(temp.x)
				);
				my_visib.first = true;
				my_visib.second = item.uv;
				//printout(
				//	temp, ": ",
				//	Vec2<double>{
				//		.x=item.uv.x,
				//		.y=item.uv.y,
				//	},
				//	"\n"
				//);
			}
		}
		for (size_t j=0; j<SCREEN_SIZE_2D.y; ++j) {
			for (size_t i=0; i<SCREEN_SIZE_2D.x; ++i) {
				const auto& my_visib = (
					visib_buf.at(j * SCREEN_SIZE_2D.x + i)
				);
				if (my_visib.first) {
					//printout(
					//	"my_visib.first: ",
					//	Vec2<size_t>(i, j), " ",
					//	double(my_visib.second.x), " ",
					//	double(my_visib.second.y),
					//	"\n"
					//);
					disp.set(
						Vec2<size_t>{
							.x=i,
							.y=j,
						},
						//0xfffffff
						//my_visib.second,
						tri.img->at_u32(
							Vec2<size_t>{
								.x=size_t(
									my_visib.second.x * MyCxFixedPt(16)
								),
								.y=size_t(
									my_visib.second.y * MyCxFixedPt(16)
								),
							}
						)
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
