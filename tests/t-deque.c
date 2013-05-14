/*   -*- c -*-
 *
 *  ----------------------------------------------------------------------
 *  Test DeQue operations.
 *  ----------------------------------------------------------------------
 *  Created      : Tue Nov 21 17:47:40 1995 tri
 *  Last modified: Tue May 14 20:21:40 2013 tri
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

#ifndef __T_DEQUE_MACRO_C__
#  ifndef __T_DEQUE_FUNC_C__
#    error "This source file can be compiled only within nongeneric source."
#  endif /* __T_DEQUE_FUNC_C__ */
#endif /* __T_DEQUE_MACRO_C__ */

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

#include <trq_deque.h>

#include "trq_test.h"

#define TMAX 16

#ifndef HAVE_RANDOM
#ifdef HAVE_RAND
#define random() rand()
#define srandom() srand()
#endif
#endif

#ifdef sprintf
#undef  sprintf
#undef  calloc
#endif

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

#define deque_clear(Q) (trq_deque_mapcar((Q), mapcar_free_and_drop, (void *)0))

int get_put_time_test(int n)
{
    time_measure_t tm;
    q_item_t b1, b2, b3, b4, b5, b6;
    int i;
    trq_deque Q;

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

    trq_deque_init(&Q, struct q_item, next);

    time_measure_start(tm);
    for (i = ((n / 50) + 1); i ; i--) {
        trq_deque_insert_head(&Q, b1);
        trq_deque_insert_head(&Q, b2);
        trq_deque_insert_head(&Q, b3);
        trq_deque_insert_head(&Q, b4);
        trq_deque_insert_head(&Q, b5);
        trq_deque_insert_head(&Q, b6);
        b4 = trq_deque_get_tail(&Q);
        b5 = trq_deque_get_tail(&Q);
        b6 = trq_deque_get_tail(&Q);
        b1 = trq_deque_get_tail(&Q);
        b2 = trq_deque_get_tail(&Q);
        b3 = trq_deque_get_tail(&Q);
        trq_deque_insert_head(&Q, b1);
        trq_deque_insert_tail(&Q, b2);
        trq_deque_insert_head(&Q, b3);
        trq_deque_insert_tail(&Q, b4);
        b1 = trq_deque_get_head(&Q);
        b2 = trq_deque_get_head(&Q);
        b3 = trq_deque_get_head(&Q);
        b4 = trq_deque_get_head(&Q);
        /* 20 operations */
        trq_deque_insert_head(&Q, b5);
        trq_deque_insert_head(&Q, b6);
        trq_deque_insert_head(&Q, b1);
        b1 = trq_deque_get_tail(&Q);
        trq_deque_insert_head(&Q, b2);
        b2 = trq_deque_get_tail(&Q);
        trq_deque_insert_tail(&Q, b3);
        b3 = trq_deque_get_tail(&Q);
        trq_deque_insert_tail(&Q, b4);
        b4 = trq_deque_get_head(&Q);
        trq_deque_insert_head(&Q, b1);
        b1 = trq_deque_get_head(&Q);
        trq_deque_insert_tail(&Q, b2);
        b2 = trq_deque_get_tail(&Q);
        trq_deque_insert_head(&Q, b3);
        b3 = trq_deque_get_tail(&Q);
        trq_deque_insert_tail(&Q, b1);
        b1 = trq_deque_get_head(&Q);
        b5 = trq_deque_get_tail(&Q);
        b6 = trq_deque_get_tail(&Q);
        /* 40 operations */
        trq_deque_insert_head(&Q, b3);
        trq_deque_insert_head(&Q, b5);
        trq_deque_insert_head(&Q, b2);
        trq_deque_insert_head(&Q, b1);
        trq_deque_insert_head(&Q, b6);
        b1 = trq_deque_get_tail(&Q);
        b2 = trq_deque_get_tail(&Q);
        b3 = trq_deque_get_tail(&Q);
        b5 = trq_deque_get_tail(&Q);
        b6 = trq_deque_get_tail(&Q);
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
    trq_deque Q, Q2;
    q_item_t b, tmp = (q_item_t)0;
    int i, state;
    int r = 0;

    state = 0;
    trq_deque_init(&Q, struct q_item, next);
    trq_deque_init(&Q2, struct q_item, next);

    state++;
    for (i = 0; i < TMAX; i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %d", state, i);
        trq_deque_insert_head(&Q, b);
    }
    while ((b = trq_deque_get_tail(&Q))) {
        if (verbose)
            fprintf(stderr, "trq_deque_get_tail -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < TMAX; i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %d", state, i);
        trq_deque_insert_head(&Q, b);
    }
    (void)trq_deque_reverse(&Q);
    while ((b = trq_deque_get_tail(&Q))) {
        if (verbose)
            fprintf(stderr, "trq_deque_get_tail -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < TMAX; i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %d", state, i);
        trq_deque_insert_tail(&Q, b);
    }
    while ((b = trq_deque_get_tail(&Q))) {
        if (verbose)
            fprintf(stderr, "trq_deque_get_tail -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < ((TMAX / 2) + 1); i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %dF", state, i);
        trq_deque_insert_head(&Q, b);
        b = alloc_item();
        sprintf(b->name, "%d) %dL", state, i);
        trq_deque_insert_tail(&Q, b);
    }
    while ((b = trq_deque_get_tail(&Q))) {
        if (verbose)
            fprintf(stderr, "trq_deque_get_tail -> \"%s\"\n", b->name);
        free_item(b);
    }
    state++;
    for (i = 0; i < ((TMAX / 2) + 1); i++) {
        b = alloc_item();
        sprintf(b->name, "%d) %dF", state, i);
        trq_deque_insert_head(&Q, b);
        b = alloc_item();
        if (i == 5)
            tmp = b;
        sprintf(b->name, "%d) %dL", state, i);
        trq_deque_insert_tail(&Q, b);
    }
    if (verbose) {
        fprintf(stderr, "This should be nonzero (%d)\n",
                trq_deque_member(&Q, tmp));
        fprintf(stderr, "This should be zero (%d)\n",
                trq_deque_member(&Q, (void*)0xffffffff));
    }
    if (trq_deque_member(&Q, tmp) == 0)
        r++;
    if (trq_deque_member(&Q, (void*)0xffffffff) != 0)
        r++;

    trq_deque_mapcar(&Q, mapcar_test_1, (void *)0);

    for (;;) {
        if ((b = trq_deque_get_head(&Q))) {
            if (verbose)
                fprintf(stderr, "trq_deque_get_tail -> \"%s\"\n", b->name);
            free_item(b);
        } else {
            break;
        }
        if ((b = trq_deque_get_tail(&Q))) {
            if (verbose)
                fprintf(stderr, "trq_deque_get_tail -> \"%s\"\n", b->name);
            free_item(b);
        } else {
            break;
        }
    }
    if (verbose)
        fprintf(stderr, "This should be zero (%d)\n",
                trq_deque_member(&Q, tmp));
    if (trq_deque_member(&Q, tmp) != 0)
        r++;
    return r;
}

int traversal_test(int items, int traversals)
{
    time_measure_t tm;
    q_item_t b;
    int i, j;
    trq_deque Q;

    if (verbose)
        fprintf(stderr, "traversing queue of %d items %d times",
                items, traversals);

    tm = time_measure_alloc();

    trq_deque_init(&Q, struct q_item, next);
    for (i = 0; i < items; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d", i);
        trq_deque_insert_head(&Q, b);
    }

    if (verbose)
        fprintf(stderr, "...\n");

    time_measure_start(tm);
    for (j = 0; j < traversals; j++)
        trq_deque_mapcar(&Q, mapcar_dummy, (void *)0);
    time_measure_stop(tm);
    if (verbose)
        time_measure_print(tm, items * traversals, "item");
    if (verbose)
        time_measure_print(tm, traversals, "traversal");
    time_measure_free(tm);

    return 0;
}

int join_test(void)
{
    int i, r, x;
    trq_deque Q1, Q2;
    q_item_t b, e1, e2, e3;

    if (verbose)
        fprintf(stderr, "join_test\n");

    r = 0;

    trq_deque_init(&Q1, struct q_item, next);
    trq_deque_init(&Q2, struct q_item, next);

    e1 = alloc_item();
    sprintf(e1->name, "Item E1");
    e2 = alloc_item();
    sprintf(e2->name, "Item E2");
    e3 = alloc_item();
    sprintf(e3->name, "Item E3");

    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_deque_insert_head(&Q1, b);
    }
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/2", i);
        trq_deque_insert_head(&Q2, b);
    }

    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
    trq_deque_mapcar(&Q2, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "trq_deque_join_head(Q1, Q2)\n");
    trq_deque_join_head(&Q1, &Q2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
    trq_deque_mapcar(&Q2, mapcar_print, NULL);

    deque_clear(&Q1);
    deque_clear(&Q2);

    if (verbose)
        fprintf(stderr, "clear Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "clear Q2:\n");
    trq_deque_mapcar(&Q2, mapcar_print, NULL);

    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_deque_insert_head(&Q1, b);
    }
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/2", i);
        trq_deque_insert_head(&Q2, b);
    }

    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
    trq_deque_mapcar(&Q2, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "trq_deque_join_tail(Q1, Q2)\n");
    trq_deque_join_tail(&Q1, &Q2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
    trq_deque_mapcar(&Q2, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_get_nth(&Q1, 77) ->");
    b = trq_deque_get_nth(&Q1, 77);
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
        fprintf(stderr, "trq_deque_get_nth(&Q1, 3) ->");
    b = trq_deque_get_nth(&Q1, 3);
    if (b) {
        if (verbose)
            fprintf(stderr, "  \"%s\"\n", b->name);
    } else {
        if (verbose)
            fprintf(stderr, "  TRQ_NO_ITEM\n");
    }
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (b)
        free_item(b);

    if (verbose)
        fprintf(stderr, "trq_deque_get_nth(&Q1, 8) ->");
    b = trq_deque_get_nth(&Q1, 8);
    if (b) {
        if (verbose)
            fprintf(stderr, "  \"%s\"\n", b->name);
    } else {
        if (verbose)
            fprintf(stderr, "  TRQ_NO_ITEM\n");
    }
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (b)
        free_item(b);

    if (verbose)
        fprintf(stderr, "trq_deque_insert_nth(Q1, 2, e1)\n");
    trq_deque_insert_nth(&Q1, 2, e1);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_insert_nth(Q1, 7, e2)\n");
    trq_deque_insert_nth(&Q1, 7, e2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_remove(Q1, e1)\n");
    trq_deque_remove(&Q1, e1);

    if (verbose)
        fprintf(stderr, "trq_deque_insert_nth(Q1, 10, e1)\n");
    trq_deque_insert_nth(&Q1, 10, e1);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_insert_nth(Q1, 12, e3)");
    x = trq_deque_insert_nth(&Q1, 12, e3);
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
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(Q1, e1, e2)\n");
    trq_deque_swap(&Q1, e1, e2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "trq_deque_swap(Q1, e1, e2)\n");
    trq_deque_swap(&Q1, e1, e2);
    if (verbose)
        fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    deque_clear(&Q1);
    return r;
}

int member_test(void)
{
    int i;
    trq_deque Q1, Q2;
    q_item_t b;
    q_item_t s11, s12, s21, s22;

    if (verbose)
            fprintf(stderr, "member_test\n");

    trq_deque_init(&Q1, struct q_item, next);
    trq_deque_init(&Q2, struct q_item, next);
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_deque_insert_head(&Q1, b);
        if (i == 2)
            s11 = b;
    }
    s12 = b;
    for (i = 0; i < 5; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/2", i);
        trq_deque_insert_head(&Q2, b);
        if (i == 2)
            s21 = b;
    }
    s22 = b;

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);
    if (verbose)
        fprintf(stderr, "Q2:\n");
    trq_deque_mapcar(&Q2, mapcar_print, NULL);

    if (verbose) {
        fprintf(stderr, "trq_deque_member(Q1, \"%s\") -> %d\n",
                s11->name,
                trq_deque_member(&Q1, s11));
        fprintf(stderr, "trq_deque_member(Q1, \"%s\") -> %d\n",
                s12->name,
                trq_deque_member(&Q1, s12));
        fprintf(stderr, "trq_deque_member(Q1, \"%s\") -> %d\n",
                s21->name,
                trq_deque_member(&Q1, s21));
        fprintf(stderr, "trq_deque_member(Q1, \"%s\") -> %d\n",
                s22->name,
                trq_deque_member(&Q1, s22));
        fprintf(stderr, "trq_deque_member(Q2, \"%s\") -> %d\n",
                s11->name,
                trq_deque_member(&Q2, s11));
        fprintf(stderr, "trq_deque_member(Q2, \"%s\") -> %d\n",
                s12->name,
                trq_deque_member(&Q2, s12));
        fprintf(stderr, "trq_deque_member(Q2, \"%s\") -> %d\n",
                s21->name,
                trq_deque_member(&Q2, s21));
        fprintf(stderr, "trq_deque_member(Q2, \"%s\") -> %d\n",
                s22->name,
                trq_deque_member(&Q2, s22));
    }

    return 0;
}

