/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  ----------------------------------------------------------------------
 *  Created      : Sat Nov 18 11:12:26 1995 tri
 *  Last modified: Wed Oct 10 01:04:28 2001 tri
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
 * $Id: trq_deque_x.h,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_deque_x.h,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.12  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.11  1999/12/09 05:02:01  kivinen
 *      Merged from 3.0 branch.
 *
 * Revision 1.10  1999/12/08 20:29:03  tmo
 *      Changes from the ipsec-3.0 branch.
 *
 * Revision 1.9  1999/11/24 17:17:52  tri
 *      Merged from the branch.
 *
 * Revision 1.8  1999/11/24 15:08:49  tri
 *      Merged patch that removes most of the "unused inline"
 *      warnings.
 *
 * Revision 1.7.12.3  1999/12/09 04:59:16  kivinen
 *      Added trq_*_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK
 *      prototype with __attribute__ ((unused)) so gcc will be silent
 *      even if this is unused.
 *
 * Revision 1.7.12.2  1999/11/24 14:41:26  tri
 *      Added comment.
 *
 * Revision 1.7.12.1  1999/11/24 12:56:53  tri
 *      Added a stub inline function to avoid "unused" warnings.
 *
 * Revision 1.7  1999/01/29 16:01:01  tri
 *      Changed variable name _Q to tmpQ, since in FreeBSD
 *      _Q is mystically defined as 0x00200000L in ctype.h.
 *      This may be the case also somewhere else.
 *
 * Revision 1.6  1999/01/25 10:50:26  tri
 *      Added trq_deque_find_and_spare.
 *
 * Revision 1.5  1999/01/25 09:08:56  tri
 *      Added trq_deque_mapcar_extended and fixed tests.
 *
 * Revision 1.4  1999/01/25 06:59:06  tri
 *      Added trq_deque_mapcar_extended.
 *
 * Revision 1.3  1998/07/06 14:02:56  tri
 *      Removed a few unused variables.
 *
 * Revision 1.2  1998/07/06 13:51:05  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:45  tri
 *      Added to CVS.
 *
 * Revision 1.31  1998/07/06 09:28:59  tri
 *      Added endlog.
 *
 * Revision 1.30  1998/06/22 18:06:51  tri
 *      No inlines are used for function versions of trq_list_x.h
 *      routines.
 *
 * Revision 1.29  1998/06/22 16:35:02  tri
 *      Fixed typo.
 *
 * Revision 1.28  1998/06/22 16:24:32  tri
 *      Make function versions of the inline stuff compile from
 *      the automagically generated source.
 *
 * Revision 1.27  1998/06/22 08:38:08  tri
 *      Fixed swap operations.
 *
 * Revision 1.26  1998/06/22 07:15:32  tri
 *      trq_list_member_p -> trq_list_member
 *      trq_deque_member_p -> trq_deque_member
 *      trq_list_pointer_valid_p -> trq_list_pointer_valid
 *      trq_list_compatible_p -> trq_list_compatible
 *      trq_deque_compatible_p -> trq_deque_compatible
 *
 * Revision 1.25  1998/06/21 20:38:19  tri
 *      Fixed insert_nth.
 *
 * Revision 1.24  1998/06/21 19:03:58  tri
 *      Fixed prototype.
 *
 * Revision 1.23  1998/06/21 19:03:29  tri
 *      Added trq_deque_insert_nth.
 *
 * Revision 1.22  1998/06/18 14:01:27  tri
 *      Fixed joins and stuff.
 *
 * Revision 1.21  1998/06/18 07:22:12  tri
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
 * Revision 1.20  1998/04/23 14:16:31  tri
 *      Removed explicit macro calls.
 *
 * Revision 1.19  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.18  1998/04/23 13:27:18  tri
 *      Added trq_deque_get_nth.
 *
 * Revision 1.17  1998/04/21 14:29:37  tri
 *      test_and_get -> find
 *
 * Revision 1.16  1998/04/21 13:22:29  tri
 *      Added trq_deque_find.
 *
 * Revision 1.15  1998/04/21 11:24:27  tri
 *      Typedef `callback' function types.
 *
 * Revision 1.14  1998/04/20 20:47:17  tri
 *      TRQ_*_NO_ITEM -> TRQ_NO_ITEM
 *
 * Revision 1.13  1998/04/20 18:12:55  tri
 *      Don't use r member of deque in inline stuff.
 *      Only in macros.
 *
 * Revision 1.12  1998/04/20 15:05:06  tri
 *      SNAFU in search and replace.
 *
 * Revision 1.11  1998/04/20 14:55:17  tri
 *      Final solution for deque basic operation names.
 *      Now they are trq_deque_insert_tail, trq_deque_insert_head,
 *      trq_deque_get_tail and trq_deque_get_head.  After intensive
 *      customer survey, this seems to be the most intuitive way.
 *
 * Revision 1.10  1998/04/18 12:02:16  tri
 *      Added trq_deque_swap.
 *
 * Revision 1.9  1998/04/18 11:53:34  tri
 *      Added trq_deque_swap.
 *
 * Revision 1.8  1998/04/18 11:02:52  tri
 *      Formatting.
 *
 * Revision 1.7  1998/04/18 10:29:47  tri
 *      Renamed API functions to more intuitive form:
 *      trq_deque_put_last to trq_deque_put,
 *      trq_deque_put to trq_deque_push,
 *      trq_deque_get_head to trq_deque_pop,
 *      trq_deque_mapcar_bw to trq_deque_mapcar_reverse,
 *      trq_list_mapcar_bw to trq_list_mapcar_reverse,
 *      trq_deque_join_bw to trq_deque_join_tail and
 *      trq_deque_join to trq_deque_join_head.
 *
 * Revision 1.6  1998/04/17 16:24:42  tri
 *      Added some __DEQUE__STATIC__FUNCTION__ and
 *      __TRQ__INLINE__FUNCTION__ directives.
 *
 * Revision 1.5  1998/04/17 16:08:11  tri
 *      Joins now keep length variable correct.
 *
 * Revision 1.4  1998/04/17 15:18:41  tri
 *      Added trq_deque_mapcar_reverse.
 *
 * Revision 1.3  1998/04/17 08:51:57  tri
 *      Types `deque' and `list' and constants `DEQUE_NO_ITEM'
 *      and `LIST_NO_ITEM' prefixed with `trq_' and `TRQ_'
 *      accordingly.
 *
 * Revision 1.2  1998/04/17 08:04:40  tri
 *      trq_deque_join_head* functions no longer traverse
 *      through the `from' deque.
 *
 *      trq_deque_member_p function no longer traverse
 *      through the whole deque, if item is found.
 *
 * Revision 1.1  1998/04/16 14:39:42  tri
 *      Initial revision
 *
 * $EndLog$
 */
