/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  Sorting of the deque.
 *  ----------------------------------------------------------------------
 *  Created      : Sun Apr 19 16:01:09 1998 tri
 *  Last modified: Tue May 14 20:23:57 2013 tri
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

#include <trq_deque.h>

#ifndef __TRQ__INLINE__FUNCTION__
#  define __TRQ__INLINE__FUNCTION__ /*NOTHING*/
#endif

/*
 * Recursive quicksort.
 */

static
__TRQ__INLINE__FUNCTION__
int trq_deque_quicksort_partition(trq_deque *q1, 
                                  trq_deque *q2,
                                  trq_deque *Q,
                                  trq_compare test,
                                  void *context)
{
    void *p, *h;

    trq_deque_init_with_offset(q1, Q->off);
    trq_deque_init_with_offset(q2, Q->off);

    if (trq_deque_empty_p(Q))
        return 0;

    p = trq_deque_get_head(Q);

    while (TRQ_NO_ITEM != (h = trq_deque_get_head(Q)))
        if (test(p, h, context) <= 0)
            trq_deque_insert_head(q1, h);
        else
            trq_deque_insert_head(q2, h);

    if (trq_deque_length(q2) < trq_deque_length(q1))
        trq_deque_insert_head(q2, p);
    else
        trq_deque_insert_head(q1, p);

    return trq_deque_length(q1);
}

int trq_deque_quicksort(trq_deque *Q,
                        trq_compare test,
                        void *context)
{
    trq_deque q1, q2;

    if (trq_deque_length(Q) < 2)
        return trq_deque_length(Q);
    trq_deque_quicksort_partition(&q1, &q2, Q, test, context);
    trq_deque_quicksort(&q1, test, context);    
    trq_deque_quicksort(&q2, test, context);    
    trq_deque_join_tail(&q1, &q2);
    *Q = q1;
    return trq_deque_length(Q);
}

/*
 * Mergesort
 */

static
__TRQ__INLINE__FUNCTION__
int trq_deque_mergesort_split(trq_deque *q1, 
                              trq_deque *q2, 
                              trq_deque *Q)
{
    void *h;
    int i;

    trq_deque_init_with_offset(q1, Q->off);
    trq_deque_init_with_offset(q2, Q->off);
    
    for (i = (trq_deque_length(Q) / 2); i > 0; i--) {
        h = trq_deque_get_head(Q);
        trq_deque_insert_tail(q2, h);
    }
    *q1 = *Q;
    trq_deque_clear(Q);
    return trq_deque_length(q1);
}

static
__TRQ__INLINE__FUNCTION__
int trq_deque_mergesort_merge(trq_deque *Q, 
                              trq_deque *q1, 
                              trq_deque *q2,
                              trq_compare test,
                              void *context)
{
    void *h1, *h2;

    trq_deque_init_with_offset(Q, q1->off);

    h1 = trq_deque_get_tail(q1);
    h2 = trq_deque_get_tail(q2);
    while (h1 || h2) {
        if (!h1) {
            trq_deque_insert_head(Q, h2);
            h2 = trq_deque_get_tail(q2);
        } else if (!h2) {
            trq_deque_insert_head(Q, h1);
            h1 = trq_deque_get_tail(q1);
        } else {
            if (test(h1, h2, context) >= 0) {
                trq_deque_insert_head(Q, h2);
                h2 = trq_deque_get_tail(q2);
            } else {
                trq_deque_insert_head(Q, h1);
                h1 = trq_deque_get_tail(q1);
            }
        }
    }
    return trq_deque_length(Q);
}

int trq_deque_mergesort(trq_deque *Q,
                        trq_compare test,
                        void *context)
{
    trq_deque q1, q2;

    if (trq_deque_length(Q) < 2)
        return trq_deque_length(Q);
    trq_deque_mergesort_split(&q1, &q2, Q);
    trq_deque_mergesort(&q1, test, context);   
    trq_deque_mergesort(&q2, test, context);
    trq_deque_mergesort_merge(Q, &q1, &q2, test, context);
    return trq_deque_length(Q);
}

/*
 * Bubblesort
 */

int trq_deque_bubblesort(trq_deque *Q,
                         trq_compare test,
                         void *context)
{
    void *h1, *h2;
    trq_deque q;
    int cont_p;

    if (trq_deque_length(Q) < 2)
        return trq_deque_length(Q);

    trq_deque_init_with_offset(&q, Q->off);

    do {
        cont_p = 0;
        h1 = trq_deque_get_tail(Q);
        while (TRQ_NO_ITEM != (h2 = trq_deque_get_tail(Q)))
            if (test(h1, h2, context) <= 0) {
                trq_deque_insert_head(&q, h1);
                h1 = h2;
            } else {
                trq_deque_insert_head(&q, h2);
                cont_p = 1;
            }
        trq_deque_insert_head(&q, h1);
        *Q = q;
        trq_deque_clear(&q);
    } while (cont_p);
    return trq_deque_length(Q);
}

/*
 * Insertionsort
 */

int trq_deque_insertionsort(trq_deque *Q,
                            trq_compare test,
                            void *context)
{
    void *h1, *h2;
    trq_deque q1, q2;

    if (trq_deque_length(Q) < 2)
        return trq_deque_length(Q);

    trq_deque_init_with_offset(&q1, Q->off);
    trq_deque_init_with_offset(&q2, Q->off);

    while (TRQ_NO_ITEM != (h1 = trq_deque_get_tail(Q))) {
        while (TRQ_NO_ITEM != (h2 = trq_deque_get_head(&q1))) {
            if (test(h1, h2, context) >= 0) {
                trq_deque_insert_tail(&q2, h1);
                trq_deque_insert_tail(&q2, h2);
                trq_deque_join_tail(&q2, &q1);
                break;
            } else {
                trq_deque_insert_tail(&q2, h2);
            }
        }
        if (TRQ_NO_ITEM == h2)
            trq_deque_insert_tail(&q2, h1);
        q1 = q2;
        trq_deque_clear(&q2);
    }
    *Q = q1;
    return trq_deque_length(Q);
}

/*
 * Item insertion into ordered deque.
 */
int trq_deque_insert_in_order(trq_deque *Q,
                              void *item,
                              trq_compare test,
                              void *context)
{
    trq_deque head_q, tail_q;
    void *hlp;

    if (trq_deque_empty_p(Q)) {
        trq_deque_insert_tail(Q, item);
        return trq_deque_length(Q);
    }

    trq_deque_init_with_offset(&head_q, Q->off);
    trq_deque_init_with_offset(&tail_q, Q->off);

    while (1) {
        hlp = trq_deque_get_head(Q);
        if (hlp == TRQ_NO_ITEM) {
            trq_deque_insert_tail(&head_q, item);
            goto join_and_return;
        }

        if (test(item, hlp, context) >= 0) {
            trq_deque_insert_tail(&head_q, item);
            trq_deque_insert_tail(&head_q, hlp);
            goto join_and_return;
        }
        trq_deque_insert_tail(&head_q, hlp);

        hlp = trq_deque_get_tail(Q);
        if (hlp == TRQ_NO_ITEM) {
            trq_deque_insert_head(&tail_q, item);
            goto join_and_return;
        }

        if (test(item, hlp, context) <= 0) {
            trq_deque_insert_head(&tail_q, item);
            trq_deque_insert_head(&tail_q, hlp);
            goto join_and_return;
        }
        trq_deque_insert_head(&tail_q, hlp);
    }

 join_and_return:
    trq_deque_join_head(Q, &head_q);
    trq_deque_join_tail(Q, &tail_q);
    return trq_deque_length(Q);
}

/*
 * Check if deque is in order?
 */
int trq_deque_in_order(trq_deque *Q,
                       trq_compare test,
                       void *context)
{
    void *hlp1, *hlp2;
    trq_deque q;

    trq_deque_init_with_offset(&q, Q->off);

    if (trq_deque_empty_p(Q))
        return 1;

    hlp2 = trq_deque_get_tail(Q);

    while ((hlp1 = trq_deque_get_tail(Q)) != TRQ_NO_ITEM) {
        if (test(hlp2, hlp1, context) > 0) {
            trq_deque_insert_head(&q, hlp2);
            trq_deque_insert_head(&q, hlp1);
            trq_deque_join_tail(Q, &q);
            return 0;
        }
        trq_deque_insert_head(&q, hlp2);
        hlp2 = hlp1;
    }

    trq_deque_insert_head(&q, hlp2);
    *Q = q;

    return 1;
}

/* eof (trq_deque_sort.c) */
