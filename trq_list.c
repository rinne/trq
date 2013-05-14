/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Efficient list operations for structures with one link pointer.
 *  Functions that can be implemented also as macros.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Nov 22 13:53:13 1995 tri
 *  Last modified: Wed Oct 10 01:03:47 2001 tri
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
 * $Id: trq_list.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_list.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.11  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.10  1999/10/21 00:33:38  huima
 *      <trq_conf.h> ==> "trq_conf.h"
 *
 * Revision 1.9  1998/12/15 16:03:20  tri
 *      trq_list_put_{before,after} -> trq_list_insert_{before,after}
 *
 * Revision 1.8  1998/12/15 13:41:47  tri
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
 * Revision 1.7  1998/10/23 21:20:04  kivinen
 *      Removed sshincludes.h. This file cannot include it, because it
 *      doesn't belong to the distribution. Changed the
 *      SSHDIST_WINDOWS to WINDOWS, because if I have understood
 *      correctly the sshincludes.h was included only to the that one
 *      define.
 *
 * Revision 1.6  1998/10/23 12:52:23  ranki
 *      Added #include "sshincludes.h". These files ceased to compile in
 *      Visual C++ without sshincludes.h
 *
 * Revision 1.5  1998/10/01 23:28:14  kivinen
 *      Removed sshincludes.h.
 *
 * Revision 1.4  1998/10/01 17:03:56  vecna
 *      IPSEC 1.2 Compiles in Windows OK
 *
 * Revision 1.3  1998/08/19 00:30:09  sjl
 *      Added trq_conf_win.h (which contains Windows-specific options) and
 *      added #ifndef SSHDIST_WINDOWS to relevant parts of code to port it
 *      to Windows.
 *
 * Revision 1.2  1998/07/06 13:51:07  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:48  tri
 *      Added to CVS.
 *
 * Revision 1.15  1998/07/06 09:30:03  tri
 *      Added endlog.
 *
 * Revision 1.14  1998/06/23 08:03:05  tri
 *      Changed default.
 *
 * Revision 1.13  1998/06/23 08:02:29  tri
 *      Enabled possible small objects.
 *
 * Revision 1.12  1998/06/23 07:57:21  tri
 *      Added file define.
 *
 * Revision 1.11  1998/06/23 07:52:50  tri
 *      Fix.
 *
 * Revision 1.10  1998/06/23 07:52:06  tri
 *      Removed ___func from symbol names.
 *
 * Revision 1.9  1998/06/22 07:15:32  tri
 *      trq_list_member_p -> trq_list_member
 *      trq_deque_member_p -> trq_deque_member
 *      trq_list_pointer_valid_p -> trq_list_pointer_valid
 *      trq_list_compatible_p -> trq_list_compatible
 *      trq_deque_compatible_p -> trq_deque_compatible
 *
 * Revision 1.8  1998/06/21 15:26:25  tri
 *      Changed symbol names of function versions of the trq_calls.
 *
 * Revision 1.7  1998/06/18 10:27:17  tri
 *      Added trq_list_pointer_invalidate.
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
 * Revision 1.5  1998/04/23 14:07:56  tri
 *      Made single TRQ_USE_FUNCTIONS instead of
 *      separate one for lists and deques.
 *
 * Revision 1.4  1998/04/17 15:38:30  tri
 *      Renamed trq_list_get_backward and trq_list_get_forward to
 *      trq_list_get_bw and trq_list_get_fw accordingly.
 *
 * Revision 1.3  1998/04/17 13:28:16  tri
 *      Removed func_trq_list_member.
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

#define __TRQ_LIST__C__ 1

#include <trq_list.h>

void trq_list_clear(trq_list *L)
{
    (void)__trq_list_clear(L);
}

int trq_list_goto_first(trq_list *L)
{
    return __trq_list_goto_first(L);
}

int trq_list_goto_last(trq_list *L)
{
    return __trq_list_goto_last(L);
}

int trq_list_length(trq_list *L)
{
    return __trq_list_length(L);
}

int trq_list_pointer_valid(trq_list *L)
{
    return __trq_list_pointer_valid(L);
}

int trq_list_pointer_invalidate(trq_list *L)
{
    return __trq_list_pointer_invalidate(L);
}

int trq_list_insert_last(trq_list *L, void *b)
{
    return __trq_list_insert_last(L, b);
}

int trq_list_insert_first(trq_list *L, void *b)
{
    return __trq_list_insert_first(L, b);
}

void *trq_list_get_last(trq_list *L)
{
    return __trq_list_get_last(L);
}

void *trq_list_get_first(trq_list *L)
{
    return __trq_list_get_first(L);
}

int trq_list_insert_before(trq_list *L, void *b)
{
    return __trq_list_insert_before(L, b);
}

int trq_list_insert_after(trq_list *L, void *b)
{
    return __trq_list_insert_after(L, b);
}

void *trq_list_get_fw(trq_list *L)
{
    return __trq_list_get_fw(L);
}

void *trq_list_get_bw(trq_list *L)
{
    return __trq_list_get_bw(L);
}

int trq_list_remove(trq_list *L, void *b)
{
    return __trq_list_remove(L, b);
}

int trq_list_compatible(trq_list *L1, trq_list *L2)
{
    return __trq_list_compatible(L1, L2);
}

void *trq_list_current(trq_list *L)
{
    return __trq_list_current(L);
}

/* eof (trq_list.c) */
