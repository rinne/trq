/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Test List operations.
 *  ----------------------------------------------------------------------
 *  Created      : Tue Nov 21 17:47:40 1995 tri
 *  Last modified: Tue May 14 20:21:05 2013 tri
 *  ----------------------------------------------------------------------
 *  Copyright © 1995-1999, 2001, 2013
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

#ifndef __T_LIST_MACRO_C__
#  ifndef __T_LIST_FUNC_C__
#    error "This source file can be compiled only within nongeneric source."
#  endif /* __T_LIST_FUNC_C__ */
#endif /* __T_LIST_MACRO_C__ */

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

#include <trq_list.h>

#include "trq_test.h"

#define TMAX 16

int verbose = 0;

typedef struct q_item {
    struct q_item *next;
    char name[16];
} *q_item_t;

static void item_init(void);
static void free_item(q_item_t b);
static q_item_t alloc_item(void);

static void *mapcar_dummy(void *item_in, void *context_in);
static void *mapcar_test_1(void *item, void *context);
static void *mapcar_print(void *item_in, void *context_in);
static void *mapcar_free_and_drop(void *item_in, void *context_in);

#define list_clear(Q) (trq_list_mapcar((Q), mapcar_free_and_drop, (void *)0))

#define REWIND_INVALIDATE 0
#define REWIND_REWIND     1
#define REWIND_END        2
#define REWIND_MIDDLE     3
#define REWIND_RANDOM     4

void list_rewind_mode(trq_list *L, int mode)
{
    int x;

    if (trq_list_length(L) == 0)
        return;

    switch (mode) {
    case REWIND_INVALIDATE:
        trq_list_pointer_invalidate(L);
        break;
    case REWIND_REWIND:
        trq_list_goto_first(L);
        break;
    case REWIND_END:
        trq_list_goto_last(L);
        break;
    case REWIND_MIDDLE:
        trq_list_goto_first(L);
        x = (int)(trq_list_length(L) / 2);
        trq_list_fw(L, x);
        break;
    case REWIND_RANDOM:
        trq_list_goto_first(L);
        x = (int)(random() % trq_list_length(L));
        trq_list_fw(L, x);
        break;
    default:
        /*NOTHING*/
        break;
    }

    return;
}

int get_put_time_test(int n)
{
    time_measure_t tm;
    q_item_t b1, b2, b3, b4, b5, b6;
    int i;
    trq_list Q;

    if (verbose)
        fprintf(stderr, "Testing %d put and get operations...\n", n);

    tm = time_measure_alloc();

    b1 = alloc_item();
    b2 = alloc_item();
    b3 = alloc_item();
    b4 = alloc_item();
    b5 = alloc_item();
    b6 = alloc_item();

    sprintf(b1->name, "Item #1");
    sprintf(b2->name, "Item #2");
    sprintf(b3->name, "Item #3");
    sprintf(b4->name, "Item #4");
    sprintf(b5->name, "Item #5");
    sprintf(b6->name, "Item #6");

    trq_list_init(&Q, struct q_item, next);

    time_measure_start(tm);
    for (i = ((n / 50) + 1); i ; i--) {
        trq_list_insert_last(&Q, b1);
        trq_list_insert_last(&Q, b2);
        trq_list_insert_last(&Q, b3);
        trq_list_insert_last(&Q, b4);
        trq_list_insert_last(&Q, b5);
        trq_list_insert_last(&Q, b6);
        b4 = trq_list_get_first(&Q);
        b5 = trq_list_get_first(&Q);
        b6 = trq_list_get_first(&Q);
        b1 = trq_list_get_first(&Q);
        b2 = trq_list_get_first(&Q);
        b3 = trq_list_get_first(&Q);
        trq_list_insert_last(&Q, b1);
        trq_list_insert_first(&Q, b2);
        trq_list_insert_last(&Q, b3);
        trq_list_insert_first(&Q, b4);
        b1 = trq_list_get_last(&Q);
        b2 = trq_list_get_last(&Q);
        b3 = trq_list_get_last(&Q);
        b4 = trq_list_get_last(&Q);
        /* 20 operations */
        trq_list_insert_last(&Q, b5);
        trq_list_insert_last(&Q, b6);
        trq_list_insert_last(&Q, b1);
        b1 = trq_list_get_first(&Q);
        trq_list_insert_last(&Q, b2);
        b2 = trq_list_get_first(&Q);
        trq_list_insert_first(&Q, b3);
        b3 = trq_list_get_first(&Q);
        trq_list_insert_first(&Q, b4);
        b4 = trq_list_get_last(&Q);
        trq_list_insert_last(&Q, b1);
        b1 = trq_list_get_last(&Q);
        trq_list_insert_first(&Q, b2);
        b2 = trq_list_get_first(&Q);
        trq_list_insert_last(&Q, b3);
        b3 = trq_list_get_first(&Q);
        trq_list_insert_first(&Q, b1);
        b1 = trq_list_get_last(&Q);
        b5 = trq_list_get_first(&Q);
        b6 = trq_list_get_first(&Q);
        /* 40 operations */
        trq_list_insert_last(&Q, b3);
        trq_list_insert_last(&Q, b5);
        trq_list_insert_last(&Q, b2);
        trq_list_insert_last(&Q, b1);
        trq_list_insert_last(&Q, b6);
        b1 = trq_list_get_first(&Q);
        b2 = trq_list_get_first(&Q);
        b3 = trq_list_get_first(&Q);
        b5 = trq_list_get_first(&Q);
        b6 = trq_list_get_first(&Q);
        /* 50 operations */
    }
    time_measure_stop(tm);
    if (verbose)
        time_measure_print(tm, n, "operation");
    time_measure_free(tm);
    return 0;
}

