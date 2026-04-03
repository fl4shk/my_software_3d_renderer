//#include "MyDisplay.hpp"
#include "MiscIncludes.hpp"
#include "Vec4.hpp"
#include "Rast.hpp"
#include "Mat4x4.hpp"
#include "Square.hpp"
#include "Clip.hpp"
#include <cmath>


volatile u8* _melted_moon_dbg_print = (
    (volatile u8*)(
        (1ul << 27ul)
        | (1ul << 26u)
    )
);

void melted_moon_print(const std::string& str) {
    for (const auto& c: str) {
        *_melted_moon_dbg_print = c;
    }
}

extern "C" {

void melted_moon_print(const char* str) {
    //void* my_dbg_stdout = tiny_fs_fopen(MY_DBG_STDOUT_FILENAME, "w");
    //tiny_fs_fwrite(my_dbg_stdout, str, sizeof(u8) * strlen(str));
    //tiny_fs_fclose(my_dbg_stdout);
    const int my_str_len = strlen(str);
    for (int i=0; i<my_str_len; ++i) {
        *_melted_moon_dbg_print = str[i];
    }
}

}


static constexpr u32 FB_BASE = 0x4000000ull;

static constexpr u32 FB_WIDTH = (
	/*64;*/ /*76 >> 1*/
	320u
	//320 >> 1
	//160
	//160 >> 1
);
static constexpr u32 FB_HEIGHT = (
	/*64;*/ 
	240u
	//240 >> 1
	//76 >> 1
);
static constexpr u32 FB_SIZE = FB_HEIGHT * FB_WIDTH;

static volatile u16* _melted_moon_fb = (
    (volatile u16*)FB_BASE
);
//static volatile u16* _melted_moon_fb_1 = (
//    ((volatile u16*)FB_BASE) + FB_SIZE
//);

//volatile u32* to_keep_loop_going = (
//	(volatile u32*)0x4ull
//);
extern "C" {
extern void do_enable_irqs(u32 irq_enable_mask);
}

static constexpr u32 VBLANK_IRQ = u32(1ul << 0ul);
static constexpr u32 TIMER_IRQ = u32(1ul << 1ul);

//#define MY_IRQ_FIXED_FRAC_SHIFT ((u32)16ul)

//static bool _my_seen_vblank_irq = false;

//static u32 _my_gettime_sec = 0ull;
//static u32 _my_gettime_usec = 0ull;
//static void _my_gettime(int* sec, int* usec) {
//    *sec = _my_gettime_sec;
//    *usec = _my_gettime_usec;
//}

//static constexpr size_t RGB555_PAL_SIZE = size_t(256ul);
//static u16 _rgb555_pal[RGB555_PAL_SIZE];
//
//void my_set_rgb555_palette(u8* palette) {
//    for (size_t i=0, k=0; i<RGB555_PAL_SIZE; ++i, k+=3u) {
//        const u32 r = ((palette[k + 0] >> 3u) & 0x1fu);
//        const u32 g = ((palette[k + 1] >> 3u) & 0x1fu);
//        const u32 b = ((palette[k + 2] >> 3u) & 0x1fu);
//        _rgb555_pal[i] = u16(
//            (b << 10u)
//            | (g << 5u)
//            | (r << 0u)
//        );
//    }
//}

static volatile bool _did_main_loop_iter = false;

extern u8 wood_block_bin[];
extern u32 wood_block_bin_size;

static void _vblank_irq_handler(void) {
    // At 70 FPS, we have this:
    // 1 / 70 Hz is approximately 14.2857 ms
    //static u32 cnt = 0;
    //++cnt;
    //if (cnt >= 70ul) {
    //    cnt = 0;
    //    ++_my_gettime_sec;
    //}

    //const u8* raw_fb = doom_get_framebuffer(4);
    if (_did_main_loop_iter) {
        //const unsigned char* my_screen_buf = doom_get_framebuffer(1);
        for (size_t i=0; i<SCREEN_SIZE_2D.x * SCREEN_SIZE_2D.y; ++i) {
            //_melted_moon_fb[i] = _rgb555_pal[my_screen_buf[i]];
        }
    }
}

//static void _timer_irq_handler(void) {
//    _my_gettime_usec += 1000u;
//}


extern "C" {
void irq_handler_primary_logic(u32 which_irqs) {
    if (which_irqs & VBLANK_IRQ) {
        _vblank_irq_handler();
    }
    if (which_irqs & TIMER_IRQ) {
        //_timer_irq_handler();
    }
}
}

