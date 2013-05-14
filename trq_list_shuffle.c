/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  Shuffle deque.
 *  ----------------------------------------------------------------------
 *  Created      : Tue Oct  9 17:01:32 2001 tri
 *  Last modified: Tue May 14 20:22:37 2013 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 2001, 2013
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

#include <trq_list.h>

int trq_list_shuffle(trq_list *L, unsigned char *seed, size_t seed_len)
{
    trq_deque q;

    trq_list_to_deque(&q, L);
    trq_deque_shuffle(&q, seed, seed_len);
    trq_deque_to_list(L, &q);
    return trq_list_length(L);
}

/* eof (trq_list_shuffle.c) */