int functional_test(void)
{
    trq_list Q, Q2;
    q_item_t b, tmp = (q_item_t)0;
    int i, state, r = 0;

    state = 0;
    trq_list_init(&Q, struct q_item, next);
    trq_list_init(&Q2, struct q_item, next);

    state++;
    for (i = 0; i < TMAX; i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %d", state, i);
        trq_list_insert_last(&Q, b);
    }
    while ((b = trq_list_get_last(&Q))) {
        if (verbose)
            fprintf(stderr, "list_get -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < TMAX; i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %d", state, i);
        trq_list_insert_last(&Q, b);
    }
    (void)trq_list_reverse(&Q);
    while ((b = trq_list_get_last(&Q))) {
        if (verbose)
            fprintf(stderr, "list_get -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < TMAX; i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %d", state, i);
        trq_list_insert_first(&Q, b);
    }
    while ((b = trq_list_get_last(&Q))) {
        if (verbose)
            fprintf(stderr, "list_get -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < ((TMAX / 2) + 1); i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %dF", state, i);
        trq_list_insert_last(&Q, b);
        b = alloc_item();
        sprintf(b->name, "%d) %dL", state, i);
        trq_list_insert_first(&Q, b);
    }
    while ((b = trq_list_get_last(&Q))) {
        if (verbose)
            fprintf(stderr, "list_get -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < ((TMAX / 2) + 1); i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %dF", state, i);
        trq_list_insert_last(&Q, b);
        b = alloc_item();
        if (i == 5)
            tmp = b;
        sprintf(b->name, "%d) %dL", state, i);
        trq_list_insert_first(&Q, b);
    }
    if (verbose)
        fprintf(stderr, "This should be nonzero (%d)\n",
                trq_list_member(&Q, tmp));
    if (verbose)
        fprintf(stderr, "This should be zero (%d)\n",
                trq_list_member(&Q, (void*)0xffffffff));

    if (trq_list_member(&Q, tmp) == 0)
        r++;
    if (trq_list_member(&Q, (void*)0xffffffff) != 0)
        r++;

    trq_list_mapcar(&Q, mapcar_test_1, (void *)0);
    (void)trq_list_reverse(&Q);
    trq_list_mapcar(&Q, mapcar_test_1, (void *)0);

    for (;;) {
        if ((b = trq_list_get_first(&Q))) {
            if (verbose)
                fprintf(stderr, "list_get -> \"%s\"\n", b->name);
            free_item(b);
        } else {
            break;
        }
        if ((b = trq_list_get_last(&Q))) {
            if (verbose)
                fprintf(stderr, "list_get -> \"%s\"\n", b->name);
            free_item(b);
        } else {
            break;
        }
    }
    if (verbose)
        fprintf(stderr, "This should be zero (%d)\n",
                trq_list_member(&Q, tmp));
    if (trq_list_member(&Q, tmp) != 0)
        r++;

    return r;
}

int member_test(void)
{
    int i;
    trq_list Q1, Q2;
    q_item_t b;
    q_item_t s11, s12, s21, s22;

    if (verbose)
        fprintf(stderr, "member_test\n");

    trq_list_init(&Q1, struct q_item, next);
    trq_list_init(&Q2, struct q_item, next);
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_list_insert_last(&Q1, b);
        if (i == 2)
            s11 = b;
    }
    s12 = b;
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/2", i);
        trq_list_insert_last(&Q2, b);
        if (i == 2)
            s21 = b;
    }
    s22 = b;

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "Q2:\n");
    trq_list_mapcar(&Q2, mapcar_print, NULL);

    if (verbose) {
        fprintf(stderr, "trq_list_member(Q1, \"%s\") -> %d\n", 
                s11->name,
                trq_list_member(&Q1, s11));
        fprintf(stderr, "trq_list_member(Q1, \"%s\") -> %d\n", 
                s12->name,
                trq_list_member(&Q1, s12));
        fprintf(stderr, "trq_list_member(Q1, \"%s\") -> %d\n", 
                s21->name,
                trq_list_member(&Q1, s21));
        fprintf(stderr, "trq_list_member(Q1, \"%s\") -> %d\n", 
                s22->name,
                trq_list_member(&Q1, s22));
        fprintf(stderr, "trq_list_member(Q2, \"%s\") -> %d\n", 
                s11->name,
                trq_list_member(&Q2, s11));
        fprintf(stderr, "trq_list_member(Q2, \"%s\") -> %d\n", 
                s12->name,
                trq_list_member(&Q2, s12));
        fprintf(stderr, "trq_list_member(Q2, \"%s\") -> %d\n", 
                s21->name,
                trq_list_member(&Q2, s21));
        fprintf(stderr, "trq_list_member(Q2, \"%s\") -> %d\n", 
                s22->name,
                trq_list_member(&Q2, s22));
    }
    return 0;
}

