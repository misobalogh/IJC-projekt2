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


void print_item(htab_pair_t *pair)
{
    printf("%s\t%d\n", pair->key, pair->value);
}


int main()
{
    htab_t *m = htab_init(10);
    char word[MAX_WORD];
    while (read_word(word, MAX_WORD, stdin) != EOF)
    {
        htab_lookup_add(m, word)->value++;
    }
    
    htab_for_each(m, print_item);

    htab_free(m);
}
