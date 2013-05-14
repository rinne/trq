## Process this file with automake to produce Makefile.in

#
#
# trq/tests/Makefile.am
#
# Authors: Timo J. Rinne <tri@iki.fi>
#          Tero Kivinen <kivinen@iki.fi>
#
# Copyright (C) 1998 Timo J. Rinne and Tero Kivinen
# All rights reserved.  See file COPYRIGHT for details.
# 
#

AUTOMAKE_OPTIONS = 1.0 foreign dist-zip no-dependencies

TESTS = 	t-deque-func	\
		t-deque-macro	\
		t-list-func	\
		t-list-macro

EXTRA_PROGRAMS = $(TESTS)

EXTRA_DIST =	t-deque.c	\
		t-list.c

LDADD = ../libtrq.a ../trqtest/libtrqtest.a

INCLUDES =	-I$(srcdir) -I.				\
		-I$(srcdir)/.. -I..			\
		-I$(srcdir)/../trqtest -I../trqtest

t_deque_func_SOURCES =		t-deque-func.c
t_deque_func_DEPENDENCIES =	$(LDADD)
t_deque_macro_SOURCES =		t-deque-macro.c
t_deque_macro_DEPENDENCIES =	$(LDADD)
t_list_func_SOURCES =		t-list-func.c
t_list_func_DEPENDENCIES =	$(LDADD)
t_list_macro_SOURCES =		t-list-macro.c
t_list_macro_DEPENDENCIES =	$(LDADD)

t-deque-func.o: t-deque.c
t-list-func.o: t-list.c
t-deque-macro.o: t-deque.c
t-list-macro.o: t-list.c

# eof (Makefile.am)
