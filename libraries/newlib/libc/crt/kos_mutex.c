/* 
* Copyright (C) KolibriOS team 2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#include <sys/ksys.h>
#include <sys/kos_mutex.h>

#include "tls.h"

#define exchange_acquire(ptr, new) \
  __atomic_exchange_4((ptr), (new), __ATOMIC_ACQUIRE)

#define exchange_release(ptr, new) \
  __atomic_exchange_4((ptr), (new), __ATOMIC_RELEASE)

void kos_mutex_init(kos_mutex_t *mutex)
{
    mutex->lock = 0;
    mutex->handle  = _ksys_futex_create(mutex);
}

int kos_mutex_lock(kos_mutex_t *mutex)
{
    if( __sync_fetch_and_add(&mutex->lock, 1) == 0)
        return 0;

    while (exchange_acquire(&mutex->lock, 2) != 0)
    {
        _ksys_futex_wait(mutex->handle, 2, 0);
    }

    return 0;
}

int kos_mutex_unlock(kos_mutex_t *mutex)
{
    int prev;

    prev = exchange_release(&mutex->lock, 0);

    if (prev != 1)
    {
        _ksys_futex_wake(mutex->handle, 1);
    }

    return 0;
}

void kos_recursive_mutex_init(kos_recursive_mutex_t *mutex)
{
    int handle;
    mutex->lock = 0;

    mutex->handle = _ksys_futex_create(mutex);

    mutex->depth = 0;
    mutex->owner = 0;
}

int kos_recursive_mutex_lock(kos_recursive_mutex_t *mutex)
{
    unsigned long me = (unsigned long)tls_get(TLS_KEY_LOW_STACK);

    if (__sync_fetch_and_add(&mutex->lock, 1) == 0)
    {
        mutex->depth = 1;
        mutex->owner = me;
        return 0;
    }
    else if (mutex->owner == me)
    {
        __sync_fetch_and_sub(&mutex->lock, 1);
        ++(mutex->depth);
    }
    else
    {
        while (exchange_acquire(&mutex->lock, 2) != 0)
        {
            _ksys_futex_wait(mutex->handle, 2, 0);
            mutex->depth = 1;
            mutex->owner = me;
        }
    }

    return 0;
}

int kos_recursive_mutex_unlock (kos_recursive_mutex_t *mutex)
{
    --(mutex->depth);

    if (mutex->depth == 0)
    {
        int prev;

        prev = exchange_release(&mutex->lock, 0);

        if (prev != 1)
        {
            _ksys_futex_wake(mutex->handle, 1);
        }
        mutex->owner = 0;
    }

    return 0;
}

int kos_recursive_mutex_destroy(kos_recursive_mutex_t *mutex)
{
    return _ksys_futex_destroy(mutex->handle);
}
