//=========================================//
//   Title:  start.c                       //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//=========================================//
__asm__(
"   .section .text.boot    \n"
"   .global _start         \n"
"   _start:                \n"
"   ldr sp, =stack         \n"
"   bl      main           \n"
"                          \n"
"   .section .data         \n"
"   .space 4096            \n"
"   stack:                 \n"
);
