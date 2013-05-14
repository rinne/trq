/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Efficient list operations for structures with one link pointer.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Apr 15 17:16:07 1998 tri
 *  Last modified: Wed Oct 10 01:04:53 2001 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 1995-1999, 2001
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
 * $Id: trq_list_x.h,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_list_x.h,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.9  2001/04/24 18:29:58  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.8  1999/12/09 05:02:52  kivinen
 *      Merged from 3.0 branch.
 *
 * Revision 1.7  1999/12/08 20:29:12  tmo
 *      Changes from the ipsec-3.0 branch.
 *
 * Revision 1.6  1999/11/24 17:17:52  tri
 *      Merged from the branch.
 *
 * Revision 1.5  1999/11/24 15:08:50  tri
 *      Merged patch that removes most of the "unused inline"
 *      warnings.
 *
 * Revision 1.4.14.3  1999/12/09 04:59:33  kivinen
 *      Added trq_*_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK
 *      prototype with __attribute__ ((unused)) so gcc will be silent
 *      even if this is unused.
 *
 * Revision 1.4.14.2  1999/11/24 14:41:43  tri
 *      Added comment.
 *
 * Revision 1.4.14.1  1999/11/24 12:57:03  tri
 *      Added a stub inline function to avoid "unused" warnings.
 *
 * Revision 1.4  1998/12/15 13:41:53  tri
 *      Renamed a few interfaces to make things more intuitive:
 *          - trq_list_rewind -> trq_list_goto_first
 *          - trq_list_end -> trq_list_goto_last
 *          - trq_list_insert_head -> trq_list_insert_last
 *          - trq_list_insert_tail -> trq_list_insert_first
 *          - trq_list_get_head -> trq_list_get_last
 *          - trq_list_get_tail -> trq_list_get_first
 *          - trq_list_join_head -> trq_list_join_after_last
 *          - trq_list_join_tail -> trq_list_join_before_first
 *
 * Revision 1.3  1998/07/06 14:02:16  tri
 *      Removed a few unused variables.
 *
 * Revision 1.2  1998/07/06 13:51:12  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:55  tri
 *      Added to CVS.
 *
 * Revision 1.26  1998/07/06 09:31:32  tri
 *      Added endlog.
 *
 * Revision 1.25  1998/06/22 16:24:04  tri
 *      Make function versions of the inline stuff compile from
 *      the automagically generated source.
 *
 * Revision 1.24  1998/06/22 08:38:08  tri
 *      Fixed swap operations.
 *
 * Revision 1.23  1998/06/22 07:23:31  tri
 *      Fixed trq_list_member.
 *
 * Revision 1.22  1998/06/22 07:19:26  tri
 *      Fixed trq_list_member.
 *
 * Revision 1.21  1998/06/22 07:15:32  tri
 *      trq_list_member_p -> trq_list_member
 *      trq_deque_member_p -> trq_deque_member
 *      trq_list_pointer_valid_p -> trq_list_pointer_valid
 *      trq_list_compatible_p -> trq_list_compatible
 *      trq_deque_compatible_p -> trq_deque_compatible
 *
 * Revision 1.20  1998/06/21 20:38:06  tri
 *      Added trq_list_insert_nth.
 *
 * Revision 1.19  1998/06/18 13:55:58  tri
 *      Fixed nth again.
 *
 * Revision 1.18  1998/06/18 13:36:56  tri
 *      Fixed joins.
 *
 * Revision 1.17  1998/06/18 13:24:58  tri
 *      Fixed nth.
 *
 * Revision 1.16  1998/06/18 13:17:35  tri
 *      Added trq_list_get_nth.
 *
 * Revision 1.15  1998/06/18 07:22:12  tri
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
 * Revision 1.14  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.13  1998/04/22 22:46:40  tri
 *      Added one missing return type.  It defaulted correctly
 *      to int anyway.
 *
 * Revision 1.12  1998/04/22 22:26:15  tri
 *      Added rewind_to and rewind_find.
 *
 * Revision 1.11  1998/04/20 20:47:17  tri
 *      TRQ_*_NO_ITEM -> TRQ_NO_ITEM
 *
 * Revision 1.10  1998/04/20 15:05:06  tri
 *      SNAFU in search and replace.
 *
 * Revision 1.9  1998/04/20 14:55:17  tri
 *      Final solution for deque basic operation names.
 *      Now they are trq_deque_insert_head, trq_deque_insert_tail,
 *      trq_deque_get_head and trq_deque_get_tail.  After intensive
 *      customer survey, this seems to be the most intuitive way.
 *
 * Revision 1.8  1998/04/18 11:01:51  tri
 *      Formatting.
 *
 * Revision 1.7  1998/04/18 10:29:47  tri
 *      Renamed API functions to more intuitive form:
 *      trq_deque_put_last to trq_deque_put,
 *      trq_deque_put to trq_deque_push,
 *      trq_deque_get_tail to trq_deque_pop,
 *      trq_deque_mapcar_bw to trq_deque_mapcar_reverse,
 *      trq_list_mapcar_bw to trq_list_mapcar_reverse,
 *      trq_deque_join_bw to trq_deque_join_tail and
 *      trq_deque_join to trq_deque_join_head.
 *
 * Revision 1.6  1998/04/17 16:51:51  tri
 *      Joins for lists.
 *
 * Revision 1.5  1998/04/17 16:19:08  tri
 *      Added deque_to_list and list_to_deque.
 *
 * Revision 1.4  1998/04/17 15:24:52  tri
 *      Added trq_list_mapcar_reverse.
 *
 * Revision 1.3  1998/04/17 15:18:20  tri
 *      Fixed almost all list operations.  List pointer
 *      stuff was really buggy.
 *
 * Revision 1.2  1998/04/17 08:51:57  tri
 *      Types `deque' and `list' and constants `DEQUE_NO_ITEM'
 *      and `LIST_NO_ITEM' prefixed with `trq_' and `TRQ_'
 *      accordingly.
 *
 * Revision 1.1  1998/04/16 14:39:42  tri
 *      Initial revision
 *
 * $EndLog$
 */
