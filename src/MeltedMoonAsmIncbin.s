//.section .rodata
//.global _doom1_wad
//.type _doom1_wad, @object
//.align 4
//
//_doom1_wad:
//.incbin "doom1.wad"
////.i32 0x12345678
//
//.section .rodata
//.global _doom1_wad_end
//.type _doom1_wad_end, @object
//.align 4
//_doom1_wad_end:
//
//.section .rodata
//.global _doom1_wad_size
//.type _doom1_wad_size, @object
//.align 4
//_doom1_wad_size:
//.i32 _doom1_wad_end - _doom1_wad
////.i32 _doom1_wad_end
////.i32 0x12345679
//
////.section .text
////.global _start
////_start:
////    beq r0, r0, _start
