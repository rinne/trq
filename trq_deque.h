/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  ----------------------------------------------------------------------
 *  Created      : Sat Nov 18 11:12:26 1995 tri
 *  Last modified: Wed Oct 10 01:04:16 2001 tri
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
 * $Id: trq_deque.h,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_deque.h,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.13  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.12  1999/12/08 20:29:00  tmo
 *      Changes from the ipsec-3.0 branch.
 *
 * Revision 1.11  1999/11/24 17:17:51  tri
 *      Merged from the branch.
 *
 * Revision 1.10.2.1  1999/11/24 16:28:37  tri
 *      Made default value of TRQ_USE_FUNCTIONS to be defined
 *      in configure time by --enable-trq-macros[=no] argument.
 *      Default is no.
 *
 * Revision 1.10  1999/10/21 00:33:36  huima
 *      <trq_conf.h> ==> "trq_conf.h"
 *
 * Revision 1.9  1999/05/11 08:07:48  tmo
 *      Made trq_deque_len() macro implementation to cast the
 *      lenth value to (int), as the function implementation
 *      returns int. This removed a lot of warnings at code that
 *      uses this library.
 *
 * Revision 1.8  1999/01/25 09:08:55  tri
 *      Added trq_deque_mapcar_extended and fixed tests.
 *
 * Revision 1.7  1999/01/25 06:59:05  tri
 *      Added trq_deque_mapcar_extended.
 *
 * Revision 1.6  1998/10/23 21:21:15  kivinen
 *      Changed the SSHDIST_WINDOWS to WINDOWS.
 *
 * Revision 1.5  1998/08/19 00:30:05  sjl
 *      Added trq_conf_win.h (which contains Windows-specific options) and
 *      added #ifndef SSHDIST_WINDOWS to relevant parts of code to port it
 *      to Windows.
 *
 * Revision 1.4  1998/07/06 16:02:30  tri
 *      Added some comments.
 *
 * Revision 1.3  1998/07/06 14:29:01  tri
 *      Changed deque length type to int (from long).
 *
 * Revision 1.2  1998/07/06 13:51:02  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:41  tri
 *      Added to CVS.
 *
 * Revision 1.22  1998/07/06 08:05:46  tri
 *      Added endlog.
 *
 * Revision 1.21  1998/06/23 07:59:42  tri
 *      Prototypes are defined for trq_deque.c.
 *
 * Revision 1.20  1998/06/23 07:49:52  tri
 *      Removed ___func from symbol names.
 *
 * Revision 1.19  1998/06/22 07:15:32  tri
 *      trq_list_member_p -> trq_list_member
 *      trq_deque_member_p -> trq_deque_member
 *      trq_list_pointer_valid_p -> trq_list_pointer_valid
 *      trq_list_compatible_p -> trq_list_compatible
 *      trq_deque_compatible_p -> trq_deque_compatible
 *
 * Revision 1.18  1998/06/21 15:26:25  tri
 *      Changed symbol names of function versions of the trq_calls.
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
 * Revision 1.16  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.15  1998/04/22 22:39:44  tri
 *      Formatting.
 *
 * Revision 1.14  1998/04/22 22:39:13  tri
 *      Return type of compare function was wrong.
 *      Should be int.
 *
 * Revision 1.13  1998/04/21 11:24:41  tri
 *      Typedef `callback' function types.
 *
 * Revision 1.12  1998/04/20 20:47:17  tri
 *      TRQ_*_NO_ITEM -> TRQ_NO_ITEM
 *
 * Revision 1.11  1998/04/20 20:43:46  tri
 *      Added put/get and push/pop compatibility.
 *
 * Revision 1.10  1998/04/20 15:07:02  tri
 *      Formatting.
 *
 * Revision 1.9  1998/04/20 15:05:06  tri
 *      SNAFU in search and replace.
 *
 * Revision 1.8  1998/04/20 14:55:17  tri
 *      Final solution for deque basic operation names.
 *      Now they are trq_deque_insert_tail, trq_deque_insert_head,
 *      trq_deque_get_tail and trq_deque_get_head.  After intensive
 *      customer survey, this seems to be the most intuitive way.
 *
 * Revision 1.7  1998/04/19 14:31:01  tri
 *      Added trq_deque_f.h.
 *
 * Revision 1.6  1998/04/19 13:59:30  tri
 *      Added trq_deque_empty_p.
 *
 * Revision 1.5  1998/04/18 10:58:37  tri
 *      Formatting.
 *
 * Revision 1.4  1998/04/18 10:29:47  tri
 *      Renamed API functions to more intuitive form:
 *      trq_deque_put_last to trq_deque_put,
 *      trq_deque_put to trq_deque_push,
 *      trq_deque_get_head to trq_deque_pop,
 *      trq_deque_mapcar_bw to trq_deque_mapcar_reverse,
 *      trq_list_mapcar_bw to trq_list_mapcar_reverse,
 *      trq_deque_join_bw to trq_deque_join_tail and
 *      trq_deque_join to trq_deque_join_head.
 *
 * Revision 1.3  1998/04/17 08:51:57  tri
 *      Types `deque' and `list' and constants `DEQUE_NO_ITEM'
 *      and `LIST_NO_ITEM' prefixed with `trq_' and `TRQ_'
 *      accordingly.
 *
 * Revision 1.2  1998/04/17 08:06:38  tri
 *      Added __trq_deque_clear.  This macro is for
 *      internal use of the package only.
 *
 * Revision 1.1  1998/04/16 14:39:41  tri
 *      Initial revision
 *
 * $EndLog$
 */
#ifndef __TRQ_DEQUE__H__
#define __TRQ_DEQUE__H__ 1

#ifndef WINDOWS
#include "trq_conf.h"
#else /* WINDOWS */
#include "trq_conf_win.h"
#endif /* WINDOWS */

typedef struct {
    void           *h1;   /* one head pointer                           */
    void           *h2;   /* and another one                            */
    void           *r;    /* temporary `variable'                       */
    unsigned int    len;  /* length                                     */
    trq_p_i_t       off;  /* next pointer offset within storage unit    */
} trq_deque, *trq_deque_t;

