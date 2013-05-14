## Process this file with automake to produce Makefile.in

#
#
# trq/trqtest/Makefile.am
#
# Authors: Timo J. Rinne <tri@iki.fi>
#          Tero Kivinen <kivinen@iki.fi>
#
# Copyright (C) 1998 Timo J. Rinne and Tero Kivinen
# All rights reserved.  See file COPYRIGHT for details.
# 
#

AUTOMAKE_OPTIONS = 1.0 foreign dist-zip no-dependencies

noinst_LIBRARIES = libtrqtest.a

libtrqtest_a_SOURCES =	si_prefix.c		\
			time_measure.c

noinst_HEADERS =	trq_test.h

INCLUDES = -I$(srcdir) -I.

includes:
	for file in $(include_HEADERS); do \
		$(COPY_INCLUDE) $(srcdir)/$$file ../../include/$$file; \
	done

# eof (Makefile.am)
