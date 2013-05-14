/*   -*- c -*-
 * 
 *  ----------------------------------------------------------------------
 *  si_prefix - fit double with suitable si-prefix.
 *  ----------------------------------------------------------------------
 *  Created      : Sat Dec  6 15:55:14 1997 tri
 *  Last modified: Tue May 14 20:20:03 2013 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 1997-1998, 2001, 2013
 *  Timo J. Rinne <tri@iki.fi>
 *  All rights reserved.  See file COPYRIGHT for details.
 *  ----------------------------------------------------------------------
 *  Any express or implied warranties are disclaimed.  In no event
 *  shall the author be liable for any damages caused (directly or
 *  otherwise) by the use of this software.
 *  ----------------------------------------------------------------------
 *
 */

#include <stdio.h>

#include "trq_test.h"

static char *lo_prefix[] = { "",
			     "milli",
			     "micro",
			     "nano",
			     "pico",
			     "femto",
			     "atto",
			     "zepto",
			     "yocto",
			     NULL };

static char *hi_prefix[] = { "",
			     "kilo", 
			     "mega",
			     "giga",
			     "tera",
			     "peta",
			     "exa",
			     "zetta",
			     "yotta",
			     NULL };

/*
 * Synopsis:
 *
 * si_prefix(double value, char **prefix)
 *      
 *
 * Arguments:
 *	value	- double to fit.
 *      prefix	- char pointer to turn to prefix string
 *
 * Return value:
 *      Double that is argument multiplied according to returned prefix.
 *	if prefix is empty string, the input value is returned.
 *	Call never fails.
 */
double si_prefix(double value, char **prefix)
{
    char **pre;
    double x = (value >= 0.0) ? value : -value;
    int negative = (value < 0.0);

    if ((x > 0.0) && (x < 1.0)) {
	pre = lo_prefix;
	while ((x < 1.0) && pre[1]) {
	    x *= 1000.0;
	    pre++;
	}
	if (x < 0.001) {
	    *prefix = "";
	    return value;
	}
	*prefix = *pre;
    } else if (x >= 1000.0) {
	pre = hi_prefix;
	while ((x >= 1000.0) && pre[1]) {
	    x /= 1000.0;
	    pre++;
	}
	if (x >= 1000.0) {
	    *prefix = "";
	    return value;
	}
	*prefix = *pre;
    } else {
	*prefix = "";
    }
    return (negative ? (-x) : x);
}

#if TEST_MAIN
main(int argc, char **argv)
{
    double x, y;
    char *u;
    char *p;

    if (argc > 1)
	u = argv[1];
    else
	u = "";

    if (1 == scanf("%lf", &x)) {
	y = si_prefix(x, &p);
	printf("%.2e = %.2f %s%s(s)\n", x, y, p, u);
    }
    exit(0);
}
#endif

/* eof (si_prefix.c) */
