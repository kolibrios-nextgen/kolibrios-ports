/* 
* Copyright (C) KolibriOS team 2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#ifndef _SYS_KOS_MUTEX_H_
#define _SYS_KOS_MUTEX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/ksys.h>

typedef struct
{
    volatile int lock;
    int handle;
} kos_mutex_t;

typedef struct
{
    volatile int lock;
    int handle;
    long depth;
    unsigned long owner;
} kos_recursive_mutex_t;

void kos_mutex_init(kos_mutex_t *mutex);
int kos_mutex_trylock(kos_mutex_t *mutex);
int kos_mutex_lock(kos_mutex_t *mutex);
int kos_mutex_unlock(kos_mutex_t *mutex);
int kos_mutex_destroy(kos_mutex_t *mutex);

void kos_recursive_mutex_init(kos_recursive_mutex_t *mutex);
int kos_recursive_mutex_trylock(kos_recursive_mutex_t *mutex);
int kos_recursive_mutex_lock(kos_recursive_mutex_t *mutex);
int kos_recursive_mutex_unlock(kos_recursive_mutex_t *mutex);
int kos_recursive_mutex_destroy(kos_recursive_mutex_t *mutex);

#ifdef __cplusplus
}
#endif
#endif // _SYS_KOS_MUTEX_H_
