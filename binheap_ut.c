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
#include "binheap.h"


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
    binheap_t  *bh;
    binheap_init(&bh, int_cmp);

    size_t inputa[100];
    int i;
    for (i = 0; i < (argc - 1); i++) {
        printf("%s\n", argv[i+1]);
        inputa[i] = atol(argv[i+1]);
        binheap_insert(bh, &inputa[i]);
    }

    size_t *min = binheap_min(bh); 
    printf("Minimum element is %d\n", *min);
}
