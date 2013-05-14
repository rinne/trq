/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Efficient list operations for structures with one link pointer.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Nov 22 11:09:03 1995 tri
 *  Last modified: Tue May 14 20:22:48 2013 tri
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
#ifndef __TRQ_LIST__H__
#define __TRQ_LIST__H__ 1

#include <trq_deque.h>

typedef struct trq_list {
    void       *r;    /* Temporary for macros                       */
    trq_deque  head;  /* Deque of items before current              */
    void      *c;     /* Current item                               */
    trq_deque  tail;  /* Deque of items after current               */
} trq_list, *trq_list_t;

#define TRQ_NO_ITEM  ((void *)0)

#if (TRQ_USE_FUNCTIONS > 0) || defined (__TRQ_LIST__C__)

void  trq_list_clear              (trq_list *L);
int   trq_list_goto_first         (trq_list *L);
int   trq_list_goto_last          (trq_list *L);
int   trq_list_length             (trq_list *L);
int   trq_list_pointer_valid      (trq_list *L);
int   trq_list_pointer_invalidate (trq_list *L);
int   trq_list_insert_last        (trq_list *L, void *b);
int   trq_list_insert_first       (trq_list *L, void *b);
void *trq_list_get_last           (trq_list *L);
void *trq_list_get_first          (trq_list *L);
int   trq_list_insert_before      (trq_list *L, void *b);
int   trq_list_insert_after       (trq_list *L, void *b);
void *trq_list_get_fw             (trq_list *L);
void *trq_list_get_bw             (trq_list *L);
int   trq_list_remove             (trq_list *L, void *b);
void *trq_list_current            (trq_list *L);
int   trq_list_compatible         (trq_list *L1, trq_list *L2);

#else /* TRQ_USE_FUNCTIONS > 0 */

#  define trq_list_clear               __trq_list_clear
#  define trq_list_goto_first          __trq_list_goto_first
#  define trq_list_goto_last           __trq_list_goto_last
#  define trq_list_length              __trq_list_length
#  define trq_list_pointer_valid       __trq_list_pointer_valid
#  define trq_list_pointer_invalidate  __trq_list_pointer_invalidate
#  define trq_list_insert_last         __trq_list_insert_last
#  define trq_list_insert_first        __trq_list_insert_first
#  define trq_list_get_last            __trq_list_get_last
#  define trq_list_get_first           __trq_list_get_first
#  define trq_list_insert_before       __trq_list_insert_before
#  define trq_list_insert_after        __trq_list_insert_after
#  define trq_list_get_fw              __trq_list_get_fw
#  define trq_list_get_bw              __trq_list_get_bw
#  define trq_list_remove              __trq_list_remove
#  define trq_list_current             __trq_list_current
#  define trq_list_compatible          __trq_list_compatible

#endif /* TRQ_USE_FUNCTIONS > 0 */

#define list_assert           __list_assert
#define __list_assert(c)      trq_assert((c))

#define trq_list_init(L, t, m)                                             \
    (void)((trq_deque_init(&((L)->head), t, m)),                           \
           (trq_deque_init(&((L)->tail), t, m)),                           \
           ((L)->c = TRQ_NO_ITEM))

#define __trq_list_clear(L)                                                \
    ((void)((__trq_deque_clear(&((L)->tail))),                             \
            (__trq_deque_clear(&((L)->head))),                             \
            ((L)->c = TRQ_NO_ITEM)))

#define __trq_list_pointer_valid(L)                                        \
    (((L)->c) != TRQ_NO_ITEM)

#define __trq_list_pointer_invalidate(L)                                   \
    ((((L)->c) != TRQ_NO_ITEM)                                             \
     ?                                                                     \
     ((trq_deque_insert_head(&((L)->tail), ((L)->c))),                     \
      (((L)->c) = TRQ_NO_ITEM),                                            \
      1)                                                                   \
     :                                                                     \
     0)

#define __trq_list_length(L)                                               \
    ((trq_deque_length(&((L)->head))) +                                    \
     (trq_deque_length(&((L)->tail))) +                                    \
     (((L)->c) ? 1 : 0))

#define __trq_list_insert_last(L, b)                                       \
    ((trq_deque_insert_head(&((L)->head), (b))),                           \
     (trq_list_length((L))))

