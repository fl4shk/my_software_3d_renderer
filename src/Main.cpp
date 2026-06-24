//#include "MyDisplay.hpp"
#include "MiscIncludes.hpp"
#include "Vec4.hpp"
#include "Rast.hpp"
#include "Mat4x4.hpp"
#include "Square.hpp"
#include "Clip.hpp"
#include <cmath>
#include <cstdlib>


volatile u8* _melted_moon_dbg_print = (
    (volatile u8*)(
        (1ul << 26ul)
        | (1ul << 25u)
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
void melted_moon_write(const void* buf, size_t count) {
    const char* str = (const char*)buf;
    for (size_t i=0; i<count; ++i) {
        *_melted_moon_dbg_print = str[i];
    }
}

}


static constexpr u32 FB_BASE = 0x02000000ul; //0x4000000ull;

//static constexpr u32 FB_WIDTH = (
//  /*64;*/ /*76 >> 1*/
//  320u
//  //320 >> 1
//  //160
//  //160 >> 1
//);
//static constexpr u32 FB_HEIGHT = (
//  /*64;*/ 
//  240u
//  //240 >> 1
//  //76 >> 1
//);
//static constexpr u32 FB_SIZE = FB_HEIGHT * FB_WIDTH;

static volatile u16* _melted_moon_fb = (
    (volatile u16*)FB_BASE
);
//static volatile u16* _melted_moon_fb_1 = (
//    ((volatile u16*)FB_BASE) + FB_SIZE
//);

//volatile u32* to_keep_loop_going = (
//  (volatile u32*)0x4ull
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
        ////const unsigned char* my_screen_buf = doom_get_framebuffer(1);
        //for (size_t i=0; i<SCREEN_SIZE_2D.x * SCREEN_SIZE_2D.y; ++i) {
        //    //_melted_moon_fb[i] = _rgb555_pal[my_screen_buf[i]];
        //}
        _did_main_loop_iter = false;
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

static constexpr const char* WOOD_BLOCK_BMP_FILENAME = (
    "gfx/obj/wood_block.bmp"
);
extern u8 wood_block_bin[];
extern u32 wood_block_bin_size;

void init_textures() {
    void* my_wood_block_img_file = tiny_fs_file_init(
        WOOD_BLOCK_BMP_FILENAME,
        wood_block_bin,
        wood_block_bin_size
    );
    tiny_fs_fclose(my_wood_block_img_file);
}


//extern u32
//    test_float_sub_r1,
//    test_float_sub_r2;
//
//int main(int argc, char** argv) {
//    //static constexpr u32
//    //    r1 = 0x43312264u,
//    //    r2 = 0x430edd9bu;
//    const u32 r1 = test_float_sub_r1;
//    const u32 r2 = test_float_sub_r2;
//
//    const float r1_flt = from_bits(r1);
//    const float r2_flt = from_bits(r2);
//    const float diff_flt = r1_flt - r2_flt;
//    const u32 diff = to_bits(diff_flt);
//    static constexpr size_t BUF_SIZE = 1024;
//    char buf[BUF_SIZE];
//
//    buf[snprintf(
//        buf, BUF_SIZE,
//        "r1=%x r2=%x diff=%x\n"
//        "r1_flt=%f r2_flt=%f diff_flt=%f\n",
//        r1, r2, diff,
//        r1_flt, r2_flt, diff_flt
//    )] = '\0';
//    my_printout(buf);
//
//    for (;;) {
//        if (!_did_main_loop_iter) {
//            _did_main_loop_iter = true;
//        }
//    }
//}

//int main(int argc, char** argv) {
//    //do_enable_irqs(VBLANK_IRQ);
//
//    for (;;) {
//        if (!_did_main_loop_iter) {
//            const size_t BUF_SIZE = 128u;
//            const size_t OUTER_BUF_SIZE = 4u;
//            const float to_conv_flt = 0.002f;//5.9;
//            const u32 to_conv_u32 = 990055353;
//
//            char buf[OUTER_BUF_SIZE][BUF_SIZE];
//
//            snprintf(
//                buf[0], BUF_SIZE,
//                "%f",
//                to_conv_flt
//            );
//            float temp_flt = std::stof(
//                std::string(buf[0])
//            );
//            u32 temp_u32 = 0;
//            memcpy(&temp_u32, &temp_flt, sizeof(temp_flt));
//            snprintf(
//                buf[1], BUF_SIZE,
//                "%x",
//                temp_u32
//            );
//            my_printout(
//                buf[1],
//                "\n"
//            );
//
//            memcpy(&temp_flt, &to_conv_u32, sizeof(to_conv_u32));
//            snprintf(
//                buf[2], BUF_SIZE,
//                "%.8f",
//                temp_flt
//            );
//            snprintf(
//                buf[3], BUF_SIZE,
//                "%u",
//                to_conv_u32
//            );
//            my_printout(
//                buf[2],
//                " ",
//                buf[3],
//                "\n"
//            );
//
//            _did_main_loop_iter = true;
//        }
//    }
//}

int main(int argc, char** argv) {
    init_textures();

    //do_enable_irqs(VBLANK_IRQ | TIMER_IRQ);
    do_enable_irqs(VBLANK_IRQ);

    ////MyDisplay disp;
    Rast rast;
    const MyFixedPt
        near(0.1),
        far(10.0);
    Transform perspective(
        near, // near
        far // far
    );
    Texture texture(
        WOOD_BLOCK_BMP_FILENAME
        //"gfx/obj/wood_block.bmp"
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
    //  camera_rot;
    Transform camera(
        MAT4X4_IDENTITY<MyFixedPt>
    );
    static constexpr Vec3<MyFixedPt>
        sq_rotate_angles{0.00101, 0.00101, 0.00101};

    sq.rot = (
        sq.rot
        * Versor<MyFixedPt>::from_y_angle(
            //-sq_rotate_angles.y
            MyFixedPt(0.00101 * 200)
        )
    );
        
    for (;;) {
        if (!_did_main_loop_iter) {
            //disp.handle_sdl_events();
            //if (disp.do_exit()) {
            //  break;
            //}

            //my_printout(
            //    5.9,
            //    "\n"
            //);
            //mm_printout_base(
            //    double(5.9)
            //);
            //mm_printout_base(
            //    char('\n')
            //);

            //--------
            //{
            //    my_printout("checking keys\n");
            //    //const MyFixedPt
            //    //  amount_xy(0.0100),
            //    //  amount_z(0.0100),
            //    //  amount_angle(0.00010000);
            //    //if (
            //    //  disp.key_down_now(SnesKeyKind::DpadLeft)
            //    //  && disp.key_up_now(SnesKeyKind::DpadRight)
            //    //) {
            //    //  camera_pos.x += amount_xy;
            //    //} else if (
            //    //  disp.key_down_now(SnesKeyKind::DpadRight)
            //    //  && disp.key_up_now(SnesKeyKind::DpadLeft)
            //    //) {
            //    //  camera_pos.x -= amount_xy;
            //    //}

            //    //if (
            //    //  disp.key_down_now(SnesKeyKind::DpadUp)
            //    //  && disp.key_up_now(SnesKeyKind::DpadDown)
            //    //) {
            //    //  camera_pos.y += amount_xy;
            //    //} else if (
            //    //  disp.key_down_now(SnesKeyKind::DpadDown)
            //    //  && disp.key_up_now(SnesKeyKind::DpadUp)
            //    //) {
            //    //  camera_pos.y -= amount_xy;
            //    //}

            //    //if (
            //    //  disp.key_down_now(SnesKeyKind::Y)
            //    //  && disp.key_up_now(SnesKeyKind::A)
            //    //) {
            //    //  camera_pos.z -= amount_z;
            //    //} else if (
            //    //  disp.key_down_now(SnesKeyKind::A)
            //    //  && disp.key_up_now(SnesKeyKind::Y)
            //    //) {
            //    //  camera_pos.z += amount_z;
            //    //}

            //    //if (
            //    //    //disp.key_down_now(SnesKeyKind::L)
            //    //    //&& disp.key_up_now(SnesKeyKind::R)
            //    //    true
            //    //) {
            //    //    sq.rot = (
            //    //        sq.rot
            //    //        * Versor<MyFixedPt>::from_y_angle(
            //    //            -sq_rotate_angles.y
            //    //        )
            //    //    );
            //    //}
            //    //else if (
            //    //  disp.key_down_now(SnesKeyKind::R)
            //    //  && disp.key_up_now(SnesKeyKind::L)
            //    //) {
            //    //  sq.rot = (
            //    //      sq.rot
            //    //      * Versor<MyFixedPt>::from_y_angle(sq_rotate_angles.y)
            //    //  );
            //    //}
            //}
            //auto& tri_arr = sq.update_tri_arr();

            //camera.set_translate(camera_pos);
            ////tri.model = &my_sq_model;
            //const Transform n_view(
            //    camera.mat.inverse()
            //);
            //std::vector<VertTextureCoords> visib;
            //Clip clip;
            ////--------
            //// TODO: BEGIN: later
            //for (size_t i=0; i<tri_arr.size(); ++i) {
            //    //size_t i = 0;
            //    auto& tri = tri_arr.at(i);
            //    tri.do_project_etc(
            //        n_view,
            //        perspective
            //    );
            //    auto&& clip_vec = clip.do_clip(tri);
            //    for (size_t j=0; j<clip_vec.size(); ++j) {
            //        clip_vec.at(j).persp_div();
            //        my_printout(
            //            "post persp_div():\n",
            //            //"clip_vec.at(", j, ").proj_v:\n",
            //            //"{\n",
            //            //"\t{",
            //            //  clip_vec.at(j).proj_v.at(0).v, " ",
            //            //  clip_vec.at(j).proj_v.at(0).uv,
            //            //"}",
            //            //"\n",
            //            //"\t{",
            //            //  clip_vec.at(j).proj_v.at(1).v, " ",
            //            //  clip_vec.at(j).proj_v.at(1).uv,
            //            //"}",
            //            //"\n",
            //            //"\t{",
            //            //  clip_vec.at(j).proj_v.at(2).v, " ",
            //            //  clip_vec.at(j).proj_v.at(2).uv,
            //            //"}\n",
            //            //"}\n"
            //            "clip_vec.at(", j, ").screen_v:\n",
            //            "{\n",
            //            "\t{",
            //                clip_vec.at(j).screen_v.at(0).v, " ",
            //                clip_vec.at(j).screen_v.at(0).uv, ";    ",
            //                to_bits(clip_vec.at(j).screen_v.at(0).v), " ",
            //                to_bits(clip_vec.at(j).screen_v.at(0).uv),
            //            "}",
            //            "\n",
            //            "\t{",
            //                clip_vec.at(j).screen_v.at(1).v, " ",
            //                clip_vec.at(j).screen_v.at(1).uv, ";    ",
            //                to_bits(clip_vec.at(j).screen_v.at(1).v), " ",
            //                to_bits(clip_vec.at(j).screen_v.at(1).uv),
            //            "}",
            //            "\n",
            //            "\t{",
            //                clip_vec.at(j).screen_v.at(2).v, " ",
            //                clip_vec.at(j).screen_v.at(2).uv, ";    ",
            //                to_bits(clip_vec.at(j).screen_v.at(2).v), " ",
            //                to_bits(clip_vec.at(j).screen_v.at(2).uv),
            //            "}\n",
            //            "}\n"
            //        );
            //        rast.calc_visib(
            //            //{tri, clip_vec.at(j)},
            //            clip_vec.at(j),
            //            visib
            //        );
            //    }
            //    my_printout(
            //        "i=", i, " visib.size(): ", visib.size(), "\n"
            //    );
            //}
            // TODO: END: later
            //--------
            //my_printout(
            //    "visib.size()=", visib.size(), "\n"
            //);
            std::vector<VertTextureCoords> visib;
            auto debug_add_visib = [&](
                const Vec2<size_t>& v,
                const Vec2<size_t>& scaled_uv
            ) -> void {
                visib.push_back(VertTextureCoords{
                    .img=&texture,
                    .v={
                        .x=MyFixedPt(v.x),
                        .y=MyFixedPt(v.y),
                    },
                    .uv={
                        .x=(MyFixedPt(scaled_uv.x) / MyFixedPt(16)),
                        .y=(MyFixedPt(scaled_uv.y) / MyFixedPt(16)),
                    },
                });
            };
            for (size_t j=100; j<110; ++j) {
                for (size_t i=150; i<160; ++i) {
                    debug_add_visib(
                        {i, j}, {10, 10}
                    );
                }
            }
            debug_add_visib(
                {155, 105}, {0, 0}
            );
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
                        //  col = item.img->at_u32(Vec2<size_t>{
                        //      .x=size_t(pos.x),
                        //      .y=size_t(pos.y),
                        //  });
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
                        //  //col
                        //  temp_pos,
                        //  col
                        //  //0xff'ff'ff'ff
                        //  //item.second,
                        ///);
                        //my_printout(
                        //    "debug: col.data: ",
                        //    size_t(col.data),
                        //    "\n"
                        //);
                        const size_t fb_idx = (
                            temp_pos.y * SCREEN_SIZE_2D.x + temp_pos.x
                        );
                        _melted_moon_fb[fb_idx] = col.data;
                    }
                    //my_printout(
                    //    "inner: out of range (maybe?): ",
                    //    temp,
                    //    "\n"
                    //);
                } else {
                    //my_printout(
                    //    "outer: out of range (maybe?): ",
                    //    temp,
                    //    "\n"
                    //);
                }
            }
            _did_main_loop_iter = true;
            //disp.refresh();
        }
    }
    
    return 0;
}