int swap_test(void)
{
    int i;
    trq_deque Q1, Q2;
    q_item_t b;
    q_item_t s[10];

    if (verbose)
        fprintf(stderr, "swap_test\n");

    trq_deque_init(&Q1, struct q_item, next);
    trq_deque_init(&Q2, struct q_item, next);
    for (i = 0; i < 10; i++) {
        b = alloc_item();
        sprintf(b->name, "Item #%d/1", i);
        trq_deque_insert_head(&Q1, b);
        s[i] = b;
    }

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, s[3], s[6])\n");
    trq_deque_swap(&Q1, s[3], s[6]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, s[6], s[3])\n");
    trq_deque_swap(&Q1, s[6], s[3]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, s[0], s[9])\n");
    trq_deque_swap(&Q1, s[0], s[9]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, s[0], s[5])\n");
    trq_deque_swap(&Q1, s[0], s[5]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, s[0], s[9])\n");
    trq_deque_swap(&Q1, s[0], s[9]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, s[5], s[9])\n");
    trq_deque_swap(&Q1, s[5], s[9]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, NULL, NULL)\n");
    trq_deque_swap(&Q1, NULL, NULL);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

    if (verbose)
        fprintf(stderr, "trq_deque_swap(&Q1, NULL, s[5])\n");
    trq_deque_swap(&Q1, NULL, s[5]);

    if (verbose)
        fprintf(stderr, "Q1:\n");
    trq_deque_mapcar(&Q1, mapcar_print, NULL);

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