#ifndef __TRQ_LIST_X__H__
#define __TRQ_LIST_X__H__ 1

/*
 * This file is included from the file trq_list.h or trq_list_x.c
 * All other use is most likely a bug!  This file contains
 * list functions that cannot be implemented as macros.
 *
 * The idea is as follows:
 *
 *   1) Functions marked with __TRQ__INLINE__FUNCTION__ prefix
 *      compile as normal library functions when this file is
 *      included from trq_list_x.c.  These functions are included
 *      to the library.
 *
 *   2) If the compiler supports inline functions and user
 *      haven't forbidden macro (and inline) versions by defining
 *      TRQ_USE_FUNCTIONS to be greater than zero, these
 *      functions are declared inline when the header trq_list.h
 *      includes this file.
 *
 *   3) This file is never included from outside trq_list.h.
 *
 *   4) Prototypes are provided if inlines are not supported.
 */


#ifdef __TRQ_LIST_X_NUM__C__
#  ifdef __TRQ__INLINE__FUNCTION__
#    undef __TRQ__INLINE__FUNCTION__
#  endif
#  define __TRQ__INLINE__FUNCTION__ /*NOTHING*/
#endif /* __TRQ_LIST_X_NUM__C__ */

#ifdef __DEQUE__STATIC__FUNCTION__
#  undef __DEQUE__STATIC__FUNCTION__
#endif
#ifndef __TRQ_LIST_X_NUM__C__
#  define __DEQUE__STATIC__FUNCTION__ static
#else /* ! __TRQ_LIST_X_NUM__C__ */
#  define __DEQUE__STATIC__FUNCTION__ /*NOTHING*/
#endif /* ! __TRQ_LIST_X_NUM__C__ */

#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_001__C__)))

int trq_list_member(trq_list *L, void *b);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_member(trq_list *L, void *b)
{
    int r;

    if (L->c == b)
        return (trq_deque_length(&(L->tail)) + 1);
    else if (0 != (r = trq_deque_member(&(L->tail), b)))
        return r;
    else if (0 != (r = trq_deque_member(&(L->head), b)))
        return (r + trq_deque_length(&(L->tail)) + (L->c ? 1 : 0));
    return 0;
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_002__C__)))

int trq_list_fw(trq_list *L, int n);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_fw(trq_list *L, int n)
{
    int i;

    if (!(L->c))
        return 0;
    for (i = 0; i < n; i++) {
        trq_deque_insert_head(&(L->tail), L->c);
        L->c = trq_deque_get_tail(&(L->head));
        if (!(L->c))
            return 0;
    }
    return 1;
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_003__C__)))

int trq_list_bw(trq_list *L, int n);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_bw(trq_list *L, int n)
{
    int i;

    if (!(L->c))
        return 0;
    for (i = 0; i < n; i++) {
        trq_deque_insert_tail(&(L->head), L->c);
        L->c = trq_deque_get_head(&(L->tail));
        if (!(L->c))
            return 0;
    }
    return 1;
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_004__C__)))

int trq_list_reverse(trq_list *L);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_reverse(trq_list *L)
{
    trq_deque q;

    (void)trq_deque_reverse(&(L->head));
    (void)trq_deque_reverse(&(L->tail));
    q = L->head;
    L->head = L->tail;
    L->tail = q;
    return trq_list_length(L);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_005__C__)))

