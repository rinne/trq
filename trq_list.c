/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Efficient list operations for structures with one link pointer.
 *  Functions that can be implemented also as macros.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Nov 22 13:53:13 1995 tri
 *  Last modified: Tue May 14 20:23:11 2013 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 1995-1998, 2001, 2013
 *  Timo J. Rinne <tri@iki.fi>
 *  All rights reserved.  See file COPYRIGHT for details.
 *  ----------------------------------------------------------------------
 *  Any express or implied warranties are disclaimed.  In no event
 *  shall the author be liable for any damages caused (directly or
 *  otherwise) by the use of this software.
 *
 *  Please, send your patches to <tri@iki.fi>.
 *  ----------------------------------------------------------------------
 *
 */

#ifndef WINDOWS
#include "trq_conf.h"
#else /* WINDOWS */
#include "trq_conf_win.h"
#endif /* WINDOWS */

#ifdef  TRQ_USE_FUNCTIONS
#  undef  TRQ_USE_FUNCTIONS
#endif
#ifdef __TRQ__SMALL__OBJECTS__
#  define TRQ_USE_FUNCTIONS __TRQ__SMALL__OBJECTS__
#else
#  define TRQ_USE_FUNCTIONS 0
#endif

#define __TRQ_LIST__C__ 1

#include <trq_list.h>

void trq_list_clear(trq_list *L)
{
    (void)__trq_list_clear(L);
}

int trq_list_goto_first(trq_list *L)
{
    return __trq_list_goto_first(L);
}

int trq_list_goto_last(trq_list *L)
{
    return __trq_list_goto_last(L);
}

int trq_list_length(trq_list *L)
{
    return __trq_list_length(L);
}

int trq_list_pointer_valid(trq_list *L)
{
    return __trq_list_pointer_valid(L);
}

int trq_list_pointer_invalidate(trq_list *L)
{
    return __trq_list_pointer_invalidate(L);
}

int trq_list_insert_last(trq_list *L, void *b)
{
    return __trq_list_insert_last(L, b);
}

int trq_list_insert_first(trq_list *L, void *b)
{
    return __trq_list_insert_first(L, b);
}

void *trq_list_get_last(trq_list *L)
{
    return __trq_list_get_last(L);
}

void *trq_list_get_first(trq_list *L)
{
    return __trq_list_get_first(L);
}

int trq_list_insert_before(trq_list *L, void *b)
{
    return __trq_list_insert_before(L, b);
}

int trq_list_insert_after(trq_list *L, void *b)
{
    return __trq_list_insert_after(L, b);
}

void *trq_list_get_fw(trq_list *L)
{
    return __trq_list_get_fw(L);
}

void *trq_list_get_bw(trq_list *L)
{
    return __trq_list_get_bw(L);
}

int trq_list_remove(trq_list *L, void *b)
{
    return __trq_list_remove(L, b);
}

int trq_list_compatible(trq_list *L1, trq_list *L2)
{
    return __trq_list_compatible(L1, L2);
}

void *trq_list_current(trq_list *L)
{
    return __trq_list_current(L);
}

/* eof (trq_list.c) */