#define __trq_list_insert_first(L, b)                                      \
    ((trq_deque_insert_tail(&((L)->tail), (b))),                           \
     (trq_list_length((L))))

#define __trq_list_goto_first(L)                                           \
    (((void)((trq_list_pointer_valid(L))                                   \
             ?                                                             \
             (trq_deque_insert_tail(&((L)->head), (L)->c))                 \
             :                                                             \
             0)),                                                          \
     ((void)(trq_deque_join_tail(&((L)->head), &((L)->tail)))),            \
     ((L)->c = trq_deque_get_tail(&((L)->head))),                          \
     (trq_list_length((L))))

#define __trq_list_goto_last(L)                                            \
    (((void)((trq_list_pointer_valid(L))                                   \
             ?                                                             \
             (trq_deque_insert_head(&((L)->tail), (L)->c))                 \
             :                                                             \
             0)),                                                          \
     ((void)(trq_deque_join_head(&((L)->tail), &((L)->head)))),            \
     ((L)->c = trq_deque_get_head(&((L)->tail))),                          \
     (trq_list_length((L))))

#define __trq_list_get_last(L)                                             \
    ((((L)->r) = trq_deque_get_head(&((L)->head)))                         \
     ?                                                                     \
     ((L)->r)                                                              \
     :                                                                     \
     ((((L)->r) = ((L)->c))                                                \
      ?                                                                    \
      (((L)->c = TRQ_NO_ITEM),                                             \
       ((L)->r))                                                           \
      :                                                                    \
      (trq_deque_get_head(&((L)->tail)))))

#define __trq_list_get_first(L)                                            \
    ((((L)->r) = trq_deque_get_tail(&((L)->tail)))                         \
     ?                                                                     \
     ((L)->r)                                                              \
     :                                                                     \
     ((((L)->r) = ((L)->c))                                                \
      ?                                                                    \
      (((L)->c = TRQ_NO_ITEM),                                             \
       ((L)->r))                                                           \
      :                                                                    \
      (trq_deque_get_tail(&((L)->head)))))


#define __trq_list_insert_before(L, b)                                     \
    ((!(trq_list_pointer_valid(L)))                                        \
     ?                                                                     \
     0                                                                     \
     :                                                                     \
     ((trq_deque_insert_head(&((L)->tail), (b))), 1))

#define __trq_list_insert_after(L, b)                                      \
    ((!(trq_list_pointer_valid(L)))                                        \
     ?                                                                     \
     0                                                                     \
     :                                                                     \
     ((trq_deque_insert_tail(&((L)->head), (b))), 1))

#define __trq_list_get_fw(L)                                               \
    ((!(trq_list_pointer_valid(L)))                                        \
     ?                                                                     \
     TRQ_NO_ITEM                                                           \
     :                                                                     \
     (((L)->r = ((L)->c)),                                                 \
      ((L)->c = trq_deque_get_tail(&((L)->head))),                         \
      ((L)->r)))

#define __trq_list_get_bw(L)                                               \
    ((!(trq_list_pointer_valid(L)))                                        \
     ?                                                                     \
     TRQ_NO_ITEM                                                           \
     :                                                                     \
     (((L)->r = ((L)->c)),                                                 \
      ((L)->c = trq_deque_get_head(&((L)->tail))),                         \
      ((L)->r)))

#define __trq_list_remove(L, b)                                            \
    ((((L)->c) == (b))                                                     \
     ?                                                                     \
     ((((L)->c) = TRQ_NO_ITEM), 1)                                         \
     :                                                                     \
     ((trq_deque_remove(&((L)->head), (b)))                                \
      ?                                                                    \
      1                                                                    \
      :                                                                    \
      (trq_deque_remove(&((L)->tail), (b)))))

#define __trq_list_current(L)                                              \
    ((L)->c)

#define __trq_list_compatible(L1, L2)                                      \
    (trq_deque_compatible(&((L1)->head), &((L2)->head)))

/*
 * External function prototypes.
 */
#include <trq_list_f.h>

/*
 * Inlines or prototypes if inlines are not supported.
 */
#include <trq_list_x.h>

#endif /* !__TRQ_LIST__H__ */
/* eof (trq_list.h) */
