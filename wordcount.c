/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 25.02.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/
#include "htab.h"
#include "io.h"
#include <stdio.h>

#define MAX_WORD 255

// !! CHANGE THIS TO YOUR FUNCTION !!
void print_item(htab_pair_t *pair)
{
    printf("%s\t%d\n", pair->key, pair->value);
}

int main()
{
    htab_t *m = htab_init(10);
    char word[MAX_WORD];
    int characters_read = 0;
    bool error_not_printed = true;
    while ((characters_read = read_word(word, MAX_WORD+1, stdin)) != EOF)
    {
        if (characters_read > MAX_WORD && error_not_printed)
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
    
    //htab_statistics(m);
   
    htab_for_each(m, &print_item);

    htab_free(m);
}
