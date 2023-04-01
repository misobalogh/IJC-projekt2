/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

// TODO if return value == NULL, exit program

#include "htab.h"
#include <stdio.h>     // Error message
#include "htab_item.h" // struct htab_item_t
#include "htab_t.h"    // struct htab_t

/**
 * Constructor: create and initialize the table.
 *
 * @param n Number of array elements (.arr_size).
 *
 * @returns A pointer to the newly created hash table.
 *          Returns NULL if memory allocation error occured.
 */
htab_t *htab_init(const size_t n)
{
    htab_t *new = malloc(sizeof(htab_t));
    if (new == NULL)
    {
        fprintf(stderr, "Memmory allocation error\n");
        return NULL;
    }

    new->arr_ptr = calloc(n, sizeof(htab_item_t));
    if (new->arr_ptr == NULL)
    {
        fprintf(stderr, "Memmory allocation error\n");
        return NULL;
    }

    new->arr_size = n;
    new->size = 0;

    return new;
}