#ifndef __TRQ_DEQUE_X__H__
#define __TRQ_DEQUE_X__H__ 1

/*
 * This file is included from the file trq_deque.h or trq_deque_x_*.c
 * All other use is most likely a bug!  This file contains
 * list functions that cannot be implemented as macros.
 *
 * The idea is as follows:
 *
 *   1) Functions marked with __TRQ__INLINE__FUNCTION__ prefix
 *      compile as normal library functions when this file is
 *      included from list_x.c.  These functions are included
 *      to the library.
 *
 *   2) If the compiler supports inline functions and user
 *      haven't forbidden macro (and inline) versions by defining
 *      TRQ_USE_FUNCTIONS to be greater than zero, these
 *      functions are declared inline when the header list.h
 *      includes this file.
 *
 *   3) This file is never included from outside deque.h.
 *
 *   4) Prototypes are provided if inlines are not supported.
 */

#ifdef __TRQ_DEQUE_X_NUM__C__
#  ifdef __TRQ__INLINE__FUNCTION__
#    undef __TRQ__INLINE__FUNCTION__
#  endif
#  define __TRQ__INLINE__FUNCTION__ /*NOTHING*/
#endif /* __TRQ_DEQUE_X__NUM_C__ */

#ifdef __DEQUE__STATIC__FUNCTION__
#  undef __DEQUE__STATIC__FUNCTION__
#endif
#ifndef __TRQ_DEQUE_X_NUM__C__
#  define __DEQUE__STATIC__FUNCTION__ static
#else /* ! __TRQ_DEQUE_X__NUM_C__ */
#  define __DEQUE__STATIC__FUNCTION__ /*NOTHING*/
#endif /* ! __TRQ_DEQUE_X__NUM_C__ */