int sort_test_test(void *i1, void *i2, void *context)
{
    q_item_t item1 = (q_item_t)i1;
    q_item_t item2 = (q_item_t)i2;

#if 0
    if (verbose)
        fprintf(stderr, "sort_test_test(\"%s\", \"%s\")\n", 
                item1->name, item2->name);
#endif
    if (context)
        (*((int *)context))++;

    return strcmp(item1->name, item2->name);
}

#define DEFAULT_SORT_TEST_ITEMS 1000
#define NO_MORE_RND_BUBBLESORT  2000
#define NO_MORE_ORD_QUICKSORT   5000

int sort_test_raw(int items, int rewind_mode)
{
    int i, x, r = 0;
    trq_list Q1, Q2, Q3;
    q_item_t b1, b2, b3;
    q_item_t ti1, ti2, ti3;
    time_measure_t tm1, tm2, tm3;
    int tc1, tc2, tc3;

    if (verbose)
        fprintf(stderr, "sort_test\n");

    if (items < 1)
        items = DEFAULT_SORT_TEST_ITEMS;

    tm1 = time_measure_alloc();
    tm2 = time_measure_alloc();
    tm3 = time_measure_alloc();

    trq_list_init(&Q1, struct q_item, next);
    trq_list_init(&Q2, struct q_item, next);
    trq_list_init(&Q3, struct q_item, next);

    ti1 = alloc_item();
    ti2 = alloc_item();
    ti3 = alloc_item();

    sprintf(ti1->name, "@ Item FIRST");
    sprintf(ti2->name, "e Item CENTER");
    sprintf(ti3->name, "~ Item LAST");

    for (i = 1; i < items; i++) {
        b1 = alloc_item();
        b2 = alloc_item();
        x = (random() % 10) + 'a';
        sprintf(b1->name, "%c Item #%d", x, i);
        sprintf(b2->name, "%c Item #%d", x, i);
        trq_list_insert_last(&Q1, b1);
        trq_list_insert_last(&Q2, b2);
        if (items < NO_MORE_RND_BUBBLESORT) {
            b3 = alloc_item();
            sprintf(b3->name, "%c Item #%d", x, i);
            trq_list_insert_last(&Q3, b3);
        }
    }

    b1 = alloc_item();
    sprintf(b1->name, "z Item NONSORT");
    trq_list_insert_first(&Q1, b1);
    b2 = alloc_item();
    sprintf(b2->name, "z Item NONSORT");
    trq_list_insert_first(&Q2, b2);
    if (items < NO_MORE_RND_BUBBLESORT) {
        b3 = alloc_item();
        sprintf(b3->name, "z Item NONSORT");
        trq_list_insert_first(&Q3, b3);
    }

    tc1 = tc2 = tc3 = 0;

#if 0
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, (&Q1)->c);
    }
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_list_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
        trq_list_mapcar(&Q2, mapcar_print, (&Q2)->c);
    }
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
        trq_list_mapcar(&Q3, mapcar_print, (&Q3)->c);
    }
#endif

    list_rewind_mode(&Q1, rewind_mode);
    list_rewind_mode(&Q2, rewind_mode);
    list_rewind_mode(&Q3, rewind_mode);

#if 0
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, (&Q1)->c);
    }
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_list_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
        trq_list_mapcar(&Q2, mapcar_print, (&Q2)->c);
    }
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
        trq_list_mapcar(&Q3, mapcar_print, (&Q3)->c);
    }
