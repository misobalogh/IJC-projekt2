/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), vytvorenie hashovacej tabulky a vypis slov zo vstupu s ich poctom vyskytov
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 04.04.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/
#include "htab.h"
#include "io.h"
#include <stdio.h>

// Implementation limit of maximum word length
#define MAX_WORD 255

/**
 * Prints the key and value of the hash table item to stdout.
 * 
 * @param pair A pointer to the hash table item.
 *
 * @returns None
 */
void print_item(htab_pair_t *pair)
{
    printf("%s\t%d\n", pair->key, pair->value);
}

/**
 * Main function
 * 
 * @returns 0 on success, 1 on error
 */
int main()
{
    // Initialize the hash table
    htab_t *m = htab_init(10);

    // Read the words from stdin using function 'read_word' from io.h
    char word[MAX_WORD];
    int characters_read = 0;
    bool error_not_printed = true; 
    while ((characters_read = read_word(word, MAX_WORD+1, stdin)) != EOF)
    {
        if (characters_read > MAX_WORD && error_not_printed) // Print the warning message only once
        {
            fprintf(stderr, "Warning: The word exceeds the maximum length limit and has been truncated.\n");
            error_not_printed = false;
        } 

        if(htab_lookup_add(m, word) == NULL)
        {
            fprintf(stderr, "Error: memory allocation error.\n");
            htab_free(m);
            return 1;
        }
    }

    #ifdef STATISTICS
    htab_statistics(m);
    #endif // STATISTICS
    
    // Print the hash table
    htab_for_each(m, &print_item);

    // Free the memory
    htab_free(m);
}

//=============================== End of wordcount.c =================================//