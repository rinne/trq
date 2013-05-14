/*
 *  ----------------------------------------------------------------------
 *  Various utils for testing.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Apr 15 21:11:41 1998 tri
 *  Last modified: Tue May 14 20:34:21 2013 tri
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