void init_textures() {
    void* my_wood_block_img_file = tiny_fs_file_init(
        "gfx/obj/wood_block.bmp",
        wood_block_bin,
        wood_block_bin_size
    );
    tiny_fs_fclose(my_wood_block_img_file);
}
int main(int argc, char** argv) {
    init_textures();

    //do_enable_irqs(VBLANK_IRQ | TIMER_IRQ);
    do_enable_irqs(VBLANK_IRQ);

	//MyDisplay disp;
	Rast rast;
	const MyFixedPt
		near(0.1),
		far(10.0);
	Transform perspective(
		near, // near
		far // far
	);
	Texture texture(
		"gfx/obj/wood_block.bmp"
		//"gfx/obj/foreground_common_gfx.bmp"
	);
	Square sq{
		.size_2d{1.0, 1.0},
		.pos{00.0, 0.0, 0.00},
		//.rot{VERSOR_IDENTITY<MyFixedPt>},
		.img=&texture,
	};
	Vec3<MyFixedPt> camera_pos{0.00, 0.00, -5.001};
	//Versor<MyFixedPt>
	//	camera_rot;
	Transform camera(
		MAT4X4_IDENTITY<MyFixedPt>
	);
	static constexpr Vec3<MyFixedPt>
		sq_rotate_angles{0.00101, 0.00101, 0.00101};
		
	for (;;) {
	    if (!_did_main_loop_iter) {
            //disp.handle_sdl_events();
            //if (disp.do_exit()) {
            //	break;
            //}
            {
                //printout("checking keys\n");
                //const MyFixedPt
                //	amount_xy(0.0100),
                //	amount_z(0.0100),
                //	amount_angle(0.00010000);
                //if (
                //	disp.key_down_now(SnesKeyKind::DpadLeft)
                //	&& disp.key_up_now(SnesKeyKind::DpadRight)
                //) {
                //	camera_pos.x += amount_xy;
                //} else if (
                //	disp.key_down_now(SnesKeyKind::DpadRight)
                //	&& disp.key_up_now(SnesKeyKind::DpadLeft)
                //) {
                //	camera_pos.x -= amount_xy;
                //}

                //if (
                //	disp.key_down_now(SnesKeyKind::DpadUp)
                //	&& disp.key_up_now(SnesKeyKind::DpadDown)
                //) {
                //	camera_pos.y += amount_xy;
                //} else if (
                //	disp.key_down_now(SnesKeyKind::DpadDown)
                //	&& disp.key_up_now(SnesKeyKind::DpadUp)
                //) {
                //	camera_pos.y -= amount_xy;
                //}

                //if (
                //	disp.key_down_now(SnesKeyKind::Y)
                //	&& disp.key_up_now(SnesKeyKind::A)
                //) {
                //	camera_pos.z -= amount_z;
                //} else if (
                //	disp.key_down_now(SnesKeyKind::A)
                //	&& disp.key_up_now(SnesKeyKind::Y)
                //) {
                //	camera_pos.z += amount_z;
                //}

                if (
                    //disp.key_down_now(SnesKeyKind::L)
                    //&& disp.key_up_now(SnesKeyKind::R)
                    true
                ) {
                    sq.rot = (
                        sq.rot
                        * Versor<MyFixedPt>::from_y_angle(-sq_rotate_angles.y)
                    );
                }
                //else if (
                //	disp.key_down_now(SnesKeyKind::R)
                //	&& disp.key_up_now(SnesKeyKind::L)
                //) {
                //	sq.rot = (
                //		sq.rot
                //		* Versor<MyFixedPt>::from_y_angle(sq_rotate_angles.y)
                //	);
                //}
            }
            auto& tri_arr = sq.update_tri_arr();

            camera.set_translate(camera_pos);
            //tri.model = &my_sq_model;
            const Transform n_view(
                camera.mat.inverse()
            );
            std::vector<VertTextureCoords> visib;
            Clip clip;
            //--------
            // TODO: BEGIN: later
            for (size_t i=0; i<tri_arr.size(); ++i) {
                //size_t i = 0;
                auto& tri = tri_arr.at(i);
                tri.do_project_etc(
                    n_view,
                    perspective
                );
                auto&& clip_vec = clip.do_clip(tri);
                for (size_t j=0; j<clip_vec.size(); ++j) {
                    clip_vec.at(j).persp_div();
                    rast.calc_visib(
                        //{tri, clip_vec.at(j)},
                        clip_vec.at(j),
                        visib
                    );
                }
            }
            // TODO: END: later
            //--------
            for (const auto& item: visib) {
                const Vec2<int> temp{
                    .x=int(item.v.x),
                    .y=int(item.v.y),
                };
                if (
                    temp.x >= /*MyFixedPt*/(0)
                    && temp.x <= /*MyFixedPt*/int(SCREEN_SIZE_2D.x - 1)
                    && temp.y >= /*MyFixedPt*/(0)
                    && temp.y <= /*MyFixedPt*/int(SCREEN_SIZE_2D.y - 1)
                    //true
                ) {
                    const Vec2<int>
                        pos{
                            .x=int(
                                item.uv.x * MyFixedPt(16)
                                //+ MyFixedPt(16)
                            ),
                            .y=int(
                                item.uv.y * MyFixedPt(16)
                            ),
                        };

                    if (
                        //pos.x >= 0 + 48 && pos.x < 16 + 48
                        //&& pos.y >= 0 && pos.y < 16
                        pos.x >= 0 && pos.x < 16
                        && pos.y >= 0 && pos.y < 16
                    ) {
                        // TODO: add this back in
                        //const u32
                        //	col = item.img->at_u32(Vec2<size_t>{
                        //		.x=size_t(pos.x),
                        //		.y=size_t(pos.y),
                        //	});
                        const Color
                            col = item.img->at(Vec2<size_t>{
                                .x=size_t(pos.x),
                                .y=size_t(pos.y),
                            });
                        const Vec2<size_t>
                            temp_pos{
                                .x=size_t(item.v.x),
                                .y=size_t(item.v.y),
                            };

                        //disp.set(
                        //	//col
                        //	temp_pos,
                        //	col
                        //	//0xff'ff'ff'ff
                        //	//item.second,
                        //);
                    }
                }
            }
            _did_main_loop_iter = true;
            //disp.refresh();
        }
	}
	
	return 0;
}
