#include "MyDisplay.hpp"
#include "Vec4.hpp"
#include "Rast.hpp"
#include "Mat4x4.hpp"
#include "Square.hpp"
#include <cmath>

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
		far(10.0);
	Transform perspective(
		near, // near
		far // far
	);
	//const Vec2<MyCxFixedPt>
	//	tri_base_height(
	//		50.0,
	//		50.0
	//	),
	//	tbh(
	//		tri_base_height.x / 2.0,
	//		tri_base_height.y / 2.0
	//	);
	Vec3<MyCxFixedPt> sq_pos{
		//.x=HALF_SCREEN_SIZE_2D.x ,
		//.y=HALF_SCREEN_SIZE_2D.y,
		////.x=MyCxFixedPt(60.1),
		////.y=MyCxFixedPt(60.1),
		//.z=0.510,
		//.x=1.0,
		//.y=1.0,
		//.z=0.510,
		.x=0.0,
		.y=0.0,
		.z=0.0,
	};
	//Mat4x4<MyCxFixedPt> view_mat(MAT4X4_IDENTITY<MyCxFixedPt>);
	Vec3<MyCxFixedPt> view_pos{0.00, 0.00, -5.000};
	//view_pos.x = /*MyCxFixedPt*/(
	//	//HALF_SCREEN_SIZE_2D.x - tri_half_base_height.x
	//	//2.0
	//	0.1
	//	//-HALF_SCREEN_SIZE_2D.x
	//);
	//view_pos.y = /*MyCxFixedPt*/(
	//	//HALF_SCREEN_SIZE_2D.y - tri_half_base_height.x
	//	//2.0
	//	0.1
	//	//-HALF_SCREEN_SIZE_2D.y
	//);
	//view_pos.z = /*MyCxFixedPt*/(
	//	//MyCxFixedPt(near) + MyCxFixedPt(0.1)
	//	//MyCxFixedPt(1.00)
	//	0.100
	//);
	//view_pos = view_pos.norm();
	Versor<MyCxFixedPt>
		view_rot;
	//Mat4x4<MyCxFixedPt>
	//	view_mat;
	Transform view(
		MAT4X4_IDENTITY<MyCxFixedPt>
		//Mat4x4<MyCxFixedPt>{.m{{
		//	{},
		//	{},
		//	{},
		//	{},
		//}}}
	);
		//view_mat
		//view_pos
	//view.mat = MAT4X4_IDENTITY<MyCxFixedPt>;
	view.set_translate(view_pos);
	view.set_rot_scale(
		//view_rot
		MAT3X3_IDENTITY<MyCxFixedPt>
	);
	view.set_to_affine_finish();
	
	//Transform perspective(
	//	MAT4X4_IDENTITY<MyCxFixedPt>
	//);
	//TransformMvp mvp{
	//	.model=&model,
	//	.view=&view,
	//	.perspective=&perspective,
	//};
	//Mat4x4<MyCxFixedPt> my_sq_model = MAT4X4_IDENTITY<MyCxFixedPt>;
	//Transform my_sq_model;
	//my_sq_model.mat.set_translate(sq_pos);
	//Vec3<MyCxFixedPt>
	//	sq_rotate{0.0, 0.0, 0.0};
	Versor<MyCxFixedPt>
		sq_rotate(VERSOR_IDENTITY<MyCxFixedPt>);
	//const Vec3<Vec3<MyCxFixedPt>>
	//	tri_rotate_angles(
	//		{0.0001, 0.0, 0.0},
	//		{0.0, 0.0001, 0.0},
	//		{0.0, 0.0, 0.0001}
	//	);
	const Vec3<MyCxFixedPt>
		sq_rotate_angles{0.0001, 0.0001, 0.0001};
		
	//my_sq_model.set_rot_scale(
	//	sq_rotate
	//	//Vec3<MyCxFixedPt>{ // rotate
	//	//	.x=(0.0/*0.1 * (2 * MATH_PI)*/ /** 1.3*/),
	//	//	.y=(0.0/*MATH_PI * 1.3*/),
	//	//	.z=(0.0),
	//	//}
	//	//Vec3<MyCxFixedPt>{ // scale
	//	//	.x=MyCxFixedPt(1.00),
	//	//	.y=MyCxFixedPt(1.00),
	//	//	.z=MyCxFixedPt(1.0),
	//	//}
	//	//MAT3X3_IDENTITY<MyCxFixedPt>
	//	//* MyCxFixedPt(0.10)
	//	//* MyCxFixedPt(1 / 3.0)
	//);
	//my_sq_model.set_rot_scale(
	//	MAT3X3_IDENTITY<MyCxFixedPt>
	//);
	//my_sq_model.set_to_affine_finish();
	//const MyCxFixedPt
	//	my_z = MyCxFixedPt(0.0);
	Texture texture(
		"gfx/obj/wood_block.bmp"
		//"gfx/obj/foreground_common_gfx.bmp"
	);
	Square sq{
		.size_2d{1.0, 1.0},
		.pos{sq_pos},
		//.rot{VERSOR_IDENTITY<MyCxFixedPt>},
		.img=&texture,
	};
	//Tri tri{
	//	.img=&texture,
	//	//.model=Transform(
	//	//	//// affine
	//	//	//Vec3<MyCxFixedPt>{ // rotate
	//	//	//	.x=MyCxFixedPt(0),
	//	//	//	.y=MyCxFixedPt(0),
	//	//	//	.z=MyCxFixedPt(0),
	//	//	//},
	//	//	////Mat3x3<MyCxFixedPt>{
	//	//	////	.m={
	//	//	////	}
	//	//	////},
	//	//	//Vec3<MyCxFixedPt>{ // translate
	//	//	//	.x=MyCxFixedPt(10.0),
	//	//	//	.y=MyCxFixedPt(10.0),
	//	//	//	.z=MyCxFixedPt(200.0),
	//	//	//},
	//	//	//Vec3<MyCxFixedPt>{ // scale
	//	//	//	.x=MyCxFixedPt(2.0),
	//	//	//	.y=MyCxFixedPt(2.0),
	//	//	//	.z=MyCxFixedPt(2.0),
	//	//	//}
	//	//	//MAT4X4_IDENTITY<MyCxFixedPt>
	//	//	my_sq_model
	//	//	//Mat4x4<MyCxFixedPt>{
	//	//	//	.m={
	//	//	//		{
	//	//	//			{1.0, 0.0, 0.0, 0.0},
	//	//	//			{0.0, 1.0, 0.0, 0.0},
	//	//	//			{0.0, 0.0, 1.0, 0.0},
	//	//	//			{0.0, 0.0, 0.0, 1.0},
	//	//	//		},
	//	//	//	}
	//	//	//}
	//	//),
	//	.model=&my_sq_model,
	//	.v={
	//		Vert{
	//			.v{
	//				.x=-tbh.x,
	//				.y=-tbh.y,
	//				.z=MyCxFixedPt(0.0),
	//			},
	//			.uv{
	//				.x=MyCxFixedPt(0.01),
	//				.y=MyCxFixedPt(0.01),
	//			},
	//		},
	//		Vert{
	//			.v{
	//				.x=-tbh.x,
	//				.y=tbh.y,
	//				.z=MyCxFixedPt(0.0),
	//			},
	//			.uv{
	//				.x=MyCxFixedPt(15.0 / 16.0),
	//				.y=MyCxFixedPt(0.01),
	//			},
	//		},
	//		Vert{
	//			.v{
	//				.x=tbh.x,
	//				.y=tbh.y,
	//				.z=MyCxFixedPt(0.0),
	//			},
	//			.uv{
	//				.x=MyCxFixedPt(15.0 / 16.0),
	//				.y=MyCxFixedPt(15.0 / 16.0),
	//			},
	//		},
	//	},
	//	//.proj_v={
	//	//	Vert(),
	//	//	Vert(),
	//	//	Vert(),
	//	//},
	//	//.screen_v{
	//	//	Vert(),
	//	//	Vert(),
	//	//	Vert(),
	//	//},
	//};
	for (;;) {
		disp.handle_sdl_events();
		if (disp.do_exit()) {
			break;
		}
		{
			printout("checking keys\n");
			const MyCxFixedPt
				amount_xy(0.10),
				amount_z(0.001),
				amount_angle(0.00005);
			if (
				disp.key_down_now(SnesKeyKind::DpadLeft)
				&& disp.key_up_now(SnesKeyKind::DpadRight)
			) {
				view_pos.x += amount_xy;
				printout(
					"moving left: ",
					double(view_pos.x),
					"\n"
				);
			} else if (
				disp.key_down_now(SnesKeyKind::DpadRight)
				&& disp.key_up_now(SnesKeyKind::DpadLeft)
			) {
				view_pos.x -= amount_xy;
				printout(
					"moving right: ",
					double(view_pos.x),
					"\n"
				);
			}

			if (
				disp.key_down_now(SnesKeyKind::DpadUp)
				&& disp.key_up_now(SnesKeyKind::DpadDown)
			) {
				view_pos.y += amount_xy;
				printout(
					"moving up: ",
					double(view_pos.y),
					"\n"
				);
			} else if (
				disp.key_down_now(SnesKeyKind::DpadDown)
				&& disp.key_up_now(SnesKeyKind::DpadUp)
			) {
				view_pos.y -= amount_xy;
				printout(
					"moving down: ",
					double(view_pos.y),
					"\n"
				);
			}

			if (
				disp.key_down_now(SnesKeyKind::Y)
				&& disp.key_up_now(SnesKeyKind::A)
			) {
				view_pos.z -= amount_z;
				printout(
					"moving backward: ",
					double(view_pos.z),
					"\n"
				);
			} else if (
				disp.key_down_now(SnesKeyKind::A)
				&& disp.key_up_now(SnesKeyKind::Y)
			) {
				view_pos.z += amount_z;
				printout(
					"moving forward: ",
					double(view_pos.z),
					"\n"
				);
			}

			//if (
			//	disp.key_down_now(SnesKeyKind::B)
			//	&& disp.key_up_now(SnesKeyKind::X)
			//) {
			//	//sq_rotate.v.x = (
			//	//	/*-std::fabs*/(std::fmod(
			//	//		double(sq_rotate.v.x - amount_angle),
			//	//		(2.0 * double(MATH_PI))
			//	//	))
			//	//);
			//	//sq_rotate.v.x -= amount_angle;
			//	sq_rotate = (
			//		sq_rotate
			//		* Versor<MyCxFixedPt>::from_x_angle(-sq_rotate_angles.x)
			//	);
			//	//sq_rotate = sq_rotate.norm();
			//	printout(
			//		"rotating x minus: ",
			//		double(sq_rotate.v.x),
			//		"\n"
			//	);
			//} else if (
			//	disp.key_down_now(SnesKeyKind::X)
			//	&& disp.key_up_now(SnesKeyKind::B)
			//) {
			//	//sq_rotate.x = (
			//	//	/*-std::fabs*/(std::fmod(
			//	//		double(sq_rotate.x + amount_angle),
			//	//		(2.0 * double(MATH_PI))
			//	//	))
			//	//);
			//	//sq_rotate.v.x += amount_angle;
			//	sq_rotate = (
			//		sq_rotate
			//		* Versor<MyCxFixedPt>::from_x_angle(sq_rotate_angles.x)
			//	);
			//	//sq_rotate = sq_rotate.norm();
			//	printout(
			//		"rotating x plus: ",
			//		double(sq_rotate.v.x),
			//		"\n"
			//	);
			//}

			if (
				disp.key_down_now(SnesKeyKind::L)
				&& disp.key_up_now(SnesKeyKind::R)
			) {
				//sq_rotate.y = (
				//	std::fabs(std::fmod(
				//		double(sq_rotate.y - amount_angle),
				//		(2.0 * double(MATH_PI))
				//	))
				//);
				//sq_rotate.v.y -= amount_angle;
				sq_rotate = (
					sq_rotate
					* Versor<MyCxFixedPt>::from_y_angle(-sq_rotate_angles.y)
				);
				//sq_rotate = sq_rotate.norm();
				printout(
					"rotating y minus: ",
					double(sq_rotate.v.y),
					//double(sq_rotate.y),
					"\n"
				);
			} else if (
				disp.key_down_now(SnesKeyKind::R)
				&& disp.key_up_now(SnesKeyKind::L)
			) {
				//sq_rotate.y = (
				//	std::fabs(std::fmod(
				//		double(sq_rotate.y + amount_angle),
				//		(2.0 * double(MATH_PI))
				//	))
				//);
				//sq_rotate.v.y += amount_angle;
				sq_rotate = (
					sq_rotate
					* Versor<MyCxFixedPt>::from_y_angle(sq_rotate_angles.y)
				);
				//sq_rotate = sq_rotate.norm();
				printout(
					"rotating y plus: ",
					double(sq_rotate.v.y),
					//double(sq_rotate.y),
					"\n"
				);
			}
		}
		//sq.model.set_rot_scale(
		//	sq_rotate
		//);
		sq.rot = sq_rotate;
		//my_sq_model.set_translate(sq_pos);
		auto& tri_arr = sq.update_tri_arr();

		view.set_translate(view_pos);
		//tri.model = &my_sq_model;
		const auto n_view = (
			//view.look_at(my_sq_model)
			//view.look_at(sq.model)
			view
		);
		std::vector<VertTextureCoords> visib;
		for (size_t i=0; i<tri_arr.size(); ++i)
		{
			//size_t i = 0;
			auto& tri = tri_arr.at(i);
			//printout(
			//	"tri_arr.at(", i, "):\n",
			//	"{",
			//		"{",
			//			tri_arr.at(i).v.at(0).v.x, " ",
			//			tri_arr.at(i).v.at(0).v.y, " ",
			//			tri_arr.at(i).v.at(0).v.z, " ",
			//			tri_arr.at(i).v.at(0).v.w,
			//		"} ",
			//		tri_arr.at(i).v.at(0).uv,
			//	"}\n",
			//	"{",
			//		"{",
			//			tri_arr.at(i).v.at(1).v.x, " ",
			//			tri_arr.at(i).v.at(1).v.y, " ",
			//			tri_arr.at(i).v.at(1).v.z, " ",
			//			tri_arr.at(i).v.at(1).v.w,
			//		"} ",
			//		tri_arr.at(i).v.at(1).uv,
			//	"}\n",
			//	"{",
			//		"{",
			//			tri_arr.at(i).v.at(2).v.x, " ",
			//			tri_arr.at(i).v.at(2).v.y, " ",
			//			tri_arr.at(i).v.at(2).v.z, " ",
			//			tri_arr.at(i).v.at(2).v.w,
			//		"} ",
			//		tri_arr.at(i).v.at(2).uv,
			//	"}",
			//	"\n"
			//);
			tri.do_project_etc(
				n_view,
				perspective
			);
			//tri.do_clip();
			rast.calc_visib(
				tri,
				visib,
				near
			);
			printout(
				"i=", i, " visib.size(): ", visib.size(), "\n"
			);
		}
		for (const auto& item: visib) {
			const Vec2<int> temp{
				.x=int(item.v.x),
				.y=int(item.v.y),
			};
			//printout("visib loop: i == ", i, "\n");
			//printout(
			//	"visib loop: ", temp, "\n"
			//);
			if (
				temp.x >= /*MyCxFixedPt*/(0)
				&& temp.x <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.x - 1)
				&& temp.y >= /*MyCxFixedPt*/(0)
				&& temp.y <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.y - 1)
				//true
			) {
				const Vec2<int>
					pos{
						.x=int(
							item.uv.x * MyCxFixedPt(16)
							//+ MyCxFixedPt(16)
						),
						.y=int(
							item.uv.y * MyCxFixedPt(16)
						),
					};
				//printout(
				//	"visib: ",
				//	//Vec2<size_t>(i, j), " ",
				//	temp, " ",
				//	double(item.uv.x), " ",
				//	double(item.uv.y), " ",
				//	pos,
				//	"\n"
				//);
				if (
					//pos.x >= 0 + 48 && pos.x < 16 + 48
					//&& pos.y >= 0 && pos.y < 16
					pos.x >= 0 && pos.x < 16
					&& pos.y >= 0 && pos.y < 16
				) {
					const u32
						col = item.img->at_u32(Vec2<size_t>{
							.x=size_t(pos.x),
							.y=size_t(pos.y),
						});
					const Vec2<size_t>
						temp_pos{
							.x=size_t(item.v.x),
							.y=size_t(item.v.y),
						};
					//if (
					//	double(item.uv.x) != 0
					//	&& double(item.uv.y) != 0
					//) {
						//printout(
						//	"visib: ",
						//	//Vec2<size_t>(
						//	//	size_t(item.v.x), size_t(item.v.y)
						//	//), " ",
						//	temp_pos, " ",
						//	//temp, " ",
						//	"{",
						//		double(item.uv.x), " ",
						//		double(item.uv.y),
						//	"} ",
						//	pos, " ",
						//	std::hex, col, std::dec,
						//	"\n"
						//);
					//}
					//printout(
					//	std::hex,
					//	col,
					//	std::dec,
					//	"\n"
					//);
					disp.set(
						//col
						temp_pos,
						col
						//0xff'ff'ff'ff
						//item.second,
					);
				}
				//printout(
				//	//uint32_t(visib.at(j * SIZE_2D.x + i)),
				//	//"visib: ",
				//	//Vec2<size_t>{.x=i, .y=j},
				//	//"\n"
				//	1
				//);
			}
		}
		//std::array<
		//	std::pair<u8, Vec2<MyCxFixedPt>>,
		//	SCREEN_SIZE_2D.y * SCREEN_SIZE_2D.x
		//> visib_buf;
		////visib_buf.fill(false);
		//visib_buf.fill(
		//	std::make_pair<u8, Vec2<MyCxFixedPt>>(
		//		false,
		//		{
		//			.x=MyCxFixedPt(0),
		//			.y=MyCxFixedPt(0),
		//		}
		//	)
		//);
		////int last_y = 0;
		//for (const auto& item: visib) {
		//	//printout(item, " ");
		//	//if (last_y != item.y) {
		//	//	printout("\n");
		//	//}
		//	//last_y = item.y;
		//	const Vec2<int> temp{
		//		.x=int(item.v.x),
		//		.y=int(item.v.y),
		//	};
		//	if (
		//		temp.x >= /*MyCxFixedPt*/(0)
		//		&& temp.x <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.x - 1)
		//		&& temp.y >= /*MyCxFixedPt*/(0)
		//		&& temp.y <= /*MyCxFixedPt*/int(SCREEN_SIZE_2D.y - 1)
		//	) {
		//		//printout(temp);
		//		auto& my_visib = visib_buf.at(
		//			int(temp.y) * SCREEN_SIZE_2D.x + int(temp.x)
		//		);
		//		my_visib.first = true;
		//		my_visib.second = item.uv;
		//		//printout(
		//		//	temp, ": ",
		//		//	Vec2<double>{
		//		//		.x=double(item.uv.x),
		//		//		.y=double(item.uv.y),
		//		//	},
		//		//	"\n"
		//		//);
		//	}
		//}
		//for (size_t j=0; j<SCREEN_SIZE_2D.y; ++j) {
		//	for (size_t i=0; i<SCREEN_SIZE_2D.x; ++i) {
		//		const auto& item = (
		//			visib_buf.at(j * SCREEN_SIZE_2D.x + i)
		//		);
		//		if (item.first) {
		//			const Vec2<int>
		//				pos{
		//					.x=int(
		//						item.second.x * MyCxFixedPt(16)
		//						//+ MyCxFixedPt(16)
		//					),
		//					.y=int(
		//						item.second.y * MyCxFixedPt(16)
		//					),
		//				};
		//			//printout(
		//			//	"item.first: ",
		//			//	Vec2<size_t>(i, j), " ",
		//			//	double(item.second.x), " ",
		//			//	double(item.second.y), " ",
		//			//	pos,
		//			//	"\n"
		//			//);
		//			if (
		//				//pos.x >= 0 + 48 && pos.x < 16 + 48
		//				//&& pos.y >= 0 && pos.y < 16
		//				pos.x >= 0 && pos.x < 16
		//				&& pos.y >= 0 && pos.y < 16
		//			) {
		//				if (
		//					double(item.second.x) != 0
		//					&& double(item.second.y) != 0
		//				) {
		//					printout(
		//						"item.first: ",
		//						Vec2<size_t>(i, j), " ",
		//						double(item.second.x), " ",
		//						double(item.second.y), " ",
		//						pos,
		//						"\n"
		//					);
		//				}
		//				disp.set(
		//					Vec2<size_t>{
		//						.x=i,
		//						.y=j,
		//					},
		//					//0xfffffff
		//					//item.second,
		//					tri.img->at_u32(Vec2<size_t>{
		//						.x=size_t(pos.x + 16),
		//						.y=size_t(pos.y),
		//					})
		//				);
		//			}
		//			//printout(
		//			//	//uint32_t(visib.at(j * SIZE_2D.x + i)),
		//			//	//"visib: ",
		//			//	//Vec2<size_t>{.x=i, .y=j},
		//			//	//"\n"
		//			//	1
		//			//);
		//		} else {
		//			//printout(" ");
		//		}
		//	}
		//	//printout("\n");
		//}
		disp.refresh();
	}
	
	return 0;
}
