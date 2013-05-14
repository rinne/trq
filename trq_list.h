/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Efficient list operations for structures with one link pointer.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Nov 22 11:09:03 1995 tri
 *  Last modified: Wed Oct 10 01:05:00 2001 tri
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
 * $Id: trq_list.h,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_list.h,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.6  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.5  1999/01/25 09:08:57  tri
 *      Added trq_deque_mapcar_extended and fixed tests.
 *
 * Revision 1.4  1998/12/15 16:03:21  tri
 *      trq_list_put_{before,after} -> trq_list_insert_{before,after}
 *
 * Revision 1.3  1998/12/15 13:41:50  tri
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
 * Revision 1.2  1998/07/06 13:51:09  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:50  tri
 *      Added to CVS.
 *
 * Revision 1.23  1998/07/06 09:30:22  tri
 *      Added endlog.
 *
 * Revision 1.22  1998/06/23 08:00:38  tri
 *      Prototypes are defined for trq_list.c.
 *
 * Revision 1.21  1998/06/23 07:52:00  tri
 *      Removed ___func from symbol names.
 *
 * Revision 1.20  1998/06/22 07:15:32  tri
 *      trq_list_member_p -> trq_list_member
 *      trq_deque_member_p -> trq_deque_member
 *      trq_list_pointer_valid_p -> trq_list_pointer_valid
 *      trq_list_compatible_p -> trq_list_compatible
 *      trq_deque_compatible_p -> trq_deque_compatible
 *
 * Revision 1.19  1998/06/21 15:26:25  tri
 *      Changed symbol names of function versions of the trq_calls.
 *
 * Revision 1.18  1998/06/18 12:46:14  tri
 *      Fixed trq_list_rewind and trq_list_end.
 *
 * Revision 1.17  1998/06/18 10:27:37  tri
 *      Added trq_list_pointer_invalidate.
 *
 * Revision 1.16  1998/06/18 07:22:12  tri
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
 * Revision 1.15  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.14  1998/04/22 21:56:39  tri
 *      Added include trq_list_f.h.
 *
 * Revision 1.13  1998/04/20 20:47:17  tri
 *      TRQ_*_NO_ITEM -> TRQ_NO_ITEM
 *
 * Revision 1.12  1998/04/20 15:05:06  tri
 *      SNAFU in search and replace.
 *
 * Revision 1.11  1998/04/20 14:55:17  tri
 *      Final solution for deque basic operation names.
 *      Now they are trq_deque_insert_head, trq_deque_insert_tail,
 *      trq_deque_get_head and trq_deque_get_tail.  After intensive
 *      customer survey, this seems to be the most intuitive way.
 *
 * Revision 1.10  1998/04/18 11:01:09  tri
 *      Formatting.
 *
 * Revision 1.9  1998/04/18 10:29:47  tri
 *      Renamed API functions to more intuitive form:
 *      trq_deque_put_last to trq_deque_put,
 *      trq_deque_put to trq_deque_push,
 *      trq_deque_get_tail to trq_deque_pop,
 *      trq_deque_mapcar_bw to trq_deque_mapcar_reverse,
 *      trq_list_mapcar_bw to trq_list_mapcar_reverse,
 *      trq_deque_join_bw to trq_deque_join_tail and
 *      trq_deque_join to trq_deque_join_head.
 *
 * Revision 1.8  1998/04/17 16:45:29  tri
 *      Fixed trq_list_end.
 *
 * Revision 1.7  1998/04/17 16:04:44  tri
 *      Fixed previous addition :).
 *
 * Revision 1.6  1998/04/17 15:56:03  tri
 *      Added __trq_list_clear.
 *
 * Revision 1.5  1998/04/17 15:38:30  tri
 *      Renamed trq_list_get_backward and trq_list_get_forward to
 *      trq_list_get_bw and trq_list_get_fw accordingly.
 *
 * Revision 1.4  1998/04/17 15:17:29  tri
 *      Fixed almost all list operations.  List pointer
 *      stuff was really buggy.
 *
 * Revision 1.3  1998/04/17 08:51:57  tri
 *      Types `deque' and `list' and constants `DEQUE_NO_ITEM'
 *      and `LIST_NO_ITEM' prefixed with `trq_' and `TRQ_'
 *      accordingly.
 *
 * Revision 1.2  1998/04/16 17:30:21  tri
 *      Fixed formatting.  No functional changes.
 *
 * Revision 1.1  1998/04/16 14:39:42  tri
 *      Initial revision
 *
 * $EndLog$
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
