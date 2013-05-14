/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  Functions that can be implemented also as macros.
 *  ----------------------------------------------------------------------
 *  Created      : Sat Nov 18 11:12:23 1995 tri
 *  Last modified: Tue May 14 20:24:38 2013 tri
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

#define __TRQ_DEQUE__C__ 1

#include <trq_deque.h>

void trq_deque_clear(trq_deque *Q)
{
    (void)__trq_deque_clear(Q);
}

int trq_deque_empty_p(trq_deque *Q)
{
    return __trq_deque_empty_p(Q);
}

int trq_deque_insert_tail(trq_deque *Q, void *b)
{
    return __trq_deque_insert_tail(Q, b);
}

void *trq_deque_get_head(trq_deque *Q)
{
    return __trq_deque_get_head(Q);
}

int trq_deque_insert_head(trq_deque *Q, void *b)
{
    return __trq_deque_insert_head(Q, b);
}

void *trq_deque_get_tail(trq_deque *Q)
{
    return __trq_deque_get_tail(Q);
}

int trq_deque_length(trq_deque *Q)
{
    return __trq_deque_length(Q);
}

int trq_deque_reverse(trq_deque *Q)
{
    return __trq_deque_reverse(Q);
}

int trq_deque_compatible(trq_deque *Q1, trq_deque *Q2)
{
    return __trq_deque_compatible(Q1, Q2);
}

void trq_deque_init_with_offset(trq_deque *Q, trq_p_i_t o)
{
    (void)__trq_deque_init_with_offset(Q, o);
}

/* eof (trq_deque.c) */
