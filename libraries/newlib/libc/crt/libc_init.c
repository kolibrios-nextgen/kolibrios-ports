/* 
* Copyright (C) KolibriOS team 2016-2024. All rights reserved.
* Distributed under terms of the GNU General Public License
*/

#include <_ansi.h>

#include <reent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ksys.h>
#include <sys/kos_tls.h>

void* __dso_handle = NULL;

struct app_hdr
{
    char  banner[8];
    int   version;
    int   start;
    int   iend;
    int   memsize;
    int   stacktop;
    char  *cmdline;
    char  *path;
    int    __subsystem__;
};

#define SUBSYSTEM_CUI 3

#define ENV_SIZE 16
/* TODO: Make it dynamic?* */
static char* __environ[ENV_SIZE] = {0};
char **environ = &__environ[0];

extern void init_global_reent(void);
extern void init_stdio(void);

extern void __init_conio(void);
extern void __fini_conio(void);

extern int main(int argc, char **argv, char **envp);

void init_environ(void)
{
    ksys_ufile_t envfile = _ksys_load_file("/sys/settings/system.env");
    if (!envfile.data || !envfile.size)
        return;

    char *pch = strtok((char*)envfile.data, " \n\t");
    for (size_t env_pos = 0; pch != NULL && env_pos < ENV_SIZE-1; env_pos++)
    {
        environ[env_pos] = pch;
        pch = strtok(NULL, " \n\t");
    }
}

static int split_cmdline(char *cmdline, char **argv)
{
    enum quote_state
    {
        QUOTE_NONE,         /* no " active in current parm       */
        QUOTE_DELIMITER,    /* " was first char and must be last */
        QUOTE_STARTED       /* " was seen, look for a match      */
    };

    enum quote_state state;
    unsigned int argc;
    char *p = cmdline;
    char *new_arg, *start;

    argc = 0;

    for (;;)
    {
        /* skip over spaces and tabs */
        if (*p)
        {
            while (*p == ' ' || *p == '\t')
                ++p;
        }

        if (*p == '\0')
            break;

        state = QUOTE_NONE;
        if (*p == '\"' )
        {
            p++;
            state = QUOTE_DELIMITER;
        }
        new_arg = start = p;
        for (;;)
        {
            if( *p == '\"' )
            {
                p++;
                if( state == QUOTE_NONE )
                {
                    state = QUOTE_STARTED;
                }
                else
                {
                    state = QUOTE_NONE;
                }
                continue;
            }

            if (*p == ' ' || *p == '\t')
            {
                if( state == QUOTE_NONE )
                {
                    break;
                }
            }

            if (*p == '\0')
                break;

            if (*p == '\\')
            {
                if (p[1] == '\"')
                {
                    ++p;
                    if (p[-2] == '\\')
                    {
                        continue;
                    }
                }
            }
            if (argv)
            {
                *(new_arg++) = *p;
            }
            ++p;
        };

        if (argv)
        {
            argv[ argc ] = start;
            ++argc;

            /*
              The *new = '\0' is req'd in case there was a \" to "
              translation. It must be after the *p check against
              '\0' because new and p could point to the same char
              in which case the scan would be terminated too soon.
            */

            if( *p == '\0' )
            {
                *new_arg = '\0';
                break;
            }
            *new_arg = '\0';
            ++p;
        }
        else
        {
            ++argc;
            if (*p == '\0')
            {
                break;
            }
            ++p;
        }
    }

    return argc;
}

__attribute__((noreturn))
void __libc_init (void)
{
    struct app_hdr *header = NULL;
    int retval = 0;

    char **argv;
    int    argc;

    kos_tls_init();
    init_global_reent();
    init_stdio();

    if (header->__subsystem__ == SUBSYSTEM_CUI)
        __init_conio();

    if (header->cmdline[0] != 0)
    {
        argc = split_cmdline(header->cmdline, NULL) + 1;
        argv = alloca((argc+1)*sizeof(char*));
        argv[0] = header->path;

        split_cmdline(header->cmdline, argv + 1);
    }
    else
    {
        argc = 1;
        argv = alloca((argc+1) * sizeof(char*));
        argv[0] = header->path;
    }
    argv[argc] = NULL;

    init_environ();

    retval = main(argc, argv, environ);

done:
    if (header->__subsystem__ == SUBSYSTEM_CUI)
        __fini_conio();

    exit(retval);
}
