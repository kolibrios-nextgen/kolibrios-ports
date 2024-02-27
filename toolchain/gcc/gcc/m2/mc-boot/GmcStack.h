/* do not edit automatically generated by mc from mcStack.  */
/* mcStack.def provides a stack data type and associated procedures.

Copyright (C) 2015-2023 Free Software Foundation, Inc.
Contributed by Gaius Mulley <gaius.mulley@southwales.ac.uk>.

This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GNU Modula-2 is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Modula-2; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */


#if !defined (_mcStack_H)
#   define _mcStack_H

#include "config.h"
#include "system.h"
#   ifdef __cplusplus
extern "C" {
#   endif
#include <stdbool.h>
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_mcStack_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (mcStack_stack_D)
#  define mcStack_stack_D
   typedef void *mcStack_stack;
#endif


/*
   init - create and return a stack.
*/

EXTERN mcStack_stack mcStack_init (void);

/*
   kill - deletes stack, s.
*/

EXTERN void mcStack_kill (mcStack_stack *s);

/*
   push - an address, a, onto the stack, s.
          It returns, a.
*/

EXTERN void * mcStack_push (mcStack_stack s, void * a);

/*
   pop - and return the top element from stack, s.
*/

EXTERN void * mcStack_pop (mcStack_stack s);

/*
   replace - performs a pop; push (a); return a.
*/

EXTERN void * mcStack_replace (mcStack_stack s, void * a);

/*
   depth - returns the depth of the stack.
*/

EXTERN unsigned int mcStack_depth (mcStack_stack s);

/*
   access - returns the, i, th stack element.
            The top of stack is defined by:

            access (s, depth (s)).
*/

EXTERN void * mcStack_access (mcStack_stack s, unsigned int i);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif