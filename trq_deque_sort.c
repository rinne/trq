/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  Sorting of the deque.
 *  ----------------------------------------------------------------------
 *  Created      : Sun Apr 19 16:01:09 1998 tri
 *  Last modified: Wed Oct 10 01:03:18 2001 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 1995-1998, 2001
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
 * $Id: trq_deque_sort.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_deque_sort.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.12  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.11  1999/10/21 00:33:37  huima
 *      <trq_conf.h> ==> "trq_conf.h"
 *
 * Revision 1.10  1998/10/23 21:20:16  kivinen
 *      Removed sshincludes.h. This file cannot include it, because it
 *      doesn't belong to the distribution. Changed the
 *      SSHDIST_WINDOWS to WINDOWS, because if I have understood
 *      correctly the sshincludes.h was included only to the that one
 *      define.
 *
 * Revision 1.9  1998/10/23 12:52:20  ranki
 *      Added #include "sshincludes.h". These files ceased to compile in
 *      Visual C++ without sshincludes.h
 *
 * Revision 1.8  1998/10/01 23:28:02  kivinen
 *      Removed sshincludes.h.
 *
 * Revision 1.7  1998/10/01 17:03:55  vecna
 *      IPSEC 1.2 Compiles in Windows OK
 *
 * Revision 1.6  1998/08/19 00:30:07  sjl
 *      Added trq_conf_win.h (which contains Windows-specific options) and
 *      added #ifndef SSHDIST_WINDOWS to relevant parts of code to port it
 *      to Windows.
 *
 * Revision 1.5  1998/07/19 12:42:16  tri
 *      Fixed annoying typo in the log entry.
 *
 * Revision 1.4  1998/07/06 15:03:48  tri
 *      Removed unused variable.
 *
 * Revision 1.3  1998/07/06 14:28:18  tri
 *      Removed unused variables.
 *
 * Revision 1.2  1998/07/06 13:51:04  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:44  tri
 *      Added to CVS.
 *
 * Revision 1.21  1998/07/06 09:27:08  tri
 *      Added endlog.
 *
 * Revision 1.20  1998/06/23 07:39:35  tri
 *      Added possbility to define small objects in trq_conf.h.
 *
 * Revision 1.19  1998/06/22 16:28:02  tri
 *      Removed _p from in_order function name.
 *
 * Revision 1.18  1998/06/18 12:09:13  tri
 *      Fixed in_order_p.
 *
 * Revision 1.17  1998/06/18 07:22:12  tri
 *      Heavy rethinking of the concepts in the deque
 *      and the list.  For now on both deque and list
 *      start from `tail' and end to `head'.  Sorting
 *      functions make order ascending from tail to head.
 *      Moving list pointer forward, move it towards head
 *      and moving it backwards move it towards tail.
 *
 *      Terms head and tail are utilized also in lists
 *      replacing old `first' and `last'.
 *
 *      Now they should make sense.
 *
 * Revision 1.16  1998/06/11 18:54:59  tri
 *      Added trq_deque_in_order_p.
 *
 * Revision 1.15  1998/06/11 18:18:27  tri
 *      Added trq_deque_insert_in_order.
 *
 * Revision 1.14  1998/06/11 13:47:36  tri
 *      Fixed an annoying bug.
 *
 * Revision 1.13  1998/04/24 11:51:48  tri
 *      Removed implicit macro calls.
 *
 * Revision 1.12  1998/04/23 17:50:11  tri
 *      Added insertion sort.
 *
 * Revision 1.11  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.10  1998/04/22 21:55:39  tri
 *      Conceptual more than functional minor fix.
 *
 * Revision 1.9  1998/04/21 11:24:15  tri
 *      Typedef `callback' function types.
 *
 * Revision 1.8  1998/04/20 20:47:17  tri
 *      TRQ_*_NO_ITEM -> TRQ_NO_ITEM
 *
 * Revision 1.7  1998/04/20 17:57:39  tri
 *      Implemented bubblesort.
 *
 * Revision 1.6  1998/04/20 17:32:13  tri
 *      Statics are now also inline, if supported.
 *
 * Revision 1.5  1998/04/20 16:36:24  tri
 *      Bug in quicksort partition clobbered the length
 *      of the result.
 *
 * Revision 1.4  1998/04/20 16:16:48  tri
 *      Added mergesort.
 *
 * Revision 1.3  1998/04/20 14:55:17  tri
 *      Final solution for deque basic operation names.
 *      Now they are trq_deque_insert_tail, trq_deque_insert_head,
 *      trq_deque_get_tail and trq_deque_get_head.  After intensive
 *      customer survey, this seems to be the most intuitive way.
 *
 * Revision 1.2  1998/04/19 14:37:18  tri
 *      Prototypes.
 *
 * Revision 1.1  1998/04/19 14:22:45  tri
 *      Initial revision
 *
 * $EndLog$
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