int trq_list_mapcar(trq_list *L,
                    trq_mapper mapper,
                    void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_mapcar(trq_list *L,
                    trq_mapper mapper,
                    void *context)
{
    trq_deque_mapcar(&(L->tail), mapper, context);
    if (trq_list_pointer_valid(L))
        L->c = mapper(L->c, context);
    trq_deque_mapcar(&(L->head), mapper, context);
    return trq_list_length(L);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_006__C__)))

int trq_list_mapcar_reverse(trq_list *L,
                            trq_mapper mapper,
                            void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_mapcar_reverse(trq_list *L,
                            trq_mapper mapper,
                            void *context)
{
    trq_deque_mapcar_reverse(&(L->head), mapper, context);
    if (trq_list_pointer_valid(L))
        L->c = mapper(L->c, context);
    trq_deque_mapcar_reverse(&(L->tail), mapper, context);
    return trq_list_length(L);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_007__C__)))

int trq_list_to_deque(trq_deque *Q, trq_list *L);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_to_deque(trq_deque *Q, trq_list *L)
{
    trq_deque_init_with_offset(Q, L->head.off);
    *Q = L->tail;
    if (trq_list_pointer_valid(L))
        trq_deque_insert_head(Q, L->c);
    trq_deque_join_head(Q, &(L->head));
    trq_list_clear(L);
    return trq_deque_length(Q);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_008__C__)))

int trq_deque_to_list(trq_list *L, trq_deque *Q);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_to_list(trq_list *L, trq_deque *Q)
{
    trq_deque_init_with_offset(&(L->head), Q->off);
    L->c = TRQ_NO_ITEM;
    L->tail = *Q;
    trq_deque_clear(Q);
    return trq_list_length(L);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_009__C__)))

int trq_list_join_after_last(trq_list *L1, trq_list *L2);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_join_after_last(trq_list *L1, trq_list *L2)
{
    trq_deque q;

    trq_list_to_deque(&q, L2);
    trq_deque_join_head(&(L1->head), &q);
    return trq_list_length(L1);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_010__C__)))

int trq_list_join_before_first(trq_list *L1, trq_list *L2);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_join_before_first(trq_list *L1, trq_list *L2)
{
    trq_deque q;

    trq_list_to_deque(&q, L2);
    trq_deque_join_tail(&(L1->tail), &q);
    return trq_list_length(L1);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_011__C__)))

int trq_list_rewind_to(trq_list *L, void *item);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_rewind_to(trq_list *L, void *item)
{
    int r;

    if (trq_list_pointer_valid(L) && (item == trq_list_current(L))) {
        return (trq_deque_length(&(L->head)) + 1);
    } else {
        trq_list_goto_first(L);
        for (r = 1; trq_list_pointer_valid(L); r++)
            if (item == trq_list_current(L))
                return r;
            else
                trq_list_fw(L, 1);
        return 0;
    }
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_012__C__)))

int trq_list_rewind_find(trq_list *L, trq_test test, void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_rewind_find(trq_list *L, trq_test test, void *context)
{
    int r;

    trq_list_goto_first(L);
    for (r = 1; trq_list_pointer_valid(L); r++)
        if (test(trq_list_current(L), context))
            return r;
        else
            trq_list_fw(L, 1);
    return 0;
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_013__C__)))

void *trq_list_get_nth(trq_list *L, int nth);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void *trq_list_get_nth(trq_list *L, int nth)
{
    int tl;
    void *r;

    if ((nth < 1) || (trq_list_length(L) < nth))
        return TRQ_NO_ITEM;
    tl = trq_deque_length(&(L->tail));
    if (nth <= tl)
        return trq_deque_get_nth(&(L->tail), nth);
    if ((nth == (tl + 1)) && trq_list_pointer_valid(L)) {
        r = trq_list_current(L);
        L->c = TRQ_NO_ITEM;
        return r;
    }
    return trq_deque_get_nth(&(L->head), nth - (tl +
                                                (trq_list_pointer_valid(L) ?
                                                 1 :
                                                 0)));
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_014__C__)))

int trq_list_insert_nth(trq_list *L, int nth, void *item);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_insert_nth(trq_list *L, int nth, void *item)
{
    if ((nth < 1) || (nth > (trq_list_length(L) + 1)))
        return 0;

    if (nth <= (trq_deque_length(&(L->tail)) + 1))
        return trq_deque_insert_nth(&(L->tail), nth, item);

    return trq_deque_insert_nth(&(L->head),
                                (nth - (trq_deque_length(&(L->tail)) +
                                        (trq_list_pointer_valid(L)
                                         ? 1
                                         : 0))),
                                item);
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_015__C__)))

