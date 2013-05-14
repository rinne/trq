/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Deque for struct type with only one link pointer (x->next).
 *  Shuffle deque.
 *  ----------------------------------------------------------------------
 *  Created      : Tue Oct  9 17:01:32 2001 tri
 *  Last modified: Wed Oct 10 01:03:07 2001 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 2001
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
 * $Id: trq_deque_shuffle.c,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_deque_shuffle.c,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * $EndLog$
 */

#include <trq_deque.h>

struct trq_deque_shuffle_context {
  unsigned char *seed;
  size_t seed_len;
};

/* Internal functions */
int trq_deque_shuffle_compare(void *item1, void *item2, void *context);
unsigned long trq_shuffle_crc24_buf(unsigned char *buf, 
				    size_t buf_len,
				    unsigned long init_val);

#define TRQ_SHUFFLE_CRC24_INIT 0xb704ceL
#define TRQ_SHUFFLE_CRC24_POLY 0x1864cfbL

/* CRC24 routine. */
unsigned long trq_shuffle_crc24_buf(unsigned char *buf, 
				    size_t buf_len,
				    unsigned long init_val)
{
    unsigned long crc;
    int i, j;
	
    if (init_val == ((unsigned long)-1))
	crc = TRQ_SHUFFLE_CRC24_INIT;
    else
	crc = init_val;

    for (i = 0; i < buf_len; i++) {
	crc ^= ((unsigned long)(buf[i])) << 16;
	for (j = 0; j < 8; j++) {
	    crc <<= 1;
	    if (crc & 0x1000000)
		crc ^= TRQ_SHUFFLE_CRC24_POLY;
	}
    }
    crc = crc & 0xffffffL;
    return crc;
}

/* Make pseudorandom but deterministic "compare" between entities using
   hash value of the entity pointer and seed in context.
   CAUTION!  If you want the shuffle to be cryptographically sound,
   you MUST reimplement this function using some real hash algorithm. */
int trq_deque_shuffle_compare(void *item1, void *item2, void *context)
{
    struct trq_deque_shuffle_context *ctx = 
	(struct trq_deque_shuffle_context *)context;
    unsigned long h1, h2;
    void *x;

    x = item1;
    h1 = trq_shuffle_crc24_buf((unsigned char *)&x,
			       sizeof (void *), 
			       (unsigned long)-1);
    h1 = trq_shuffle_crc24_buf(ctx->seed,
			       ctx->seed_len, 
			       h1);
    x = item2;
    h2 = trq_shuffle_crc24_buf((unsigned char *)&x,
			       sizeof (void *), 
			       (unsigned long)-1);
    h2 = trq_shuffle_crc24_buf(ctx->seed,
			       ctx->seed_len, 
			       h2);
    if (h1 > h2)
	return 1;
    else if (h2 > h1)
	return -1;
    else
	return 0;
}

/* Shuffle a deque.  Be sure to submit different seed buffer 
   with every call or face the consequences.  In order to make
   shuffle cryptographically solid, the seed buffer should be
   initialized with cryptographically solid (pseudo)random
   numbers (again before each call). */
int trq_deque_shuffle(trq_deque *Q, unsigned char *seed, size_t seed_len)
{
    struct trq_deque_shuffle_context ctx;

    ctx.seed_len = seed_len;
    ctx.seed = seed;
    trq_deque_mergesort(Q, trq_deque_shuffle_compare, (void *)&ctx);
    return trq_deque_length(Q);
}

/* eof (trq_deque_shuffle.c) */
