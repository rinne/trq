/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Test function versions of DeQue operations.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Jun 17 19:42:57 1998 tri
 *  Last modified: Wed Oct 10 01:08:38 2001 tri
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
 * $Id: t-deque-func.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: t-deque-func.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.3  2001/04/24 18:29:58  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.2  1998/07/06 13:53:46  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:14:02  tri
 *      Added to CVS.
 *
 * Revision 1.2  1998/07/06 09:32:12  tri
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

#define __T_DEQUE_FUNC_C__

#include "t-deque.c"

/* eof (t-deque-func.c) */
