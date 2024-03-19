/* 
* Copyright (C) KolibriOS team 2016-2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#include <newlib.h>

extern void init_reent();
extern void _exit(int __status) __attribute__((noreturn));

void  __attribute__((noreturn))
__thread_startup (int (*entry)(void*), void *param,
                  void *stacklow, void *stackhigh)
{
    int retval;

    /* Save stack limits use TLS */
    __asm__ __volatile__ (
        "movl %0, %%fs:8    \n\t"
        "movl %1, %%fs:12   \n\t"
        ::"r"(stacklow), "r"(stackhigh)
    );

     /* Initialize thread reentry structure */
    init_reent();

    /* Call user thread function */
    retval = entry(param);

    _exit(retval);
}
