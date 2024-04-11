/*
 * Copyright (C) KolibriOS team 2024. All rights reserved.
 * Distributed under terms of the GNU General Public License
*/

#ifndef _DIRENT_H_
#define _DIRENT_H_

#include <sys/types.h>
#include <sys/cdefs.h>
#include <sys/ksys.h>

_BEGIN_STD_C

#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200809
enum {
    DT_UNKNOWN = 0,
#define DT_UNKNOWN DT_UNKNOWN
    DT_FIFO = 1,
#define DT_FIFO DT_FIFO
    DT_CHR = 2,
#define DT_CHR DT_CHR
    DT_DIR = 4,
#define DT_DIR DT_DIR
    DT_BLK = 6,
#define DT_BLK DT_BLK
    DT_REG = 8,
#define DT_REG DT_REG
    DT_LNK = 10,
#define DT_LNK DT_LNK
    DT_SOCK = 12,
#define DT_SOCK DT_SOCK
    DT_WHT = 14
#define DT_WHT DT_WHT
};
#endif /* __BSD_VISIBLE || __POSIX_VISIBLE >= 200809 */

#if __BSD_VISIBLE
#define MAXNAMLEN KSYS_FNAME_UTF8_SIZE
#endif /* __BSD_VISIBLE */

struct dirent {
    ino_t    d_ino;
    unsigned d_type;
    char     d_name[KSYS_FNAME_UTF8_SIZE];
};

typedef struct {
    char*           path;
    uint32_t        pos;
    struct dirent   last_entry;
} DIR;

DIR* _DEFUN(opendir, (name), const char *name);
int  _DEFUN(closedir, (dirp), register DIR *dirp);
void _DEFUN(rewinddir, (dirp), DIR *dirp);
struct dirent *_DEFUN(readdir, (dirp), register DIR *dirp);

#if defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
void _DEFUN(seekdir, (dirp, loc), DIR *dirp _AND long loc);
long _DEFUN(telldir, (dirp), DIR *dirp);
#endif

_END_STD_C

#endif /* _DIRENT_H_ */
