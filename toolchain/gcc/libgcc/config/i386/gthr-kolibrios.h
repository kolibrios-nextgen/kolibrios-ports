/* Threads compatibility routines for libgcc2  */
/* Compile this one with gcc.  */

/* Copyright (C) KolibriOS-NG team 2024. All rights reserved.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_GTHR_KOLIBRIOS_H
#define GCC_GTHR_KOLIBRIOS_H

#include <errno.h>
#include <stddef.h>

#include <sys/ksys.h>
#include <sys/kos_tls.h>
#include <sys/kos_mutex.h>

/* Make sure CONST_CAST2 (origin in system.h) is declared.  */
#ifndef CONST_CAST2
#ifdef __cplusplus
#define CONST_CAST2(TOTYPE,FROMTYPE,X) (const_cast<TOTYPE> (X))
#else
#define CONST_CAST2(TOTYPE,FROMTYPE,X) ((__extension__(union {FROMTYPE _q; TOTYPE _nq;})(X))._nq)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UNUSED_PARAM
#define __UNUSED_PARAM(x) x
#endif

#define __GTHREADS 1

#define exchange_acquire(ptr, new) \
  __atomic_exchange_4((ptr), (new), __ATOMIC_ACQUIRE)
 
#define exchange_release(ptr, new) \
  __atomic_exchange_4((ptr), (new), __ATOMIC_RELEASE)

typedef unsigned long __gthread_key_t;

typedef struct {
    int done;
    long started;
} __gthread_once_t;

typedef kos_mutex_t __gthread_mutex_t;
typedef kos_recursive_mutex_t __gthread_recursive_mutex_t ;

#define __GTHREAD_ONCE_INIT {0, -1}
#define __GTHREAD_MUTEX_INIT_FUNCTION __gthread_mutex_init_function

#define __GTHREAD_RECURSIVE_MUTEX_INIT_FUNCTION \
  __gthread_recursive_mutex_init_function

static inline int __gthread_active_p (void)
{
    return 1;
}

static inline int __gthr_kolibrios_once(__gthread_once_t *once, void (*func) (void))
{
    if (once == NULL || func == NULL)
        return EINVAL;

    if (! once->done)
    {
        if (__sync_add_and_fetch(&(once->started), 1) == 0)
        {
            (*func) ();
            once->done = 1;
        }
        else
        {
            while (! once->done)
               _ksys_thread_yield();
        }
    }

    return 0;
}
 
static inline int __gthr_kolibrios_key_create(__gthread_key_t *key,
                         void (*dtor) (void *) __attribute__((unused)))
{
    int status = 0;
    unsigned int tls_index = kos_tls_alloc();
    if (tls_index != 0xFFFFFFFF)
        *key = tls_index;
    else
        status = -1;
    return status;
}

static inline int __gthread_once(__gthread_once_t *__once, void (*__func) (void))
{
    if (__gthread_active_p())
        return __gthr_kolibrios_once(__once, __func);
    else
        return -1;
}

static inline int __gthread_key_create(__gthread_key_t *__key, void (*__dtor) (void *))
{
    return __gthr_kolibrios_key_create(__key, __dtor);
}

static inline int __gthread_key_delete(__gthread_key_t __key)
{
    return kos_tls_free(__key);
}

static inline void* __gthread_getspecific(__gthread_key_t __key)
{
    return kos_tls_get(__key);
}

static inline int __gthread_setspecific(__gthread_key_t __key, const void *__ptr)
{
    return kos_tls_set(__key, CONST_CAST2(void *, const void *, __ptr));
}

static inline void __gthread_mutex_init_function(__gthread_mutex_t *__mutex)
{
    kos_mutex_init(__mutex);
}

static inline void __gthread_mutex_destroy(__gthread_mutex_t *__mutex)
{
    kos_mutex_destroy(__mutex);
}

static inline int __gthread_mutex_lock(__gthread_mutex_t *__mutex)
{
    if (__gthread_active_p ())
        return kos_mutex_lock(__mutex);
    else
        return 0;
}

static inline int __gthread_mutex_trylock(__gthread_mutex_t *__mutex)
{
    if (__gthread_active_p())
        return kos_mutex_trylock (__mutex);
    else
        return 0;
}

static inline int __gthread_mutex_unlock(__gthread_mutex_t *__mutex)
{
    if (__gthread_active_p ())
        return kos_mutex_unlock(__mutex);
    else
        return 0;
}

static inline void __gthread_recursive_mutex_init_function(__gthread_recursive_mutex_t *__mutex)
{
    kos_recursive_mutex_init(__mutex);
}

static inline int __gthread_recursive_mutex_lock(__gthread_recursive_mutex_t *__mutex)
{
    if (__gthread_active_p ())
        return kos_recursive_mutex_lock(__mutex);
    else
        return 0;
}

static inline int __gthread_recursive_mutex_trylock(__gthread_recursive_mutex_t *__mutex)
{
    if (__gthread_active_p ())
        return kos_recursive_mutex_trylock(__mutex);
    else
        return 0;
}

static inline int __gthread_recursive_mutex_unlock(__gthread_recursive_mutex_t *__mutex)
{
    if (__gthread_active_p())
        return kos_recursive_mutex_unlock(__mutex);
    else
        return 0;
}

static inline int __gthread_recursive_mutex_destroy(__gthread_recursive_mutex_t *__mutex)
{
    return kos_recursive_mutex_destroy(__mutex);
}

#ifdef __cplusplus
}
#endif
 
#endif /* ! GCC_GTHR_KOLIBRIOS_H */
