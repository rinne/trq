## Process this file with automake to produce Makefile.in

#
#
# trq/Makefile.am
#
# Authors: Timo J. Rinne <tri@iki.fi>
#          Tero Kivinen <kivinen@iki.fi>
#
# Copyright (C) 1998 Timo J. Rinne and Tero Kivinen
# All rights reserved.  See file COPYRIGHT for details.
# 
# $Log: Makefile.am,v $
# Revision 1.1.1.1  2001/10/09 22:29:31  tri
# 	Imported back from the SSH source tree.
#
# Revision 1.6  1998/07/06 08:01:27  tri
# Added log.
#
# $EndLog$
#

AUTOMAKE_OPTIONS = 1.0 foreign dist-zip no-dependencies

SUBDIRS = trqtest tests

noinst_LIBRARIES = libtrq.a

man_MANS = 		trq_deque.3		\
			trq_list.3

EXTRA_DIST =		$(man_MANS)		\
			COPYRIGHT		\
			INSTALL			\
			README.md		\
			TODO			\
			ChangeLog		\
			configure		\
			gen_trq_x_c		\
			trq-gdbinit

libtrq_a_SOURCES =	trq_deque.c		\
			trq_deque_sort.c	\
			trq_deque_shuffle.c	\
			trq_list.c		\
			trq_list_sort.c		\
			trq_list_shuffle.c

libtrq_a_LIBADD =	trq_deque_x_001.o	\
			trq_deque_x_002.o	\
			trq_deque_x_003.o	\
			trq_deque_x_004.o	\
			trq_deque_x_005.o	\
			trq_deque_x_006.o	\
			trq_deque_x_007.o	\
			trq_deque_x_008.o	\
			trq_deque_x_009.o	\
			trq_deque_x_010.o	\
			trq_list_x_001.o	\
			trq_list_x_002.o	\
			trq_list_x_003.o	\
			trq_list_x_004.o	\
			trq_list_x_005.o	\
			trq_list_x_006.o	\
			trq_list_x_007.o	\
			trq_list_x_008.o	\
			trq_list_x_009.o	\
			trq_list_x_010.o	\
			trq_list_x_011.o	\
			trq_list_x_012.o	\
			trq_list_x_013.o	\
			trq_list_x_014.o	\
			trq_list_x_015.o	\
			trq_list_x_016.o

list_libssh_a_objects:
	@echo $(libtrq_a_OBJECTS) $(libtrq_a_LIBADD)

include_HEADERS =	trq_deque.h 		\
			trq_deque_x.h 		\
			trq_deque_f.h 		\
			trq_list.h		\
			trq_list_x.h 		\
			trq_list_f.h 		\
			trq_conf.h

INCLUDES = -I$(srcdir) -I.

TRQ_GENSRC =		trq_deque_x_001.c	\
			trq_deque_x_002.c	\
			trq_deque_x_003.c	\
			trq_deque_x_004.c	\
			trq_deque_x_005.c	\
			trq_deque_x_006.c	\
			trq_deque_x_007.c	\
			trq_deque_x_008.c	\
			trq_deque_x_009.c	\
			trq_deque_x_010.c	\
			trq_list_x_001.c	\
			trq_list_x_002.c	\
			trq_list_x_003.c	\
			trq_list_x_004.c	\
			trq_list_x_005.c	\
			trq_list_x_006.c	\
			trq_list_x_007.c	\
			trq_list_x_008.c	\
			trq_list_x_009.c	\
			trq_list_x_010.c	\
			trq_list_x_011.c	\
			trq_list_x_012.c	\
			trq_list_x_013.c	\
			trq_list_x_014.c	\
			trq_list_x_015.c	\
			trq_list_x_016.c

CLEANFILES = $(TRQ_GENSRC)

includes:
	for file in $(include_HEADERS); do \
		$(COPY_INCLUDE) $(srcdir)/$$file ../../include/$$file; \
	done

dist-hook:
	rm -f $(distdir)/trq_conf.h
	find $(distdir) -type f -exec chmod u+w {} \;
	find $(distdir) -name COPYRIGHT -exec chmod -w {} \;

$(TRQ_GENSRC): $(srcdir)/gen_trq_x_c $(srcdir)/trq_deque.h $(srcdir)/trq_list.h
	$(srcdir)/gen_trq_x_c @gen_trq_x_c_flags@ $@

# eof (Makefile.am)
