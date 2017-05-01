/*---------------------------------------------------------------------------
 * 
 * binheap.h 
 *
 *     04/30/2017 - 
 *
 *     <sunzoomass@gmail.com>
 *
 *     Copyright (c) 2017 Suraj Jaiswal.
 *     All rights reserved.
 *
 *---------------------------------------------------------------------------
 */

#ifndef BINHEAP_H
#define BINHEAP_H

typedef struct binheap_s binheap_t;


typedef int (*app_cmp_fn_t)(void*, void*);

void binheap_init(binheap_t **bh, app_cmp_fn_t cmp);
void binheap_insert(binheap_t *binheap, void *e);
void *binheap_peek_min(binheap_t *bh);
void *binheap_extract_min(binheap_t *bh);

void binheap_set_allocator();
void binheap_set_deallocator(void *);

#endif /* BINHEAP_H */