#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_001__C__)))

int trq_deque_remove(trq_deque *Q, void *b);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_remove(trq_deque *Q, void *b)
{
    trq_deque q;
    void *x;
    int r;

    trq_deque_init_with_offset(&q, Q->off);
    r = 0;
    while (TRQ_NO_ITEM != (x = trq_deque_get_head(Q)))
        if (x != b)
            trq_deque_insert_tail(&q, x);
        else
            r++;
    *Q = q;
    return r;
}

#endif

#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_002__C__)))

int trq_deque_join_tail(trq_deque *to, trq_deque *from);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_join_tail(trq_deque *to, trq_deque *from)
{
    void *h;

    trq_assert(trq_deque_compatible(from, to));

    if (TRQ_NO_ITEM != from->h1) {
        if (TRQ_NO_ITEM != to->h1) {
            h = to->h2;
            to->h2 = from->h2;
            _Q_NEXT_PTR(from->h1, from->off) =
                _Q_PTR_XOR(_Q_NEXT_PTR(from->h1, from->off), h);
            _Q_NEXT_PTR(h, to->off) =
                _Q_PTR_XOR(_Q_NEXT_PTR(h, to->off), from->h1);
            to->len += from->len;
        } else {
            *to = *from;
        }
        trq_deque_clear(from);
    }
    return trq_deque_length(to);
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_003__C__)))

int trq_deque_join_head(trq_deque *to, trq_deque *from);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_join_head(trq_deque *to, trq_deque *from)
{
    void *h;

    trq_assert(trq_deque_compatible(from, to));

    if (TRQ_NO_ITEM != from->h1) {
        if (TRQ_NO_ITEM != to->h1) {
            h = to->h1;
            to->h1 = from->h1;
            _Q_NEXT_PTR(from->h2, from->off) =
                _Q_PTR_XOR(_Q_NEXT_PTR(from->h2, from->off), h);
            _Q_NEXT_PTR(h, to->off) =
                _Q_PTR_XOR(_Q_NEXT_PTR(h, to->off), from->h2);
            to->len += from->len;
        } else {
            *to = *from;
        }
        trq_deque_clear(from);
    }
    return trq_deque_length(to);
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_004__C__)))

int trq_deque_member(trq_deque *Q, void *b);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_member(trq_deque *Q, void *b)
{
    trq_deque q;
    void *x;
    int r;

    trq_deque_init_with_offset(&q, Q->off);
    r = 0;
    while (TRQ_NO_ITEM != (x = trq_deque_get_tail(Q))) {
        r++;
        if (x == b) {
            trq_deque_insert_head(&q, x);
            trq_deque_join_tail(Q, &q);
            return r;
        }
        trq_deque_insert_head(&q, x);
    }
    *Q = q;
    return 0;
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_005__C__)))

int trq_deque_mapcar(trq_deque *Q,
                     trq_mapper mapper,
                     void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_mapcar(trq_deque *Q,
                     trq_mapper mapper,
                     void *context)
{
    trq_deque tmpQ, q;
    void *x;

    trq_deque_init_with_offset(&tmpQ, Q->off);
    trq_deque_init_with_offset(&q, Q->off);
    tmpQ = *Q;
    trq_deque_clear(Q);

    while (TRQ_NO_ITEM != (x = trq_deque_get_tail(&tmpQ)))
        if ((x = mapper(x, context)))
            trq_deque_insert_head(&q, x);
    *Q = q;
    return trq_deque_length(Q);
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_006__C__)))

