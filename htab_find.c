/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include "htab.h"
#include "htab_item.h" // struct htab_item_t
#include "htab_t.h"    // struct htab_t

/**
 * Searches table 't' for an entry corresponding to the string 'key':
 *      - if the key is found, it returns a pointer to the record
 *      - returns NULL if not found
 *
 * @param t A pointer to the hash table to search in.
 * @param key The key to search for.
 *
 * @returns A pointer to the htab_pair_t struct containing the key-value pair if found, otherwise NULL.
 */
htab_pair_t *htab_find(const htab_t *t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);

    htab_item_t *item = t->arr_ptr[hash];
    while (item != NULL)
    {
        if (strcmp(item->pair.key, key) == 0)
        {
            return &item->pair;
        }
        item = item->next;
    }
    // Key not found.
    return NULL;
}