#if (TRQ_USE_FUNCTIONS > 0) || defined (__TRQ_DEQUE__C__)

void  trq_deque_init_with_offset (trq_deque *Q, trq_p_i_t o);
int   trq_deque_empty_p          (trq_deque *Q);
void  trq_deque_clear            (trq_deque *Q);
int   trq_deque_insert_tail      (trq_deque *Q, void *b);
void *trq_deque_get_head         (trq_deque *Q);
int   trq_deque_insert_head      (trq_deque *Q, void *b);
void *trq_deque_get_tail         (trq_deque *Q);
int   trq_deque_length           (trq_deque *Q);
int   trq_deque_reverse          (trq_deque *Q);
int   trq_deque_compatible       (trq_deque *Q1, trq_deque *Q2);

#else /* TRQ_USE_FUNCTIONS > 0 */

#  define trq_deque_init_with_offset    __trq_deque_init_with_offset
#  define trq_deque_empty_p             __trq_deque_empty_p
#  define trq_deque_clear               __trq_deque_clear
#  define trq_deque_length              __trq_deque_length
#  define trq_deque_reverse             __trq_deque_reverse
#  define trq_deque_insert_tail         __trq_deque_insert_tail
#  define trq_deque_get_head            __trq_deque_get_head
#  define trq_deque_insert_head         __trq_deque_insert_head
#  define trq_deque_get_tail            __trq_deque_get_tail
#  define trq_deque_compatible          __trq_deque_compatible

#endif  /* TRQ_USE_FUNCTIONS > 0 */

#define TRQ_NO_ITEM ((void *)0)  /* This better have integral value 0 */

#define trq_assert            __trq_assert
#define __trq_assert(c)     /**/