int trq_deque_mapcar_reverse(trq_deque *Q,
                             trq_mapper mapper,
                             void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_mapcar_reverse(trq_deque *Q,
                             trq_mapper mapper,
                             void *context)
{
    trq_deque tmpQ, q;
    void *x;

    trq_deque_init_with_offset(&tmpQ, Q->off);
    trq_deque_init_with_offset(&q, Q->off);
    tmpQ = *Q;
    trq_deque_clear(Q);

    while (TRQ_NO_ITEM != (x = trq_deque_get_head(&tmpQ)))
        if ((x = mapper(x, context)))
            trq_deque_insert_tail(&q, x);
    *Q = q;
    return trq_deque_length(Q);
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_007__C__)))

void *trq_deque_get_nth(trq_deque *Q, int nth);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void *trq_deque_get_nth(trq_deque *Q, int nth)
{
    trq_deque q;
    int i;
    void *x;

    if ((nth < 1) || (nth > trq_deque_length(Q)))
        return TRQ_NO_ITEM;

    trq_deque_init_with_offset(&q, Q->off);

    if (nth <= (trq_deque_length(Q) / 2)) {
        for (i = (nth - 1); i > 0; i--) {
            x = trq_deque_get_tail(Q);
            trq_deque_insert_head(&q, x);
        }
        x = trq_deque_get_tail(Q);
        trq_deque_join_head(&q, Q);
    } else {
        for (i = (trq_deque_length(Q) - nth); i > 0; i--) {
            x = trq_deque_get_head(Q);
            trq_deque_insert_tail(&q, x);
        }
        x = trq_deque_get_head(Q);
        trq_deque_join_tail(&q, Q);
    }
    *Q = q;
    return x;
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_008__C__)))

int trq_deque_insert_nth(trq_deque *Q, int nth, void *item);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_insert_nth(trq_deque *Q, int nth, void *item)
{
    trq_deque q;
    int i;
    void *x;

    if ((nth < 1) || (nth > (trq_deque_length(Q) + 1)))
        return 0;

    trq_deque_init_with_offset(&q, Q->off);

    if (nth <= (trq_deque_length(Q) / 2)) {
        for (i = (nth - 1); i > 0; i--) {
            x = trq_deque_get_tail(Q);
            trq_deque_insert_head(&q, x);
        }
        trq_deque_insert_head(&q, item);
        trq_deque_join_head(&q, Q);
    } else {
        for (i = ((trq_deque_length(Q) - nth) + 1); i > 0; i--) {
            x = trq_deque_get_head(Q);
            trq_deque_insert_tail(&q, x);
        }
        trq_deque_insert_tail(&q, item);
        trq_deque_join_tail(&q, Q);
    }
    *Q = q;
    return 1;
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_009__C__)))

int trq_deque_swap(trq_deque *Q, void *item1, void *item2);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_swap(trq_deque *Q, void *item1, void *item2)
{
    int x1, x2;

    if (0 == (x1 = trq_deque_member(Q, item1)))
        return 0;
    if (0 == (x2 = trq_deque_member(Q, item2)))
        return 0;

    trq_deque_remove(Q, item1);
    trq_deque_remove(Q, item2);

    if (x1 < x2) {
        trq_deque_insert_nth(Q, x1, item2);
        trq_deque_insert_nth(Q, x2, item1);
    } else {
        trq_deque_insert_nth(Q, x2, item1);
        trq_deque_insert_nth(Q, x1, item2);
    }
    return 1;
}

#endif


#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_010__C__)))

