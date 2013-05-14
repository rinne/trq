/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  Functions that can be implemented also as macros.
 *  ----------------------------------------------------------------------
 *  Created      : Sat Nov 18 11:12:23 1995 tri
 *  Last modified: Wed Oct 10 01:04:01 2001 tri
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
 * $Id: trq_deque.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_deque.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.9  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.8  1999/10/21 00:33:35  huima
 *      <trq_conf.h> ==> "trq_conf.h"
 *
 * Revision 1.7  1998/10/23 21:20:30  kivinen
 *      Removed sshincludes.h. This file cannot include it, because it
 *      doesn't belong to the distribution. Changed the
 *      SSHDIST_WINDOWS to WINDOWS, because if I have understood
 *      correctly the sshincludes.h was included only to the that one
 *      define.
 *
 * Revision 1.6  1998/10/23 12:52:16  ranki
 *      Added #include "sshincludes.h". These files ceased to compile in
 *      Visual C++ without sshincludes.h
 *
 * Revision 1.5  1998/10/01 23:27:48  kivinen
 *      Removed sshincludes.h.
 *
 * Revision 1.4  1998/10/01 17:03:55  vecna
 *      IPSEC 1.2 Compiles in Windows OK
 *
 * Revision 1.3  1998/08/19 00:30:03  sjl
 *      Added trq_conf_win.h (which contains Windows-specific options) and
 *      added #ifndef SSHDIST_WINDOWS to relevant parts of code to port it
 *      to Windows.
 *
 * Revision 1.2  1998/07/06 13:51:01  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:39  tri
 *      Added to CVS.
 *
 * Revision 1.16  1998/07/06 08:05:23  tri
 *      Added endlog.
 *
 * Revision 1.15  1998/06/23 08:02:53  tri
 *      Changed default.
 *
 * Revision 1.14  1998/06/23 08:01:51  tri
 *      Enabled possible small objects.
 *
 * Revision 1.13  1998/06/23 07:57:54  tri
 *      Added file define.
 *
 * Revision 1.12  1998/06/23 07:49:47  tri
 *      Removed ___func from symbol names.
 *
 * Revision 1.11  1998/06/22 07:15:32  tri
 *      trq_list_member_p -> trq_list_member
 *      trq_deque_member_p -> trq_deque_member
 *      trq_list_pointer_valid_p -> trq_list_pointer_valid
 *      trq_list_compatible_p -> trq_list_compatible
 *      trq_deque_compatible_p -> trq_deque_compatible
 *
 * Revision 1.10  1998/06/21 15:26:25  tri
 *      Changed symbol names of function versions of the trq_calls.
 *
 * Revision 1.9  1998/06/18 07:22:12  tri
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
 * Revision 1.8  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.7  1998/04/20 15:05:06  tri
 *      SNAFU in search and replace.
 *
 * Revision 1.6  1998/04/20 14:55:17  tri
 *      Final solution for deque basic operation names.
 *      Now they are trq_deque_insert_tail, trq_deque_insert_head,
 *      trq_deque_get_tail and trq_deque_get_head.  After intensive
 *      customer survey, this seems to be the most intuitive way.
 *
 * Revision 1.5  1998/04/19 13:59:10  tri
 *      Minor fix.
 *
 * Revision 1.4  1998/04/19 13:57:57  tri
 *      Added trq_deque_empty_p.
 *
 * Revision 1.3  1998/04/18 10:29:47  tri
 *      Renamed API functions to more intuitive form:
 *      trq_deque_put_last to trq_deque_put,
 *      trq_deque_put to trq_deque_push,
 *      trq_deque_get_head to trq_deque_pop,
 *      trq_deque_mapcar_bw to trq_deque_mapcar_reverse,
 *      trq_list_mapcar_bw to trq_list_mapcar_reverse,
 *      trq_deque_join_bw to trq_deque_join_tail and
 *      trq_deque_join to trq_deque_join_head.
 *
 * Revision 1.2  1998/04/17 08:51:57  tri
 *      Types `deque' and `list' and constants `DEQUE_NO_ITEM'
 *      and `LIST_NO_ITEM' prefixed with `trq_' and `TRQ_'
 *      accordingly.
 *
 * Revision 1.1  1998/04/16 14:39:41  tri
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
#  define TRQ_USE_FUNCTIONS __TRQ__SMALL__OBJECTS__
#else
#  define TRQ_USE_FUNCTIONS 0
#endif

#define __TRQ_DEQUE__C__ 1

#include <trq_deque.h>

void trq_deque_clear(trq_deque *Q)
{
    (void)__trq_deque_clear(Q);
}

int trq_deque_empty_p(trq_deque *Q)
{
    return __trq_deque_empty_p(Q);
}

int trq_deque_insert_tail(trq_deque *Q, void *b)
{
    return __trq_deque_insert_tail(Q, b);
}

void *trq_deque_get_head(trq_deque *Q)
{
    return __trq_deque_get_head(Q);
}

int trq_deque_insert_head(trq_deque *Q, void *b)
{
    return __trq_deque_insert_head(Q, b);
}

void *trq_deque_get_tail(trq_deque *Q)
{
    return __trq_deque_get_tail(Q);
}

int trq_deque_length(trq_deque *Q)
{
    return __trq_deque_length(Q);
}

int trq_deque_reverse(trq_deque *Q)
{
    return __trq_deque_reverse(Q);
}

int trq_deque_compatible(trq_deque *Q1, trq_deque *Q2)
{
    return __trq_deque_compatible(Q1, Q2);
}

void trq_deque_init_with_offset(trq_deque *Q, trq_p_i_t o)
{
    (void)__trq_deque_init_with_offset(Q, o);
}

/* eof (trq_deque.c) */