/************************************************************************/
/************************** DRAGONS LIVE HERE ***************************/
/************************************************************************/
/*
 * Basic deque operations are macros in order to achieve
 * maximum perforemance and avoid function calls.
 *
 * Theory behind the deque with only one next pointer on storage
 * unit is based on the fact that (x ^ y) ^ x == y.
 * We store pointers to the `last' and the `first' item in the deque.
 * Whenever new item is stored into the list we xor the next pointer
 * in the old last item with the pointer to the new item, store pointer
 * to the old last item into the next pointer of the new last and
 * update the last pointer in the deque struct.  Now when we are
 * removing an item from the deque we just need to store the pointer to
 * the item removed and xor the next pointer in the item now becoming
 * the last in the deque with the pointer to the removed item and
 * update the deque structuture.  Beauty of this system is that we can
 * add and remove stuff into and from the both ends of the deque with
 * virtually identical functions and we only need one next pointer
 * within the structures stored into the deque.  This is important
 * if we have a predefined system structure that we can't change.
 */

/*
 * ANSI forbids bitwise operations between pointers.  Dull.
 * Now we need some preprocessing power with intersive casting.
 */
#define _Q_PTR_XOR(x, y) ((void *)(((trq_p_i_t)(x)) ^ ((trq_p_i_t)(y))))

/*
 * Given the struct pointer and offset of the next pointer within
 * the struct, give the next pointer.  Value returned is also valid
 * left side expression.
 */
#define _Q_NEXT_PTR(s, o) (*((void **)(((trq_p_i_t)(s)) + ((trq_p_i_t)(o)))))

/*
 * Function definitions are macros because get and put operations
 * are symmetric and they are almost identical to get_last and
 * put_last.  Only h1 and h2 have to be swapped.
 *
 */

#define __trq_deque_empty_p(Q)                                              \
    (TRQ_NO_ITEM == ((Q)->h1))

#define __trq_deque_clear(Q)                                                \
    ((void)((((Q)->h1) = ((Q)->h2) = TRQ_NO_ITEM),                          \
            (((Q))->len) = 0))

#define __trq_deque_init_with_offset(Q, o)                                  \
    ((void)((((Q)->off) = (o)),                                             \
            (__trq_deque_clear((Q)))))

#define trq_deque_init(Q, t, m)                                             \
    (trq_deque_init_with_offset(Q, (_Q_STRUCT_OFFSET(t, m))))

#define __trq_deque_length(Q) ((int)((Q)->len))

#define __trq_deque_reverse(Q)                                              \
    (((Q)->r = (Q)->h1),                                                    \
     ((Q)->h1 = (Q)->h2),                                                   \
     ((Q)->h2 = (Q)->r),                                                    \
     (trq_deque_length((Q))))

#define __trq_deque_compatible(Q1, Q2)                                      \
    (((Q1)->off) == ((Q2)->off))

#define _TRQ_Q_PUT_PROTO(Q, b, h1, h2)                                      \
    ((((Q)->h1 == TRQ_NO_ITEM)                                              \
      ?                                                                     \
      (((Q)->h1 = (Q)->h2 = b),                                             \
       (_Q_NEXT_PTR(b, (Q)->off) = TRQ_NO_ITEM))                            \
      :                                                                     \
      ((_Q_NEXT_PTR(b, (Q)->off) = (Q)->h2),                                \
       ((Q)->h2 = b),                                                       \
       (_Q_NEXT_PTR(_Q_NEXT_PTR(b, (Q)->off), (Q)->off) =                   \
        _Q_PTR_XOR(_Q_NEXT_PTR(_Q_NEXT_PTR(b, (Q)->off), (Q)->off), b)))),  \
     (++((Q)->len)))

