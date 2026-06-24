.section .text.start
.align 4
.global _my_text_start
_my_text_start:
	cpy r0, r0
	cpy r0, r0
	cpy r0, r0
	cpy r0, r0

	cpy r1, r0
	cpy r2, r0
	cpy r3, r0
	cpy r4, r0
	cpy r5, r0
	cpy r6, r0
	cpy r7, r0
	cpy r8, r0
	cpy r9, r0
	cpy r10, r0
	cpy r11, r0
	cpy r12, r0
	cpy lr, r0
	cpy fp, r0
	cpy sp, r0

	//bl r0, _start
	bl lr, _start

	//cpy sp, 0x800
	//bl r0, _main

.set VBLANK_IRQ, (0x1 << 0x0)
.set TIMER_IRQ, (0x1 << 0x1)

.set IRQ_ID_REG, (1 << 26)
.set IRQ_ENABLE_REG, ((1 << 26) + 4)

.align 4
.global _do_enable_irqs
_do_enable_irqs:
    // This function exists so as to make sure an IRQ does *not* occur
    // before `sp` is initialized.
    // It is intended to be called in `main()` in the C code.

    //cpy r1, (VBLANK_IRQ | TIMER_IRQ)
    str r1, r0, IRQ_ENABLE_REG

    cpy r1, _irq_handler
    cpy ids, r1

    cpy r1, 0x1
    cpy ie, r1

    jmp lr

.align 4
.global _irq_handler
_irq_handler:
    add sp, sp, -36
    str r1, sp, 0
    str r2, sp, 4
    str r3, sp, 8
    str r4, sp, 12
    str r5, sp, 16
    str r6, sp, 20
    str lr, sp, 24
    str fp, sp, 28
    cpy r1, hi
    str r1, sp, 32

    ldr r1, r0, IRQ_ID_REG
    bl _irq_handler_primary_logic

.Lirq_handler_return:
    ldr r1, sp, 32
    cpy hi, r1
    ldr r1, sp, 0
    ldr r2, sp, 4
    ldr r3, sp, 8
    ldr r4, sp, 12
    ldr r5, sp, 16
    ldr r6, sp, 20
    ldr lr, sp, 24
    ldr fp, sp, 28
    add sp, sp, 36
    ret ira

.global _my_data_start
_my_data_start:
    .i32 ___data_start
.global _my_data_end
_my_data_end:
    .i32 ___data_end
.global _my_data_size
_my_data_size:
    .i32 ___data_size

.global _my_rodata_start
_my_rodata_start:
    .i32 ___rodata_start
.global _my_rodata_end
_my_rodata_end:
    .i32 ___rodata_end
.global _my_rodata_size
_my_rodata_size:
    .i32 ___rodata_size

.global _my_bss_start
_my_bss_start:
    .i32 ___bss_start
.global _my_bss_end
_my_bss_end:
    .i32 ___bss_end
.global _my_bss_size
_my_bss_size:
    .i32 ___bss_size
