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


typedef int (*app_cmp_fn_t)(void*, void*);
void binheap_set_allocator();
void binheap_set_deallocator(void *);


typedef struct binheap_s {
    void    *dynarr[100];
    size_t   dynarr_size;
    size_t   n_elt;
    app_cmp_fn_t    cmp_fn;
    void    *alloc_fn;
} binheap_t;


void binheap_insert(binheap_t *binheap, void *e);

void binheap_init(binheap_t *bh, app_cmp_fn_t cmp)
{
    bh->n_elt = 0;
    bh->dynarr_size = 100;
    bh->cmp_fn = cmp;
}

size_t 
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
binheap_min(binheap_t *bh)
{
    void *min = NULL;

    if (bh->n_elt) {
        return bh->dynarr[1];
    }

    return min;
}

int int_cmp(void *e1, void *e2)
{
    size_t ei = *(size_t *)e1;
    size_t ej = *(size_t *)e2;

    if (ei > ej) {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    binheap_t  bh;
    binheap_init(&bh, int_cmp);

    size_t inputa[10];
    int i;
    for (i = 0; i < (argc - 1); i++) {
        printf("%s\n", argv[i+1]);
        inputa[i] = atol(argv[i+1]);
        binheap_insert(&bh, &inputa[i]);
    }

    size_t *min = binheap_min(&bh); 
    printf("Minimum element is %d\n", *min);
}
