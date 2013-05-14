/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Test function versions of DeQue operations.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Jun 17 19:42:57 1998 tri
 *  Last modified: Tue May 14 20:21:28 2013 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 1995-1998, 2001, 2013
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

#define TRQ_USE_FUNCTIONS 2

#define __T_DEQUE_FUNC_C__

#include "t-deque.c"

/* eof (t-deque-func.c) */
