/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  List for struct type with only one link pointer (x->next).
 *  Prototypes for fuction-only i.e. non-inlined library functions.
 *  ----------------------------------------------------------------------
 *  Created      : Sun Apr 19 17:25:48 1998 tri
 *  Last modified: Wed Oct 10 01:04:46 2001 tri
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
 * $Id: trq_list_f.h,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_list_f.h,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.4  2001/04/24 18:29:57  fis
 * 	changed method names in sshadt_map.h
 *
 * Revision 1.3  1998/07/19 12:42:18  tri
 *      Fixed annoying typo in the log entry.
 *
 * Revision 1.2  1998/07/06 13:51:10  tri
 *      Fixed log entries to have CVS like indentation.
 *
 * Revision 1.1  1998/07/06 13:11:52  tri
 *      Added to CVS.
 *
 * Revision 1.7  1998/07/06 09:30:58  tri
 *      Added endlog.
 *
 * Revision 1.6  1998/06/22 16:27:09  tri
 *      Removed _p from in_order function name.
 *
 * Revision 1.5  1998/06/18 14:01:01  tri
 *      Added trq_list_in_order_p.
 *
 * Revision 1.4  1998/06/12 21:19:33  tri
 *      Added trq_list_insert_in_order.
 *
 * Revision 1.3  1998/04/23 17:51:51  tri
 *      SNAFU
 *
 * Revision 1.2  1998/04/23 17:51:23  tri
 *      Added insertion sort.
 *
 * Revision 1.1  1998/04/22 22:00:12  tri
 *      Initial revision
 *
 * $EndLog$
 */
#ifndef __TRQ_LIST_F__H__
#define __TRQ_LIST_F__H__ 1

int trq_list_quicksort(trq_list *L,
                       trq_compare test,
                       void *context);

int trq_list_mergesort(trq_list *L,
                       trq_compare test,
                       void *context);

int trq_list_bubblesort(trq_list *L,
                        trq_compare test,
                        void *context);

int trq_list_insertionsort(trq_list *L,
                           trq_compare test,
                           void *context);

int trq_list_insert_in_order(trq_list *L,
                             void *item,
                             trq_compare test,
                             void *context);

int trq_list_in_order(trq_list *L,
                      trq_compare test,
                      void *context);

int trq_list_shuffle(trq_list *L, 
		     unsigned char *seed, 
		     size_t seed_len);

#endif /* !__TRQ_LIST_F__H__ */
/* eof (trq_list_f.h) */
