/* 
* Copyright (C) KolibriOS team 2016-2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

.global _create_thread

.section .text

/* 
 * create_thread(int (*entry)(void*), void *param, size_t stack_size) 
 */
_create_thread:
    pushl %ebx

    movl    $68, %eax
    movl    $12, %ebx
    movl    16(%esp), %ecx      /* [stack_size] */
    addl    $4095, %ecx
    andl    $-4096, %ecx
    movl    %ecx, 16(%esp)      /* Save stack size */
    int     $0x40               /* Alloc memory (sf 68.12) */
    testl   %eax, %eax
    jz      1f

    leal    -20(%eax,%ecx), %edx

    movl    8(%esp), %ebx       /* [thr_proc] */
    mov     %ebx, 4(%edx)

    movl    12(%esp), %ebx      /* [param] */
    movl    %ebx, 8(%edx)

    addl    %eax, %ecx
    movl    %eax, 12(%edx)      /* Stack low limit */
    movl    %ecx, 16(%edx)      /* Stack high limit */

    movl    $51, %eax
    movl    $1,  %ebx
    lea     ___thread_startup , %ecx
    int     $0x40               /* Create thread (sf 51.1) */                
    popl    %ebx
    ret
1:
    notl    %eax
    popl    %ebx
    ret
