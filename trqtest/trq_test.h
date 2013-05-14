/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Various utils for testing.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Apr 15 21:11:41 1998 tri
 *  Last modified: Wed Oct 10 01:09:55 2001 tri
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
 * $Id: trq_test.h,v 1.1.1.1 2001/10/09 22:29:31 tri Exp $
 *
 * $Log: trq_test.h,v $
 * Revision 1.1.1.1  2001/10/09 22:29:31  tri
 * 	Imported back from the SSH source tree.
 *
 * Revision 1.1  1998/04/16 14:39:41  tri
 * Initial revision
 *
 *
 */
#ifndef __TEST__H__
#define __TEST__H__ 1

/*
 * Time measurement stuff.
 */
typedef struct time_measure *time_measure_t;

void time_measure_calibrate();
time_measure_t time_measure_alloc(void);
void time_measure_start(time_measure_t m);
void time_measure_stop(time_measure_t m);
void time_measure_reset(time_measure_t m);
double time_measure_get(time_measure_t m);
void time_measure_print(time_measure_t m, unsigned long count, char *unit);
void time_measure_free(time_measure_t m);

/*
 * SI-Unit prefix.
 */
double si_prefix(double value, char **prefix);

#endif /* __TEST__H__ */
