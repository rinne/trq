/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  List for struct type with only one link pointer (x->next).
 *  Prototypes for fuction-only i.e. non-inlined library functions.
 *  ----------------------------------------------------------------------
 *  Created      : Sun Apr 19 17:25:48 1998 tri
 *  Last modified: Tue May 14 20:22:59 2013 tri
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
