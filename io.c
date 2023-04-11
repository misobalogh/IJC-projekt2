/***************************************************************
* File Name: htab.h
* Description: riesnie IJC-DU2, priklad b) Funkcia pouzita na ziskanie slov zo vstupu vo wordcount.c
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 04.04.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include "io.h"
#include <ctype.h>

int read_word(char *s, int max, FILE *f){
    char c;
    int len = 0;
    // Removes all whitespaces from beginning of the word.
    while ((c = fgetc(f)) != EOF && isspace(c));

    // Read word up to length of max-1.
    while (c != EOF && !isspace(c) && len < max-1){
        s[len++] = c;
        c = fgetc(f);
    }

    // Skip the rest of the word.
    while (c != EOF && !isspace(c)){
        c = fgetc(f);
    }

    // Add null terminatorl to the end of the word.
    s[len] = '\0';
    
    if (c == EOF && len == 0)
        return EOF;
    else
        return len;
}

//====================== End of file io.c ===============================//