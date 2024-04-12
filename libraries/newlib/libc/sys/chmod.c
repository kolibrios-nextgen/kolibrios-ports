/*
 * Copyright (C) KolibriOS-NG team 2024. All rights reserved.
 * Distributed under terms of the GNU General Public License
*/

#include <sys/stat.h>

int
_DEFUN (chmod, (path, mode),
       __unused const char *path _AND
       __unused mode_t mode)
{
    /* STUB! Not supported in KolibriOS */
    return 0;
}

int
_DEFUN (fchmod, (fd, mode),
       __unused int fd _AND
       __unused mode_t mode)
{
    /* STUB! Not supported in KolibriOS-NG */
    return 0;
}
