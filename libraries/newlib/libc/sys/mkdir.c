/*
 * Copyright (C) KolibriOS-NG team 2024. All rights reserved.
 * Distributed under terms of the GNU General Public License
*/

#include <errno.h>
#include <sys/stat.h>
#include <sys/ksys.h>

int
_DEFUN (mkdir, (path, mode),
       const char *path _AND
       __unused mode_t mode)
{
    /* File mode not supported in KolibriOS */
    int st = _ksys_mkdir(path);
    if (st) 
    {
        /* FIXME: It is necessary to convert the error code 
           of KolibriOS FS into POSIX errno */
        errno = EACCES;
        return -1;
    }

    return 0;
}
