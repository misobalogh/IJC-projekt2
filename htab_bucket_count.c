/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include "htab.h"
#include "htab_t.h"    

/**
 * Returns the number of elements in the pointer array.
 *
 * @param t A pointer to the hash table.
 *
 * @returns The number of elements in the pointer array.
 */
size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}
