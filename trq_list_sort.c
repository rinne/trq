/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  List for struct type with only one link pointer (x->next).
 *  Sorting of the list.
 *  ----------------------------------------------------------------------
 *  Created      : Sun Apr 19 16:01:09 1998 tri
 *  Last modified: Tue May 14 20:22:30 2013 tri
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
#define TRQ_USE_FUNCTIONS __TRQ__SMALL__OBJECTS__
#else
#define TRQ_USE_FUNCTIONS 0
#endif

#include <trq_list.h>

#ifndef __TRQ__INLINE__FUNCTION__
#  define __TRQ__INLINE__FUNCTION__ /*NOTHING*/
#endif

/*
 * Quicksort.
 */

int trq_list_quicksort(trq_list *L,
                       trq_compare test,
                       void *context)
{
    trq_deque q;

    trq_list_to_deque(&q, L);
    trq_deque_quicksort(&q, test, context);
    trq_deque_to_list(L, &q);
    return trq_list_length(L);
}

/*
 * Mergesort
 */

int trq_list_mergesort(trq_list *L,
                       trq_compare test,
                       void *context)
{
    trq_deque q;

    trq_list_to_deque(&q, L);
    trq_deque_mergesort(&q, test, context);
    trq_deque_to_list(L, &q);
    return trq_list_length(L);
}

/*
 * Bubblesort
 */
int trq_list_bubblesort(trq_list *L,
                        trq_compare test,
                        void *context)
{
    trq_deque q;

    trq_list_to_deque(&q, L);
    trq_deque_bubblesort(&q, test, context);
    trq_deque_to_list(L, &q);
    return trq_list_length(L);
}

/*
 * Insertionsort
 */
int trq_list_insertionsort(trq_list *L,
                           trq_compare test,
                           void *context)
{
    trq_deque q;

    trq_list_to_deque(&q, L);
    trq_deque_insertionsort(&q, test, context);
    trq_deque_to_list(L, &q);
    return trq_list_length(L);
}

/*
 * Item insertion into ordered deque.
 */
int trq_list_insert_in_order(trq_list *L,
                             void *item,
                             trq_compare test,
                             void *context)
{
    if (!trq_list_pointer_valid(L)) {
        trq_deque_join_tail(&(L->head), &(L->tail));
        trq_deque_insert_in_order(&(L->head), item, test, context);
    } else if (test(trq_list_current(L), item, context) <= 0) {
        trq_deque_insert_in_order(&(L->head), item, test, context);
    } else {
        trq_deque_insert_in_order(&(L->tail), item, test, context);
    }
    return trq_list_length(L);
}

/*
 * Check if list is in order?
 */
int trq_list_in_order(trq_list *L,
                      trq_compare test,
                      void *context)
{
    void *hlp;

    if (! trq_list_pointer_valid(L)) {
        trq_deque_join_tail(&(L->head), &(L->tail));
        return trq_deque_in_order(&(L->head), test, context);
    } else {
        if (! trq_deque_in_order(&(L->tail), test, context))
            return 0;
        if (! trq_deque_in_order(&(L->head), test, context))
            return 0;
        if (! trq_deque_empty_p(&(L->tail))) {
            hlp = trq_deque_get_head(&(L->tail));
            if (test(hlp, L->c, context) > 0) {
                trq_deque_insert_head(&(L->tail), hlp);
                return 0;
            }
            trq_deque_insert_head(&(L->tail), hlp);
        }
        if (! trq_deque_empty_p(&(L->head))) {
            hlp = trq_deque_get_tail(&(L->head));
            if (test(L->c, hlp, context) > 0) {
                trq_deque_insert_tail(&(L->head), hlp);
                return 0;
            }
            trq_deque_insert_tail(&(L->head), hlp);
        }
        return 1;
    }
}

/* eof (trq_list_sort.c) */
