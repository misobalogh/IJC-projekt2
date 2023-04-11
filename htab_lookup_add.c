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
#include <stdio.h>

/**
 * Looks up 'key' in the hash table 't' and if it does not exist,
 * creates new record and adds it to the table.
 *
 * @param t Pointer to hash table where to look up.
 * @param key The key to look up or add to the hash table.
 *
 * @returns A pointer to the htab_pair_t struct containing pair key-value.
 *          If the key already exists, function returns
 *          a pointer to the existing pair. If the key is not found and does not exist,
 *          the function adds the pair to the table
 *          and returns a pointer to the newly added pair.
 *          Returns NULL if memory allocation error occured.
 */
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    // First, check if the key already exists.
    htab_pair_t *pair = htab_find(t, key);
    if (pair != NULL)
    {
        pair->value++;
        return pair;
    }

    // Key not found, create new item.
    htab_item_t *new_item = malloc(sizeof(htab_item_t));
    if (new_item == NULL)
    {
        return NULL;
    }
    
    // Get hash of the key.
    size_t index = (htab_hash_function(key) % t->arr_size);

    // Assign the pointer to next item to the newly created item.
    new_item->next = t->arr_ptr[index];
    // Add newly created item to the list.
    t->arr_ptr[index] = new_item;

    new_item->pair.key = malloc(sizeof(*new_item->pair.key) * (strlen(key) + 1));
    if (new_item->pair.key == NULL)
    {
        free(new_item);
        return NULL;
    }
    // Copy the key to the new item, copies only up to length of the key + 1 for null terminator.
    memcpy((void *)new_item->pair.key, (void *)key, strlen(key) + 1);

    new_item->pair.value = 1;
    t->size++; // Update the number of records.

    // Return the pointer to the newly created record.
    return &new_item->pair;
}
