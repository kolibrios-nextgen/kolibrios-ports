
/*
 * Copyright (C) KolibriOS-NG team 2024. All rights reserved.
 * Distributed under terms of the GNU General Public License
*/

#include <unistd.h>
#include <limits.h>
#include <errno.h>

long
_DEFUN (fpathconf, (fd, name),
       __unused int fd _AND 
       int name)
{
    /* _PC_PATH_MAX is required by libstdc++ */
    static const short values[] = {
        [_PC_PATH_MAX] = PATH_MAX,
    };

    if (name >= sizeof(values)/sizeof(values[0])) {
        errno = EINVAL;
        return -1;
    }

    return values[name];
}

long
_DEFUN (pathconf, (path, name),
       __unused const char* path _AND 
       int name)
{
    return fpathconf(-1, name);
}
