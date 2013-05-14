/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  Prototypes for fuction-only i.e. non-inlined library functions.
 *  ----------------------------------------------------------------------
 *  Created      : Sun Apr 19 17:25:48 1998 tri
 *  Last modified: Wed Oct 10 01:04:38 2001 tri
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
 * $Id: trq_deque_f.h,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_deque_f.h,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.4  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.3  1998/07/19 12:42:15  tri
 *      Fixed annoying typo in the log entry.
 *
 * Revision 1.2  1998/07/06 13:51:03  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:42  tri
 *      Added to CVS.
 *
 * Revision 1.9  1998/07/06 08:06:14  tri
 *      Added endlog.
 *
 * Revision 1.8  1998/06/22 16:28:24  tri
 *      Removed _p from in_order function name.
 *
 * Revision 1.7  1998/06/11 18:55:20  tri
 *      Added trq_deque_in_order_p.
 *
 * Revision 1.6  1998/06/11 18:18:10  tri
 *      Added trq_deque_insert_in_order.
 *
 * Revision 1.5  1998/04/23 17:51:35  tri
 *      SNAFU
 *
 * Revision 1.4  1998/04/23 17:50:51  tri
 *      Added insertion sort.
 *
 * Revision 1.3  1998/04/21 11:24:04  tri
 *      Typedef `callback' function types.
 *
 * Revision 1.2  1998/04/20 18:13:20  tri
 *      Added bubblesort.
 *
 * Revision 1.1  1998/04/19 14:28:20  tri
 *      Initial revision
 *
 * $EndLog$
 */
#ifndef __TRQ_DEQUE_F__H__
#define __TRQ_DEQUE_F__H__ 1

int trq_deque_quicksort(trq_deque *Q,
                        trq_compare test,
                        void *context);

int trq_deque_mergesort(trq_deque *Q,
                        trq_compare test,
                        void *context);

int trq_deque_bubblesort(trq_deque *Q,
                         trq_compare test,
                         void *context);

int trq_deque_insertionsort(trq_deque *Q,
                            trq_compare test,
                            void *context);

int trq_deque_insert_in_order(trq_deque *Q,
                              void *item,
                              trq_compare test,
                              void *context);

int trq_deque_in_order(trq_deque *Q,
                       trq_compare test,
                       void *context);

int trq_deque_shuffle(trq_deque *Q, 
		      unsigned char *seed, 
		      size_t seed_len);

#endif /* !__TRQ_DEQUE_F__H__ */
/* eof (trq_deque_f.h) */