int sort_test(int items)
{
    int i, x, r = 0;
    trq_deque Q1, Q2, Q3;
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

    trq_deque_init(&Q1, struct q_item, next);
    trq_deque_init(&Q2, struct q_item, next);
    trq_deque_init(&Q3, struct q_item, next);

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
        trq_deque_insert_head(&Q1, b1);
        trq_deque_insert_head(&Q2, b2);
        if (items < NO_MORE_RND_BUBBLESORT) {
            b3 = alloc_item();
            sprintf(b3->name, "%c Item #%d", x, i);
            trq_deque_insert_head(&Q3, b3);
        }
    }

    b1 = alloc_item();
    sprintf(b1->name, "z Item NONSORT");
    trq_deque_insert_tail(&Q1, b1);
    b2 = alloc_item();
    sprintf(b2->name, "z Item NONSORT");
    trq_deque_insert_tail(&Q2, b2);
    if (items < NO_MORE_RND_BUBBLESORT) {
        b3 = alloc_item();
        sprintf(b3->name, "z Item NONSORT");
        trq_deque_insert_tail(&Q3, b3);
    }

    tc1 = tc2 = tc3 = 0;

    if ((trq_deque_length(&Q1) > 1) &&
        trq_deque_in_order(&Q1, sort_test_test, NULL)) {
        fprintf(stderr, "Q1 in order where shouldn't be\n");
        r++;
    }
    if ((trq_deque_length(&Q2) > 1) &&
        trq_deque_in_order(&Q2, sort_test_test, NULL)) {
        fprintf(stderr, "Q2 in order where shouldn't be\n");
        r++;
    }
    if (items < NO_MORE_RND_BUBBLESORT) {
        if ((trq_deque_length(&Q3) > 1) &&
            trq_deque_in_order(&Q3, sort_test_test, NULL)) {
            fprintf(stderr, "Q3 in order where shouldn't be\n");
            r++;
        }
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
        trq_deque_mapcar(&Q1, mapcar_print, NULL);
    }

    if (verbose)
        fprintf(stderr, "trq_deque_quicksort(Q1)\n");
    time_measure_reset(tm1);
    time_measure_start(tm1);
    trq_deque_quicksort(&Q1, sort_test_test, &tc1);
    time_measure_stop(tm1);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
        trq_deque_mapcar(&Q1, mapcar_print, NULL);
    }

    if (trq_deque_in_order(&Q1, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q1 not order where should be\n");
        r++;
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_deque_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
        trq_deque_mapcar(&Q2, mapcar_print, NULL);
    }

    if (verbose)
        fprintf(stderr, "trq_deque_mergesort(Q2)\n");
    time_measure_reset(tm2);
    time_measure_start(tm2);
    trq_deque_mergesort(&Q2, sort_test_test, &tc2);
    time_measure_stop(tm2);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_deque_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
        trq_deque_mapcar(&Q2, mapcar_print, NULL);
    }

    if (trq_deque_in_order(&Q2, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q2 not order where should be\n");
        r++;
    }

    if (items < NO_MORE_RND_BUBBLESORT) {
        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q3: %d items\n", trq_deque_length(&Q3));
        } else {
            if (verbose)
                fprintf(stderr, "Q3 (%d):\n", trq_deque_length(&Q3));
            trq_deque_mapcar(&Q3, mapcar_print, NULL);
        }

        if (verbose)
            fprintf(stderr, "trq_deque_bubblesort(Q3)\n");
        time_measure_reset(tm3);
        time_measure_start(tm3);
        trq_deque_bubblesort(&Q3, sort_test_test, &tc3);
        time_measure_stop(tm3);

        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q3: %d items\n", trq_deque_length(&Q3));
        } else {
            if (verbose)
                fprintf(stderr, "Q3 (%d):\n", trq_deque_length(&Q3));
            trq_deque_mapcar(&Q3, mapcar_print, NULL);
        }
        if (verbose) {
            fprintf(stderr, "trq_deque_in_order(Q3)\n");
        }
        if (trq_deque_in_order(&Q3, sort_test_test, NULL) == 0) {
            fprintf(stderr, "Q3 not order where should be\n");
            r++;
        }
        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q3: %d items\n", trq_deque_length(&Q3));
        } else {
            if (verbose)
                fprintf(stderr, "Q3 (%d):\n", trq_deque_length(&Q3));
            trq_deque_mapcar(&Q3, mapcar_print, NULL);
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

    if (items < NO_MORE_ORD_QUICKSORT) {
        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
        } else {
            if (verbose)
                fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
            trq_deque_mapcar(&Q1, mapcar_print, NULL);
        }

        if (verbose)
            fprintf(stderr, "trq_deque_quicksort(Q1)\n");
        time_measure_reset(tm1);
        time_measure_start(tm1);
        trq_deque_quicksort(&Q1, sort_test_test, &tc1);
        time_measure_stop(tm1);

        if (items > 100) {
            if (verbose)
                fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
        } else {
            if (verbose)
                fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
            trq_deque_mapcar(&Q1, mapcar_print, NULL);
        }
        if (trq_deque_in_order(&Q1, sort_test_test, NULL) == 0) {
            fprintf(stderr, "Q1 not order where should be\n");
            r++;
        }
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_deque_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
        trq_deque_mapcar(&Q2, mapcar_print, NULL);
    }

    if (verbose)
        fprintf(stderr, "trq_deque_mergesort(Q2)\n");
    time_measure_reset(tm2);
    time_measure_start(tm2);
    trq_deque_mergesort(&Q2, sort_test_test, &tc2);
    time_measure_stop(tm2);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q2: %d items\n", trq_deque_length(&Q2));
    } else {
        if (verbose)
            fprintf(stderr, "Q2 (%d):\n", trq_deque_length(&Q2));
        trq_deque_mapcar(&Q2, mapcar_print, NULL);
    }
    if (trq_deque_in_order(&Q2, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q2 not order where should be\n");
        r++;
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_deque_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_deque_length(&Q3));
        trq_deque_mapcar(&Q3, mapcar_print, NULL);
    }

    if (items >= NO_MORE_RND_BUBBLESORT) {
        Q3 = Q2;
    }
    if (verbose)
        fprintf(stderr, "trq_deque_bubblesort(Q3)\n");
    time_measure_reset(tm3);
    time_measure_start(tm3);
    trq_deque_bubblesort(&Q3, sort_test_test, &tc3);
    time_measure_stop(tm3);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_deque_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_deque_length(&Q3));
        trq_deque_mapcar(&Q3, mapcar_print, NULL);
    }
    if (trq_deque_in_order(&Q3, sort_test_test, NULL) == 0) {
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
        fprintf(stderr, "trq_deque_insert_in_order 3 items\n");

    trq_deque_insert_in_order(&Q3, ti1, sort_test_test, NULL);
    trq_deque_insert_in_order(&Q3, ti2, sort_test_test, NULL);
    trq_deque_insert_in_order(&Q3, ti3, sort_test_test, NULL);

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q3: %d items\n", trq_deque_length(&Q3));
    } else {
        if (verbose)
            fprintf(stderr, "Q3 (%d):\n", trq_deque_length(&Q3));
        trq_deque_mapcar(&Q3, mapcar_print, NULL);
    }

    if (trq_deque_in_order(&Q3, sort_test_test, NULL) == 0) {
        fprintf(stderr, "Q3 not order where should be\n");
        r++;
    }

    return r;
}

