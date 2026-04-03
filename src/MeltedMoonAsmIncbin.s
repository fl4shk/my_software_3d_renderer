.section .rodata
.global _wood_block_bin
.type _wood_block_bin, @object
.align 4

_wood_block_bin:
.incbin "src/wood_block.bin"
//.i32 0x12345678

.section .rodata
.global _wood_block_bin_end
.type _wood_block_bin_end, @object
.align 4
_wood_block_bin_end:

.section .rodata
.global _wood_block_bin_size
.type _wood_block_bin_size, @object
.align 4
_wood_block_bin_size:
.i32 _wood_block_bin_end - _wood_block_bin
//.i32 _wood_block_bin_end
//.i32 0x12345679

//.section .text
//.global _start
//_start:
//    beq r0, r0, _start