#define _TRQ_Q_GET_PROTO(Q, h1, h2)                                         \
    ((((Q)->h1 == TRQ_NO_ITEM)                                              \
      ?                                                                     \
      ((Q)->r = TRQ_NO_ITEM)                                                \
      :                                                                     \
      (((Q)->h1 == (Q)->h2)                                                 \
       ?                                                                    \
       ((((Q)->len)--),                                                     \
        ((Q)->r = (Q)->h1),                                                 \
        ((Q)->h1 = (Q)->h2 = TRQ_NO_ITEM))                                  \
       :                                                                    \
       ((((Q)->len)--),                                                     \
        ((Q)->r = (Q)->h1),                                                 \
        ((Q)->h1 = _Q_NEXT_PTR((Q)->r, (Q)->off)),                          \
        (_Q_NEXT_PTR((Q)->h1, (Q)->off) =                                   \
         _Q_PTR_XOR(_Q_NEXT_PTR((Q)->h1, (Q)->off), (Q)->r))))),            \
    ((Q)->r))

#define __trq_deque_insert_tail(Q, b)    (_TRQ_Q_PUT_PROTO((Q), (b), h1, h2))
#define __trq_deque_insert_head(Q, b)    (_TRQ_Q_PUT_PROTO((Q), (b), h2, h1))
#define __trq_deque_get_head(Q)          (_TRQ_Q_GET_PROTO((Q), h1, h2))
#define __trq_deque_get_tail(Q)          (_TRQ_Q_GET_PROTO((Q), h2, h1))

/************************************************************************/
/*********************** END OF THE DRAGON'S NEST ***********************/
/************************************************************************/

/*
 * Types of the `callback' functions.
 */
/*
 * Mapper function gets pointer to the item and a context pointer
 * and returns a pointer to the item itself, pointer to another item
 * or TRQ_NO_ITEM (i.e. NULL).
 */
typedef void *(*trq_mapper)(void *item, void *context);
/*
 * Extended mapper function gets pointer to the item and a context pointer
 * and returns a pointer to the item itself, pointer to another item
 * or TRQ_NO_ITEM (i.e. NULL).  In addition to that, it also gets pointer
 * to two deques.  These deques are the deque of already processed items
 * and deque of items still waiting for processing.  The mapper function
 * is allowed to change these deques and therefore manipulate the outcome
 * of the operationf using extended mapper.
 */
typedef void *(*trq_mapper_extended)(void *item,
                                     trq_deque *processed,
                                     trq_deque *waiting,
                                     void *context);
/*
 * Compare function gets two items and a context pointer and compares
 * the item.  If item1 is `smaller' than item2, function returns
 * a negative integer.  If item1 is `larger' than item2, function
 * returns a positive integer.  Zero is returned if items are equal.
 */
typedef int (*trq_compare)(void *item1, void *item2, void *context);
/*
 * Test function gets a pointer to the item and a context pointer.
 * It returns nonzero integer, if the test is `true' and zero if
 * the test is `false'.
 *
 * Testing in search functions that require ordered deque or list is
 * somewhat different and require that sign of the return value is
 * also significant.  Test function should return negative value if
 * test failed and tested item is `smaller' than the one that is
 * searched.  Analogously the test function should return positive
 * value, if test fails and tested item is `bigger' than the one that
 * is searched.  In this case the succesful test is returned as zero.
 */
typedef int (*trq_test)(void *item, void *context);

/*
 * External function prototypes.
 */
#include <trq_deque_f.h>

/*
 * Inlines or prototypes if inlines are not supported.
 */
#include <trq_deque_x.h>

/*
 * These make stack operations more intuitive.
 */
#define trq_deque_push(q, b)    (trq_deque_insert_tail((q), (b)))
#define __trq_deque_push(q, b)  (__trq_deque_insert_tail((q), (b)))
#define trq_deque_pop(q)        (trq_deque_get_tail((q)))
#define __trq_deque_pop(q)      (__trq_deque_get_tail((q)))

/*
 * These make queue operations more intuitive.
 */
#define trq_deque_put(q, b)     (trq_deque_insert_tail((q), (b)))
#define __trq_deque_put(q, b)   (__trq_deque_insert_tail((q), (b)))
#define trq_deque_get(q)        (trq_deque_get_head((q)))
#define __trq_deque_get(q)      (__trq_deque_get_head((q)))

#endif /* !__TRQ_DEQUE__H__ */
/* eof (trq_deque.h) */
