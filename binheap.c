/*---------------------------------------------------------------------------
 * 
 * binheap.c 
 *
 *     04/29/2017 - 
 *
 *     <sunzoomass@gmail.com>
 *
 *     Copyright (c) 2017 Suraj Jaiswal.
 *     All rights reserved.
 *
 *---------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

struct binheap_s {
    void    *dynarr[100];
    size_t   dynarr_size;
    size_t   n_elt;
    app_cmp_fn_t    cmp_fn;
    void    *alloc_fn;
};

static void binheap_bubbleup(binheap_t *bh, size_t n);
static void binheap_bubbledown(binheap_t *bh, size_t n);


void 
binheap_init(binheap_t **bh, app_cmp_fn_t cmp)
{
    *bh = malloc(sizeof(**bh));

    (*bh)->n_elt = 0;
    (*bh)->dynarr_size = 100;
    (*bh)->cmp_fn = cmp;
}

void 
binheap_insert(binheap_t *bh, void *e)
{
    if (bh->n_elt >= bh->dynarr_size) {
        printf("Dynamic array is full\n");
        return;
    }
    bh->n_elt++;
    bh->dynarr[bh->n_elt] = e;
    binheap_bubbleup(bh, bh->n_elt);

    return;
}

void * 
binheap_peek_min(binheap_t *bh)
{
    void *min = NULL;

    if (bh->n_elt) {
        return bh->dynarr[1];
    }

    return min;
}


void * 
binheap_extract_min(binheap_t *bh)
{
    void *min = NULL;
    
    if (bh->n_elt) {
        min = bh->dynarr[1];
        bh->dynarr[1] = bh->dynarr[bh->n_elt];
        bh->n_elt--;

        binheap_bubbledown(bh, 1);
    }

    return min;
}


static size_t 
binheap_parent(size_t i)
{
    if (i == 1) {
        return -1;
    }
    return (i/2);
}

static void
binheap_swap(binheap_t *bh, size_t n, size_t p)
{
    void *te = bh->dynarr[p];
    bh->dynarr[p] = bh->dynarr[n];
    bh->dynarr[n] = te;

    return;
}

static void
binheap_bubbleup(binheap_t *bh, size_t n)
{
    size_t p = binheap_parent(n);
    if (p == -1) {
        return;
    }

    if (bh->cmp_fn(bh->dynarr[p], bh->dynarr[n])) {
        binheap_swap(bh, n, p);
        binheap_bubbleup(bh, p);
    }

    return;
}

static void
binheap_bubbledown(binheap_t *bh, size_t n)
{
    size_t i, chi, mini;

    chi = n * 2;    /* child index */
    mini = n;       /* seed the min index */
    
    for (i = 0; i <= 1; i++) {
        if (chi <= bh->n_elt) {
            if (bh->cmp_fn(bh->dynarr[mini],
                           bh->dynarr[chi + i])) {
                mini = chi + i;
            }
        }
    }

    if (mini != n) {
        binheap_swap(bh, n, mini);
        binheap_bubbledown(bh, mini);
    }
}
