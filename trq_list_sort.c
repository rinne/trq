/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  List for struct type with only one link pointer (x->next).
 *  Sorting of the list.
 *  ----------------------------------------------------------------------
 *  Created      : Sun Apr 19 16:01:09 1998 tri
 *  Last modified: Wed Oct 10 01:03:28 2001 tri
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
 * $Id: trq_list_sort.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_list_sort.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.10  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.9  1999/10/21 00:33:38  huima
 *      <trq_conf.h> ==> "trq_conf.h"
 *
 * Revision 1.8  1998/10/23 21:19:50  kivinen
 *      Removed sshincludes.h. This file cannot include it, because it
 *      doesn't belong to the distribution. Changed the
 *      SSHDIST_WINDOWS to WINDOWS, because if I have understood
 *      correctly the sshincludes.h was included only to the that one
 *      define.
 *
 * Revision 1.7  1998/10/23 12:52:26  ranki
 *      Added #include "sshincludes.h". These files ceased to compile in
 *      Visual C++ without sshincludes.h
 *
 * Revision 1.6  1998/10/01 23:28:21  kivinen
 *      Removed sshincludes.h.
 *
 * Revision 1.5  1998/10/01 17:03:56  vecna
 *      IPSEC 1.2 Compiles in Windows OK
 *
 * Revision 1.4  1998/08/19 00:30:11  sjl
 *      Added trq_conf_win.h (which contains Windows-specific options) and
 *      added #ifndef SSHDIST_WINDOWS to relevant parts of code to port it
 *      to Windows.
 *
 * Revision 1.3  1998/07/19 12:42:18  tri
 *      Fixed annoying typo in the log entry.
 *
 * Revision 1.2  1998/07/06 13:51:11  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:53  tri
 *      Added to CVS.
 *
 * Revision 1.14  1998/07/06 09:31:13  tri
 *      Added endlog.
 *
 * Revision 1.13  1998/06/23 07:39:27  tri
 *      Added possbility to define small objects in trq_conf.h.
 *
 * Revision 1.12  1998/06/22 16:45:55  tri
 *      Fixed _p call that was forgotten.
 *
 * Revision 1.11  1998/06/22 16:27:29  tri
 *      Removed _p from in_order function name.
 *
 * Revision 1.10  1998/06/22 07:15:32  tri
 *      trq_list_member_p -> trq_list_member
 *      trq_deque_member_p -> trq_deque_member
 *      trq_list_pointer_valid_p -> trq_list_pointer_valid
 *      trq_list_compatible_p -> trq_list_compatible
 *      trq_deque_compatible_p -> trq_deque_compatible
 *
 * Revision 1.9  1998/06/18 14:31:34  tri
 *      Minor cosmetic fix.
 *
 * Revision 1.8  1998/06/18 12:28:40  tri
 *      Fixed in_order_p.
 *
 * Revision 1.7  1998/06/18 08:37:14  tri
 *      Added trq_list_in_order_p.
 *
 * Revision 1.6  1998/06/18 07:22:12  tri
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
 * Revision 1.5  1998/06/12 21:24:19  tri
 *      Fixed previous.
 *
 * Revision 1.4  1998/06/12 21:20:05  tri
 *      Added trq_list_insert_in_order.
 *
 * Revision 1.3  1998/04/23 17:52:51  tri
 *      Added insertion sort.
 *
 * Revision 1.2  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.1  1998/04/22 22:00:08  tri
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