#endif

    if ((trq_list_length(&Q1) > 1) &&
        trq_list_in_order(&Q1, sort_test_test, NULL)) {
        fprintf(stderr, "Q1 in order where shouldn't be\n");
        r++;
    }
    if ((trq_list_length(&Q2) > 1) &&
        trq_list_in_order(&Q2, sort_test_test, NULL)) {
        fprintf(stderr, "Q2 in order where shouldn't be\n");
        r++;
    }
    if (items < NO_MORE_RND_BUBBLESORT) {
        if ((trq_list_length(&Q3) > 1) &&
            trq_list_in_order(&Q3, sort_test_test, NULL)) {
            fprintf(stderr, "Q3 in order where shouldn't be\n");
            r++;
        }
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, (&Q1)->c);
    }

    if (verbose)
        fprintf(stderr, "trq_list_quicksort(Q1)\n");
    time_measure_reset(tm1);
    time_measure_start(tm1);
    trq_list_quicksort(&Q1, sort_test_test, &tc1);
    time_measure_stop(tm1);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, (&Q1)->c);
    }

    list_rewind_mode(&Q1, rewind_mode);

    if (trq_list_in_order(&Q1, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q1 not order where should be\n");
        r++;
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_list_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
        trq_list_mapcar(&Q2, mapcar_print, (&Q2)->c);
    }

    if (verbose)
        fprintf(stderr, "trq_list_mergesort(Q2)\n");
    time_measure_reset(tm2);
    time_measure_start(tm2);
    trq_list_mergesort(&Q2, sort_test_test, &tc2);
    time_measure_stop(tm2);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_list_length(&Q2));
    } else {
        if (verbose) {
            fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
        trq_list_mapcar(&Q2, mapcar_print, (&Q2)->c);
        }               
    }

    list_rewind_mode(&Q2, rewind_mode);

    if (trq_list_in_order(&Q2, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q2 not order where should be\n");
        r++;
    }

    if (items < NO_MORE_RND_BUBBLESORT) {
        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
        } else {
            if (verbose)
                fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
            trq_list_mapcar(&Q3, mapcar_print, (&Q3)->c);
        }
        
        if (verbose)
            fprintf(stderr, "trq_list_bubblesort(Q3)\n");
        time_measure_reset(tm3);
        time_measure_start(tm3);
        trq_list_bubblesort(&Q3, sort_test_test, &tc3);
        time_measure_stop(tm3);
        
        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
        } else {
            if (verbose)
                fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
            trq_list_mapcar(&Q3, mapcar_print, Q3.c);
        }
        if (verbose) {
            fprintf(stderr, "trq_list_in_order(Q3)\n");
        }
        list_rewind_mode(&Q3, rewind_mode);
        if (trq_list_in_order(&Q3, sort_test_test, NULL) == 0) {
            fprintf(stderr, "Q3 not order where should be\n");
            r++;
        }
        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
        } else {
            if (verbose)
                fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
            trq_list_mapcar(&Q3, mapcar_print, Q3.c);
        }
    }

    if (verbose)
        fprintf(stderr, "quicksort (%d tests):\n", tc1);
    if (verbose)
        time_measure_print(tm1, items, "item");
    if (verbose)
        fprintf(stderr, "mergesort (%d tests):\n", tc2);
    if (verbose)
        time_measure_print(tm2, items, "item");
    if (items < NO_MORE_RND_BUBBLESORT) {
        if (verbose)
            fprintf(stderr, "bubblesort (%d tests):\n", tc3);
        if (verbose)
            time_measure_print(tm3, items, "item");
    }

    /*
     * Same again with already sorted lists.
     */

    tc1 = tc2 = tc3 = 0;

    list_rewind_mode(&Q1, rewind_mode);
    list_rewind_mode(&Q2, rewind_mode);
    list_rewind_mode(&Q3, rewind_mode);

    if (items < NO_MORE_ORD_QUICKSORT) {
        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
        } else {
            if (verbose)
                fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
            trq_list_mapcar(&Q1, mapcar_print, Q1.c);
        }
        
        if (verbose)
            fprintf(stderr, "trq_list_quicksort(Q1)\n");
        time_measure_reset(tm1);
        time_measure_start(tm1);
        trq_list_quicksort(&Q1, sort_test_test, &tc1);
        time_measure_stop(tm1);

        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
        } else {
            if (verbose)
                fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
            trq_list_mapcar(&Q1, mapcar_print, Q1.c);
        }
        list_rewind_mode(&Q1, rewind_mode);
        if (trq_list_in_order(&Q1, sort_test_test, NULL) == 0) {
            fprintf(stderr, "Q1 not order where should be\n");
            r++;
        }
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_list_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
        trq_list_mapcar(&Q2, mapcar_print, Q2.c);
    }

    if (verbose)
        fprintf(stderr, "trq_list_mergesort(Q2)\n");
    time_measure_reset(tm2);
    time_measure_start(tm2);
    trq_list_mergesort(&Q2, sort_test_test, &tc2);
    time_measure_stop(tm2);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_list_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
        trq_list_mapcar(&Q2, mapcar_print, Q2.c);
    }
    list_rewind_mode(&Q2, rewind_mode);
    if (trq_list_in_order(&Q2, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q2 not order where should be\n");
        r++;
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
        trq_list_mapcar(&Q3, mapcar_print, Q3.c);
    }

    if (items >= NO_MORE_RND_BUBBLESORT) {
        Q3 = Q2;
    }
    if (verbose)
        fprintf(stderr, "trq_list_bubblesort(Q3)\n");
    time_measure_reset(tm3);
    time_measure_start(tm3);
    trq_list_bubblesort(&Q3, sort_test_test, &tc3);
    time_measure_stop(tm3);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
        trq_list_mapcar(&Q3, mapcar_print, Q3.c);
    }
    list_rewind_mode(&Q3, rewind_mode);
    if (trq_list_in_order(&Q3, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q3 not order where should be\n");
        r++;
    }

    if (items < NO_MORE_ORD_QUICKSORT) {
        if (verbose) {
            fprintf(stderr, "quicksort (%d tests):\n", tc1);
            time_measure_print(tm1, items, "item");
        }
    }
    if (verbose) {
        fprintf(stderr, "mergesort (%d tests):\n", tc2);
        time_measure_print(tm2, items, "item");
        fprintf(stderr, "bubblesort (%d tests):\n", tc3);
        time_measure_print(tm3, items, "item");
    }

    if (verbose)
        fprintf(stderr, "trq_list_insert_in_order 3 items\n");

    trq_list_insert_in_order(&Q3, ti1, sort_test_test, NULL);
    trq_list_insert_in_order(&Q3, ti2, sort_test_test, NULL);
    trq_list_insert_in_order(&Q3, ti3, sort_test_test, NULL);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_list_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_list_length(&Q3));
        trq_list_mapcar(&Q3, mapcar_print, Q3.c);
    }

    if (trq_list_in_order(&Q3, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q3 not order where should be\n");
        r++;
    }

    return r;
}

