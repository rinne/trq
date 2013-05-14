/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Time measurement stuff for testing.
 *  ----------------------------------------------------------------------
 *  Created      : Wed Apr 15 21:11:41 1998 tri
 *  Last modified: Tue May 14 20:26:58 2013 tri
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
#include <stdio.h>

#ifdef HAVE_STRING_H
#include <string.h>
#elif HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif

#ifdef HAVE_STDLIB_H
#  include <stdlib.h>
#elif HAVE_MALLOC_H
#  include <malloc.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#elif HAVE_TYPES_H
#include <types.h>
#endif

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#elif HAVE_TIME_H
#include <time.h>
#endif

struct time_measure {
#if HAVE_GETTIMEOFDAY
    struct timeval t0, t1;
#else
    time_t t0, t1;
#endif
    int t0_valid, t1_valid;
};

#include "trq_test.h"

static double time_measure_calibration = 0.0;

#ifndef HAVE_SLEEP
#ifndef HAVE_USLEEP
int dummy_var = 0;

int dummy_call(int x)
{
    dummy_var = x + 1;
    return dummy_var;
}

void busy_sleep(int sec)
{
    int i;
    int j;
    unsigned long t0 = (unsigned long)(time(NULL));
    unsigned long t1;

    if (sec < 1)
	return;
    for (j = 0; j < 100; j++) {
	for (i = 0; i < 1000000; i++)
	    dummy_call(i);
	t1 = (unsigned long)(time(NULL));
	if ((int)(t1 - t0) >= sec)
	    return;
	dummy_call(j);
    }
    return; /* We bailed out, but it took a while anyway... */
}

#define sleep busy_sleep

#endif
#endif

void time_measure_calibrate()
{
    int i, j, n;
    time_measure_t m;
    double diff, cum;
    char *prefix;

    cum = 0.0;;
    n = 0;
    m = time_measure_alloc();
    for (i = 0; i < 3; i++) {
	if (i)
#ifdef HAVE_USLEEP
	    usleep(100000 * i);
#else
	    sleep(1);
#endif
	for (j = 0; j < 4096; j++) {
	    time_measure_reset(m);
	    time_measure_start(m);
	    time_measure_stop(m);
	    cum += time_measure_get(m);
	    n++;
	}
    }
    time_measure_calibration += cum / (double)n;
    return;
}

time_measure_t time_measure_alloc(void)
{
    time_measure_t  r;

    r = calloc(1, sizeof (struct time_measure));
    return r;
}

void time_measure_start(time_measure_t m)
{
    if (!m)
	return;
#if HAVE_GETTIMEOFDAY
    gettimeofday(&(m->t0), NULL);
#else
    m->t0 = time(NULL);
#endif
    m->t0_valid = 1;
    return;
}

void time_measure_stop(time_measure_t m)
{
    if (!m)
	return;
#if HAVE_GETTIMEOFDAY
    gettimeofday(&(m->t1), NULL);
#else
    m->t1 = time(NULL);
#endif
    if (m->t0_valid)
	m->t1_valid = 1;
    return;
}

void time_measure_reset(time_measure_t m)
{
    if (m)
	memset(m, 0, sizeof (struct time_measure));
    return;
}

double time_measure_get(time_measure_t m)
{
    double r;

#if HAVE_GETTIMEOFDAY
    r = ((((double)(m->t1.tv_sec)) - ((double)(m->t0.tv_sec))) +
	 ((((double)(m->t1.tv_usec)) - ((double)(m->t0.tv_usec))) /
	  1000000.0)) - time_measure_calibration;
#else
    r = (double)(m->t1) - (double)(m->t0);
#endif
    return r;
}

void time_measure_print(time_measure_t m, unsigned long count, char *unit)
{
    double diff;
    double countdiff;
    unsigned long countfreq;

    if (!(m && m->t0_valid && m->t1_valid)) {
	fprintf(stderr, "Time measurement failed.\n");
	return;
    }
    if (!unit)
	unit = "unit";
    diff = time_measure_get(m);
    if (diff > 0.000001) {
	fprintf(stderr, "Measured time: %.6f sec", diff);
	if (count) {
	    char *prefix;

	    fprintf(stderr, " (%lu %s)\n", count, unit);
	    countdiff = diff / (double)count;
	    countfreq = (unsigned long)(count / diff);
	    fprintf(stderr, "               ");
	    if (countfreq)
		fprintf(stderr, "%lu %s/sec (", countfreq, unit);
	    countdiff = si_prefix(countdiff, &prefix);
	    fprintf(stderr, "%.6f %sseconds/%s", countdiff, prefix, unit);
	    if (countfreq)
		fprintf(stderr, ")");
	}
	fprintf(stderr, "\n");
    } else {
	fprintf(stderr, "Measured time: 0 seconds\n");
    }

}

void time_measure_free(time_measure_t m)
{
    time_measure_reset(m);
    if (m)
	free(m);
    return;
}

/* eof (time_measure.c) */
