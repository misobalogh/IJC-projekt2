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
 * Clears all records from the hash table.
 *
 * @param t Pointer to hash table that will be cleared.
 *
 * @returns None
 */
void htab_clear(htab_t *t)
{
    // Iterates through all the items in the table.
    for (size_t i = 0; i < t->arr_size; i++)
    {
        // Iterates through all the records of the item.
        for (htab_item_t *item = t->arr_ptr[i]; item != NULL;)
        {
            htab_item_t *next = item->next;
            htab_erase(t, item->pair.key);
            item = next;
        }
    }
}
