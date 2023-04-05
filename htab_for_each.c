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
#include "htab_item.h"

/**
 * Applies function pointed to by 'f' to each element in a hash table.
 *
 * @param t A pointer to the hash table.
 * @param f A pointer to the function that will be applied on each element.
 *
 * @returns None
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    if (f == NULL) {
        return;
    }
    // Iterate through the array.
    for (size_t i = 0; i < t->arr_size; i++) 
    {
        // Iterate through the records in the list.
        for (htab_item_t *item = t->arr_ptr[i]; item != NULL; item = item->next) 
        {
            // Applies function 'f' on the item.
            f(&item->pair);
        }
    }
}