int sort_test(int items)
{
    int r;
    
    r = 0;

    r += sort_test_raw(items, REWIND_INVALIDATE);
    r += sort_test_raw(items, REWIND_REWIND);
    r += sort_test_raw(items, REWIND_END);
    r += sort_test_raw(items, REWIND_MIDDLE);
    r += sort_test_raw(items, REWIND_RANDOM);

    return r;
}

int pointer_test(void)
{
    int i;
    trq_list Q1, Q2;
    trq_deque D;
    q_item_t b;
    q_item_t e1, e2, h1, h2;

    if (verbose)
        fprintf(stderr, "pointer_test\n");

    trq_list_init(&Q1, struct q_item, next);
    trq_list_init(&Q2, struct q_item, next);

    for (i = 0; i < 8; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_list_insert_last(&Q1, b);
    }
    for (i = 0; i < 4; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/2", i);
        trq_list_insert_last(&Q2, b);
    }
    e1 = alloc_item();
    sprintf(e1->name, "Item #1/E");
    e2 = alloc_item();
    sprintf(e2->name, "Item #2/E");

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_goto_first(Q1)\n");
    trq_list_goto_first(&Q1);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_goto_first(Q1)\n");
    trq_list_goto_first(&Q1);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_fw(Q1, 2)\n");
    trq_list_fw(&Q1, 2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_insert_before(Q1, e1)\n");
    trq_list_insert_before(&Q1, e1);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_insert_after(Q1, e2)\n");
    trq_list_insert_after(&Q1, e2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_remove(Q1, e1 and e2)\n");
    trq_list_remove(&Q1, e1);
    trq_list_remove(&Q1, e2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_insert_last(Q1, e1)\n");
    if (verbose)
        fprintf(stderr, "trq_list_insert_first(Q1, e2)\n");
    trq_list_insert_last(&Q1, e1);
    trq_list_insert_first(&Q1, e2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_remove(Q1, e1 and e2)\n");
    trq_list_remove(&Q1, e1);
    trq_list_remove(&Q1, e2);

    if (verbose)
        fprintf(stderr, "trq_list_get_fw(Q1)");
    h1 = trq_list_get_fw(&Q1);
    if (verbose)
        fprintf(stderr, "-> %s\n", h1 ? h1->name : NULL);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    
    if (verbose)
        fprintf(stderr, "trq_list_get_bw(Q1)");
    h2 = trq_list_get_bw(&Q1);
    if (verbose)
        fprintf(stderr, "-> %s\n", h2 ? h2->name : NULL);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    
    if (verbose)
        fprintf(stderr, "trq_list_insert_after(Q1, %s)\n", h1->name);
    trq_list_insert_after(&Q1, h1);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_fw(Q1, 2)\n");
    trq_list_fw(&Q1, 2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_insert_before(Q1, %s)\n", h2->name);
    trq_list_insert_before(&Q1, h2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_bw(Q1, 2)\n");
    trq_list_bw(&Q1, 2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_insert_first(Q1, %s)\n", e1->name);
    trq_list_insert_first(&Q1, e1);

    if (verbose)
        fprintf(stderr, "trq_list_insert_last(Q1, %s)\n", e2->name);
    trq_list_insert_last(&Q1, e2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_reverse(Q1)\n");
    trq_list_reverse(&Q1);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_get_last(Q1)");
    h1 = trq_list_get_last(&Q1);
    if (verbose)
        fprintf(stderr, "-> %s\n", h1 ? h1->name : NULL);
    if (verbose)
        fprintf(stderr, "trq_list_get_first(Q1)");
    h2 = trq_list_get_first(&Q1);
    if (verbose)
        fprintf(stderr, "-> %s\n", h2 ? h2->name : NULL);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx) (backwards)\n", 
                (unsigned long)(Q1.c));
    trq_list_mapcar_reverse(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_to_deque(&D, &Q1)\n");
    trq_list_to_deque(&D, &Q1);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "D: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_deque_mapcar(&D, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_to_list(&Q1, &D)\n");
    trq_deque_to_list(&Q1, &D);

    if (verbose)
        fprintf(stderr, "D: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_deque_mapcar(&D, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_goto_first(Q1)\n");
    trq_list_goto_first(&Q1);
    if (verbose)
        fprintf(stderr, "trq_list_fw(Q1, 2)\n");
    trq_list_fw(&Q1, 2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "Q2: (ptr = 0x%08lx)\n", (unsigned long)(Q2.c));
    trq_list_mapcar(&Q2, mapcar_print, Q2.c);

    if (verbose)
        fprintf(stderr, "trq_list_join_after_last(Q1, Q2)\n");
    trq_list_join_after_last(&Q1, &Q2);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "Q2: (ptr = 0x%08lx)\n", (unsigned long)(Q2.c));
    trq_list_mapcar(&Q2, mapcar_print, Q2.c);

    if (verbose)
        fprintf(stderr, "trq_list_goto_last(Q1)\n");
    trq_list_goto_last(&Q1);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_bw(Q1, 4)\n");
    trq_list_bw(&Q1, 4);

    if (verbose)
        fprintf(stderr, "Q1: (ptr = 0x%08lx)\n", (unsigned long)(Q1.c));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    return 0;
}

int shuffle_test(int items)
{
    int i, x, r = 0;
    trq_list Q1;
    q_item_t b1;
    time_measure_t tm1;

    if (verbose)
        fprintf(stderr, "shuffle_test\n");

    if (items < 1)
        items = DEFAULT_SORT_TEST_ITEMS;

    tm1 = time_measure_alloc();

    trq_list_init(&Q1, struct q_item, next);

    for (i = 1; i <= items; i++) {
        b1 = alloc_item();
        x = (random() % 10) + 'a';
        sprintf(b1->name, "%c Item #%d", x, i);
        trq_list_insert_last(&Q1, b1);
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "trq_list_shuffle(Q1, \"foo\")\n");
    time_measure_reset(tm1);
    time_measure_start(tm1);
    trq_list_shuffle(&Q1, (unsigned char *)"foo", 3);
    time_measure_stop(tm1);
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "trq_list_shuffle(Q1, \"barbar\")\n");
    trq_list_shuffle(&Q1, (unsigned char *)"barbar", 6);
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "trq_list_shuffle(Q1, \"foo\")\n");
    trq_list_shuffle(&Q1, (unsigned char *)"foo", 3);
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_list_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "shuffle:\n");
    if (verbose)
        time_measure_print(tm1, items, "item");
    return r;
}

int traversal_test(int items, int traversals)
{
    time_measure_t tm;
    q_item_t b;
    int i, j;
    trq_list Q;

    if (verbose)
        fprintf(stderr, "traversing queue of %d items %d times",
                items, traversals);

    tm = time_measure_alloc();

    trq_list_init(&Q, struct q_item, next);
    for (i = 0; i < items; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d", i);
        trq_list_insert_last(&Q, b);
    }

    if (verbose)
        fprintf(stderr, "...\n");

    time_measure_start(tm);
    for (j = 0; j < traversals; j++)
        trq_list_mapcar(&Q, mapcar_dummy, (void *)0);
    time_measure_stop(tm);
    if (verbose)
        time_measure_print(tm, items * traversals, "item");
    if (verbose)
        time_measure_print(tm, traversals, "traversal");
    time_measure_free(tm);

    return 0;
}

int join_test_raw(int rewind_mode)
{
    int i, r, x, y;
    trq_list Q1, Q2;
    q_item_t b, e1, e2, e3;

    if (verbose)
        fprintf(stderr, "join_test\n");

    r = 0;

    trq_list_init(&Q1, struct q_item, next);
    trq_list_init(&Q2, struct q_item, next);

    e1 = alloc_item();
    sprintf(e1->name, "Item E1");
    e2 = alloc_item();
    sprintf(e2->name, "Item E2");
    e3 = alloc_item();
    sprintf(e3->name, "Item E3");

    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_list_insert_last(&Q1, b);
    }
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/2", i);
        trq_list_insert_last(&Q2, b);
    }

    list_rewind_mode(&Q1, rewind_mode);
    list_rewind_mode(&Q2, rewind_mode);

    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
    trq_list_mapcar(&Q2, mapcar_print, Q2.c);
    if (verbose)
        fprintf(stderr, "trq_list_join_after_last(Q1, Q2)\n");
    trq_list_join_after_last(&Q1, &Q2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
    trq_list_mapcar(&Q2, mapcar_print, Q2.c);

    list_clear(&Q1);
    list_clear(&Q2);

    if (verbose)
        fprintf(stderr, "clear Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "clear Q2:\n");
    trq_list_mapcar(&Q2, mapcar_print, Q2.c);

    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_list_insert_last(&Q1, b);
    }
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/2", i);
        trq_list_insert_last(&Q2, b);
    }

    list_rewind_mode(&Q1, rewind_mode);
    list_rewind_mode(&Q2, rewind_mode);

    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
    trq_list_mapcar(&Q2, mapcar_print, Q2.c);
    if (verbose)
        fprintf(stderr, "trq_list_join_before_first(Q1, Q2)\n");
    trq_list_join_before_first(&Q1, &Q2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_list_length(&Q2));
    trq_list_mapcar(&Q2, mapcar_print, Q2.c);

    if (verbose)
        fprintf(stderr, "trq_list_get_nth(&Q1, 77) ->");
    b = trq_list_get_nth(&Q1, 77);
    if (b) {
        if (verbose)
            fprintf(stderr, "  \"%s\"\n", b->name);
    } else {
        if (verbose)
            fprintf(stderr, "  TRQ_NO_ITEM\n");
    }
    if (b)
        free_item(b);

    if (verbose)
        fprintf(stderr, "trq_list_get_nth(&Q1, 3) ->");
    b = trq_list_get_nth(&Q1, 3);
    if (b) {
        if (verbose)
            fprintf(stderr, "  \"%s\"\n", b->name);
    } else {
        if (verbose)
            fprintf(stderr, "  TRQ_NO_ITEM\n");
    }
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (b)
        free_item(b);

    if (verbose)
        fprintf(stderr, "trq_list_get_nth(&Q1, 8) ->");
    b = trq_list_get_nth(&Q1, 8);
    if (b) {
        if (verbose)
            fprintf(stderr, "  \"%s\"\n", b->name);
    } else {
        if (verbose)
            fprintf(stderr, "  TRQ_NO_ITEM\n");
    }
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (b)
        free_item(b);

    if (trq_list_pointer_valid(&Q1)) {
        int x = trq_deque_length(&(Q1.tail)) + 1;
        
        if (verbose)
            fprintf(stderr, "trq_list_get_nth(&Q1, %d) ->", x);
        b = trq_list_get_nth(&Q1, x);
        if (b) {
            if (verbose)
                fprintf(stderr, "  \"%s\"\n", b->name);
        } else {
            if (verbose)
                fprintf(stderr, "  TRQ_NO_ITEM\n");
        }
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
        trq_list_mapcar(&Q1, mapcar_print, Q1.c);
        if (b)
            free_item(b);
    }

    list_rewind_mode(&Q1, rewind_mode);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_insert_nth(Q1, 2, e1)\n");
    trq_list_insert_nth(&Q1, 2, e1);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_insert_nth(Q1, 7, e2)\n");
    trq_list_insert_nth(&Q1, 7, e2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_remove(Q1, e1)\n");
    trq_list_remove(&Q1, e1);

    y = trq_list_length(&Q1);
    if (verbose)
        fprintf(stderr, "trq_list_insert_nth(Q1, %d, e1)\n", y + 1);
    trq_list_insert_nth(&Q1, y + 1, e1);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    y = trq_list_length(&Q1);
    if (verbose)
        fprintf(stderr, "trq_list_insert_nth(Q1, %d, e3)", y + 2);
    x = trq_list_insert_nth(&Q1, y + 2, e3);
    if (verbose)
        fprintf(stderr, " -> %d\n", x);
    if (x != 0) {
        r++;
        if (verbose)
            fprintf(stderr, "Should have been 0\n");
    } else {
        free_item(e3);
    }
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(Q1, e1, e2)\n");
    trq_list_swap(&Q1, e1, e2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);
    if (verbose)
        fprintf(stderr, "trq_list_swap(Q1, e1, e2)\n");
    trq_list_swap(&Q1, e1, e2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_list_length(&Q1));
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    list_clear(&Q1);
    return 0;
}

int swap_test_raw(int rewind_mode)
{
    int i;
    trq_list Q1, Q2;
    q_item_t b;
    q_item_t s[10];

    if (verbose)
        fprintf(stderr, "swap_test\n");

    trq_list_init(&Q1, struct q_item, next);
    trq_list_init(&Q2, struct q_item, next);
    for (i = 0; i < 10; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_list_insert_last(&Q1, b);
        s[i] = b;
    }

    list_rewind_mode(&Q1, rewind_mode);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, s[3], s[6])\n");
    trq_list_swap(&Q1, s[3], s[6]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, s[6], s[3])\n");
    trq_list_swap(&Q1, s[6], s[3]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, s[0], s[9])\n");
    trq_list_swap(&Q1, s[0], s[9]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, s[0], s[5])\n");
    trq_list_swap(&Q1, s[0], s[5]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, s[0], s[9])\n");
    trq_list_swap(&Q1, s[0], s[9]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, s[5], s[9])\n");
    trq_list_swap(&Q1, s[5], s[9]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, NULL, NULL)\n");
    trq_list_swap(&Q1, NULL, NULL);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    if (verbose)
        fprintf(stderr, "trq_list_swap(&Q1, NULL, s[5])\n");
    trq_list_swap(&Q1, NULL, s[5]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_list_mapcar(&Q1, mapcar_print, Q1.c);

    return 0;
}

int join_test(void)
{
    int r;
    
    r = 0;

    r += join_test_raw(REWIND_INVALIDATE);
    r += join_test_raw(REWIND_REWIND);
    r += join_test_raw(REWIND_END);
    r += join_test_raw(REWIND_MIDDLE);
    r += join_test_raw(REWIND_RANDOM);

    return r;
}

int swap_test(void)
{
    int r;
    
    r = 0;

    r += swap_test_raw(REWIND_INVALIDATE);
    r += swap_test_raw(REWIND_REWIND);
    r += swap_test_raw(REWIND_END);
    r += swap_test_raw(REWIND_MIDDLE);
    r += swap_test_raw(REWIND_RANDOM);

    return r;
}

int all_tests(void)
{
    int i, j;

    verbose = 0;

    j = 0;

    fprintf(stderr, "functional_test ... ");
    i = functional_test();
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "get_put_time_test ... ");
    i = get_put_time_test(10000000);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "sort_test 1 ... ");
    i = sort_test(0);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "sort_test 2 ... ");
    i = sort_test(10);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "sort_test 3 ... ");
    i = sort_test(2000);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "sort_test 4 ... ");
    i = sort_test(1);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "sort_test 5 ... ");
    i = sort_test(2);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "shuffle_test 1 ... ");
    i = shuffle_test(10);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "shuffle_test 2 ... ");
    i = shuffle_test(2000);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "swap_test ... ");
    i = swap_test();
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "traversal_test 1 ... ");
    i = traversal_test(10, 1000000);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "traversal_test 2 ... ");
    i = traversal_test(1000, 10000);
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "pointer_test ... ");
    i = pointer_test();
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "member_test ... ");
    i = member_test();
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "join_test ... ");
    i = join_test();
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    return j;
}

