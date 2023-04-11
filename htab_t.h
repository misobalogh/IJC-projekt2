/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b) datova struktura htab_t
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 28.03.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#ifndef HTAB_T_H__
#define HTAB_T_H__

#include "htab.h"
#include "htab_item.h"

/**
 * Hash table data structure.
 *
 * @param size Current number of records [(key,data),next].
 * @param arr_size The pointer array size (number of items).
 * @param arr_ptr A pointer to a dynamically allocated array of pointers.
 */
struct htab
{
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

#endif /* HTAB_T_H__ */

//====================== End of file htab_t.h ===============================//