/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Test macro versions of list operations.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Jun 17 19:42:57 1998 tri
 *  Last modified: Tue May 14 20:20:31 2013 tri
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

#ifdef TRQ_USE_FUNCTIONS
#  undef TRQ_USE_FUNCTIONS
#endif

#define TRQ_USE_FUNCTIONS 0

#define __T_LIST_MACRO_C__

#include "t-list.c"

#ifdef __TRQ__INLINE__FUNCTION__
/* This is to remove "unused" warning from the compilation. */
void dummy_do_not_call()
{
  trq_list_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK(0,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    0,
                                                    NULL);
  trq_deque_THIS_CAN_GIVE_UNUSED_WARNING_WHICH_IS_OK(0,
                                                     NULL,
                                                     NULL,
                                                     NULL,
                                                     NULL,
                                                     0,
                                                     NULL);
}
#endif /* __TRQ__INLINE__FUNCTION__ */

/* eof (t-list-macro.c) */
