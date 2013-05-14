/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Test function versions of list operations.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Jun 17 19:42:57 1998 tri
 *  Last modified: Wed Oct 10 01:07:31 2001 tri
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
 * $Id: t-list-func.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: t-list-func.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.5  2001/04/24 18:29:58  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.4  1999/12/08 20:29:18  tmo
 *      Changes from the ipsec-3.0 branch.
 *
 * Revision 1.3  1999/11/24 17:45:17  tri
 *      Merged from branch.
 *
 * Revision 1.2.20.1  1999/11/24 17:44:45  tri
 *      Comment.
 *
 * Revision 1.2  1998/07/06 13:53:50  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:14:05  tri
 *      Added to CVS.
 *
 * Revision 1.2  1998/07/06 09:33:56  tri
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

#define TRQ_USE_FUNCTIONS 2

#define __T_LIST_FUNC_C__

#include "t-list.c"

/* eof (t-list-func.c) */
