/* 
* Copyright (C) KolibriOS team 2016-2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#ifndef _SYS_KOS_TLS_H_
#define _SYS_KOS_TLS_H_

/* TLS reserved keys */
#define TLS_KEY_PID         0
#define TLS_KEY_TID         4
#define TLS_KEY_LOW_STACK   8
#define TLS_KEY_HIGH_STACK 12
#define TLS_KEY_LIBC       16

#ifndef __ASSEMBLER__

#ifdef __cplusplus
extern "C" {
#endif

void kos_tls_init();

unsigned int kos_tls_alloc();
int kos_tls_free(unsigned int key);

int kos_tls_set(unsigned int key, void *val);
void *kos_tls_get(unsigned int key);

#ifdef __cplusplus
}
#endif

#endif /*!__ASSEMBLER__ */

#endif /* _SYS_KOS_TLS_H_ */
