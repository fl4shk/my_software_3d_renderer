#include "MiscIncludes.hpp"
#include "Texture.hpp"
#include <cstdio>

int main(int argc, char** argv) {
    //std::fprintf(
    //    stderr,
    //    "argc:%i\n", argc
    //);

    //for (int i=0; i<argc; ++i) {
    //    std::fprintf(
    //        stderr,
    //        "  argv[%i]:%s\n",
    //        i, argv[i]
    //    );
    //}
    //std::fprintf(
    //    stderr,
    //    "\n"
    //);
    if (argc != 3) {
        std::fprintf(
            stderr,
            "Usage: %s <input_image> <output_binary>\n",
            argv[0]
        );
        std::exit(1);
    }
    auto* inp_img = std::fopen(argv[1], "r");
    if (!inp_img) {
        std::fprintf(
            stderr,
            "Couldn't open :\"%s\" (argument: <input_image>) "
            "for reading.\n",
            argv[1]
        );
        std::exit(1);
    }
    std::fclose(inp_img);

    auto texture = Texture(std::string(argv[1]));
    //sdl::Surface img = IMG_Load(argv[1]);

    auto* outp_bin = std::fopen(argv[2], "w");
    if (!outp_bin) {
        std::fprintf(
            stderr,
            "Couldn't open :\"%s\" (argument: <output_binary>) "
            "for writing.\n",
            argv[2]
        );
        std::exit(1);
    }
    //SDL_LockSurface(img);

    //SDL_PixelFormat* fmt = img->format;
    //SDL_Color col;
    //Uint8 pal_idx = 0;
    //auto get_pal_idx = [&](const Vec2<size_t>& pos) -> Uint8 {
    //    return ((Uint8*)img->pixels)[
    //        pos.y * img->w + pos.x
    //    ];
    //};
    ////auto get_col = [&](const Vec2<size_t>& pos) -> SDL_Color {
    ////    
    ////};
    const Vec2<size_t> TEMP_IMG_SIZE_2D = texture.size_2d();
    const Vec2<u32> IMG_SIZE_2D{
        .x=u32(TEMP_IMG_SIZE_2D.x),
        .y=u32(TEMP_IMG_SIZE_2D.y),
    };

    Vec2<size_t> pos{.x=0u, .y=0u};
    std::fwrite(&IMG_SIZE_2D.x, sizeof(IMG_SIZE_2D.x), 1ul, outp_bin);
    std::fwrite(&IMG_SIZE_2D.y, sizeof(IMG_SIZE_2D.y), 1ul, outp_bin);

    for (pos.y=0u; pos.y<IMG_SIZE_2D.y; ++pos.y) {
        for (pos.x=0u; pos.x<IMG_SIZE_2D.x; ++pos.x) {
            //pal_idx = get_pal_idx(pos);
            //col = fmt->palette->colors[pal_idx];
            const SDL_Color col_sdl = texture.at(pos);
            Rgb555 col_rgb555;
            col_rgb555.set_r(col_sdl.r);
            col_rgb555.set_g(col_sdl.g);
            col_rgb555.set_b(col_sdl.b);
            std::fwrite(
                &col_rgb555.data,
                sizeof(col_rgb555.data),
                1ul,
                outp_bin
            );
        }
    }

    //SDL_UnlockSurface(img);

    std::fflush(outp_bin);
    std::fclose(outp_bin);

    return 0;
}
