/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#ifndef HTAB_ITEM_H__
#define HTAB_ITEM_H__

#include "htab.h"

// !  Tento záznam je definován v privátním hlavičkovém souboru pro všechny
// !  moduly tabulky a není dostupný při použití knihovny ("Opaque data type").
// !  Uživatel používá ukazatel na vnořenou strukturu htab_pair_t. 

/**
 * A struct representing an item in a hash table.
 *
 * @param next Pointer to the next item
 * @param pair public structure with items:
 *            - key - pointer to a dynamically allocated string
 *            - value - associated data = number of occurrences
 */
typedef struct htab_item htab_item_t;

struct htab_item
{
    struct htab_item *next;
    htab_pair_t pair;
};


#endif /* HTAB_ITEM_H__ */