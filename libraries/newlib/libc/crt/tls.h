/* 
* Copyright (C) KolibriOS team 2016-2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#ifndef _CRT_TLS_H_
#define _CRT_TLS_H_

/* TLS reserved keys */
#define TLS_KEY_PID         0
#define TLS_KEY_TID         4
#define TLS_KEY_LOW_STACK   8
#define TLS_KEY_HIGH_STACK 12
#define TLS_KEY_LIBC       16

#ifndef __ASSEMBLER__

void tls_init();

unsigned int tls_alloc();
int tls_free(unsigned int key);

int tls_set(unsigned int key, void *val);
void *tls_get(unsigned int key);

#endif /*__ASSEMBLER__ */

#endif /* _CRT_TLS_H */
