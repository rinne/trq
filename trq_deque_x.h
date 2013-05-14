/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  ----------------------------------------------------------------------
 *  Created      : Sat Nov 18 11:12:26 1995 tri
 *  Last modified: Tue May 14 20:23:46 2013 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 1995-1999, 2001, 2013
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
