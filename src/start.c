//=========================================//
//   Title:  start.c                       //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
//=========================================//
#include <rpi.h>
#if RPI_VERSION==0 || RPI_VERSION==1
__asm__(
"  .section .text.boot          \n"
"  .globl _start                \n"
"  .org 0x8000                  \n"
"  _start:                      \n"
"    ldr r4, =__bss_start       \n"
"    ldr r9, =__bss_end         \n"
"    mov r5, #0                 \n"
"    mov r6, #0                 \n"
"    mov r7, #0                 \n"
"    mov r8, #0                 \n"
"  _zero_bss:                   \n"
"    cmp r4, r9                 \n"
"    bhs _blx_main              \n"
"    stmia r4!, {r5-r8}         \n"
"    bal _zero_bss              \n"
"  _blx_main:                   \n"
"    ldr sp, =_start            \n"
"    blx main                   \n"
"  halt:                        \n"
"    wfe                        \n"
"    bal halt                   \n"
);
#elif RPI_VERSION==2
__asm__(
"  .section .text.boot          \n"
"  .globl _start                \n"
"  .org 0x8000                  \n"
"  _start:                      \n"
"    mrc p15, 0, r5, c0, c0, 5  \n"
"    and r5, r5, #3             \n"
"    cmp r5, #0                 \n"
"    bne halt                   \n"
"    ldr r4, =__bss_start       \n"
"    ldr r9, =__bss_end         \n"
"    mov r5, #0                 \n"
"    mov r6, #0                 \n"
"    mov r7, #0                 \n"
"    mov r8, #0                 \n"
"  _zero_bss:                   \n"
"    cmp r4, r9                 \n"
"    bhs _blx_main              \n"
"    stmia r4!, {r5-r8}         \n"
"    bal _zero_bss              \n"
"  _blx_main:                   \n"
"    ldr sp, =_start            \n"
"    blx main                   \n"
"  halt:                        \n"
"    wfe                        \n"
"    bal halt                   \n"
);
#elif RPI_VERSION==3 || RPI_VERSION==4
__asm__(
"  .section .text.boot     \n"
"  .global _start          \n"
"  .org 0x8000             \n"
"  _start:                 \n"
"    ldr r5, =__bss_start  \n"
"    ldr r6, =__bss_end    \n"
"    mov r7, #0            \n"
"  _zero_bss:              \n"
"    cmp r5, r6            \n"
"    beq _bl_main          \n"
"    str r7, [r5], #4      \n"
"    bal _zero_bss         \n"
"  _bl_main:               \n"
"    ldr sp, =_start       \n"
"    bl  main              \n"
"  halt:                   \n"
"    wfe                   \n"
"    b halt                \n"
);
#endif