void *trq_deque_find(trq_deque *Q, trq_test test, void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void *trq_deque_find(trq_deque *Q, trq_test test, void *context)
{
    trq_deque tmpQ, q;
    void *x;

    trq_deque_init_with_offset(&tmpQ, Q->off);
    trq_deque_init_with_offset(&q, Q->off);
    tmpQ = *Q;
    trq_deque_clear(Q);
    while (TRQ_NO_ITEM != (x = trq_deque_get_head(&tmpQ)))
        if (test(x, context)) {
            trq_deque_join_tail(&q, &tmpQ);
            break;
        } else {
            trq_deque_insert_tail(&q, x);
        }
    *Q = q;
    return x;
}

#endif

#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_011__C__)))

int trq_deque_mapcar_extended(trq_deque *Q,
                              trq_mapper_extended mapper,
                              void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
int trq_deque_mapcar_extended(trq_deque *Q,
                              trq_mapper_extended mapper,
                              void *context)
{
    trq_deque head;
    trq_deque tail;
    void *x;

    trq_deque_init_with_offset(&head, Q->off);
    trq_deque_init_with_offset(&tail, Q->off);
    tail = *Q;
    trq_deque_clear(Q);
    while (TRQ_NO_ITEM != (x = trq_deque_get_tail(&tail)))
        if ((x = mapper(x, &head, &tail, context)))
            trq_deque_insert_head(&head, x);
    *Q = head;
    return trq_deque_length(Q);
}

#endif

#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__) && (! defined (__TRQ_DEQUE_X_012__C__)))

void *trq_deque_find_and_spare(trq_deque *Q, trq_test test, void *context);

#else

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void *trq_deque_find_and_spare(trq_deque *Q, trq_test test, void *context)
{
    trq_deque tmpQ, q;
    void *x;

    trq_deque_init_with_offset(&tmpQ, Q->off);
    trq_deque_init_with_offset(&q, Q->off);
    tmpQ = *Q;
    trq_deque_clear(Q);
    while (TRQ_NO_ITEM != (x = trq_deque_get_head(&tmpQ)))
        if (test(x, context)) {
            trq_deque_insert_tail(&q, x);
            trq_deque_join_tail(&q, &tmpQ);
            break;
        } else {
            trq_deque_insert_tail(&q, x);
        }
    *Q = q;
    return x;
}

#endif

#if (defined (__TRQ_LIST_X_NUM__C__)) || ((! defined (__TRQ_DEQUE_X_NUM__C__)) && ((TRQ_USE_FUNCTIONS > 0) || (! defined (__TRQ__INLINE__FUNCTION__)))) || (defined (__TRQ_DEQUE_X_NUM__C__))

/* No trq_deque_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK needed here */

#else

#ifdef __GNUC__
__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void trq_deque_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK(int do_not_set,
                                                        trq_deque *Q,
                                                        trq_test t,
                                                        trq_mapper m,
                                                        trq_mapper_extended e,
                                                        int i,
                                                        void *v)
     __attribute__ ((unused));
#endif /* __GNUC__ */
     


/* The code within following function is nonsense.  It is not to be called
   at any time.  The sole purpose is to avoid annoying warnings that some
   systems give from unused inline functions. */

__DEQUE__STATIC__FUNCTION__
__TRQ__INLINE__FUNCTION__
void trq_deque_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK(int do_not_set,
                                                        trq_deque *Q,
                                                        trq_test t,
                                                        trq_mapper m,
                                                        trq_mapper_extended e,
                                                        int i,
                                                        void *v)
{
  if (do_not_set != 0)
    {
      trq_deque_remove(Q, v);
      trq_deque_join_tail(Q, Q);
      trq_deque_join_head(Q, Q);
      trq_deque_member(Q, v);
      trq_deque_get_nth(Q, i);
      trq_deque_insert_nth(Q, i, v);
      trq_deque_swap(Q, v, v);
      trq_deque_find(Q, t, v);
      trq_deque_find_and_spare(Q, t, v);
      trq_deque_mapcar(Q, m, v);
      trq_deque_mapcar_reverse(Q, m, v);
      trq_deque_mapcar_extended(Q, e, v);
    }
  return;
}

#endif

#endif /* !__TRQ_DEQUE_X__H__ */
/* eof (deque_inline.h) */
