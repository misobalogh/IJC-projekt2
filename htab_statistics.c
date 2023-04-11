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
#include <stdio.h>


/**
 * Calculate and print list length statistics (min,max,avg) to stderr
 * 
 * @param t A pointer to the hash table.
 *
 * @returns None
 */
void htab_statistics(const htab_t * t)
{ 
    size_t size_of_htable = htab_bucket_count(t);
    int min = htab_size(t);
    int max = 0;
    size_t sum = 0;

    for (size_t i = 0; i < size_of_htable; i++) 
    {
        // Go through the list and find the min and max values
        for (htab_item_t *item = t->arr_ptr[i]; item != NULL; item = item->next) 
        {
            if (item->pair.value < min)
            {
                min = item->pair.value; 
            }
            if (item->pair.value > max)
            {
                max = item->pair.value;
            }
            sum += item->pair.value; 
        }
    }

    double avg = (double)sum / htab_bucket_count(t); // Typecast to double to get the correct average

    fprintf(stderr, "Minimum length: %d\n", min);
    fprintf(stderr, "Maximum length: %d\n", max);
    fprintf(stderr, "Average length: %.4f\n", avg);
}
