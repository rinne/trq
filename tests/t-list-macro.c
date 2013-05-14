/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Test macro versions of list operations.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Jun 17 19:42:57 1998 tri
 *  Last modified: Wed Oct 10 01:07:44 2001 tri
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
 * $Id: t-list-macro.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: t-list-macro.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.5  2001/04/24 18:29:58  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.4  1999/12/08 20:29:21  tmo
 *      Changes from the ipsec-3.0 branch.
 *
 * Revision 1.3  1999/11/24 17:45:17  tri
 *      Merged from branch.
 *
 * Revision 1.2.20.1  1999/11/24 17:44:24  tri
 *      Removed warning.
 *
 * Revision 1.2  1998/07/06 13:53:51  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:14:06  tri
 *      Added to CVS.
 *
 * Revision 1.2  1998/07/06 09:33:27  tri
 *      Added endlog.
 *
 * Revision 1.1  1998/06/17 17:02:55  tri
 *      Initial revision
 *
 * $EndLog$
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