int shuffle_test(int items)
{
    int i, x, r = 0;
    trq_deque Q1;
    q_item_t b1;
    time_measure_t tm1;

    if (verbose)
        fprintf(stderr, "shuffle_test\n");

    if (items < 1)
        items = DEFAULT_SORT_TEST_ITEMS;

    tm1 = time_measure_alloc();

    trq_deque_init(&Q1, struct q_item, next);

    for (i = 1; i < items; i++) {
        b1 = alloc_item();
        x = (random() % 10) + 'a';
        sprintf(b1->name, "%c Item #%d", x, i);
        trq_deque_insert_head(&Q1, b1);
    }

    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
        trq_deque_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "trq_deque_shuffle(Q1, \"foo\")\n");
    time_measure_reset(tm1);
    time_measure_start(tm1);
    trq_deque_shuffle(&Q1, (unsigned char *)"foo", 3);
    time_measure_stop(tm1);
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
        trq_deque_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "trq_deque_shuffle(Q1, \"barbar\")\n");
    trq_deque_shuffle(&Q1, (unsigned char *)"barbar", 6);
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
        trq_deque_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "trq_deque_shuffle(Q1, \"foo\")\n");
    trq_deque_shuffle(&Q1, (unsigned char *)"foo", 3);
    if (items > 100) {
        if (verbose)
            fprintf(stderr, "Q1: %d items\n", trq_deque_length(&Q1));
    } else {
        if (verbose)
            fprintf(stderr, "Q1 (%d):\n", trq_deque_length(&Q1));
        trq_deque_mapcar(&Q1, mapcar_print, NULL);
    }
    if (verbose)
        fprintf(stderr, "shuffle:\n");
    if (verbose)
        time_measure_print(tm1, items, "item");
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

    fprintf(stderr, "join_test ... ");
    i = join_test();
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "member_test ... ");
    i = member_test();
    fprintf(stderr, "%s\n", (i == 0) ? "passed" : "FAILED!");
    if (i != 0)
        j = (j == 0) ? i : -1;

    fprintf(stderr, "swap_test ... ");
    i = swap_test();
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

#ifdef HAVE_SRANDOMDEV
    srandomdev();
#else
    srandom(time(NULL));
#endif

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
        exit(1);
    }
    i = all_tests();
    return i;
}

static void *mapcar_dummy(void *item_in, void *context_in)
{
    return item_in;
}

static void *mapcar_print(void *item_in, void *context_in)
{
    q_item_t item = (q_item_t)item_in;

    if (verbose)
        fprintf(stderr, "  %s\n", item->name);
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
static trq_deque free_item_q;

static void item_init(void)
{
    trq_deque_init(&free_item_q, struct q_item, next);
}

static void free_item(q_item_t b)
{
    trq_deque_insert_tail(&free_item_q, b);
}

static q_item_t alloc_item(void)
{
    q_item_t b;

    b = trq_deque_get_tail(&free_item_q);
    if (!b)
        b = (q_item_t)calloc(1, sizeof (struct q_item));
    if (!b) {
        exit(10);
    }
    return b;
}

/* eof (dtest.c) */
