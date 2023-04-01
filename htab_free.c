/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include "htab.h"
#include "htab_t.h"    // struct htab_t

/**
 * Destructor of the table.
 *
 * @param t A pointer to the hash table to be freed.
 *
 * @returns None
 */
void htab_free(htab_t *t)
{
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}