int trq_list_swap(trq_list *L, void *item1, void *item2);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_list_swap(trq_list *L, void *item1, void *item2)
{
    void *i1, *i2;
    int x1, x2, l1, l2;

    if (trq_list_pointer_valid(L) && ((trq_list_current(L) == item1) ||
                                      (trq_list_current(L) == item2))) {
        if (trq_list_current(L) == item1) {
            i1 = item1;
            i2 = item2;
        } else {
            i1 = item2;
            i2 = item1;
        }
        if (0 != (x2 = trq_deque_member(&(L->tail), i2))) {
            trq_deque_remove(&(L->tail), i2);
            trq_deque_insert_nth(&(L->tail), x2, i1);
            L->c = i2;
        } else if (0 != (x2 = trq_deque_member(&(L->head), i2))) {
            trq_deque_remove(&(L->head), i2);
            trq_deque_insert_nth(&(L->head), x2, i1);
            L->c = i2;
        } else {
            return 0;
        }
    }

    if (0 != (x1 = trq_deque_member(&(L->tail), item1)))
        l1 = 1;
    else if (0 != (x1 = trq_deque_member(&(L->head), item1)))
        l1 = 2;
    else
        return 0;

    if (0 != (x2 = trq_deque_member(&(L->tail), item2)))
        l2 = 1;
    else if (0 != (x2 = trq_deque_member(&(L->head), item2)))
        l2 = 2;
    else
        return 0;

    if (l1 == l2) {
        if (l1 == 1)
            return trq_deque_swap(&(L->tail), item1, item2);
        else
            return trq_deque_swap(&(L->head), item1, item2);
    }
    if (l1 == 1) {
        i1 = item1;
        i2 = item2;
    } else {
        i1 = item2;
        i2 = item1;
        x1 ^= x2;
        x2 ^= x1;
        x1 ^= x2;
    }
    trq_deque_remove(&(L->tail), i1);
    trq_deque_remove(&(L->head), i2);
    trq_deque_insert_nth(&(L->tail), x1, i2);
    trq_deque_insert_nth(&(L->head), x2, i1);
    return 1;
}

#endif


#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__) && (! defined (__TRQ_LIST_X_016__C__)))

void *trq_list_find(trq_list *L, trq_test test, void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void *trq_list_find(trq_list *L, trq_test test, void *context)
{
    void *r;

    r = trq_deque_find(&(L->tail), test, context);
    if (r != TRQ_NO_ITEM)
        return r;

    if (trq_list_pointer_valid(L)) {
        r = trq_list_current(L);
        if (test(r, context)) {
            L->c = TRQ_NO_ITEM;
            return r;
        }
    }

    r = trq_deque_find(&(L->head), test, context);
    if (r != TRQ_NO_ITEM)
        return r;

    return TRQ_NO_ITEM;
}

#endif

#if ((! defined (__TRQ_LIST_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_LIST_X_NUM__C__))

/* No trq_list_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK needed here */

#else

#ifdef __GNUC__
__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void trq_list_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK(int do_not_set,
                                                       trq_deque *Q,
                                                       trq_list *L,
                                                       trq_test t,
                                                       trq_mapper m,
                                                       int i,
                                                       void *v)
     __attribute__ ((unused));
#endif /* __GNUC__ */

/* The code within following function is nonsense.  It is not to be called
   at any time.  The sole purpose is to avoid annoying warnings that some
   systems give from unused inline functions. */

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void trq_list_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK(int do_not_set,
                                                       trq_deque *Q,
                                                       trq_list *L,
                                                       trq_test t,
                                                       trq_mapper m,
                                                       int i,
                                                       void *v)
{
  if (do_not_set != 0)
    {
      trq_list_member(L, v);
      trq_list_fw(L, i);
      trq_list_bw(L, i);
      trq_list_reverse(L);
      trq_list_mapcar(L, m, v);
      trq_list_mapcar_reverse(L, m, v);
      trq_list_to_deque(Q, L);
      trq_deque_to_list(L, Q);
      trq_list_join_after_last(L, L);
      trq_list_join_before_first(L, L);
      trq_list_rewind_to(L, v);
      trq_list_rewind_find(L, t, v);
      trq_list_get_nth(L, i);
      trq_list_insert_nth(L, i, v);
      trq_list_swap(L, v, v);
      trq_list_find(L, t, v);
    }
  return;
}

#endif

#endif /* !__TRQ_LIST_X__H__ */
/* eof (trq_list_x.h) */
