/* 
* Copyright (C) KolibriOS team 2016-2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#include <sys/kos_tls.h>

.section .text

.global __exit
.global __Exit

.align 4
__exit:
__Exit:
    movl  4(%esp), %edx     /* Store exit code */
    movl  $68, %eax
    movl  $13, %ebx
    movl  %fs:TLS_KEY_LOW_STACK, %ecx
    int   $0x40             /* Free memory (sf 68.13)  */

    movl  $-1, %eax
    int   $0x40             /* Terminate thread (sf -1) */