int main(int argc, char **argv)
{
    int i, j, x;

    verbose = 1;

    if (sizeof (trq_p_i_t) != sizeof (void *)) {
        fprintf(stderr, 
                "(sizeof (trq_p_i_t) == %d) != (sizeof (void *) == %d\n",
                sizeof (trq_p_i_t),
                sizeof (void *));
        fprintf(stderr, "LIBRARY IS NOT WORKING!\n");
        exit(-1);
    }

    time_measure_calibrate();

    item_init();

    if ((argc == 2) &&
        (0 < (i = atoi(argv[1])))) {
        x = get_put_time_test(i);
        exit(x);
    } else if ((argc == 2) &&
               (0 == strcmp("basic", argv[1]))) {
        x = functional_test();
        exit(x);
    } else if ((argc == 2) &&
               (0 == strcmp("join", argv[1]))) {
        x = join_test();
        exit(x);
    } else if ((argc == 2) &&
               (0 == strcmp("member", argv[1]))) {
        x = member_test();
        exit(x);
    } else if ((argc == 2) &&
               (0 == strcmp("pointer", argv[1]))) {
        x = pointer_test();
        exit(x);
    } else if ((argc == 2) &&
               (0 == strcmp("swap", argv[1]))) {
        x = swap_test();
        exit(x);
    } else if ((argc == 2) &&
               (0 == strcmp("sort", argv[1]))) {
        x = sort_test(0);
        exit(x);
    } else if ((argc == 3) &&
               (0 == strcmp("sort", argv[1])) &
               (0 < (j = atoi(argv[2])))) {
        x = sort_test(j);
        exit(x);
    } else if ((argc == 2) &&
               (0 == strcmp("shuffle", argv[1]))) {
        x = shuffle_test(0);
        exit(x);
    } else if ((argc == 3) &&
               (0 == strcmp("shuffle", argv[1])) &
               (0 < (j = atoi(argv[2])))) {
        x = shuffle_test(j);
        exit(x);
    } else if ((argc == 3) &&
               (0 < (i = atoi(argv[1]))) &
               (0 < (j = atoi(argv[2])))) {
        x = traversal_test(i, j);
        exit(x);
    } else if (argc > 1) {
        exit(-1);
    }
    x = all_tests();
    exit(x);
}

