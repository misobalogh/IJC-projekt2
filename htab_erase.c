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
 * Removes item from the hash table.
 *
 * @param t A pointer to the hash table.
 * @param key The key of the item that will be removed.
 *
 * @returns True if the item was successfully removed, false if not.
 */
bool htab_erase(htab_t *t, htab_key_t key)
{
    // Get the hash value of the key.
    size_t index = htab_hash_function(key) % t->arr_size;

    htab_item_t *prev = NULL;
    htab_item_t *item = t->arr_ptr[index];

    while (item != NULL)
    {
        // Key found.
        if (strcmp(item->pair.key, key) == 0)
        {

            if (prev == NULL) // First item in the list.
            {
                // Moves the pointer from the first item to the next item -> deletes the first item.
                t->arr_ptr[index] = item->next;
            }
            else // Any other item in the list.
            {
                // Moves the pointer from previous item to the next item -> deletes the current item.
                prev->next = item->next;
            }
            free(item->pair.key);
            free(item);
            t->size--; // Updates the size of records in the table.
            return true;
        }
        prev = item;       // Saves the current item as the previous item.
        item = item->next; // Itterates to the next item.
    }
    return false;
}