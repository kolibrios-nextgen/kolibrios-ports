/* 
* Copyright (C) KolibriOS team 2016-2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#include "tls.h"

.section .init

.global __crt_start

.align 4
__crt_start:
    movl    $68, %eax
    movl    12, %ebx
    lea     __size_of_stack_reserve__, %ecx
    addl    $4095, %ecx                     /* Load stack size */
    andl    $-4096, %ecx                    /* Align to page granularity */
    int     $0x40                           /* Allocate (sf 68.12) */
    testl   %eax, %eax
    jz      1f

    addl    %eax, %ecx
    movl    %eax, %fs:TLS_KEY_LOW_STACK     /* Save stack base - low limit */
    movl    %ecx, %fs:TLS_KEY_HIGH_STACK    /* Save stack top  - high limit */
    movl    %ecx, %esp                      /* Set new stack */

    subl    $1024, %esp                     /* Alloc information structure on the stack */
    movl    $9, %eax
    movl    %esp, %ebx                      
    movl    $-1, %ecx                       /* This procces */
    int     $0x40                           /* Get procces info (sf 9) */

    movl    30(%ebx), %eax                  /* PID (offset in info structure) */ 
    movl    %eax, %fs:TLS_KEY_PID           /* Save PID */

    addl    $1024, %esp

    jmp     ___libc_init                    /* Jump to __libc_init */
1:
    int3                                    /* Trap to debugger */
    .ascii "No enough memory for stack allocation"