static void *mapcar_dummy(void *item_in, void *context_in)
{
    return item_in;
}

static void *mapcar_print(void *item_in, void *context_in)
{
    q_item_t item = (q_item_t)item_in;

    if (verbose)
        fprintf(stderr, "  %-16s (addr 0x%08lx)%s\n", 
                item->name, 
                (unsigned long)item,
                (context_in == item_in) ? " !!!!!!" : "");
    return item_in;
}

static void *mapcar_free_and_drop(void *item_in, void *context_in)
{
    q_item_t item = (q_item_t)item_in;

    free_item(item);
    return NULL;
}

static void *mapcar_test_1(void *item_in, void *context_in)
{
    q_item_t item = (q_item_t)item_in;

    if (verbose)
        fprintf(stderr, "mapcar_test_1(\"%s\", 0x%08lx) -> ",
                item->name, (unsigned long)context_in);
    if (item->name[3] == '0') {
        if (verbose)
                fprintf(stderr, "NULL\n");
        return NULL;
    }
    if (verbose)
        fprintf(stderr, "0x%08lx\n", (unsigned long)item);
    return item;
}

/*
 * Static allocator functions
 */
static trq_list free_item_q;

static void item_init(void)
{
    trq_list_init(&free_item_q, struct q_item, next);
}

static void free_item(q_item_t b)
{
    trq_list_insert_first(&free_item_q, b);
}

static q_item_t alloc_item(void)
{
    q_item_t b;

    b = trq_list_get_first(&free_item_q);
    if (!b)
        b = (q_item_t)calloc(1, sizeof (struct q_item));
    if (!b) {
        fprintf(stderr, "Out of memory");
        exit(10);
    }
    return b;
}

/* eof (ltest.c) */
